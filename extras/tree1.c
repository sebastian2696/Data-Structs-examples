#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX_KEY_LEN (32)
#define MAX_VALUE_LEN (32)
struct tree_data {
	char key[MAX_KEY_LEN];
	char value[MAX_VALUE_LEN];
};

struct tree_node {
	struct tree_data data;
	struct tree_node *left;
	struct tree_node *right;
};


void tree_print(struct tree_node *node)
{
	/* Iterate through the tree with an in-order traversal and
	 * print each every key and value per line.
	 */
	 if(node!=NULL){
	 	tree_print(node->left);
	 	printf("Key: %s Value: %s\n", node->data.key, node->data.value);
	 	tree_print(node->right);
	 }
}

struct tree_node *tree_find(struct tree_node *root, const char *key)
{
	/* Search through the tree for a node with the given key.
	 * Return a pointer to the node if found, and NULL if not
	 * found.
	 */
	 struct tree_node *temp = root;
	 
	 while(temp!=NULL){
	 	if(strcmp(temp->data.key, key) == 0){
	 		return temp;
	 	}
	 	else if(strcmp(temp->data.key, key) > 0){
	 		temp = temp->left;
	 	}
	 	else if(strcmp(temp->data.key, key) < 0){
	 		temp = temp->right;
	 	}
	 }
	 return NULL;
}

int tree_insert(struct tree_node **p_root, struct tree_data data)
{
	/* Insert a piece of data into the BST with
	 * the given root.
	 * Return 0 if successful, -1 if it exists already, or if
	 * there is an allocation failure.
	 */
	 
}

void tree_destroy(struct tree_node *root)
{
	/* Traverse the tree from the root and safely dellocate every node. */
}


int main(int argc, char *argv[])
{
	if (argc < 2) {
		fprintf(stderr, "Usage: dict data_file.txt [lookup_commands.txt]\n"
			         "Note: There is no sorted argument.\n");
		return 1;
	}

	FILE *fp_data = fopen(argv[1], "rb");
	if (fp_data == NULL) {
		fprintf(stderr, "Error opening %s\n", argv[1]);
		return 1;
	}

	FILE *fp_lookup = NULL;
	if (argc > 2) {
		fp_lookup = fopen(argv[2], "rb");
		if (fp_lookup == NULL) {
			fprintf(stderr, "Error opening lookups file %s\n", argv[2]);
			return 1;
		}
	}

	struct tree_data d;
	struct tree_node *root = NULL;

	while (!feof(fp_data) && !ferror(fp_data)) {
		if (fscanf(fp_data, "%s %s", d.key, d.value) != 2)
			continue;
		
		printf("Insert %s %s in sorted order\n", d.key, d.value);

		if (tree_insert(&root, d) < 0) {
			fprintf(stderr, "Error while inserting into tree: %s\n", strerror(errno));
		}

		tree_print(root);
	}


	char lookup_key[MAX_KEY_LEN];
	struct tree_node *lookup_node;

	while (fp_lookup && !feof(fp_lookup) && !ferror(fp_lookup)) {
		if (fscanf(fp_lookup, "%s", lookup_key) != 1)
			continue;

		if ((lookup_node = tree_find(root, lookup_key)) != NULL) {
			printf("Found: %s %s\n", lookup_node->data.key, lookup_node->data.value);
		}
		else {
			printf("Failed to find: %s\n", lookup_key);
		}
	}

	tree_destroy(root);
	
	fclose(fp_data);

	if (fp_lookup) {
		fclose(fp_lookup);
	}

	return 0;
}