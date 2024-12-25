#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
typedef struct Node {
    int data;
    struct Node *next;
    struct Node *prev;
} Node;

Node* newnode(int value) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = value;
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

void insert(Node **head_ref, int value) {
    Node *new_node = newnode(value);
    Node *last = *head_ref;

    if (*head_ref == NULL) {
        *head_ref = new_node;
        new_node->next = new_node;
        new_node->prev = new_node;
        return;
    }

    while (last->next != *head_ref) {
        last = last->next;
    }

    new_node->next = *head_ref;
    new_node->prev = last;
    last->next = new_node;
    (*head_ref)->prev = new_node;
}

void print(Node *head) {
    Node *current = head;
    do {
        printf("%d ", current->data);
        current = current->next;
    } while (current != head);
    printf("\n");
}

void swap(Node *a, Node *b) {
    int temp = a->data;
    a->data = b->data;
    b->data = temp;
}

bool comp(int a, int b) {
    if (abs(a) < abs(b))
        return true;
    else
        return false;
}

void quick_sort(Node *start, Node *end) {
    if (start == end || start->next == end) {
        return;
    }

    Node *pivot = start;
    Node *curr = pivot->next;
    Node *tail = end->prev;

    while (curr != tail) {
        if (comp(curr->data, pivot->data)) {
            swap(start->next, curr);
            start = start->next;
        }
        curr = curr->next;
    }

    swap(pivot, start);

    quick_sort(start, pivot);
    quick_sort(pivot->next, end);
}

int main() {
    Node *head = NULL;
    int num_elements;
    scanf("%d", &num_elements);
    for (int i = 0; i < num_elements; i++) {
        int value;
        scanf("%d", &value);
        insert(&head, value);
    }

    quick_sort(head, head->prev);

    print(head);

    return 0;
}
