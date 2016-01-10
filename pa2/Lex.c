//Alejadro Aguilar aaguil10@ucsc.edu

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "List.h"

#define MAX_LEN 160
#define MAX_LINES 160

List sortArray(char data[MAX_LINES][MAX_LEN], int count){
   if(data == NULL){
      printf("Lex Error: calling sortArray() on NULL data reference\n");
      exit(1);
   }
   List myList = newList();
   append(myList, 0);
   char *key = NULL;
   for(int j = 1; j < count; j++){
      key = data[j];
      moveTo(myList, j - 1);
      if(getIndex(myList) >= 0){
         if(strcmp(key,data[getElement(myList)]) >= 0){
            while(strcmp(key,data[getElement(myList)]) >= 0 
                  && getIndex(myList) < length(myList) - 1){
               moveNext(myList);
            }
            if(strcmp(key,data[getElement(myList)]) < 0){
               insertBefore(myList,j);
            }else{
               insertAfter(myList,j);
            }
         }else{
            while(strcmp(key,data[getElement(myList)]) < 0
                  && getIndex(myList) > 0){
               movePrev(myList);
            }
            if(strcmp(key,data[getElement(myList)]) >= 0){
               insertAfter(myList,j);
            }else{
               insertBefore(myList,j);
            }
         }
      }else{
         printf("Lex ERROR: In sortArray(), cursor is unidetified");
         exit(1);
      }


   }
   return myList;
}


int main(int argc, char * argv[]){

   int count = 0;
   FILE *in, *out;
   char line[MAX_LEN];

   // check command line for correct number of arguments
   if(argc != 3){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }
   
   // open files for reading and writing
   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");
   if(in == NULL){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }
   if(out == NULL){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }
   
   //Count number of lines in file
   while(fgets(line, MAX_LEN, in) != NULL)  {
      count++;
   }
   fclose(in);

   //Store each line in dara[line][chars]
   FILE *myFile = fopen(argv[1], "r");
   char data[count][MAX_LEN];
   int i = 0;
   while( fgets(line, MAX_LEN, myFile) != NULL)  {
      strcpy(data[i++],line);
   }
   fclose(myFile);

   List myList;
   myList = sortArray(data, count);

   //Print data
   for(moveTo(myList,0); getIndex(myList)>=0; moveNext(myList)){
      fprintf(out,"%s", data[getElement(myList)]);
   }
   
   /* close files */
   fclose(out);

   clear(myList);

   return(0);
}

