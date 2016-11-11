/*graph.c*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


typedef struct adjNode
{
    int vertex;                
    struct adjNode *next; 
}adjNodeType, *adjNodeP;
 

typedef struct adjList
{
    int num_members;           
    adjNodeType *head;      
}adjListType, *adjListP;
 
 
/* Graph structure.*/
typedef struct graph
{
    int num_vertices;         
    adjListP adjListArr;     
}graphT, *graphP;

inline void err_exit(char* msg)
{
    printf("[Fatal Error]: %s \nExiting...\n", msg);
    exit(1);
}
 
/* Function to create an adjacency list node*/
adjNodeP createNode(int v)
{
	/*
	
	Allocate memory space to a new node
	newNode's vertex is v
	newNode's next is NULL
	
	*/
	adjNodeP newNode = (adjNodeP) calloc (1,sizeof(adjNodeType));
    newNode->vertex  = v;
    newNode->next = NULL;
 
    return newNode;
}
 
/* Function to create a graph with n vertices; */
graphP createGraph(int n)
{
	/*
	
	Allocate memory space to a new graph
	n is the number of vertices
	Allocate memory space to each adjList
	each adjList is for a vertex
	
	*/
    int i;
    graphP graph = (graphP)malloc(sizeof(graphT));
    if(!graph)
        err_exit("Unable to create a new graph: memory issue");
    graph -> num_vertices = n;
    graph -> adjListArr = (adjListP) calloc (1, n*sizeof(adjListType));
    for (i = 0; i < n ; ++i )
        graph -> adjListArr[i].head = NULL;
 
    return graph;
}
 
/*Destroys the graph*/
void destroyGraph(graphP graph)
{
	/*	
	free memory spaces you have allocated	
	*/
    if(graph)
    {
        if(graph->adjListArr)
        {
            int v;
            /*Free up the nodes*/
            for (v = 0; v < graph->num_vertices; v++)
            {
                adjNodeP adjListPtr = graph->adjListArr[v].head;
                while (adjListPtr)
                {
                    adjNodeP tmp = adjListPtr;
                    adjListPtr = adjListPtr->next;
                    free(tmp);
                }
            }
            /*Free the adjacency list array*/
            free(graph->adjListArr);
        }
        /*Free the graph*/
        free(graph);
    }
}
 
/* Adds an edge to a graph*/
void addEdge(graphT *graph, int src, int dest)
{
    /* 
	Add an edge from src to dst in the adjacency list 
	*/
	adjNodeP newnode = createNode(dest);
	newnode -> next = graph -> adjListArr[src].head;
	graph -> adjListArr[src].head = newnode;

}
 
/* Function to print the adjacency list of graph*/
void displayGraph(graphP graph)
{
    int i;
    for ( i=0; i < graph->num_vertices ; ++i)
    {
        adjNodeP temp = graph->adjListArr[i].head;
        printf("Vertex %d: ",i);
        while (temp)
        {
            printf("%d->",temp -> vertex);
            temp = temp -> next;
        }
        printf("NULL\n");
    }
}
 
int main(int argc, char *argv[])
{
	
	if (argc < 3) {
		fprintf(stderr, "Usage: CreateDirectedGraph data_file.txt number_of_vertices\n");
		return 1;
	}

	FILE *fp_data = fopen(argv[1], "rb");
	if (fp_data == NULL) {
		fprintf(stderr, "Error opening %s\n", argv[1]);
		return 1;
	}
    
        graphP directGraph = createGraph(atoi(argv[2]));
	
	int src;
	int dst;
	struct tree_node *root = NULL;

	while (!feof(fp_data) && !ferror(fp_data)) {
		if (fscanf(fp_data, "%d %d", &src, &dst) != 2)
			continue;
		
		addEdge(directGraph, src, dst);
	}
	

        printf("\nDIRECTED GRAPH\n");
        displayGraph(directGraph);
        destroyGraph(directGraph);
 
        return 0;
}
