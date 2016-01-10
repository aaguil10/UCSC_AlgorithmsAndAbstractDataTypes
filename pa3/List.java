//Alejandro Aguilar aaguil10@ucsc.edu


class List{

   private class Node{
      //fileds
      private Object data;
      private int index;
      private Node next;
      private Node prev;

      //Constructor
      Node(Object _data){
         data = _data;
         next = null;
         prev = null;
         index = -1;
      }

      public boolean equals(Object rhs){
         Node R = null;
         boolean eq = false;
         int i, n, m;

         if(rhs instanceof Node){
            R = (Node) rhs;
            eq = (this.data.equals(R.data));

          }
          return eq;
       }

   }


//fileds
private int length;
private Node front;
private Node back;
private Node cursor;

// Constructor
// Creates a new empty list.
List(){
   length = 0;
   front = null;
   back = null;
   cursor = null;

} 

// Access functions
// Returns number of elements in this list.
int length(){
   return length; 
}

// Returns the index of the cursor element in this list, or
// returns -1 if the cursor element is undefined.
int getIndex(){
   if(cursor == null){
      return -1;
   }
   return cursor.index;
}
 
// Returns front element in this list. Pre: length()>0
Object front(){
   if(length  <= 0){
      System.err.println("ERROR: In front() length <= 0");
      System.exit(1);
   }
   return front.data;
}

// Returns back element in this List. Pre: length()>0
Object back(){
   if(length <= 0){
      System.err.println("ERROR: In back() length <= 0");
      System.exit(1);
   }
   return back.data;
}

// Returns cursor element in this list.
// Pre: length()>0, getIndex()>=0
Object getElement(){
   if(length <= 0){
      System.err.println("ERROR: In getElement(), length <= 0");
      System.exit(1);
   }
   if(cursor == null){
      System.err.println("ERROR: In getElement(), cursor == -1");
      System.exit(1);
   }
   return cursor.data;
} 

// Returns true if this List and L are the same integer
// sequence. The cursor is ignored in both listsi.
public boolean equals(Object X){
   boolean flag = false;
   List L;
   if(X instanceof List){
      L = (List) X;
      flag = true;
      Node N = this.front;
      Node M = L.front;

      if(this.length == L.length){
         while(flag && N != null){
            flag = (N.data.equals(M.data));
            N = N.next;
            M = M.next;
         }
         if(flag == false){
         }
         return flag;
       }else{
         return false;
      }
   }
   return flag;
}



// Manipulation procedures
// Re-sets this List to the empty state.
void clear() {
   length = 0;
   front = null;
   back = null;
   cursor = null;
}

// If 0<=i<=length()-1, moves the cursor to the element
// at index i, otherwise the cursor becomes undefined.
void moveTo(int i){
   if(i < 0 || i > length - 1){
      cursor.index = -1;
   }
   Node curr = front;
   while(curr.index != i){
      curr = curr.next;
   } 
   cursor = curr;
} 

// If 0<getIndex()<=length()-1, moves the cursor one step toward the
// front of the list. If getIndex()==0, cursor becomes undefined.
// If getIndex()==-1, cursor remains undefined. This operation is
// equivalent to moveTo(getIndex()-1).
void movePrev(){
   if(cursor == null){
      return;
   }
   if(cursor.index > length - 1){
      System.err.println("ERROR: In movePrev, cursor index >= length");
      System.exit(1);
   }
   if(cursor.index == 0){
      cursor = null;
      return;
   }
   cursor = cursor.prev;
}

// If 0<=getIndex()<length()-1, moves the cursor one step toward the
// back of the list. If getIndex()==length()-1, cursor becomes
// undefined. If index==-1, cursor remains undefined. This
// operation is equivalent to moveTo(getIndex()+1).
void moveNext() {
   if(cursor == null){
      return;
   }
   if(cursor.index > length - 1){
      System.err.println("ERROR: In List.moveNext(),cursor.index > length - 1");
      System.exit(1);
   }
   if(cursor.index == length - 1){
      cursor = null;
      return;
   }
      cursor = cursor.next;
}

// Inserts new element before front element in this List.
void prepend(Object data){
   Node tmp = new Node(data);
   if(front == null){
      tmp.index = 0;
      front = tmp;
      back = tmp;
      length++;
      return;
   }
   tmp.next = front;
   front.prev = tmp;
   front = tmp;
   int i = 0;
   Node curr = front;
   while(curr.next != null){
      curr.index = i++;
      curr = curr.next;
   }
   curr.index = i;
   length++;
}

// Inserts new element after back element in this List.
void append(Object data){
   Node tmp = new Node(data);
      if(back == null){
      tmp.index = 0;
      front = tmp;
      back = tmp;
      length++;
      return;
   }
   tmp.prev = back;
   tmp.index = back.index + 1;
   back.next = tmp;
   back = tmp;
   length++;
}

// Inserts new element before cursor element in this
// List. Pre: length()>0, getIndex()>=0
void insertBefore(Object data){
   if(cursor == null){
      System.err.println("ERROR: In List.insertBefore(), cursor is undefined");
      System.exit(1);
   }
   if(length <= 0){
      System.err.println("ERROR: In List.insertBefore(), length <= 0");
      System.exit(1);
   }

   Node tmp = new Node(data);
   tmp.next = cursor;        //ajusting pointers
   if(cursor != front){
      tmp.prev = cursor.prev;
      cursor.prev.next = tmp;
      cursor.prev = tmp;

   }else{
      cursor.prev = tmp;
      front = tmp;
   }
   
   int i = cursor.index;    //Updating index
   Node curr = tmp;
   while(curr.next != null){
      curr.index = i++;
      curr = curr.next;
   }
   curr.index = i;
   length++;
}

// Inserts new element after cursor element in this
// List. Pre: length()>0, getIndex()>=0
void insertAfter(Object data){
   if(cursor == null){
      System.err.println("ERROR: In List.insertAfter(), cursor is undefined");
      System.exit(1);
   }
   if(length <= 0){
      System.err.println("ERROR: In List.insertAfter(), length <= 0");
      System.exit(1);
   }
   Node tmp = new Node(data);
   tmp.prev = cursor;        //ajusting pointers
   if(cursor != back){
      tmp.next = cursor.next;
      cursor.next.prev = tmp;
      cursor.next = tmp;
   }else{
      cursor.next = tmp;
      tmp.index = cursor.index +1;
      back = tmp;
      length++;
      return;
   }
   int i = cursor.index + 1;    //Updating index
   Node curr = cursor.next;
   while(curr.next != null){
      curr.index = i++;
      curr = curr.next;
   }
   curr.index = i;
   length++;
}

// Deletes the front element in this List. Pre: length()>0
void deleteFront(){
   if(length <= 0){
      System.err.println("ERROR: In List.deleteFront(), length <= 0");
      System.exit(1);
   }
   if(front == back){
      front = null;
      back = null;
      length--;
      return;
   }
   front = front.next;
   front.prev = null;
   int i = 0;   
   Node curr = front;
   while(curr.next != null){
      curr.index = i++;
      curr = curr.next;
   }
   curr.index = i;
   length--;
}

// Deletes the back element in this List. Pre: length()>0
void deleteBack(){
   if(length <= 0){
      System.err.println("ERROR: In List.deleteBack(), length <= 0");
      System.exit(1);
   }
   back = back.prev;
   back.next = null;
   length--;
}

// Deletes cursor element in this List. Cursor is undefined after this
// operation. Pre: length()>0, getIndex()>=0
void delete(){
   if(cursor == null){
      System.err.println("ERROR: In List.delete(), cursor is unidentifed");
      System.exit(1);
   }
   if(length <= 0){
      System.err.println("ERROR: In List.delete(), length <= 0");
      System.exit(1);
   }
   if(cursor == front){
      cursor = null;
      deleteFront();
      return;
   }
   if(cursor == back){
      cursor = null;
      deleteBack();
      return;
   }
   Node tmp = cursor.prev;
   tmp.next = cursor.next;
   int i = tmp.index;
   Node curr = tmp;
   while(curr.next != null){
      curr.index = i++;
      curr = curr.next;
   }
   curr.index = i;
   cursor = null;
   length--;
}



// Other methods
//Overides Object's toString method. Creates a string
//consisting of a space separated sequence of integers
//with front on the left and back on the right. The
//cursor is ignored.
public String toString(){
   String str = "";
   for(Node N = front; N != null; N= N.next){
      str += N.data + " ";
   }
   return str;
}


}
