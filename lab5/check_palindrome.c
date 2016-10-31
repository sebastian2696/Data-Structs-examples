#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#define MAX_SIZE (1024)

int Array[MAX_SIZE];

typedef struct Stack {
	int A[MAX_SIZE];
	int top;
} Stack;

void stack_initialize(struct Stack *st)
{
	st->top = -1;
}

typedef struct Queue {
	int A[MAX_SIZE];
	int head;
	int tail;
} Queue;

void queue_initialize(struct Queue *st)
{
	st->tail = -1;
	st->head = 0;
}

typedef struct list_node {
	int value;
	struct list_node *next;
}list_node;

/* Push an item onto the array.
 * Return 0 if success and -1 if failure.
 */
int array_insert(int index, int data) 
{
	if (index > MAX_SIZE-1 || index <0) {
		return -1;
	}
	Array[index] = data;
	return 0;
}

/* Push an item onto the stack.
 * Return 0 if success and -1 if failure.
 */
int stack_push(struct Stack *s, int t)
{
	if (s->top == (MAX_SIZE - 1))
		return -1;

	s->A[++s->top] = t;
	return 0;
}

/* Pop an item from the top the stack.
 * Return 0 if success and -1 if failure.
 */
int stack_pop(struct Stack *s, int *t)
{
	if (s->top >= 0) {
		*t = s->A[s->top--];
		return 0;
	}

	return -1;
}

/* Push an item onto the queue.
 * Return 0 if success and -1 if failure.
 */
int queue_push(struct Queue *s, int t)
{
	if (s->tail == (MAX_SIZE - 1))
		return -1;

	s->A[++s->tail] = t;
	return 0;
}

/* Pop an item from the head the queue.
 * Return 0 if success and -1 if failure.
 */
int queue_pop(struct Queue *s, int *t)
{
        int i;
	if (s->head >= 0) {
		*t = s->A[s->head];
		for (i=0; i<s->tail; i++) {
			s->A[i] = s->A[i+1];
		}
		s->tail = s->tail-1;
		return 0;
	}

	return -1;
}

/* Insert a piece of data into the singly-linked list with
* the given head. Always insert the data before the current head.
*/

int list_insert(struct list_node **head, int data)
{
	struct list_node *node = calloc(1, sizeof(struct list_node));
	if (node == NULL) {
		return -1;
	}

	node->value = data;

	node->next = *head;
	*head = node;
	
	return 0;
}

void list_destroy(struct list_node *head)
{
	/* Iterate through the list and safely dellocate every node. */

	struct list_node *node = head;
	while (node) {
		struct list_node *next = node->next;
		free(node);
		node = next;
	}
}

void list_print(struct list_node *head)
{
	/* Iterate through the list and print each value per line. */
	struct list_node *node = head;
	while (node) {
		printf("%d\n", node->value);
		node=node->next;
	}
}

bool checkPalByArray(FILE *fp_data, int count) {
    char buf[256];

	int i=0;
	while (fgets(buf, sizeof(buf), fp_data) !=NULL)
    {
    	Array[i] = buf[0];
    	i++;
    }
    for (i = 0; i< count/2; i++)
    {
    	if(Array[i] != Array[(count-i-1)] ) return false;

    }
	
    return true;

}

bool checkPalByQueueAndStack(FILE *fp_data, int count) {
	char buf[256];
	int p,q;
	Queue queue;
	queue_initialize(&queue);
	Stack stack;
	stack_initialize(&stack);
	while (fgets(buf, sizeof(buf), fp_data) !=NULL)
    {
        stack_push(&stack,buf[0]);
        queue_push(&queue,buf[0]);
    }
    while (stack_pop(&stack, &p) == 0 && queue_pop(&queue, &q) == 0)
    {
	 	if(p != q ) return false;

    }
	return true;
	
}

bool checkPalByStack(FILE *fp_data, int count) {
	
	char buf[256];
	int p;
	int i=0;
	Stack stack;
	stack_initialize(&stack);
	while (fgets(buf, sizeof(buf), fp_data) !=NULL)
    {
    	Array[i] = buf[0];
        i++;
        stack_push(&stack,buf[0]);
    }
    i=0;
    while (stack_pop(&stack, &p) >= 0 )
    {
    	if(p != Array[i] ) return false;
		i++;
    }
    return true;

}
	
bool checkPalByList(FILE *fp_data) {
	char buf[256];
	list_node *head = NULL;
	int i=0;
	while (fgets(buf, sizeof(buf), fp_data) !=NULL){
//		printf("list:%d\t",buf[0]);
    	list_insert(&head,buf[0]);
    	Array[i] = buf[0];
//    	printf("array:%d\n",Array[i]);
    	i++;
	}
//	list_print(head);
	i=0;
	list_node *node = head;

	while(node){
		if(node -> value != Array[i]) return false;
		i++;
		node = node->next;
		
	}
	return true;
}

int countDigits(FILE *fp_data) {
	char ch;
	int lines = 0;
	while(!feof(fp_data))
	{
		ch = fgetc(fp_data);
		if(ch == '\n')
		{
			lines++;
		}
	}
	return lines;
}

int main(int argc, char *argv[])
{
	if (argc != 2) {
		fprintf(stderr, "Usage: ./<executable file> inputDataFile\n");
		return 1;
	}
	
	FILE *fp_data = fopen(argv[1], "rb");
	if (fp_data == NULL) {
		fprintf(stderr, "Error opening %s\n", argv[1]);
		return 1;
	}
	
	
	int count = countDigits(fp_data);
	rewind(fp_data);
	printf("Is palindrome? checked by array %s\n", checkPalByArray(fp_data, count)? "true":"false");
	rewind(fp_data);
	printf("Is palindrome? checked by stack %s\n", checkPalByStack(fp_data, count)? "true":"false");
	rewind(fp_data);
	printf("Is palindrome? checked by queue %s\n", checkPalByQueueAndStack(fp_data, count)? "true":"false");
	rewind(fp_data);
	printf("Is palindrome? checked by linkedlist %s\n", checkPalByList(fp_data)? "true":"false");
	
	fclose(fp_data);
	return 0;
}
