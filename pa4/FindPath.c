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

int main(int argc, char * argv[]){

   int count = 0;
   FILE *in, *out;
   char line[MAX_LEN];
//   char tokenlist[MAX_LEN];
   char *token;
   int graphOrder = 0;
   int edge[2];
   char blank[] = " ";
   int source = 0;
   int destination = 0;
   Graph G = NULL;
   List L = newList();

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
      //fprintf(out,"%d:%s\n",count,line);
         token = strtok(line, blank);
         edge[0] = atoi(token);
	 token = strtok(NULL, blank);
         edge[1] = atoi(token);
         if(edge[0] == 0 && edge[1] == 0){
            break;
         }
         addEdge(G,edge[0],edge[1]);
   }
   printGraph(out,G);
   fprintf(out, "\n");

      while( fgets(line, MAX_LEN, in) != NULL)  {
      count++;
      //fprintf(out,"%d:%s\n",count,line);
         token = strtok(line, blank);
         source = atoi(token);
		 token = strtok(NULL, blank);
         destination = atoi(token);
         if(source == 0 && destination == 0){
            break;
         }
         BFS(G,source);
         getPath(L,G,destination);
         if(front(L) == -1){
            fprintf(out,"Distance from %d to %d is infinity\n",source,destination);
            fprintf(out,"No path %d-%d exists",source, destination);
         }else{ 
	    fprintf(out,"Distance from %d to %d is %d\n",source,destination,length(L)-1);
            fprintf(out,"Shortest path %d-%d path is: ",source, destination);
            printList(out,L);
         }
         fprintf(out,"\n");
	 clear(L);
	 fprintf(out,"\n");
	 fflush(out);
   }
   

   /* close files */
   fclose(in);
   fclose(out);

   return(0);
}


