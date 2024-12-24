#include <stdlib.h>
#include <stdio.h>
typedef struct stk stack;
typedef struct nd node;
typedef struct nd{
	int x;
	node* prev;
} node;
typedef struct stk{
	node* top;
	int (*get)(stack*);
	void (*pop)(stack*);
	void (*push_back)(stack*,int);
	void (*des)(stack*);
} stack;
int stackGet(stack* s){
	node* top = s -> top;
	node* pr = top -> prev;
	s -> top = pr;
	int res = top -> x;
	free(top);
	return res;
}
void stackPop(stack* s){
	node* top = s -> top;
	node* pr = top -> prev;
	s -> top = pr;
	free(top);
}
void stackPush_back(stack* s, int x){
	node* newnode = (node*) malloc(sizeof(node));
	newnode -> prev = s -> top;
	newnode -> x = x;
	s -> top = newnode;
}
void stackDestroy(stack* s){
	while(s -> top != NULL)
		s -> pop(s);
	free(s);
}
stack* newstack(){
	stack* s = (stack*)malloc(sizeof(stack));
	s -> top = NULL;
	s -> get = stackGet;
	s -> pop = stackPop;
	s -> push_back = stackPush_back;
	s -> des = stackDestroy;
	return s;
}