//Ahlden Brough
//ajbrough
//pa5

#include<stdio.h>
#include<stdlib.h>
#include "List.h"
#include "Graph.h"

int main(int argc, char* argv[]) {
  FILE *in, *out;
  int n;
  int u;
  int v;
  List L = newList();
  // check command line for correct number of arguments
    if( argc != 3 ){
      printf("Usage: FindPath <input file> <output file>\n");
      exit(1);
    }

    // open files for reading and writing 
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");
    if( in==NULL ){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
    }
    if( out==NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
    }
    fscanf(in, "%d", &n);
    Graph G = newGraph(n);
    fscanf(in, "%d", &u);
    fscanf(in, "%d", &v);
    while(u != 0 && v != 0){
      addEdge(G, u, v);
      fscanf(in, "%d", &u);
      fscanf(in, "%d", &v);
    }
    printGraph(out, G);
    fprintf(out, "\n");
    fscanf(in, "%d", &u);
    fscanf(in, "%d", &v);
    while(u != 0 && v != 0){
      BFS(G, u);
      if(getDist(G, v) == -1){
        fprintf(out, "The distance from %d to %d is infinity\n", u, v);
        fprintf(out, "No %d-%d path exists", u, v);
      }
      else{
        fprintf(out, "The distance from %d to %d is %d\n", u, v, getDist(G, v));
        fprintf(out, "A shortest %d-%d path is: ", u, v);
        clear(L);
        getPath(L, G, v);
        printList(out, L);
      }
      fprintf(out, "\n");
      fprintf(out, "\n");
      fscanf(in, "%d", &u);
      fscanf(in, "%d", &v);
    }

  fclose(in);
  fclose(out);

  freeList(&L);
  freeGraph(&G);
  return(0);
}