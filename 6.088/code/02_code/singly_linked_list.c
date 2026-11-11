#include <stdlib.h>
#include <stdio.h>
#include "singly_linked_list.h"

/* Returns a new node with the given value. */
node_t* make_node(int val) {
  node_t* new_node = malloc(sizeof(node_t));
  new_node->val = val;
  new_node->next = NULL;
  return new_node;
}

/* Insert at the head of a linked list. */
node_t* insert_val(int val, node_t* cur_head) {
  node_t* new_node = make_node(val);
  new_node->next = cur_head;
  return new_node;
}

/* Deletes the first occurence of value val from the list. */
node_t* delete_val(int val, node_t* cur_head, int* succeeded) {
  *succeeded = 0;

  /* Special case: if first guy is the one we want to remove. */
  if (cur_head == NULL) {
    return NULL;
  } else if (cur_head->val == val) {
    node_t* new_head = cur_head->next;
    free(cur_head);
    *succeeded = 1;
    return new_head;
  } else {
    node_t* prev = cur_head;
    node_t* cur = cur_head->next;
    while (cur != NULL) {
      if (cur->val == val) {
        prev->next = cur->next;
        free(cur);
        *succeeded = 1;
        return cur_head;
      } else {
        cur = cur->next;
      }
    }
  }
  return cur_head;
}

/* Frees the memory associated with a linked list. */
void delete_list(node_t* head) {
  node_t* cur = head;
  node_t* next;
  
  while (cur != NULL) {
    /* Store our next one. */
    next = cur->next;

    /* Free the current guy. */
    free(cur);

    /* Move on. */
    cur = next;
  }
}

/* Prints a linked list. */
void print_sll(node_t* head) {
  node_t* cur = head;
  while (cur != NULL) {
    printf ("%d ", cur->val);
    cur = cur->next;
  }
  printf("\n");
  return;
}
