

class QueueTest {
   public static void main(String[] args){
   //Allocate several Queue Objects, and manipulate
   // them in various ways. Call each of the above
   // ADT operations at least once.
   // ... ... ...
      Queue line = new Queue();
      line.Enqueue(4);
      line.Enqueue(7);
      System.out.println(line.getFront());
      System.out.println(line.getLength());
      while(line.isEmpty() == false){
         line.Dequeue();
      }
      System.out.println(line.isEmpty());
 }
 }
