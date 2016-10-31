#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX_KEY_LEN (32)
#define MAX_VALUE_LEN (32)
typedef struct tree_data {
	char key[MAX_KEY_LEN];
	char value[MAX_VALUE_LEN];
}tree_data;

typedef struct tree_node {
	struct tree_data data;
	struct tree_node *left;
	struct tree_node *right;
}tree_node;


void tree_print(struct tree_node *node)
{
	/* Iterate through the tree with an in-order traversal and
	 * print each every key and value per line.
	 */

/*	 if(node!=NULL){
	 	tree_print(node->left);
	 	printf("Key: %s\t Value: %s\n", node->data.key, node->data.value);
	 	tree_print(node->right);
	 }
	 return;*/
}

struct tree_node *tree_find(struct tree_node *root, const char *key)
{
	/* Search through the tree for a node with the given key.
	 * Return a pointer to the node if found, and NULL if not
	 * found.
	 */
	 if (root == NULL) return NULL;
	 tree_node *temp = root;
	 if(strcmp(temp->data.key, key) == 0){
	 		return temp;
	 	}
	 	else if(strcmp(temp->data.key, key) > 0){
	 		return tree_find(temp->left,key);//temp = temp->left;
	 	}
	 	else if(strcmp(temp->data.key, key) < 0){
	 		return tree_find(temp->right,key);//temp = temp->right;
	 	}
	 	return NULL;
}
tree_node *Insert(tree_node *node,tree_data data)
{
        tree_node *temp = NULL;
        if(node==NULL)
        {
                
                temp = (tree_node *)malloc(sizeof(tree_node));
                temp -> data = data;
                temp -> left = temp -> right = NULL;
                return temp;
        }

        if(strcmp(temp->data.key,node ->data.key) < 0)
        {
                node->right = Insert(node->right,data);
        }
        else if(strcmp(temp->data.key,node ->data.key) > 0)
        {
                node->left = Insert(node->left,data);
        }
        /* Else there is nothing to do as the data is already in the tree. */
        return node;

}

int tree_insert(struct tree_node **p_root, struct tree_data data)
{
	/* Insert a piece of data into the BST with
	 * the given root.
	 * Return 0 if successful, -1 if it exists already, or if
	 * there is an allocation failure.
	 */
//	 Insert(*p_root,data);
//	 return 0;
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
	if(strcmp(data.key,(*p_root)->data.key) == 0)
        return 0;	

	if(strcmp((*p_root)->data.key, data.key ) > 0)

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
//		fprintf(stderr, "Usage: dict data_file.txt [lookup_commands.txt]\n"
//			         "Note: There is no sorted argument.\n");
		return 1;
	}

	FILE *fp_data = fopen(argv[1], "rb");
	if (fp_data == NULL) {
//		fprintf(stderr, "Error opening %s\n", argv[1]);
		return 1;
	}

	FILE *fp_lookup = NULL;
	if (argc > 2) {
		fp_lookup = fopen(argv[2], "rb");
		if (fp_lookup == NULL) {
//			fprintf(stderr, "Error opening lookups file %s\n", argv[2]);
			return 1;
		}
	}

	struct tree_data d;
	struct tree_node *root = NULL;
	int found_count =0;
	
	while (!feof(fp_data) && !ferror(fp_data)) {
		if (fscanf(fp_data, "%s %s", d.key, d.value) != 2)
			continue;
		
//		printf("Insert %s %s in sorted order\n", d.key, d.value);
		//Insert(root,d);
		if (tree_insert(&root, d) < 0) {
//			fprintf(stderr, "Error while inserting into tree: %s\n", strerror(errno));
		}

//		tree_print(root);
	}


	char lookup_key[MAX_KEY_LEN];
	struct tree_node *lookup_node;

	while (fp_lookup && !feof(fp_lookup) && !ferror(fp_lookup)) {
		if (fscanf(fp_lookup, "%s", lookup_key) != 1)
			continue;

		if ((lookup_node = tree_find(root, lookup_key)) != NULL) {
//			printf("Found: %s %s\n", lookup_node->data.key, lookup_node->data.value);
			found_count++;
		}
		else {
//			printf("Failed to find: %s\n", lookup_key);
		}
	}
	printf("Found count is %d\n", found_count);
	tree_destroy(root);
	
	fclose(fp_data);

	if (fp_lookup) {
		fclose(fp_lookup);
	}

	return 0;
}
	
