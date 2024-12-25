#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define _PRE_PROCESS_PATTERN(pat, sz, arr) _build_prefix_table(pat, sz, arr)
#define _SEARCH_TEXT(pat, txt) _perform_pattern_matching(pat, txt)

static void _build_prefix_table(const char* pattern, int pat_len, int* prefix_table);
static void _perform_pattern_matching(const char* pattern, const char* text);

static void _build_prefix_table(const char* pattern, int pat_len, int* prefix_table) {
    int length = 0;
    prefix_table[0] = 0;
    int iterator = 1;

    while (iterator < pat_len) {
        if (pattern[iterator] == pattern[length]) {
            length++;
            prefix_table[iterator] = length;
            iterator++;
        } else {
            if (length != 0) {
                length = prefix_table[length - 1];
            } else {
                prefix_table[iterator] = 0;
                iterator++;
            }
        }
    }
}

static void _perform_pattern_matching(const char* pattern, const char* text) {
    int pat_len = strlen(pattern);
    int text_len = strlen(text);


    int* prefix_table = (int*)malloc(pat_len * sizeof(int));
    _PRE_PROCESS_PATTERN(pattern, pat_len, prefix_table);

    int i = 0;
    int j = 0;
    while (i < text_len) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }


        if (j == pat_len) {
           printf("%d\n", i - j);
             j = prefix_table[j - 1];
        } else if (i < text_len && pattern[j] != text[i]) {
            if (j != 0)
                j = prefix_table[j - 1];
            else
                i = i + 1;
         }
    }
   free(prefix_table);
}

int main(int argc, char* argv[]) {

    char* search_pattern = argv[1];
    char* target_text = argv[2];

    _SEARCH_TEXT(search_pattern, target_text);
   return 0;
}
