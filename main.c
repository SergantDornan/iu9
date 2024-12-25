#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define CREATE_NODE(val) _allocate_node(val)
#define ABS(x) (((x) < 0) ? -(x) : (x))
#define CMP(a,b) (ABS(a) < ABS(b))

typedef struct _Node {
    int _data;
    struct _Node *_next;
    struct _Node *_previous;
} _Node;

inline _Node* _allocate_node(int value) {
    _Node *new_node = (_Node *)malloc(sizeof(_Node));
    if (new_node == NULL) {
      fprintf(stderr, "Memory allocation failed\n");
      exit(EXIT_FAILURE);
    }
    new_node->_data = value;
    new_node->_next = NULL;
    new_node->_previous = NULL;
    return new_node;
}


void _add_element(_Node **head_ref, int value) {
    _Node *new_node = CREATE_NODE(value);
    _Node *tail_node = *head_ref;

    if (*head_ref == NULL) {
        *head_ref = new_node;
        new_node->_next = new_node;
        new_node->_previous = new_node;
        return;
    }

    while (tail_node->_next != *head_ref) {
        tail_node = tail_node->_next;
    }

    new_node->_next = *head_ref;
    new_node->_previous = tail_node;
    tail_node->_next = new_node;
    (*head_ref)->_previous = new_node;
}

void _display(_Node *head) {
    if (head == NULL) return;
    _Node *curr = head;
    do {
        printf("%d ", curr->_data);
        curr = curr->_next;
    } while (curr != head);
    printf("\n");
}

inline void _exchange_values(_Node *a, _Node *b) {
    int temp = a->_data;
    a->_data = b->_data;
    b->_data = temp;
}

void _sort_elements(_Node *start, _Node *end) {
    if (start == end || start->_next == end) {
        return;
    }

    _Node *base = start;
    _Node *curr = base->_next;
    _Node *last = end->_previous;

    _Node *low_head = NULL;
    _Node *low_tail = NULL;
    _Node *high_head = NULL;
    _Node *high_tail = NULL;

    while (curr != last) {
       if(CMP(curr->_data, base->_data)){
            if (low_head == NULL) {
                low_head = curr;
                low_tail = curr;
            } else {
                low_tail->_next = curr;
                curr->_previous = low_tail;
                low_tail = curr;
            }
        }
         else{
            if (high_head == NULL) {
                high_head = curr;
                high_tail = curr;
            } else {
                high_tail->_next = curr;
                curr->_previous = high_tail;
                high_tail = curr;
            }
        }
         curr = curr->_next;
    }

        if (low_head != NULL) {
          low_tail->_next = base;
            base->_previous = low_tail;
            if (low_head != base) {
              low_head->_previous = NULL;
        }
    }


    if (high_head != NULL) {
      high_head->_previous = base;
        base->_next = high_head;
      if (high_tail != end) {
            high_tail->_next = end;
            end->_previous = high_tail;
        }
    }


     _sort_elements(low_head, low_tail);
    _sort_elements(high_head, high_tail);
}

int main() {
    int num_elements;
    scanf("%d", &num_elements);

    _Node *head_node = NULL;

    for (int i = 0; i < num_elements; i++) {
        int value;
        scanf("%d", &value);
        _add_element(&head_node, value);
    }

    _sort_elements(head_node, head_node->_previous);
    _display(head_node);
    return 0;
}
