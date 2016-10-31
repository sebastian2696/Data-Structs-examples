#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Quick and dirty clone of dc */


#include <math.h>
typedef double dc_data_t;

int parse_number(const char *tok, double *p_d)
{
	char *endptr;
	double d = strtod(tok, &endptr);
	if (*endptr == '\0') {
		*p_d = d;
		return 0;
	}

	return -1;
}

/* Define struct dc_queue with its members with enough space for at
 * least 1024 elements.
 */
 #define STACK_MAX 1024

struct dc_queue {
/* Fill in structure members here. */
	int capacity;
    int size;
    int rear;
	double *elements;
};

/* Initialize the queue to empty. */
void queue_initialize(struct dc_queue *st)
{
	/* Fill in code here. */
		st->elements = malloc(sizeof(double)*STACK_MAX);
	if (!st->elements)
	{
		printf("can't malloc #2, ERROR\n");
		exit(-1);
	}
	
	st->rear = 0;
    st->size = 0;
    st->capacity = STACK_MAX;
}

/* Return the number of items on the queue. */
int queue_count(const struct dc_queue *st)
{
	/* Fill in working code here.
	 * The return 2 is bogus.
	 */
	 return (st->rear - st->size);
}

/* Push an item onto the queue.
 * Return 0 if success and -1 if failure.
 */
int push(struct dc_queue *s, dc_data_t t)
{
//	printf("element.push: %f\n",t);
	int i = s->rear - s->size;
	/* Fill in code here. */
	 if(i == s->capacity)
        {
                printf("Stack is Full\n");
                return -1;
        }
        else
        {
  //      		printf("tadpissed");
                /* Push an element on the top of it and increase its size by one*/ 
                s->elements[s->rear] = t;
    //            printf("Pushed:%f\n",s->elements[s->rear]);
                s->rear++;
                return 0;
        }
}

/* Pop an item from the head the queue.
 * Return 0 if success and -1 if failure.
 */
int pop(struct dc_queue *s, dc_data_t *t)
{
	/* Fill in code here. */
//	printf("Element.pop:%f\n",s->elements[s->size]);
	int i = s->rear - s->size;	
	if(i==0)
        {
                printf("Stack is Empty\n");
                return -1;
        }
        /* Removing an element is equivalent to reducing its size by one */
        else
        {		
        		
  //      		printf("Pop:%f\n",s->elements[s->size]);
            	*t = s->elements[s->size];
//            	s->rear--;
                s->size++;
            	return 0;
        }
}

/* parse_op() tells the caller whether the string tok is a valid
 * operator, and puts the single character operator into op.
 * Return 0 if it is and -1 if it is not.
 */ 
int parse_op(const char *tok, char *op)
{
	int rc = -1;

	if (tok == NULL)
		return -1;

	/* Make sure the token length is exactly 1. */
	if (strlen(tok) != 1)
		return -1;

	/* Fill in the rest of the code below. 
	 * Better still, use a switch statement.
	 */
	/*if (tok[0] == 'p' || tok[0] == '+') {
		*op = tok[0];
		return 0;*/
		switch (*tok) {
		case 'p': *op = tok[0];return 0;
		case 'f': *op = tok[0];return 0;
		case 'c': *op = tok[0];return 0;
		case '+': *op = tok[0];return 0;
		case '-': *op = tok[0];return 0;
		case '*': *op = tok[0];return 0;
		case '/': *op = tok[0];return 0;
		case '%': *op = tok[0];return 0;
		case '^': *op = tok[0];return 0;
	}
	

	return -1;
}

/* Execute a single character operator.
 */
int apply_op(struct dc_queue *s, const char op)
{
	dc_data_t A, B, C;

	switch (op) {
	case 'p':
		/* Print the value of the head element (but leave it on
		 * the head of the queue.
		 */
		if (pop(s, &A) < 0) {
			printf("dc: queue empty\n");
			return -1;
		}
		else {
			printf("%f\n", A);
			push(s, A);
			return 0;
		}
	case 'f':
	{
		/* Print the value of every element on the queue (but
		 * leave them all in the queue).
		 */
		/* Fill in code here. */
		int i = s->size;
		while ( i != s->rear){
			printf("%f\n",s->elements[i]);
			i++;
		}
		return 0;
	}

	case 'c':
		/* Clear the queue by removing every element. */
		free(s->elements);
		queue_initialize(s);
		return 0;
	} /* end switch */

	/* Apply two-operand operators from this point down. */

	/* First check if there are fewer than 2 elements on the
	 * queue. 
	 */
	if (queue_count(s) < 2) {
		printf("dc: queue empty\n");
		return -1;
	}

	/* Remove the operands, perform the computation indicated by
	 * op, and push the result.
	 */



	switch (op) {
		case '+':{
		pop(s,&A);
		pop(s,&B);
		C = A + B;

		push(s,C);
		return 0;
					
	}
	case '-':{ 
		pop(s,&A);
		B = A;
		pop(s,&A);
		A = A - B;
		push(s,A);
		return 0;
		
	}
	case '*':{
		pop(s,&A);
		B = A;
		pop(s,&A);
		A = A * B;
		push(s,A);
		return 0;
		
	}	
	case '/':{
		pop(s,&A);
		B = A;
		pop(s,&A);
		A = A / B;
		push(s,A);
		return 0;
		
	}	
	case '%':{
		pop(s,&A);
		B = A;
		pop(s,&A);
		A = fmod (A,B);
		push(s,A);
		return 0;
	}
	case '^':{
		pop(s,&A);
		B = A;
		pop(s,&A);
		A = pow(A, B);
		push(s,A);
		return 0;
		
	}
	} /* end switch */

	return push(s, C);
}


int dcc(FILE *fp)
{
	char buf[256], *tok;
	char op;
	dc_data_t dd;

	struct dc_queue queue;

	queue_initialize(&queue);

	for (;;) {
		/* Read a line from the input file into buf. */
		if (fgets(buf, sizeof(buf), fp) == NULL)
			break;

		/* Get all the whitespace-delmited tokens from buf. */
		tok = strtok(buf, " \t\n");
		while (tok != NULL) {
			/* This printf may be uncommented for
			 * additional debug output. 
			 */
			//printf("token %s\n", tok);

			if (parse_op(tok, &op) == 0) {
				/* This printf may be uncommented for
				 * additional debug output. 
				 */
	//			printf("parsed op %c\n", op);
				apply_op(&queue, op);
			}
			else if (parse_number(tok, &dd) == 0) {
				push(&queue, dd);
			}

			tok = strtok(NULL, " \t\n");
		}
	}

	if (feof(fp))
		return 0;

	return -1;
}


int main(int argc, char *argv[])
{
	int rc;
	FILE *fp;

	if (argc < 2) {
		fp = stdin;
	}
	else {
		fp = fopen(argv[1], "rb");

		if (!fp) {
			perror("fopen");
			return 1;
		}
	}

	rc = dcc(fp);

	fclose(fp);

	if (rc < 0)
		return 1;

	return 0;
}