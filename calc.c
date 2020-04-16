#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "calc.h"
#include "stack.h"

double compute_rpn(char* rpn){
    char *tok;
    tok = strtok(rpn, " ");
    struct stack* stack = create_stack();
    while (tok != NULL) //while not pointing to NULL
    {
        if (unary_op(*tok))
        { //pop one out
            double result;
            double op1 = pop(stack);
            switch (*tok)
            {
                case 's': result = sin(op1); break;
                case 'c': result = cos(op1); break;
                case 't': result = tan(op1); break;
                case 'e': result = exp(op1); break;
                case 'i': result = 1/op1; break;
                case 'm': result = -op1; break;
                case 'r': result = sqrt(op1); break;

            }
            push(stack, result);
        }
        else if (binary_op(*tok))
        { //pop two out
            double result;
            double op1 = pop(stack);
            double op2 = pop(stack);
            double temp;
            switch (*tok){
                case '+': result = op1 + op2; push(stack, result); break;
                case '-': result = op2 - op1; push(stack, result); break;
                case '*': result = op1 * op2; push(stack, result); break;
                case '/': result = op2 /op1; push(stack, result); break;
                case '^': result = pow(op2, op1); push(stack, result); break;
                case 'f':
                    push(stack, op1);
                    push(stack, op2);
                    break;

            }
        }
        else
        { //numbers (?)
            double character = atof(tok); //convert string to double
            push(stack, character);
        }
        tok = strtok(NULL, " "); //change the pointer
    }
    double finally = stack -> top ->value;
    delete_stack(stack);
    return finally;
}


char* get_expressions(char* filename){

    FILE *file;
    file = fopen(filename, "r");

    char line [258];

    char *str = (char*) malloc(258*sizeof(char)); // store here

    *str = '\0';

    while (fgets(line, 258, file)!= NULL){
        str = strcat(str,line);

    }

    fclose(file);

    return str;
}

void process_expressions(char* expressions, char* filename){
    FILE *output = fopen(filename, "w");

    char* string = expressions; //pointer to string

    char *tok = strtok_r(expressions,"\n", &string);

    int i = 0;
    while (tok){

        double answer = compute_rpn(tok);

        fprintf(output,"%f\n", answer);
        tok = strtok_r(NULL, "\n", &string);
    }
    fclose(output);
}
