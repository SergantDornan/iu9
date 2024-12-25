
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