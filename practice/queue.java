// Queue.java
// An integer queue ADT

 class Queue {

    private class Node {
       // Fields
       int data;
       Node next;

       // Constructor
       Node(int nData) {
       data = nData;
       }

       // toString: overrides Objects toString method
       //public String toString() {...}
    }

    // Fields
    private Node front;
    private Node back;
    private int length;

   // Constructors
   Queue() {
      front = null;
      back = null;
      length = 0;
   }

   // Access functions
   int getFront() {
      if(front == null){
         System.err.println("getFront: Error queue is empty!");
         System.exit(1);
      }
      return front.data;
   }

   int getLength() {
      return length;
   }

   boolean isEmpty() {
      return front == null;
   }


   // Manipulation procedures
   void Enqueue(int data) {
      Node theOne = new Node(data);
      if(front == null){
         front = theOne;
         back = theOne;
      }else{
         theOne.next = front;
         front = theOne;
      }
      length++;
   }

   void Dequeue() {
      if(front == null){
         System.err.println("Dequeue: Error queue is empty!");
         System.exit(1);
      }
      if(front.next == null){
         front = null;
         length--;
         return;
      }
      Node curr = front;
      Node prev = curr;
      while(curr.next != null){
      prev = curr;
      curr = curr.next;

      }
      prev.next = null;
      length--;
   }
 
   // other methods
   // toString: Overrides Object's toString method.
   //public String toString() {...}
}


