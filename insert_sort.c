#include <stdlib.h>
#include <stdio.h>
#include "vec.c"
void insert_sort(vector* a){    //insertion sort, O(n^2)
    for(int i = 1; i < a -> size; ++i){
        for(int j = i-1; j >= 0 && (a -> at(a,j) > a -> at(a,j+1)); --j){
            int tmp = a -> at(a,j);
            a -> put(a,j, a -> at(a,j+1));
            a -> put(a,j+1,tmp);
        }
    }
} 