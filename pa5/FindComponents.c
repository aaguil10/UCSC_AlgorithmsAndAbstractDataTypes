//-----------------------------------------------------------------------------
// FileIO.c
// Illustrates file input-output commands and text processing using the
// string functions strtok and strcat.
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Graph.h"

#define MAX_LEN 160


void printComponents(FILE *out,Graph G, List L){
   if(G == NULL){
      printf("FindComponents.c ERROR: In printComponents()");
      printf(" calling G on a NULL Graph reffrence\n");
      exit(1);
   }
   if(L == NULL){
      printf("FindComponents.c ERROR: In printComponents()");
      printf("calling List on a NULL list refrence\n");
      exit(1);
   }
   if(length(L) == 0){
      return;
   }
   moveTo(L,0);
   int count = 0;
   while(getIndex(L) >= 0){
      if(getParent(G,getElement(L)) == -1){
      count++;
      }
      moveNext(L);
   }
   fprintf(out,"G contains %d strongly connected components:\n",count);
   int comp = 1;
   moveTo(L,0);
   while(comp <= count){
      fprintf(out,"Component %d: ",comp);
      while(getIndex(L) >= 0 && getParent(G,getElement(L)) != -1){
         if(getParent(G,getElement(L)) != -1 && getIndex(L) >= 0){
            fprintf(out,"%d ",getElement(L));
            moveNext(L);
         }else{
            fprintf(out,"%d\n",getElement(L));
            moveNext(L);
            comp++;
            break;
         }
      }
      if(getParent(G,getElement(L)) == -1 && getIndex(L) >= 0){
            fprintf(out,"%d\n",getElement(L));
            moveNext(L);
            comp++;
            continue;
      }
      fprintf(out,"\n");
   }

}

void revList(List L){
   if(length(L) == 0){
      return;
   }
   int tmp = front(L);
   deleteFront(L);
   revList(L);
   append(L,tmp);
}

int main(int argc, char * argv[]){

   int count = 0;
   FILE *in, *out;
   char line[MAX_LEN];
   char *token;
   int graphOrder = 0;
   int edge[2];
   char blank[] = " ";
   Graph G = NULL;

   // check command line for correct number of arguments
   if( argc != 3 ){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
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
   
   /* read each line of input file, then count and print tokens */
   if(fgets(line, MAX_LEN, in) == NULL){
       printf("Unable to read first line of file");
       exit(1);	   
   }
   graphOrder = atoi(line);
   G = newGraph(graphOrder);
   while( fgets(line, MAX_LEN, in) != NULL)  {
      count++;
      token = strtok(line, blank);
      edge[0] = atoi(token);
      token = strtok(NULL, blank);
      edge[1] = atoi(token);
      if(edge[0] == 0 && edge[1] == 0){
         break;
      }
      addArc(G,edge[0],edge[1]);
   }
   printGraph(out,G);
   fprintf(out, "\n");
   List S = newList();
   for(int i = 1; i <= getOrder(G); i++){
      append(S, i);
   }
   DFS(G,S);
   Graph T = transpose(G);
   DFS(T,S);
   revList(S);
   printComponents(out,T,S);

   freeGraph(&G);   
   freeGraph(&T);
   freeList(&S);

   fclose(in);
   fclose(out);

   return(0);
}


