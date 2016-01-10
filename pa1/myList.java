


public class myList{
   public static void main(String[] args){
      List A = new List();
      A.append(23);
      A.moveTo(0);
      for(int i = 1; i <= 10; i++){
         A.insertAfter(i);
      }
       A.moveTo(4);
       A.insertAfter(345421);
      System.out.println(A.front());
      System.out.println(A);
      System.out.println(23%1);
      /*List B = A.copy();

      A.moveTo(4);
      A.insertBefore(22);
      A.insertAfter(33);
      A.movePrev();
      A.delete();
      A.deleteFront();
      A.deleteBack();
      List C = A.copy(); 
      System.out.println(A.equals(B));

      for(A.moveTo(0); A.getIndex() >= 0; A.moveNext()){
         System.out.println("ElementA: " + A.getElement());
         System.out.println("IndexA: " + A.getIndex());
      }
      
      for(B.moveTo(0); B.getIndex() >= 0; B.moveNext()){
         System.out.println("ElementB: " + B.getElement());
         System.out.println("IndexB: " + B.getIndex());
      }*/



   }


}
