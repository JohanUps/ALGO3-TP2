/*-----------------------------------------------------------------*/
/*
 Licence Informatique - Structures de données
 Mathias Paulin (Mathias.Paulin@irit.fr)
 
 Implantation du TAD Queue étudié en cours.
 
 */
/*-----------------------------------------------------------------*/

/**
 * @file example.c
 * @brief Ce fichier contient des exemples pour Doxygen.
 *
 * Un fichier de démonstration pour expliquer l'utilisation de Doxygen
 * dans la génération de documentation.
 */
#include "queue.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#define BUFFER_GETLINE 100
#define LEN_OP 1
#include "token.h"
/* Full definition of the queue structure */
typedef struct s_internalQueue {
	const void* value;
	struct s_internalQueue* next;
} InternalQueue;

struct s_queue{
	InternalQueue* head;
	InternalQueue* tail;
	unsigned int size;
};

typedef struct s_StringIterator{
	const char * str;
	int curpos;
}StringIterator;

//Fonction qui créer un iterateur initialisé
StringIterator create_StringIterator(const char* str){
	StringIterator itr = {str,0};
	return itr;
}

//Fonction qui revoie true si l'on se trouve à la fin de la chaine
bool is_string_end(StringIterator* itr){
	return itr->str[itr->curpos] == '\0';
}

//Fonction qui renvoie le caractère courant et incrémente l'iterateur (curpos)
char nextChar(StringIterator* itr){
	return itr->str[itr->curpos++];
}


/** LALALALALALLALALALALALA
 *@brief Cette fonction alloue la memeoire du TAD queue
 *@return pointeur queue.
*/
Queue* create_queue(void){
	Queue* q = calloc(1, sizeof(Queue));
	return(q);
}

void delete_queue(ptrQueue *q) {
	InternalQueue* toDelete = (*q)->head;
	while (toDelete) {
		InternalQueue* f = toDelete;
		toDelete = toDelete->next;
		free (f);
	}
	free(*q);
	*q = NULL;
}

Queue* queue_push(Queue* q, const void* v){
	InternalQueue* new = calloc(1, sizeof(InternalQueue));
	new->value = v;
	InternalQueue** insert_at = (q->size ? &(q->tail->next) : &(q->head));
	*insert_at = new;
	q->tail = new;
	++(q->size);
	return (q);
}

Queue* queue_pop(Queue* q){
	assert (!queue_empty(q));
	InternalQueue* old = q->head;
	q->head = q->head->next;
	--(q->size);
	free (old);
	return (q);
}

const void* queue_top(const Queue* q){
	assert (!queue_empty(q));
	return (q->head->value);
}

bool queue_empty(const Queue* q){
	return (queue_size(q) == 0);
}

unsigned int queue_size(const Queue* q) {
	return q->size;
}

void queue_map(const Queue* q, QueueMapOperator f, void* user_param) {
	for (InternalQueue *c = q->head; c ; c = c->next)
		f(c->value, user_param);
}



Queue* stringToTokenQueue(const char* expression){
    Queue * queue = create_queue();
    int nbNumber;
    char* value = NULL;
	ptrToken ptToken;
	//Initialisation d'un iterateur
	StringIterator itr = create_StringIterator(expression);	
	
	//Traitement des symbols
    while(!is_string_end(&itr)){
		char current = nextChar(&itr);
        if(isSymbol(current)){											
			ptToken = create_token_from_string(&current,sizeof(char));
            queue_push(queue,(void*)ptToken);
		}
		
		//Traitement des nombres
        else{															
            if(isNumber(current)){
                nbNumber = 1;
				int posStartNumber = itr.curpos - 1;
				while(isNumber(expression[itr.curpos])){
					nextChar(&itr);
					nbNumber++;
				}
                value = subString(expression, posStartNumber, nbNumber );
				ptToken = create_token_from_string(value,nbNumber);
                queue_push(queue,(void*)ptToken);
			}    
		}
	}
	return queue;
}
        
    
    
    
    
bool isSymbol(char c){
    return (c=='+' || c=='-' || c=='*' || c=='/' || c=='^' || c=='(' || c==')');
}

bool isNumber(char c){
    return (c=='0' || c=='1' || c=='2' || c=='3' || c=='4' || c=='5' || c=='6' || c=='7' || c=='8' || c=='9');
}
    
    
char* subString(const char * inputString, int startPos, int len ){
    char* subString = malloc(sizeof(char)*len);
    strncpy(subString,inputString + startPos*sizeof(char),len);
    return subString;
}    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    







