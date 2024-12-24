#include <stdlib.h>
#include <stdio.h>
#include "insert_sort.c"

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