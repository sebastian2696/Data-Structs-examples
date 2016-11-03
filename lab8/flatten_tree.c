#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct tree_node {
	int data;
	struct tree_node *left;
	struct tree_node *right;
} tree_node;


void tree_print(struct tree_node *node)
{
	/* Iterate through the tree with an in-order traversal and
	 * print all data value for each node.
	 */
	 if(node!=NULL){
	 	tree_print(node->left);
	 	printf("%d ",node -> data) ;
	 	tree_print(node->right);
	 }
	 return;
}

void list_print(struct tree_node *node)
{   
    /* Iterate through the list starting with node and print
     * all data value for each node.
     */
  if (!node) return;
   
  tree_node *temp = node;
  
  while (temp)
  {
    //if (temp -> data != NULL) 
    printf("%d ",temp -> data);
    temp = temp -> right;
  }	
}



void flatten_tree(struct tree_node *root) 
{
    /*
     * Flatten the tree to a linked list, you can still use
     * 'right' to denote the 'next' node in the list.
     */
    while (root){
        if (root->left){
        	tree_node* temp=root->left;
            while (temp->right) temp = temp->right;
            temp->right = root->right;
            root->right = root->left;
            root->left = NULL;
    }
    root=root->right;
    }
}


struct tree_node *tree_find(struct tree_node *root, int data)
{
	/* Search through the tree for a node with the given key.
	 * Return a pointer to the node if found, and NULL if not
	 * found.
	 */
	 if (root == NULL) return NULL;
	 tree_node *temp = root;
	 if(temp -> data == data){
	 		return temp;
	 	}
	 	else if(temp -> data > data){
	 		return tree_find(temp->left,data);//temp = temp->left;
	 	}
	 	else if(temp -> data < data){
	 		return tree_find(temp->right,data);//temp = temp->right;
	 	}
	 	return NULL;
}

int tree_insert(struct tree_node **p_root, int data)
{
	/* Insert a piece of data into the BST with
	 * the given root.
	 * Return 0 if successful, -1 if it exists already, or if
	 * there is an allocation failure.
	 */
	tree_node *temp = NULL;
	temp = calloc(1, sizeof(tree_node));//malloc(sizeof(tree_node));
	if (!temp)
	{
		printf("can't calloc #1, ERROR\n");
		return -1;
	}
	temp -> data = data;
        temp -> left = temp -> right = NULL;
        if (!*p_root)
	{
		(*p_root) = temp;
        	return 0;
	}
	if(data == (*p_root)->data)
        return 0;	

	if((*p_root)->data > data)

       	{
        	return tree_insert(&((*p_root)->left),data);
       	}
	else
	{
            	return tree_insert(&((*p_root)->right),data);
        
	}
	return -1;
	 
}

void tree_destroy(struct tree_node *root)
{
	/* Traverse the tree from the root and safely dellocate every node. */
	if (root == NULL) return;
	 if(root!=NULL){
	 	tree_destroy(root->left);
	 	free(root);
	 	tree_destroy(root->right);
	 }
}

int main(int argc, char *argv[])
{
	if (argc < 2) {
		fprintf(stderr, "Usage: flatten_tree data_file.txt\n");
		return 1;
	}

	FILE *fp_data = fopen(argv[1], "rb");
	if (fp_data == NULL) {
		fprintf(stderr, "Error opening %s\n", argv[1]);
		return 1;
	}


	int data;
	struct tree_node *root = NULL;

	while (!feof(fp_data) && !ferror(fp_data)) {
		if (fscanf(fp_data, "%d", &data) != 1)
			continue;
		
		if (tree_insert(&root, data) < 0) {
			fprintf(stderr, "Error while inserting into tree: %s\n", strerror(errno));
		}
	}

	tree_print(root);
	printf("\n");

        flatten_tree(root);
        
        list_print(root);
        printf("\n");

	tree_destroy(root);

	fclose(fp_data);

	return 0;
}
