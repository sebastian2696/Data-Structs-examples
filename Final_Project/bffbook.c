#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* BFF Book is the hotest social networking app. Ever. */
/* by your name here. */

typedef struct bff_user_key {
	int bff_count;
	int userid;
}bff_user_key;

struct bff_user {
	struct bff_user_key key;
	char name[100];
	char summary[100];
	char profile[100];
};

int bff_user_cmp(const struct bff_user_key *a, const struct bff_user_key *b)
{
	/* Compare two users first by bff_count and then by userid. */
	/* Fill in some code here. */
	// -1 a < b , 1 a > b , 0 a = b 
	if(a->bff_count < b->bff_count)
		return -1;

	else if(a->bff_count > b->bff_count)
		return 1;

	else
	{
		if(a->userid < b->userid)
			return -1;
		
		if(a->userid > b->userid)
			return 1;
	}
	
	return 0;

}


typedef struct bff_user tree_data_t;
typedef struct tree_node {
	tree_data_t data;
	struct tree_node *left;
	struct tree_node *right;
	struct tree_node *parent;
}tree_node;

int tree_validate(struct tree_node *node)
{
	if (node == NULL)
		return 0;

	if (node->left && node->left->parent != node) {
		printf("Sanity check failed for node %p node->left %p, node->left->parent != node.\n", node, node->left);
		return -1;
	}

	if (node->right && node->right->parent != node) {
		printf("Sanity check failed for node %p node->right %p, node->right->parent != node.\n", node, node->right);
		return -1;
	}

	if (node->left && bff_user_cmp(&node->left->data.key, &node->data.key) >= 0) {
		printf("Sanity check failed for node %p, node->left >= node.\n", node);
		return -1;
	}

	if (node->right && bff_user_cmp(&node->right->data.key, &node->data.key) < 0) {
		printf("Sanity check failed for node %p, node->right < node\n", node);
		return -1;
	}

	if (tree_validate(node->left) < 0) {
		return -1;
	}

	if (tree_validate(node->right) < 0) {
		return -1;
	}

	return 0;
}


void tree_print(struct tree_node *node)
{
	/* Iterate through the tree with an in-order traversal and
	 * print each every key and value per line.
	 */
	 
	if(node)
	{
		tree_print(node->left);
		printf("Name: %s userid: %3d bffs: %4d\n", node->data.name, node->data.key.userid, node->data.key.bff_count);
		tree_print(node->right);
	} 

	/* Use this format for printing: */
	/* printf("Name: %s userid: %3d bffs: %4d\n", node->data.name, node->data.key.userid, node->data.key.bff_count); */
}

struct tree_node *tree_find(struct tree_node *root, const struct bff_user_key *key)
{
	/* Search through the tree for a node with the given key.
	 */

	/* Fill in some code here. */

	/* Return a pointer to the actual node, else return NULL if
	 * not found.
	 */
	tree_node *temp = root;
	while(temp)
	{
		//int cmp = bff_user_cmp()
		
		if(bff_user_cmp(&(temp->data.key), key) == 0)
			return temp;
		
		else if(bff_user_cmp(&(temp->data.key), key) < 0)
			temp = temp->right;
			
		else if(bff_user_cmp(&(temp->data.key), key) > 0)
			temp = temp->left;
	}
	
	return NULL;
}

struct tree_node *tree_delete(struct tree_node **p_root, const struct bff_user_key *key)
{
	/* First find the node, then delete it. */

	struct tree_node *node = tree_find(*p_root, key);

	if (!node) {
		return NULL;
	}

	/* Fill in a lot of code here for tree delete. */

	/* You have to set all of the links properly for all of the
	 * cases:
	 *       node is a leaf node
	 *       node has just a left child
	 *       node has just a right child
	 *       node has two children
	 */

	/* Note: a lot of links need to be taken care of, especially,
	 * Don't forget about the parent links. 
	 */
	 
	 if(node->left == NULL && node->right == NULL)//leaf node
	{
		if(node == *p_root)
			*p_root = NULL;
		
		else
		{
			if(node->parent->left == node)
				node->parent->left = NULL;
				
			else
				node->parent->right = NULL;
		}
	}

	else if(node->right == NULL)// singular left child
	{
		if(node == *p_root)
			*p_root = node->left;
		
		else
		{
			if(node->parent->right == node)
				node->parent->right = node->left;
			
			else
				node->parent->left = node->left;
			
			node->left->parent = node->parent;
		}
	}

	else if(node->left == NULL)//singular right child 
	{
		if(node == *p_root)
			*p_root = node->right;
		
		else
		{
			if(node->parent->right == node)
				node->parent->right = node->right;
			
			else
				node->parent->left = node->right;
			
			node->right->parent = node->parent;
		}
	}
else if(node->left != NULL && node->right != NULL)//two children
	{
		struct tree_node *maxleft_par = NULL;
		struct tree_node *maxleft = node->left;//initial Max left
		
		while(maxleft->right) //max left
		{
			maxleft_par = maxleft;
			maxleft = maxleft->right;
		}

		//check to see if maxleft is the root of another tree that's smaller (aka if it has a left child)
		if(maxleft->left != NULL) //sub tree
		{
			struct tree_node *temp = maxleft;
			
			maxleft_par->right = maxleft->left;//changes pointers parents/child
			free(maxleft);
			maxleft_par->right->parent = maxleft_par;
			
			node->left->parent = temp;
			temp->left = node->left;
			node->right->parent = temp;
			temp->right = node->right;
			
			if(node == *p_root)
				*p_root = temp;
				
			else 
			{
				if(node->parent->left == node)
					node->parent->left = temp;
			
				else
					node->parent->right = temp;
				
				temp->parent = node->parent;
			}
		}
	
		else//non -existant sub tree
		{
			if(maxleft_par == NULL)
			{
				maxleft->right = node->right;
				node->right->parent = maxleft;
				*p_root = maxleft;
			}
		}

	}
	
	node->left = NULL;
	node->right = NULL;
	node->parent = NULL;
	
	return node;
}

tree_data_t *tree_insert(struct tree_node **root, tree_data_t data) // error here8
{
	/* Insert a piece of data into the BST with
	 * the given root.
	 */

	/* Fill in some code here. */
	tree_node *new_node = NULL;
	tree_node *temp = *root;

	new_node = calloc(1, sizeof(struct tree_node));
	if (!new_node)
	{
		printf("can't calloc #1, ERROR\n");
		return NULL;
	}
	new_node->data = data;
	new_node->left = NULL;
	new_node->right = NULL;
	if(*root == NULL)
	{
		*root = new_node;
		return &(new_node->data);
	}


	while(temp)
	{
		if(bff_user_cmp(&(temp->data.key), &(data.key)) < 0)
		{
			if(temp->right == NULL)
			{
				tree_node *node;
				node  = calloc(1, sizeof(tree_node));
				if (!node)
				{
					printf("can't calloc #1, ERROR\n");
					return NULL;
				}
				node->data = data;
				node->parent = temp;
				node->left = NULL;
				node->right = NULL;
				temp->right = node;
				temp = node;
		
				return &(node->data);
			}
			
			else
				temp = temp->right;
		}
			
		if(bff_user_cmp(&(temp->data.key), &(data.key)) > 0)
		{
			if(temp->left == NULL)
			{
				tree_node *node;
				node  = calloc(1, sizeof(tree_node));
				if (!node)
				{
					printf("can't calloc #1, ERROR\n");
					return NULL;
				}
				node->data = data;
				node->parent = temp;
				node->left = NULL;
				node->right = NULL;
				
				temp->left = node;
				temp = node;

				return &(node->data);
			}
				
			else
				temp = temp->left;
			}
		}


	return NULL;
}



void tree_destroy(struct tree_node *root)
{
	/* Traverse the tree from the root and safely dellocate every node. */
	/* Fill in some code here. */
	tree_node *temp = root;
	
	if(temp)
	{
		tree_destroy(temp->left);
		tree_destroy(temp->right);
		free(temp);
	}
}


int parse_unsigned_integer(const char *tok, int *p_int)
{
	char *endptr;
	unsigned long l = strtol(tok, &endptr, 10);
	if (*endptr == '\0') {
		*p_int = l;
		return 0;
	}

	return -1;
}

void print_matrix(int **m, int n)
{
	int i, j;
	printf("[[");
	for (i=0; i<n; i++) {
		if (i != 0) {
			printf(" [");
		}
		for (j=0; j<n; j++) {
			printf(" %3d.", m[i][j]);
		}
		if (i!=n-1) {
			printf("]\n");
		}
		else {
			printf("]]\n");
		}
	}
	
}

void print_bff_counts(struct bff_user **users, int user_count)
{
	int i;
	printf("bff_counts:\n [");
	for (i=0; i<user_count; i++) {
		if (users[i]) {
			printf(" %3d.", users[i]->key.bff_count);
		}
	}
	printf("]\n");
}


#define MAX_DIST (999)

void update_distances_full(int **dist, int ** edge, int user_count)
{
	/* Full update of distance matrix using the Floyd–Warshall
	 * algorithm for all-pairs shortest distances.
	 */
	int i = 0;
	int j = 0;
	int k = 0;

	for(i=0; i<user_count; i++)
	{
		for(j=0; j<user_count; j++)
		{
			*dist[i*user_count + j] = 500;
		}
	}

	for(i=0; i<user_count; i++)
	{
		*dist[i*user_count + i] = 0;
	}
	
	for(i=0; i<user_count; i++)
	{
		for(j=0; j<user_count; j++)
		{
			if(*edge[i*user_count +j] !=0)
			{
				*dist[i*user_count +j] = *edge[i*user_count +j];
			}
		}
	}
	
	for(k=0; k<user_count; k++)
	{
		for(i=0; i<user_count; i++)
		{
			for(j=0; j<user_count; j++)
			{
				if(*dist[i*user_count +j] > *dist[i*user_count +k] + *dist[k*user_count +j])
				{
					*dist[i*user_count +j] = *dist[i*user_count +k] + *dist[k*user_count +j];
				}
			}
		}
	}
	
}



void update_distances_incrementally(int **dist, int edge_u, int edge_v, int user_count)
{
	/* Partial update of distance matrix using one step of the
	 * Floyd–Warshall algorithm when only a single edge (u,v) has
	 * changed.
	 */
}


void update_popularity_tree(struct bff_user **users, struct tree_node **p_root, int userid, int increment)
{
	struct bff_user user;
	struct tree_node *node = NULL;

	if (users[userid]) {
		user = *users[userid];

		printf("Before temporary deletion:\n");
		tree_print(*p_root);

		node = tree_delete(p_root, &user.key);

		/* Useful debug code: */
#if 1
		printf("Found node %p with bff_count %d and userid %d:\n", node, user.key.bff_count, user.key.userid);
		if (node) {
			printf("node->key.bff_count = %d node->key.userid = %d\n", node->data.key.bff_count, node->data.key.userid);
		}


		printf("After temporary deletion.\n");
		tree_print(*p_root);
		printf(".\n");
#endif

		free(node);
		user.key.bff_count += increment;
		users[userid] = tree_insert(p_root, user);

		printf("After re-insertion:\n");
		tree_print(*p_root);
		printf(".\n");

		if (tree_validate(*p_root) < 0) {
			abort();
		}
	}
}

int main(int argc, char *argv[])
{
	int max_users = 1000;
	int user_count = 0;
	
	if (argc < 2) {
		fprintf(stderr, "Usage: bff_book input_file.txt [max_users]\n");
		return 1;
	}

	if (argc > 2) {
		if (parse_unsigned_integer(argv[2], &max_users) < 0) {
			fprintf(stderr, "Failed to parse argument %s\n", argv[2]);
			return 1;
		}
		if (max_users < 0) {
			fprintf(stderr, "Invalid value for max_users\n");
			return 1;
		}
	}


	FILE *fp = fopen(argv[1], "rb");
	if (fp == NULL) {
		fprintf(stderr, "Error opening %s\n", argv[1]);
		return 1;
	}

	int i, j;
	struct tree_node *root = NULL;

	struct bff_user **users = calloc(max_users, sizeof(struct bff_user *));

	if (users == NULL) {
		perror("calloc");
		return 1;
	}

	/* Distances between users not used in part 1. */
	int **dist = calloc(max_users, sizeof(int *));

	if (dist == NULL) {
		perror("calloc");
		return 1;
	}

	for (i=0; i<max_users; i++) {
		dist[i] = calloc(max_users, sizeof(int));
		if (dist[i] == NULL) {
			perror("calloc");
			return 1;
		}
	}

	for (i=0; i<max_users; i++) {
		for (j=0; j<max_users; j++) {
			dist[i][j] = MAX_DIST;
		}
	}

	/* Edges between users, 1 bff 0 for not-bff. */
	int **edge = calloc(max_users, sizeof(int *));

	if (edge == NULL) {
		perror("calloc");
		return 1;
	}

	for (i=0; i<max_users; i++) {
		edge[i] = calloc(max_users, sizeof(int));
		if (edge[i] == NULL) {
			perror("calloc");
			return 1;
		}
	}

	char *lineptr = NULL;
	size_t n_chars;

	for (;;) {
		/* Read a line from the input file. */
		free(lineptr);
		lineptr = NULL;
		if (getline(&lineptr, &n_chars, fp) < 0) {
			free(lineptr);
			break;
		}

		struct bff_user new_user;
		int userid;
		int userid_from, userid_to;
		char name[100];
		char piece_of_info[100];

		if (sscanf(lineptr, "create_user %d, %[^,],%[^,],%[^,]\n",
			   &userid, name, new_user.summary, new_user.profile) == 4)
		{
			if (userid < 0 || userid >= max_users) {
				printf("Create_user failed: userid %d exceeds the range 0 to maximum %d\n", userid, max_users - 1);
				continue;
			}

			new_user.key.userid = userid;
			strcpy(new_user.name, name);
			new_user.key.bff_count = 0;

			printf("Create_user %d %s %s %s\n", userid, new_user.name, new_user.summary, new_user.profile);
			users[userid] = tree_insert(&root, new_user);
			tree_print(root);

			if (tree_validate(root) < 0) {
				abort();
			}
			user_count++;

			dist[userid][userid] = 0;

			printf("Edges:\n");
			print_matrix(edge, user_count);
			print_bff_counts(users, user_count);
		}
		else if (sscanf(lineptr, "delete_user %d\n",
				&userid) == 1)
		{
			printf("Delete_user %d\n", userid);

			struct bff_user user;
			struct tree_node *node = NULL;

			if (users[userid]) {
				user = *users[userid];
				node = tree_delete(&root, &user.key);

				/* Sometimes useful debug code: */
				/*
				printf("Found node %p with bff_count %d and userid %d:\n", node, user.key.bff_count, user.key.userid);
				if (node) {
					printf("node->key.bff_count = %d node->key.userid = %d\n", node->data.key.bff_count, node->data.key.userid);
				}
				printf("After user deletion:\n");
				tree_print(root);
				printf(".\n");
				*/

				free(node);

				/* Now clear distances for deleted id */
				for (i=0; i<user_count; i++) {
					if (edge[userid][i] > 0) {
						update_popularity_tree(users, &root, i, -1);
					}
					edge[userid][i] = 0;
					edge[i][userid] = 0;
				}
				update_distances_full(dist, edge, user_count);
			}
		}
		else if (sscanf(lineptr, "bff %d, %d\n",
				&userid_from, &userid_to) == 2)
		{
			printf("Bff %d %d\n", userid_from, userid_to);
			edge[userid_from][userid_to] = 1;
			edge[userid_to][userid_from] = 1;

			//update_distances_incrementally(dist, userid_from, userid_to, user_count);
			update_distances_full(dist, edge, user_count);
			update_popularity_tree(users, &root, userid_from, +1);
			//tree_print(root);
			update_popularity_tree(users, &root, userid_to, +1);
			//tree_print(root);

			printf("Edges:\n");
			print_matrix(edge, user_count);
			print_bff_counts(users, user_count);

			
		        printf("Distances:\n");
			print_matrix(dist, user_count);
		}
		else if (sscanf(lineptr, "unbff %d, %d\n",
				&userid_from, &userid_to) == 2)
		{
			printf("Unbff %d %d\n", userid_from, userid_to);

			if (edge[userid_from][userid_to] == 0) {
				printf("Unbff %d and %d are not bffs.\n", userid_from, userid_to);
				continue;
			}

			edge[userid_from][userid_to] = 0;
			edge[userid_to][userid_from] = 0;
			update_distances_full(dist, edge, user_count);

			update_popularity_tree(users, &root, userid_from, -1);
			//tree_print(root);
			update_popularity_tree(users, &root, userid_to, -1);
			//tree_print(root);

			printf("Edges:\n");
			print_matrix(edge, user_count);
			print_bff_counts(users, user_count);

		        printf("Distances:\n");
			print_matrix(dist, user_count);
		}
		else if (sscanf(lineptr, "read %d, %d, %[^,\n]\n", &userid_to, &userid_from, piece_of_info) == 3) {
			printf("Read %d %d %s\n", userid_to, userid_from, piece_of_info);
			int d = dist[userid_from][userid_to];
			int denied = 1;

			if (!strcmp(piece_of_info, "profile")) {
				if (d <= 1) {
					printf("Read %s: %s\n", piece_of_info, users[userid_from]->profile);
					denied = 0;
				}
			}
			else if (!strcmp(piece_of_info, "summary")) {
				if (d <= 2) {
					printf("Read %s: %s\n", piece_of_info, users[userid_from]->summary);
					denied = 0;
				}
			}
			else if (!strcmp(piece_of_info, "bffs")) {
				if (d <= 3) {
					printf("Read %s: \n", piece_of_info);
					denied = 0;
				}
			}
			else if (!strcmp(piece_of_info, "name")) {
				if (d <= 4) {
					printf("Read %s: %s\n", piece_of_info, users[userid_from]->name);
					denied = 0;
				}
			}
			else {
				printf("Read %s failed: Unkown record.\n", piece_of_info);
				denied = 0;
			}

			if (denied) {
				printf("Read %s: Permission denied, insufficient distance %d.\n", piece_of_info, d);

			}
		}
		else if (!strcmp(lineptr, "rank\n")) {
			printf("Rank:\n");
			tree_print(root);
			printf(".\n");
		}
		else {
			printf("Unrecognized command: %s\n", lineptr);
		}
	}

	if (ferror(fp)) {
		perror("read");
	}

	printf("Exiting...\n");

	printf("Final rank:\n");
	tree_print(root);

	tree_destroy(root);

	for (i=0; i<max_users; i++) {
		free(dist[i]);
	}
	free(dist);

	for (i=0; i<max_users; i++) {
		free(edge[i]);
	}
	free(edge);

	free(users);
	
	fclose(fp);
	return 0;
}
