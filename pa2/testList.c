

#include <stdio.h>
#include <stdlib.h>
#include "List.h"

int main (int argc, char *argv[]){

   printf("Que Onda vato!\n");

   List myList = newList();
   for(int i = 0; i <= 10; i++){
      prepend(myList, i);
   }
   printList(stdout,myList);
   printf("Length: %d\n", length(myList));
   printf("Front: %d Back: %d\n", front(myList), back(myList));

   List copy = copyList(myList);

   /*moveTo(myList,length(myList)-1);
   movePrev(myList);
   printf("%d(%d) ", getIndex(myList), getElement(myList));*/
   
   moveTo(myList,0);
   insertBefore(myList,53059);
   insertAfter(myList,890000);
 for(moveTo(myList,0);getIndex(myList) >= 0;moveNext(myList)){
      printf("%d(%d) ", getIndex(myList), getElement(myList));
   }
   moveTo(copy,0);
   delete(copy);
   //List copy = copyList(myList);
   printf("\n");
   printList(stdout,copy);
   printList(stdout,myList);
   printf("Length: %d\n", length(copy));
   printf("Length: %d\n", length(myList));
   printf("Front: %d Back: %d\n", front(myList), back(myList));

   if(equals(myList,copy) == 1){
      printf("true\n");
   }else{
      printf("false\n");
   }

return (0);
}
 
