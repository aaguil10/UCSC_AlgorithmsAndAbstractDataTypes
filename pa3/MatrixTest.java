//Alejandro Aguilar aaguil10


class MatrixTest{

   public static void main(String[] args){
      System.out.println("hello world");

      //testing change entry and print
      Matrix neo = new Matrix(2);
      Matrix b = new Matrix(2);
      neo.changeEntry(1,1,1.0);
      neo.changeEntry(1,2,2.0);
      b.changeEntry(1,1,2.1);
      b.changeEntry(2,2,6.2);
      b.changeEntry(2,2,0);
      //neo.changeEntry(1,5,2.3);
      //neo.changeEntry(5,2,3.0);
      //neo.changeEntry(5,5,4.0);
      //neo.changeEntry(3,4,5.0);
      neo.changeEntry(2,2,3.0);
      //neo.changeEntry(2,1,4.0);
      //neo.changeEntry(1,2,9.9);
      //Matrix morpheus = neo.transpose();
      //Matrix trinity = neo.copy();
      //trinity.makeZero();
      Matrix theMachine = neo.mult(b);
      //System.out.println(neo);
      //System.out.println(morpheus);
      //System.out.println(trinity);
      //System.out.println(theMachine);
      //trinity = neo.scalarMult(5);
      //neo = neo.sub(trinity);
      System.out.println(neo);
      System.out.println(b);
      System.out.println(theMachine);
      //System.out.println(trinity);




   }





}
