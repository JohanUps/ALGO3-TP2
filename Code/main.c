// Need this to use the getline C function on Linux. Works without this on MacOs. Not tested on Windows.
#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "token.h"
#include "queue.h"
#include "stack.h"



void print_token(const void* e, void* user_param);
void print_queue(FILE* f, Queue* q);

 
/**
 * @brief Cette fonction lit des lignes d'expressions depuis un fichier
 * et les transforme en une file (queue) de tokens, puis les affiche.
 * 
 * @param input Pointeur vers un fichier contenant les expressions.
 */
void computeExpressions(FILE* input) {
	char * line = NULL;
    size_t len = 0;
    ssize_t read;
	while((read = getline(&line,&len,input)) != -1){
		fprintf(stdout,"Input   : %s",line);
		Queue* q = stringToTokenQueue((const char*)line);
		fprintf(stdout,"Infix   : ");
		print_queue(stdout,q);
		printf("\n");
		Queue* shYard = shuntingYard(q);
		fprintf(stdout,"Shunting Yard   : ");
		print_queue(stdout,shYard);
		printf("\n\n");
	}
	
}

/** Main function for testing.
 * The main function expects one parameter that is the file where expressions to translate are
 * to be read.
 *
 * This file must contain a valid expression on each line
 *
 */
int main(int argc, char** argv){
	if (argc<2) {
		fprintf(stderr,"usage : %s filename\n", argv[0]);
		return 1;
	}
	
	FILE* input = fopen(argv[1], "r");

	if ( !input ) {
		perror(argv[1]);
		return 1;
	}

	computeExpressions(input);

	fclose(input);
	return 0;
}
 
void print_token(const void* e, void* user_param) {
	FILE* f = (FILE*)user_param;
	Token* t = (Token*)e;
	token_dump(f, t);
}

void print_queue(FILE* f, Queue* q) {
	fprintf(f, "(%d) --  ", queue_size(q));
	queue_map(q, print_token, f);
}