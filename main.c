#include "stack.c"
#include "vec.c"
#include "merge_sort.c"
#include "insert_sort.c"


int main(int argc, char* argv[]){
	vector* v = newvector(10);
	v -> push_back(v,1);
	printf("========= SUCCES =========\n");
	return 0;
}