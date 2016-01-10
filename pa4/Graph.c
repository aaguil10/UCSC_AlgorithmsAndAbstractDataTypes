//Alejandro Aguilar aaguil10@ucsc.edu

#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"
#include "List.h"

#define NIL -1
#define INF -1

typedef struct GraphObj{
   List *list;
   char *color;
   int *pie;
   int *dis;
   List Q;
   int size;
   int order;
   int s; 

} GraphObj;

/*** Constructors-Destructors ***/
Graph newGraph(int n){
   Graph myGraph = malloc(sizeof(GraphObj));
   myGraph->list = calloc(n+1,sizeof(List));
   myGraph->color = calloc(n+1, sizeof(char));
   myGraph->pie = calloc(n+1, sizeof(int));
   myGraph->dis = calloc(n+1, sizeof(int));
   myGraph->Q = malloc(sizeof(List));
   //myGraph->list[1] = newList();
   for(int i = 1; i < n + 1; i++){
      myGraph->list[i] = newList();
      myGraph->color[i] = 'w';
      myGraph->pie[i] = NIL;
      myGraph->dis[i] = INF;
   }
   myGraph->Q = newList();
   myGraph->order = n;
   myGraph->size = 0;
   myGraph->s = NIL;
   return myGraph;
}

void freeGraph(Graph* pG){
   if(pG != NULL && pG != NULL){
      free(*pG);
      *pG = NULL;
   }
}


/*** Access functions ***/
int getOrder(Graph G){
   if(G == NULL){
      printf("Graph.c ERROR: calling getOrder() on a NULL Graph reference\n");
      exit(1);
   }
   return G->order;
}


int getSize(Graph G){
   if(G == NULL){
      printf("Graph.c ERROR: calling getSize() on a NULL Graph reference\n");
      exit(1);
   }
   return G->size;
}

int getSource(Graph G){
   if(G == NULL){
      printf("Graph.c ERROR: calling getSource() on a NULL Graph reference\n");
      exit(1);
   }
   return G->s;
}

// precondition 1 <= u <= getOrder(G)
int getParent(Graph G, int u){
   if(G == NULL){
      printf("Graph.c ERROR: calling getParent() on a NULL Graph reference\n");
      exit(1);
   }
   if(u < 1 || u > getOrder(G)){
      printf("Graph.c ERROR: in getParent() u < 1 || u > G.getOrder(G)\n");
      exit(1);
   }
   return G->pie[u];
}

// precondition 1 <= u <= getOrder(G)
int getDist(Graph G, int u){
   if(G == NULL){
      printf("Graph.c ERROR: calling getDist() on a NULL Graph reference\n");
      exit(1);
   }
   if(u < 1 || u > getOrder(G)){
      printf("Graph.c ERROR: in getDist() u < 1 || u > G.getOrder(G)\n");
      exit(1);
   }
   return G->dis[u];
}

//appends to the List L the vertices of a shortest path in G from 
//source to u, or appends to L the value NIL if no such path exists
//precondition getSource(G)!=NIL , 1 <= u <= getOrder(G)
 void getPath(List L, Graph G, int u) {
    if (u == G->s) {
        append(L, G->s);
    }

    else if (G->pie[u] == NIL) {
        append(L, NIL);
    }

    else {
        getPath(L, G, G->pie[u]);
        append(L, u);
    }
}

/*** Manipulation procedures ***/

//deletes all edges of G, restoring it to its original (no edge) state
void makeNull(Graph G){
   printf("In makeNull()\n");
   fflush(stdout);
   if(G == NULL){
      printf("Graph.c ERROR: calling makeNull() on a NULL Graph reference\n");
      exit(1);
   }
   for(int i = 1; i <= getOrder(G); i++){
      if(length(G->list[i]) != 0){
         printf("clear(G->list[%d])\n",i);
         fflush(stdout);
         clear(G->list[i]);
      }
   }
}

void insertSorted(List L, int u, int max){

   if(L == NULL){
    printf("Graph.c ERROR: calling insertSorted() on a NULL List reference\n");
      exit(1);
   }
   if(u <= 0 || u > max){
      printf("Graph.c ERROR: calling insertSorted() ");
      printf("when u < 0 || u > length(L)\n");
      printf("u:%d\n",u);
      exit(1);
   }
   if(length(L) == 0){
      append(L,u);
      return;
   }else{
      moveTo(L,0);
   }
   if(u >= getElement(L)){
      while(u >= getElement(L) && getIndex(L) < length(L) - 1){
         moveNext(L);
      }
      if(u < getElement(L)){
         insertBefore(L,u);
      }else if(u > getElement(L)){
         insertAfter(L,u);
      }
   }else{
      while(u < getElement(L) && getIndex(L) > 0){
         movePrev(L);
      }
      if(u > getElement(L)){
         insertAfter(L,u);
      }else if(u < getElement(L)){
         insertBefore(L,u);
      }
   }
}


//inserts a new edge joining u to v, i.e. u is added 
//to the adjacency List of vand v to the adjacency List of u. 
//Your program is required to maintain these lists in sorted order 
//by increasing labels
//Precondition: 1 <= u/v <= getOrder()
void addEdge(Graph G, int u, int v){
   if(G == NULL){
      printf("Graph.c ERROR: calling addEdge() on a NULL Graph reference\n");
      exit(1);
   }
   if(u < 1 || u > getOrder(G)){
      printf("Graph.c ERROR: in addEdge() u < 1 || u > G.getOrder(G)\n");
      printf("u: %d v: %d\n", u, v);
      exit(1);
   }
   if(v < 1 || v > getOrder(G)){
      printf("Graph.c ERROR: in addEdge() v < 1 || v > G.getOrder(G)\n");
      printf("u: %d v: %d\n", u, v);
      exit(1);
   }

  
   insertSorted(G->list[u],v,getOrder(G));
   insertSorted(G->list[v], u,getOrder(G));
   G->size++;
}


//inserts a new directed edge from u to v, i.e. v is added 
//to the adjacency List of u (but not u to the adjacency List of v)
//Precondition: 1 <= u/v <= getOrder()
void addArc(Graph G, int u, int v){
   if(G == NULL){
      printf("Graph.c ERROR: calling addArc() on a NULL Graph reference\n");
      exit(1);
   }
   if(u < 1 || u > getOrder(G)){
      printf("Graph.c ERROR: in addEdge() u < 1 || u > G.getOrder(G)\n");
      exit(1);
   }
   if(v < 1 || v > getOrder(G)){
      printf("Graph.c ERROR: in addEdge() v < 1 || v > G.getOrder(G)\n");
      exit(1);
   }
   insertSorted(G->list[u], v,getOrder(G));
   G->size++;
}

//runs the BFS
//algorithm on the Graph G with source s,
// setting the color, distance, parent, 
// and source fields of G accordingly
void BFS(Graph G, int s){
   G->s = s;
   if(G == NULL){
      printf("Graph.c ERROR: calling BFS() on a NULL Graph reference\n");
      exit(1);
   }
   G->color[s] = 'g';
   G->dis[s] = 0;
   prepend(G->Q,s);
   while(length(G->Q) != 0){
      if(G->Q == NULL){
         printf("G->Q == NULL\n");
         fflush(stdout);
      }
      moveTo(G->Q,0);
      int u = front(G->Q);
      deleteFront(G->Q); 
     for(moveTo(G->list[u],0); getIndex(G->list[u]) >= 0; moveNext(G->list[u])){
         int v = getElement(G->list[u]);      
         if(G->color[v] == 'w'){
            G->color[v] = 'g';
            G->dis[v] = G->dis[u] + 1;
            G->pie[v] = u;
            append(G->Q,v);
         }
      }
   G->color[u] = 'b';
   }
}

/*** Other operations ***/

//prints the adjacency list representation of G to the file 
//pointed to by out
void printGraph(FILE* out, Graph G){
   if(G == NULL){
      printf("Graph.c ERROR: calling printGraph() on a NULL Graph reference\n");
      exit(1);
   }

   for(int i = 1; i <= getOrder(G); i++){
      if(length(G->list[i]) != 0){
         fprintf(out,"%d: ",i);
         printList(out,G->list[i]);
         fprintf(out, "\n");
      }
   }
}



