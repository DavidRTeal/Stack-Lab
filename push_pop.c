#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "push_pop.h"

// The valid commands:
//   status
//   push %reg
//   push $val
//   pop %reg

int is_verbose = 0;
FILE *ofile = NULL;

static unsigned long stack_bot = DEF_STACK_BOT; // the high address for the stack
static unsigned long stack_limit = DEF_STACK_LIMIT; // the low address for the stack
static unsigned long rsp = DEF_RSP; // the initial value for the rsp register
static unsigned long *stack = NULL; // points to the bytes for the stack
static unsigned long registers[REG_RDX + 1] = { // the general purpose registers
    // These are just some default values.
    REG_RAX + 20
    , REG_RBX + 30
    , REG_RCX + 40
    , REG_RDX + 50
};

static void pop(char *);
static void push_reg(char *);
static void push_value(char *);
static void
pop(char *reg)
{
     int num = reg[2] - 'a';
     registers[num] = stack[(stack_bot - rsp)/REG_SIZE];
     rsp += REG_SIZE;
}
    
static void
push_reg(char *reg)
{
    int num = reg[2] - 'a';
    rsp -= REG_SIZE;
    stack[(stack_bot - rsp)/REG_SIZE] = registers[num];
}


static void
push_value(char *reg)
{
    unsigned long val = 0;
    sscanf(reg, "%lx", &val);
    rsp -= REG_SIZE;
    stack[(stack_bot - rsp)/REG_SIZE] = val;
}


    char * token = NULL;
    char line[BUFFER_SIZE] = {'\0'};


int
main(int argc, char *argv[])
{
    FILE *ifile = stdin;

    ofile = stdout;
    {
        int opt = 0;
        //int res_count = 0;

        // Do not begin processing input until AFTER you have completely
        // processed the command line using getopt() .

        while ((opt = getopt(argc, argv, GETOPT_STRING)) != -1) {
            switch (opt) {
		case 'i':
		    ifile = fopen(optarg, "r");
		    //printf("ifile thingy has been called\n");
		    if(!ifile)
		    {
		        fprintf(stderr, "Error: couldn't open input file: %s\n", optarg);
		        exit(EXIT_FAILURE);
		    }
		    break;

		case 'o':
		    ofile = fopen(optarg, "w");
		    //printf("ofile thingy has been called\n");
		    if(!ofile)
		    { 
		        fprintf(stderr, "Error: couldn't open output file: %s\n", optarg);
			exit(EXIT_FAILURE);
		    }
		    break;

		case 'b':
		    sscanf(optarg, "%lx", &stack_bot);
		    //printf("stack bot thingy has been called\n");
		    if(stack_bot % 8 != 0)		  
		    {					  
		        fprintf(stderr, "Error: stack_bottom address must be a multiple of 8.\n");
			exit(EXIT_FAILURE);
		    }
		    break;

	        case 'l':
		    sscanf(optarg, "%lx", &stack_limit);
		    //printf("stack limit thingy has been called\n"); 
		    if(stack_limit % 8 != 0)	
		    {					  
		        fprintf(stderr, "Error: stack_limit address must be a multiple of 8.\n");
			exit(EXIT_FAILURE);
		    }
		    break;

	        case 's':
		    sscanf(optarg, "%lx", &rsp);
		    //printf("rsp thingy has been called\n"); 
		    if(rsp % 8 != 0)
		    {
		        fprintf(stderr, "Error: rsp address must be a multiple of 8.\n");
			exit(EXIT_FAILURE);
		    }
		    break;

            case 'v':
                is_verbose++;
		//printf("Verbose mode on\n");
                break;

            case 'h':
                printf("%s\n\toptions: %s\n", argv[0], GETOPT_STRING);
                printf("\ti: name of input file\n");
                printf("\to: name of output file\n");
                printf("\tb: stack_bottom (high address, as hex)\n");
                printf("\tl: stack limit (low address, as hex)\n");
                printf("\ts: beginning %%rsp value (within the stack, as hex)\n");
                printf("\tv  verbose output\n");
                printf("\th  help\n");

                exit(EXIT_SUCCESS);
                break;
            default:
                break;
            }
        }
    }
    // Do not begin processing input until AFTER you have completely
    // processed the command line using the getopt() loop.


    stack = calloc(((stack_bot - stack_limit)+1), REG_SIZE);


    if(stack_bot - stack_limit < 8 * sizeof(unsigned long))
    {
        fprintf(stderr, "Error, Stack size is too small");
	exit(EXIT_FAILURE);
    }

    if (!stack) 
    {       
        fprintf(stderr, "Error: could not allocate memory for the stack.\n");
        exit(EXIT_FAILURE);
    }


    while(fgets(line, BUFFER_SIZE, ifile)!= NULL) {
	//line[strlen(line) - 1] = '\0';
        token = strtok(line, WHITESPACE);



	if(strcmp(token, CMD_PUSH)==0) {
	    token = strtok(NULL, WHITESPACE);	     
	    if(token[0] == '$')
	    {
	        push_value(&(token[1]));
	    // push value
	    }
	    else
	    {
	        push_reg(token);
	    // push reg
	    }

	}
	else if (strcmp(token, CMD_POP)==0) {
            token = strtok(NULL, WHITESPACE);
	    pop(token);
	}
	else if (strcmp(token, CMD_STATUS)==0) {

	    stack_status(stack, registers, rsp , stack_bot, stack_limit, ofile);
	}
    }
    free(stack);
    if(ifile)
    {
        fclose(ifile);
	ifile = NULL;
    }
    if(ofile)
    {
	fclose(ofile);
	ofile = NULL;
    }
    token = NULL;
    stack = NULL;
    


    // Do all the validation of upper and lower bounds down here, NOT
    // within the getopt() loop.


    // Have your loop for processing all the input down here.
    
    return EXIT_SUCCESS;
}
