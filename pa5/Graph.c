//Alejandro Aguilar aaguil10@ucsc.edu
//Graph.c

#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"
#include "List.h"

#define NIL -1
#define UNDEF -2

typedef struct GraphObj{
   List *list;
   char *color;
   int *pie;
   int *dTime;
   int *fTime;
   int size;
   int order;

} GraphObj;

/*** Constructors-Destructors ***/
//newGraph() will return a reference to a new graph object 
//containing n vertices and no edges.
Graph newGraph(int n){
   Graph myGraph = malloc(sizeof(GraphObj));
   myGraph->list = calloc(n+1,sizeof(List));
   myGraph->color = calloc(n+1, sizeof(char));
   myGraph->pie = calloc(n+1, sizeof(int));
   myGraph->dTime = calloc(n+1, sizeof(int));
   myGraph->fTime = calloc(n+1, sizeof(int));
   for(int i = 1; i < n + 1; i++){
      myGraph->list[i] = newList();
      myGraph->color[i] = 'w';
      myGraph->pie[i] = NIL;
      myGraph->dTime[i] = UNDEF;
      myGraph->fTime[i] = UNDEF;
   }
   myGraph->order = n;
   myGraph->size = 0;
   return myGraph;
}

void freeLists(Graph *pG,int x){
   if(x == 0){
      return;
   }
   freeList(&((*pG)->list[x]));
   freeLists(pG,x-1);
}


//freeGraph() frees all heap memory associated with a graph 
//and sets its Graph argument to NULL.
void freeGraph(Graph* pG){
   if(pG != NULL && pG != NULL){
      freeLists(pG,(*pG)->order);
      free((*pG)->list);
      free((*pG)->color);
      free((*pG)->pie);
      free((*pG)->dTime);
      free((*pG)->fTime);
      free(*pG);
      *pG = NULL;
   }
}


/*** Access functions ***/
//getOrder() returns the number of vertices in G,
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

//Pre: 1<=u<=n=getOrder(G)
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

//Pre: 1<=u<=n=getOrder(G)
int getDiscover(Graph G, int u){
   if(G == NULL){
      printf("Graph.c ERROR: calling getDiscover() on a NULL Graph reference\n");
      exit(1);
   }
   if(u < 1 || u > getOrder(G)){
      printf("Graph.c ERROR: in getDiscover() u < 1 || u > G.getOrder(G)\n");
      exit(1);
   }
   return G->dTime[u];
}

//Pre: 1<=u<=n=getOrder(G)
int getFinish(Graph G, int u){
   if(G == NULL){
      printf("Graph.c ERROR: calling getFinish() on a NULL Graph reference\n");
      exit(1);
   }
   if(u < 1 || u > getOrder(G)){
      printf("Graph.c ERROR: in getFinish() u < 1 || u > G.getOrder(G)\n");
      exit(1);
   }
   return G->fTime[u];
}

/*** Manipulation procedures ***/
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

void addArc(Graph G, int u, int v){
   if(G == NULL){
      printf("Graph.c ERROR: calling addArc() on a NULL Graph reference\n");
      exit(1);
   }
   if(u < 1 || u > getOrder(G)){
      printf("Graph.c ERROR: in addArc() u < 1 || u > G.getOrder(G)\n");
      exit(1);
   }
   if(v < 1 || v > getOrder(G)){
      printf("Graph.c ERROR: in addArc() v < 1 || v > G.getOrder(G)\n");
      exit(1);
   }
   insertSorted(G->list[u], v,getOrder(G));
   G->size++;
}

void visit(Graph G, List S, int u, int *time,int count){
   if(G == NULL){
      printf("Graph.c ERROR: calling visit() on a NULL Graph reference\n");
      exit(1);
   }
   if(S == NULL){
      printf("Graph.c ERROR: calling visit() on a NULL List reference\n");
      exit(1);
   }
   if(count == -1){
      printf("Yeaaaaa!\n");
      return;
   }
   (*time)++;
   G->dTime[u] = *time;
   G->color[u] = 'g';
   for(moveTo(G->list[u],0); getIndex(G->list[u]) >= 0; moveNext(G->list[u])){
      int v = getElement(G->list[u]);
      if(G->color[v] == 'w'){
         G->pie[v] = u;
         visit(G,S,v,time,count--);
      }
   }
   G->color[u] = 'b';
   (*time)++;
   G->fTime[u] = *time;
   append(S,u);
}

void reverseList(List L){
    if(length(L) == 0){
       return;
    }
    int tmp = front(L);
    deleteFront(L);
    reverseList(L);
    append(L,tmp);
}


//See sheet for description
void DFS(Graph G, List S){
   if(G == NULL){
      printf("Graph.c ERROR: calling DFS() on a NULL Graph reference\n");
      exit(1);
   }
   if(S == NULL){
      printf("Graph.c ERROR: calling DFS() on a NULL List reference\n");
      exit(1);
   }
   for(int i = 1; i <= getOrder(G); i++){
      G->color[i] = 'w';
      G->pie[i] = NIL;
   }
   int count = length(S);
   int time = 0;
   for(moveTo(S,0); getIndex(S) >= 0; moveNext(S)){
      if(count-- == 0){
         int i = getElement(S);
         if(G->color[i] == 'w'){
            visit(G,S,i,&time,count);
         }
         break;
      }
      int i = getElement(S);
      if(G->color[i] == 'w'){
         visit(G,S,i,&time,count);
      }  
   }
   for(count = length(S)/2;count > 0;count--){
      deleteFront(S);
   }
   reverseList(S);
}

/*** Other operations ***/
//transpose() returns a reference to a new graph object
//representing the transpose of G
Graph transpose(Graph G){
   if(G == NULL){
      printf("Graph.c ERROR: calling transpose() on a NULL Graph reference\n");
      exit(1);
   }
   Graph trans = newGraph(getOrder(G));
   for(int i = 1; i <= getOrder(G); i++){
      if(length(G->list[i]) > 0){
         for(moveTo(G->list[i],0); getIndex(G->list[i]) >= 0; moveNext(G->list[i])){
            int data = getElement(G->list[i]);
            addArc(trans, data, i);
         }
      }
   }
   return trans;
}

//copyGraph() returns a reference to a new graph which is a copy of G
Graph copyGraph(Graph G){
   if(G == NULL){
      printf("Graph.c ERROR: calling copyGraph() on a NULL Graph reference\n");
      exit(1);
   }
   Graph C = newGraph(getOrder(G));
   printGraph(stdout,C);
   for(int i = 1; i <= getOrder(G); i++){
      C->list[i] = copyList(G->list[i]);
      C->pie[i] = G->pie[i];
      C->dTime[i] = G->dTime[i];
      C->fTime[i] = G->fTime[i];
      C->color[i] = G->color[i];
   }
   C->size = G->size;
   C->order = G->order;
   return C;
}


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




