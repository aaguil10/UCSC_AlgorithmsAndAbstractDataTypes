//Alejandro Aguilar aaguil10@ucsc.edu

#include<stdio.h>
#include<stdlib.h>
#include "List.h"

typedef struct NodeObj{
   int data;
   struct NodeObj* prev;
   struct NodeObj* next;

} NodeObj;

typedef struct CursorObj{
   Node pointer;
   int index;
} CursorObj;

typedef struct ListObj{
   Node front;
   Node back;
   int length;
   Cursor cruz;
} ListObj;





// Constructors-Destructors ---------------------------------------------------
Node newNode(int dat){
   Node myNode = malloc(sizeof(Node));
   myNode->data = dat;
   myNode->prev = NULL;
   myNode->next = NULL;
   return myNode;
}

Cursor newCursor(void){
   Cursor myCursor = malloc(sizeof(Cursor));
   myCursor->pointer = NULL;
   myCursor->index = -1;
   return myCursor;
}


List newList(void){
   List myList = malloc(sizeof(List));
   myList->front = NULL;
   myList->back = NULL;
   myList->length = 0;
   myList->cruz = newCursor();
   return myList;
}

void freeNode(Node* pN){
   if(pN != NULL && *pN != NULL){
      free(*pN);
      *pN = NULL;
   }
}

void freeCursor(Cursor* pC){
   if(pC != NULL && *pC != NULL){
      free(*pC);
      *pC = NULL;
   }

}

void freeList(List* pL){
   if(pL != NULL && *pL != NULL){
      freeCursor(&(*pL)->cruz); 
      free(*pL);
      *pL = NULL;
    }
}

// Access functions -----------------------------------------------------------
int length(List L){
   if(L == NULL){
      printf("List ERROR: calling length() on a NULL List reference");
      exit(1);
   }
   return L->length;
}

int getIndex(List L){
   if(L == NULL){
      printf("List ERROR: calling getIndex() on a NULL List reference");
      exit(1);
   }
   return L->cruz->index;
}

int front(List L){
   if(L == NULL){
      printf("List ERROR: calling front() on a NULL List reference");
      exit(1);
   }
   if(L->length <= 0){
      printf("List ERROR: calling front() when length <= 0");
      exit(1);
   }
   return L->front->data;
}

int back(List L){
   if(L == NULL){
      printf("List ERROR: calling back() on a NULL List reference");
      exit(1);
   }
   if(L->length <= 0){
      printf("List ERROR: calling back() when length <= 0");
      exit(1);
   }

   return L->back->data;;
}

int getElement(List L){
   if(L == NULL){
      printf("List ERROR: calling getElement() on a NULL List reference");
      exit(1);
   }
   if(L->length <= 0){
      printf("List ERROR: calling getElement() when length <= 0");
      exit(1);
   }
   if(L->cruz == NULL){
      printf("List ERROR: calling getElement() when cruz == NULL");
      exit(1);
   }
   return L->cruz->pointer->data;
}

int equals(List A, List B){
   if(A == NULL){
      printf("List ERROR: calling equals() on a NULL List A reference");
      exit(1);
   }
   if(B == NULL){
      printf("List ERROR: calling equals() on a NULL List B reference");
      exit(1);
   }
   int flag = 1;//bool true
   Node N = A->front;
   Node M = B->front;

   if(A->length == B->length){
      while(flag == 1 && N != NULL){
         flag = (N->data == M->data);
         N = N->next;
         M = M->next;
      }
      return flag;
   }else{
      return 0;
   }
}

// Manipulation procedures ----------------------------------------------------
void clear(List L){
   if(L == NULL){
      printf("List ERROR: calling clear() on a NULL List reference");
      exit(1);
   }
   L->cruz->pointer = NULL;
   L->cruz->index = -1;
      if(L->front != NULL){
         while(L->front->next != NULL){
            deleteFront(L);
         }
         freeNode(&L->front);
         L->front = NULL;
         L->back = NULL;
         L->length = 0;
   }
}

void moveTo(List L, int i){
   if(L == NULL){
      printf("List ERROR: calling moveTo() on a NULL List reference");
      exit(1);
   }
   if(L->cruz->index == -1){
      return;
   }
   if(i < 0 || i > L->length - 1){
      L->cruz->pointer = NULL;
      L->cruz->index = -1;
   }
   L->cruz->pointer = L->front;
   L->cruz->index = 0;
   while(L->cruz->index != i){
      L->cruz->pointer = L->cruz->pointer->next;
      L->cruz->index++;
   }
}

void movePrev(List L){
   if(L == NULL){
      printf("List ERROR: calling movePrev() on a NULL List reference");
      exit(1);
   }
   if(L->cruz->pointer == NULL){
      return;
   }
   if(L->cruz->index > L->length -1){
      printf("List ERROR: calling movePrev() when L->cruz->index > L->length -1");
      exit(1);
   }
   if(L->cruz->index == 0){
      printf("movePrev() index == 0\n");
      L->cruz->pointer = NULL;
      L->cruz->index = -1;
      return;
   }
   L->cruz->pointer = L->cruz->pointer->prev;
   L->cruz->index--;
}

void moveNext(List L){
   if(L == NULL){
      printf("List ERROR: calling moveNext() on a NULL List reference\n");
      exit(1);
   }
   if(L->cruz->pointer == NULL){
      return;
   }
   if(L->cruz->index > L->length -1){
      printf("List ERROR: calling moveNext() when L->cruz->index > L->length -1\n");
      exit(1);
   }
   if(L->cruz->index == L->length - 1){
      L->cruz->pointer = NULL;
      L->cruz->index = -1;
      return;
   }
   L->cruz->pointer = L->cruz->pointer->next;
   L->cruz->index++;
}

void prepend(List L, int data){
   if(L == NULL){
      printf("List ERROR: calling prepend() on a NULL List reference");
      exit(1);
   }
   Node tmp = newNode(data);
   if(L->front == NULL){
      L->front = tmp;
      L->back = tmp;
      L->length++;
      return;
   }
   tmp->next = L->front;
   L->front->prev = tmp;
   L->front = tmp;
   if(L->cruz->index != -1){
      L->cruz->index++;
   }
   L->length++;

}

void append(List L, int data){
   if(L == NULL){
      printf("List ERROR: calling append() on a NULL List reference");
      exit(1);
   }
   Node tmp = newNode(data);
   if(L->back == NULL){
      L->front = tmp;
      L->back = tmp;
      L->length++;
      return;
   }
   tmp->prev = L->back;
   L->back->next = tmp;
   L->back = tmp;
   L->length++;
}

void insertBefore(List L, int data){
   if(L == NULL){
      printf("List ERROR: calling insertBefore() on a NULL List reference");
      exit(1);
   }
   if(L->cruz->index == -1){
      printf("List ERROR: calling insertBefore() on a NULL Cursor reference");
      exit(1);
   }
   if(L->length <= 0){
      printf("List ERROR: calling insertBefore() when length <= 0");
      exit(1);
   }
   Node tmp = newNode(data);
   //tmp->next = L->cruz->pointer;
   if(L->cruz->pointer != L->front){
      tmp->next = L->cruz->pointer;
      tmp->prev = L->cruz->pointer->prev;
      L->cruz->pointer->prev->next = tmp;
      L->cruz->pointer->prev = tmp;
   }else{
      L->cruz->pointer->prev = tmp;
      tmp->next = L->front;
      L->front = tmp;
      L->length++;
      return;
   }
   L->cruz->index++;
   L->length++;

}

void insertAfter(List L, int data){
   if(L == NULL){
      printf("List ERROR: calling insertAfter() on a NULL List reference");
      exit(1);
   }
   if(L->cruz->index == -1){
      printf("List ERROR: calling insertAfter() on a NULL Cursor reference");
      exit(1);
   }
   if(L->length <= 0){
      printf("List ERROR: calling insertAfter() when length <= 0");
      exit(1);
   }
   Node tmp = newNode(data);
   //tmp->next = L->cruz->pointer;
   if(L->cruz->pointer != L->back){
      tmp->prev = L->cruz->pointer;
      tmp->next = L->cruz->pointer->next;
      L->cruz->pointer->next->prev = tmp;
      L->cruz->pointer->next = tmp;
   }else{
      L->cruz->pointer->next = tmp;
      tmp->prev = L->back;
      L->back = tmp;
      L->length++;
      return;
   }
   L->length++;
}

void deleteFront(List L){
   if(L == NULL){
      printf("List ERROR: calling deleteFront() on a NULL List reference");
      exit(1);
   }
   if(L->length <= 0){
      printf("List ERROR: calling deleteFront() when length <= 0");
      exit(1);
   }
   if(L->cruz->index != -1){
      if(L->cruz->pointer == L->front){
         L->cruz->pointer = NULL;
         L->cruz->index = -1;
      }else{
         L->cruz->index--;
      }
   }
   if(L->front != L->back){
      L->front = L->front->next;
      freeNode(&L->front->prev);
      //L->front->prev = NULL;
   }else{
      freeNode(&L->front);
      //L->front = NULL;
      //L->back = NULL;
   }
   L->length--;
}

void deleteBack(List L){
   if(L == NULL){
      printf("List ERROR: calling deleteBack() on a NULL List reference");
      exit(1);
   }
   if(L->length <= 0){
      printf("List ERROR: calling deleteBack() when length <= 0");
      exit(1);
   }
   if(L->cruz->pointer == L->back){
      L->cruz->pointer = NULL;
      L->cruz->index = -1;
   }
   if(L->back != L->front){
      L->back = L->back->prev;
      freeNode(&L->back->next);
      L->back->prev = NULL;
   }else{
      freeNode(&L->back);
      L->back = NULL;
      L->front = NULL;
   }
   L->length--;
}

void delete(List L){
   if(L == NULL){
      printf("List ERROR: calling delete() on a NULL List reference");
      exit(1);
   }
   if(L->cruz->index == -1){
      printf("List ERROR: calling delete() on a NULL Cursor reference");
      exit(1);
   }
   if(L->length <= 0){
      printf("List ERROR: calling delete() when length <= 0");
      exit(1);
   }
   if(L->length != 0){
      if(L->cruz->pointer == L->back){
         deleteBack(L);
         L->length--;
         return;
      }
      if(L->cruz->pointer == L->front){
         deleteFront(L);
         L->length--;
         return;
      }
      Node tmp = L->cruz->pointer->prev;
      tmp->next = L->cruz->pointer->next;
      freeNode(&tmp->next->prev);
      tmp->next->prev = tmp;
   }else{
      deleteFront(L);
   }
   L->length--;
}

// Other operations -----------------------------------------------------------
void printList(FILE* out, List L){
   if(L == NULL){
      printf("List ERROR: calling printList() on a NULL List reference");
      exit(1);
   }
   if(L->front == NULL){
      printf("There are no items in the list\n");
   }
   for(Node N = L->front;N != NULL; N = N->next){
      fprintf(out, "%d ",N->data);
   }
   //fprintf(out,"\n");
}

List copyList(List L){
   if(L == NULL){
      printf("List ERROR: calling copyList() on a NULL List reference");
      exit(1);
   }
   List A = newList();
   Node N = L->front;
   while(N != NULL){
      append(A, N->data);
      N = N->next;
   }
   return A;
}



