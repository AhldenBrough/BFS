//Ahlden Brough
//ajbrough
//pa4

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Graph.h"
#include"List.h"

int INF = -1;
int NIL = 0;
int WHITE = 1;
int GRAY = 2;
int BLACK = 3;

typedef struct GraphObj{
  int size;
  int order;
  int source;
  List* neighbors;
  int* color;
  int* parent;
  int* distance;
}GraphObj;

/*** Constructors-Destructors ***/
Graph newGraph(int n){
  Graph G;
  G = malloc(sizeof(GraphObj));
  G->size = 0;
  G->order = n;
  G->source = NIL;
  G->neighbors = calloc(n+1, sizeof(List));
  G->color = calloc(n+1, sizeof(int));
  G->parent = calloc(n+1, sizeof(int));
  G->distance = calloc(n+1, sizeof(int));
  for(int i = 1; i < n+1; i++){ //start i at 0 or 1?
    G->neighbors[i] = newList();
    G->color[i] = WHITE;  
    G->distance[i] = INF;
    G->parent[i] = NIL;
  }
  return G;
}

void freeGraph(Graph* pG){
  if(pG!=NULL && *pG!=NULL){
    makeNull(*pG);
    for(int i = 1; i < (*pG)->order + 1; i++){
      freeList(&(*pG)->neighbors[i]);
    }
    free((*pG)->neighbors);
    free((*pG)->color);
    free((*pG)->parent);
    free((*pG)->distance);
    (*pG)->color =  NULL;
    (*pG)->parent = NULL;
    (*pG)->distance = NULL;
    (*pG)->neighbors = NULL;
    (*pG)->order = 0;
    (*pG)->source = 0;
    (*pG)->size = 0;
    free(*pG);
    *pG = NULL;
  }
}

/*** Access functions ***/
int getOrder(Graph G){
  if(G == NULL){
    printf("Graph Error: calling getOrder() on NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  return G->order;
}

int getSize(Graph G){
  if(G == NULL){
    printf("Graph Error: calling getSize() on NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  return G->size;
}

int getSource(Graph G){
  if(G == NULL){
    printf("Graph Error: calling getSource() on NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  return G->source;
}

int getParent(Graph G, int u){
  if(G == NULL){
    printf("Graph Error: calling getParent() on NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  return G->parent[u];
}

int getDist(Graph G, int u){
  if(G == NULL){
    printf("Graph Error: calling getDist() on NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  return G->distance[u];
}

void getPath(List L, Graph G, int u){
  if(G == NULL){
    printf("Graph Error: calling getPatht() on NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  //printf("starts getPath\n");
  if(getSource(G)== NIL){
    printf("Graph Error: calling getPath before BFS has been run on the graph\n");
    exit(EXIT_FAILURE);
  }
  if(u == getSource(G)){
    append(L, getSource(G));
  }
  else if(getParent(G, u) == NIL){
    append(L, NIL);
  }
  else{
    getPath(L, G, getParent(G, u));
    append(L, u);
    }
}

/*** Manipulation procedures ***/
void makeNull(Graph G){
  if(G == NULL){
    printf("Graph Error: calling makeNull() on NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  for(int i = 1; i< getOrder(G) + 1; i++){
    clear(G->neighbors[i]);
    G->color[i] = 0;  
    G->distance[i] = INF;
    G->parent[i] = NIL;
  }
  G->source = NIL;
  G->size = 0;
}

void addEdge(Graph G, int u, int v){
  //printf("starts addEdge\n");
  if(G == NULL){
    printf("Graph Error: calling addEdge() on NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  if(u == v){
    addArc(G, u, v);
  }
  else{
    addArc(G, u, v);
    addArc(G, v, u);
    G->size--;
  }
}

void addArc(Graph G, int u, int v){
  if(G == NULL){
    printf("Graph Error: calling addArc() on NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  //printf("addArc(%d, %d)----------------------\n", u, v);
  //printf("printList: ");
  //printList(stdout, G->neighbors[u]);
  //printf("\n");
  if(length(G->neighbors[u]) != 0){
    moveFront(G->neighbors[u]);
    //printf("moves front\n");
    while(index(G->neighbors[u]) > -1){
     // printf("iterates\n");
      if(get(G->neighbors[u]) == v){
        return;
      }
      moveNext(G->neighbors[u]);
    }
    //printf("gets past checking for duplicates\n");
    //printf("get(G->neighbors[%d]) = %d\n", u, get(G->neighbors[u]));
    moveFront(G->neighbors[u]);
    while(1){
      //printf("top of while(1)\n");
      //bigger and not at the back
      if( (get(G->neighbors[u]) < v) && (get(G->neighbors[u]) != back(G->neighbors[u])) ){
        //printf("attempts moveNext\n");
        moveNext(G->neighbors[u]);
        //printf("moves next\n");
      }
      //bigger and at the back
      else if( (get(G->neighbors[u]) < v) && (get(G->neighbors[u]) == back(G->neighbors[u])) ){
        //printf("attempts append\n");
        append(G->neighbors[u], v);
        G->size++;
        //printf("appends\n");
        break;
      }
      //smaller
      else{
        //printf("attempts insert before\n");
        insertBefore(G->neighbors[u], v);
        G->size++;
        //printf("inserts before\n");
        break;
      }
    }
  }
  else{
    append(G->neighbors[u], v);
    G->size++;
  }
  //printf("----------------------\n");
}
void BFS(Graph G, int s){
  if(G == NULL){
    printf("Graph Error: calling addArc() on NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  //printf("starts BFS\n");
  // for𝑥∈V(G)−{s}
  //   color[𝑥] = white
  //   𝑑[𝑥] = ∞
  //   𝑝[𝑥] = nil
  // color[𝑠] = gray
  // 𝑑[𝑠]=0
  // 𝑝[𝑠] = nil
  // 𝑄 = ∅
  // Enqueue(𝑄, 𝑠)
  // while 𝑄 ≠ ∅
  //   𝑥 = Dequeue(𝑄)
  //   for 𝑦 ∈ adj[𝑥]
  //     if color[𝑦] == white
  //       color[𝑦] = gray
  //       𝑑[𝑦] = 𝑑[𝑥] + 1
  //       𝑝[𝑦] = 𝑥
  //       Enqueue(𝑄, 𝑦)
  //   COLOR[X] = BLACK
  G->source = s;
  for(int i = 1; i < getOrder(G) + 1; i++){
    //printf("first loop iterates\n");
    G->color[i] = WHITE;
    G->distance[i] = INF;
    G->parent[i] = NIL;
  }
  G->color[s] = GRAY;
  G->distance[s] = 0;
  List Q = newList();
  append(Q, s);
  while(length(Q) != 0){
    //printf("length(Q) != 0\n");
    int x = front(Q);
    deleteFront(Q);
    if(length(G->neighbors[x]) != 0){
      moveFront(G->neighbors[x]);
    }
    while(index(G->neighbors[x]) > -1){
      int y = get(G->neighbors[x]);
      if(G->color[y] == WHITE){
        G->color[y] = GRAY;
        G->distance[y] = getDist(G, x) + 1;
        G->parent[y] = x;
        append(Q, y);
      }
      moveNext(G->neighbors[x]);
    }
    G->color[x] = BLACK;
  }
  freeList(&Q);
}
/*** Other operations ***/
void printGraph(FILE* out, Graph G){
  if(G == NULL){
    printf("Graph Error: calling printGraph() on NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  for(int i = 1; i < getOrder(G) + 1; i++){
    fprintf(out, "%d: ", i);
    if(length(G->neighbors[i]) != 0){
      moveFront(G->neighbors[i]);
      while(index(G->neighbors[i]) > -1){
        fprintf(out, "%d ", get(G->neighbors[i]));
        moveNext(G->neighbors[i]);
      }
    }
    fprintf(out, "\n");
  }
}

