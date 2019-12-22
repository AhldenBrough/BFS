//Ahlden Brough
//ajbrough
//pa4

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"
#include"List.h"

int main(int argc, char* argv[]){
	Graph G = newGraph(5);
	addEdge(G, 1, 2);
	addEdge(G, 1, 2);
	addEdge(G, 2, 3);
	addEdge(G, 3, 4);
	addEdge(G, 4, 5);
	addEdge(G, 5, 1);
	addEdge(G, 5, 5);
	printGraph(stdout, G);
	makeNull(G);
	printGraph(stdout, G);
	addEdge(G, 1, 2);
	addEdge(G, 1, 2);
	addEdge(G, 2, 3);
	addEdge(G, 3, 4);
	addEdge(G, 4, 5);
	addEdge(G, 5, 1);
	addEdge(G, 5, 5);
	BFS(G, 1);
	List L = newList();
	getPath(L, G, 3);
	printList(stdout, L);
	Graph A  = newGraph(99);
		if(getSize(A) != 0){
			printf("size wasn't zero\n");
		}
		printf("gets past\n");
        addArc(A, 54, 1);
        printf("adds arc 1\n");
        addArc(A, 54, 2);
        printf("adds arc 2\n");
        addArc(A, 54, 3);
        printf("adds arc 3\n");
        addArc(A, 1, 54);
        printf("adds arc 4\n");
        addArc(A, 1, 55);
        printf("adds arc 5\n");
        if (getSize(A) != 5){
        	printf("size wasn't 5\n");
        }
        BFS(A, 67);
        printf("BFS\n");
        if (getSize(A) != 5){
        	printf("size wasn't 5 (2)\n");
        }
        addArc(A, 55, 1);
        printf("adds arc 6\n");
        if (getSize(A) != 6){
        	printf("size wasn't 6\n");
        }
    printf("getOrder(G) = %d\n", getOrder(G));
    printf("getSize(G) = %d\n", getSize(G));
    printf("getSource(G) = %d\n", getSource(G));
    printf("getDist(G, 5) = %d\n", getDist(G, 5));
	return(0);
}
