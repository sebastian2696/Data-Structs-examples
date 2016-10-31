#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define ERROR 0
#define MAX_KEY_LEN (32)
#define MAX_VALUE_LEN (32)

struct list_data {
  char key[MAX_KEY_LEN];
  char value[MAX_VALUE_LEN];
};

typedef struct list_node {
  /* Fill in the structure defintion here. */
  struct list_data data;
  struct list_node *next;
} list_node;

void list_print(struct list_node *head)
{
  /* Iterate through the list and print each every key and value
   * per line.
   */
/*  if (!head) return;
  if(ERROR) printf("streak1\n");
   
  list_node *temp = head;
  
  while (temp)
  {
    if (strlen(temp->data.key)) printf("Key: %s\n",temp -> data.key);
    if (strlen(temp->data.value)) printf("Value: %s\n",temp -> data.value);
    temp = temp -> next;
  }*/
}

struct list_node *list_find_exact(struct list_node *head, const char *key)
{
  /* Search the list for an exact string match, returning a
   * pointer to the node if found and NULL if not found.
   */
   if (!head) return NULL;
 //  if(ERROR)
 // printf("streak2");
   list_node *temp = head;
    while (temp -> next != NULL)
    {
      if(strcmp(key, temp->next->data.key) == 0)
      {
        return temp;
      }
      temp = temp -> next; 
      
    }
   
  return NULL;
}

struct list_node *list_find_before(struct list_node *head, const char *key)
{
  /* Search the list for the insertion point for a key, i.e. the
   * node such that node->key < key.
   */
 
  if (head == NULL) return NULL;
//  if (ERROR) printf("streak4\n");
   
   list_node *temp = head;
    while (temp -> next != NULL)
    {
      if(strcmp(key, temp->next->data.key) > 0)
      {
        if (temp->next->next)
        {
          if (strcmp(key, temp->next->next->data.key) < 0)
          {
            return temp->next;
          }
        }
        else
        {
          return temp->next;
        }
      }
      temp = temp -> next; 
    }
    
  return head;
  

}

int list_insert(struct list_node **head, struct list_node *before, struct list_data data)
{
  /* Insert a piece of data into the singly-lined list with
   * the given head. Insert the new node just after the node
   * pointed to by before.
   */
  
  list_node *return_list = NULL;
  list_node *n = NULL;
  
  // make space in memory for our new node
  if (head == NULL) return -1;
  
  if (!*head)
  {
    return_list = malloc(sizeof(list_node));
    if (!return_list) return -1;
    return_list->next = NULL;
  }
  
  n = malloc(sizeof(list_node));
  if (!n)
	{
//		printf("can't malloc #1, ERROR\n");
		return -1;
	}
	
	n -> data = data;
	
  if (before)
  {
    n -> next = before -> next;
    before -> next = n;
  }
  else
  {
    if (return_list)
    {
      n -> next = return_list->next;
      return_list -> next = n;
      
      *head = return_list;
    }
    else
    {
      n -> next = (*head) -> next;
      (*head) -> next = n;
    }
  }
  
  return 0;
}


void list_destroy(struct list_node *head)
{
  /* Iterate through the list and safely dellocate every node. */
  if (!head) return;
//  if(ERROR)
//  printf("streak5");
  list_node *temp = head;
  while (temp -> next != NULL)
    {
      free(temp->next);
      temp = temp -> next; 
      
    }
}



int main(int argc, char *argv[])
{
  int use_sorted = 0;

  if (argc < 3) {
//    fprintf(stderr, "Usage: dict sort data_file.txt [lookup_commands.txt]\n"
//        "sort: 0 or 1\n");
    return 1;
  }

  use_sorted = strtol(argv[1], NULL, 10);

  FILE *fp_data = fopen(argv[2], "rb");
  if (fp_data == NULL) {
//    fprintf(stderr, "Error opening %s\n", argv[1]);
    return 1;
  }

  FILE *fp_cmd = NULL;
  if (argc > 3) {
    fp_cmd = fopen(argv[3], "rb");
    if (fp_cmd == NULL) {
 //     fprintf(stderr, "Error opening cmd file %s\n", argv[3]);
      return 1;
    }
  }

  struct list_data d;
  struct list_node *head = NULL;

  while (!feof(fp_data) && !ferror(fp_data)) {
    if (fscanf(fp_data, "%s %s", d.key, d.value) != 2)
      continue;

    if (use_sorted) {
 //     printf("Insert %s %s in sorted order\n", d.key, d.value);
//     if(ERROR)
//  printf("streaknan");
      struct list_node *node_before = list_find_before(head, d.key);
//       if(ERROR)
//  printf("streaknan");
      if (list_insert(&head, node_before, d) < 0) {
  //      fprintf(stderr, "Error while inserting into list: %s %s\n", d.key, d.value);
      }
    }
    else {
  //    printf("Insert %s %s in front\n", d.key, d.value);
      if (list_insert(&head, NULL, d) < 0) {
  //      fprintf(stderr, "Error while inserting into list: %s %s\n", d.key, d.value);
      }
    }

//    list_print(head);
  }


  char lookup_key[MAX_KEY_LEN];
  struct list_node *lookup_node;
  int found_count = 0;
  
  while (fp_cmd && !feof(fp_cmd) && !ferror(fp_cmd)) {
    if (fscanf(fp_cmd, "%s", lookup_key) != 1)
      continue;

    if ((lookup_node = list_find_exact(head, lookup_key)) != NULL) {
//      printf("Found: %s %s\n", lookup_node->data.key, lookup_node->data.value);
        found_count++;
    }
    else {
//     printf("Failed to find: %s\n", lookup_key);
    }
  }
  printf("Found count is %d\n", found_count);
  list_destroy(head);

  fclose(fp_data);

  if (fp_cmd) {
    fclose(fp_cmd);
  }

  return 0;
}
