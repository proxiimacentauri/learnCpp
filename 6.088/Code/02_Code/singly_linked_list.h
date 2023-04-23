/*
 * Define a node structure.
 * 
 * Doing this is the same as doing:
 * struct node {
 *    int val;
 *    struct node* next;
 * };
 * typedef struct node node_t;
 */
typedef struct node {
  int val;
  struct node* next;
} node_t;

/*
 * Creates a new node from a given value, allocating heap memory for it.
 */
node_t* make_node(int val);

/*
 * Inserts a new value into a given linked list, allocating heap memory for
 * it.
 */
node_t* insert_val(int val, node_t* cur_head);

/*
 * Deletes the first value with the given value, deallocating the associated
 * memory.  Sets the "succeeded" flag to 1 if it found and deleted the value, 0
 * otherwise.
 */
node_t* delete_val(int val, node_t* cur_head, int* succeeded);

/*
 * Given a pointer to the head, frees the memory associated with an entire list.
 */
void delete_list(node_t* head);

/* Given a pointer to the head, prints all o fthe values in a list. */
void print_sll(node_t* head);
