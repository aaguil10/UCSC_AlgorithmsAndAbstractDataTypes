//Alejandro Aguilar aaguil10
//GraphTest.c

#include<stdio.h>
#include<stdlib.h>
#include"List.h"
#include"Graph.h"


int main(int argc, char* argv[]){
   printf("Que ondaDAdA!.!\n");
   Graph A = newGraph(8);
   addArc(A,1,2);
   addArc(A,2,3);
   addArc(A,3,4);
   addArc(A,3,7);
   addArc(A,4,3);
   addArc(A,4,8);
   addArc(A,8,8);
   addArc(A,7,8);
   addArc(A,6,7);
   addArc(A,7,6);
   addArc(A,2,6);
   addArc(A,5,6);
   addArc(A,2,5);
   addArc(A,5,1);

   printGraph(stdout,A);

   /*List L = newList();
   //append(L,1);
   //append(L,2);
   //append(L,3);
   printList(stdout,L);
   fflush(stdout);
   printf("length: %d\n",length(L));
   fflush(stdout);
   List cp = copyList(L);
   printList(stdout,cp);*/

   


   Graph B = transpose(A);
   printGraph(stdout,B);

   List L = newList();
   for(int i = 1; i <= getOrder(A); i++){
   append(L,i);
   }


   DFS(A,L);
   /*printf("List: ");
   printList(stdout, L);
   printf("\n");*/

   fprintf(stdout, "x:  d  f  p\n");
   for(int i = 1; i <= getOrder(A); i++){
      fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(A, i), getFinish(A, i), getParent(A, i));
   }
   fprintf(stdout, "\n");
   printList(stdout, L);
   fprintf(stdout, "\n");


   return 0;
}

