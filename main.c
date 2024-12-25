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


typedef struct vec vector;
typedef struct vec{
	size_t size, cap;
	int* arr;
	void (*des)(vector*);
	void (*copy)(vector*,vector*);
	void (*partcopy)(vector*,vector*,size_t,size_t);
	void (*move)(vector*,vector*);
	void (*push_back)(vector*,int);
	void (*pop)(vector*);
	void (*put)(vector*,int,int);
	int (*at)(vector*,int);
	void (*print)(vector*);
	void (*clear)(vector*);
} vector;
void destroyVec(vector* v){
	free(v -> arr);
	free(v);
}
void copyVec(vector* self, vector* v){
	if(self -> cap < (v -> size)){
		self -> cap = (v -> size)*2;
		self -> arr = (int*) realloc(self -> arr, sizeof(int)*(self -> cap));
	}
	self -> size = v -> size;
	for(int i = 0; i < self -> size; ++i)
		self -> arr[i] = (v -> arr[i]);
}
void copyVectorPart(vector* self, vector* v, size_t start, size_t end){
	end--;
	if(end >= v -> size){
		printf("============== ERROR ==============\n");
		printf("vector: copyVectorPart: end >= v -> size\n");
		return;
	}
	if(self -> cap < (end - start + 1)){
		self -> cap = (end - start + 1)*2;
		self -> arr = (int*) realloc(self -> arr, sizeof(int)*(self -> cap));
	}
	self -> size = end - start + 1;
	self -> clear(self);
	for(int i = start; i <= end; ++i)
		self -> push_back(self,(v -> arr[i]));
}
void moveVec(vector* self, vector* v){
	self -> size = v -> size;
	self -> cap = v -> cap;
	self -> arr = v -> arr;
}
void vectortorPush_back(vector* self, int x){
	if(self -> size < self -> cap)
		self -> arr[self -> size] = x;
	else{
		(self -> cap) *= 2;
		(self -> arr) = (int*) realloc(self -> arr, sizeof(int)*(self -> cap));
		self -> arr[self -> size] = x;
	}
	++(self -> size);
}
void vectorPop(vector* self){
	if(self -> size > 0)
		--(self -> size);
}
int vectorAt(vector* self, int pos){
	if(pos < self -> size)
		return self -> arr[pos];
	else{
		printf("================== ERROR ==================\n");
		printf("vectortor: at: position out of bound\n");
		return 0;
	}
}
void vectorPut(vector* self, int pos, int x){
	if(pos < self -> size)
		self -> arr[pos] = x;
	else{
		printf("================== ERROR ==================\n");
		printf("vectortor: put: position out of bound\n");
	}
}
void printVector(vector* v){
	printf("{");
	for(int i = 0; i < v -> size; ++i)
		printf("%d ", v -> at(v,i));
	printf("}\n");
}
void clearVector(vector* v){
	v -> size = 0;
}
vector* newvector(size_t size){
	vector* v = (vector*)malloc(sizeof(vector));
	v -> size = 0;
	v -> cap = size*2; 
	v -> arr = (int*) malloc(size*2*sizeof(int));
	v -> des = destroyVec;
	v -> copy = copyVec;
	v -> partcopy = copyVectorPart;
	v -> move = moveVec;
	v -> push_back = vectortorPush_back;
	v -> pop = vectorPop;
	v -> at = vectorAt;
	v -> put = vectorPut;
	v -> print = printVector;
	v -> clear = clearVector;
	return v;
}

void insert_sort(vector* a){    //insertion sort, O(n^2)
    for(int i = 1; i < a -> size; ++i){
        for(int j = i-1; j >= 0 && (a -> at(a,j) > a -> at(a,j+1)); --j){
            int tmp = a -> at(a,j);
            a -> put(a,j, a -> at(a,j+1));
            a -> put(a,j+1,tmp);
        }
    }
} 

void merge(vector* v,vector* v1,vector* v2){
	v -> clear(v);
    long unsigned int i = 0, j = 0;
    while(i < v1 -> size && j < v2 -> size){
        if(v1 -> at(v1,i) < v2 -> at(v2,j)){
            v -> push_back(v,v1 -> at(v1,i));
            i++;
        }
        else{
            v -> push_back(v, v2 -> at(v2,j));
            j++;
        }
    }
    if(i < v1 -> size){
        for(long unsigned int k = i; k < v1 -> size;++k)
            v -> push_back(v, v1 -> at(v1,k));
    }
    else if(j < v2 -> size){
        for(long unsigned int k = j; k < v2 -> size;++k)
            v -> push_back(v,v2 -> at(v2,k));
    }
}
void merge_sort(vector* v){   // Merge Sort, O(n * log(n))
    if(v -> size <= 5){
    	insert_sort(v);
    }
    else if(v -> size > 5){
        vector* v1 = newvector((v -> size) / 2);
        vector* v2 = newvector((v -> size) - ((v -> size) / 2));
        v1 -> partcopy(v1,v,0,(v -> size)/2);
        v2 -> partcopy(v2,v,(v -> size)/2,v -> size);
        merge_sort(v1);
        merge_sort(v2);
        merge(v,v1,v2);
        v1 -> des(v1);
        v2 -> des(v2);
    }
}


int main(int argc, char* argv[]){
	vector* v = newvector(10);
	v -> push_back(v,1);
	printf("========= SUCCES =========\n");
	return 0;
}