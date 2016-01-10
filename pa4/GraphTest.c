

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"
#include"Fly.h"

int main(int argc, char* argv[]){
   
   
/*   List L = newList();
   append(L,5);
   printf("length: %d\n", length(L));
  */
/*   Fly F = newFly(5);
   List B = returnList(F,L);
   printList(B); 
   printf("\n"); */
 
   Graph G = newGraph(12);
   //addEdge(G);
   /*addEdge(G,1,3);
   addEdge(G,1,2);
   addEdge(G,2,4);
   addEdge(G,2,5);   //graph One
   addEdge(G,4,5);
   addEdge(G,6,5);
   addEdge(G,6,4);*/

   addEdge(G,1,2);
   addEdge(G,2,3);
   addEdge(G,2,8);
   addEdge(G,3,8);   //graph Two
   addEdge(G,3,4);
   addEdge(G,8,4);
   addEdge(G,8,12);
   addEdge(G,12,4);
   addEdge(G,8,4);
   addEdge(G,4,9);
   addEdge(G,5,6);
   addEdge(G,10,6);
   addEdge(G,6,7);
   addEdge(G,6,11);
   addEdge(G,7,11);




   //printf("getSize():%d\n", getSize(G));
   /*addArc(G,1,2);
   addArc(G,3,2);
   addArc(G,7,3);
   addArc(G,6,3);
   addArc(G,7,6);
   addArc(G,11,7);
   addArc(G,10,11);
   addArc(G,6,10);
   addArc(G,10,9);
   addArc(G,6,9);
   addArc(G,6,5);
   addArc(G,9,5);
   addArc(G,3,5);
   addArc(G,2,5);
   addArc(G,5,4);
   addArc(G,4,1);
   addArc(G,9,4);
   addArc(G,8,4);
   addArc(G,9,8);*/

   //printf("getSize():%d\n", getSize(G));

   printGraph(stdout, G);
   //printf("\n");
   //printf("getSource():%d\n", getSource(G));
   BFS(G,1);
   //printf("getSource():%d\n", getSource(G));
   for(int i = 1;i <= 12; i++){
      printf("Dis: %d Parent():%d \n",getDist(G,i), getParent(G,i));
   }
   List darkpath = newList();
   for(int i = 1; i <= 12;i++){ 
      printf("i: %d\n", i);
      getPath(darkpath,G,i);
      printf("distance from 3 to %d is %d\n", i, length(darkpath));
      printf("Shortest path 3-%d path is: ", i);
      printList(stdout,darkpath);
      printf("\n");
      clear(darkpath);
      
   }


   return(0);
}
