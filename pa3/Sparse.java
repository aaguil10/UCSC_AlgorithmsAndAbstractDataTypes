//////////////////////////////////////////////////////////////////////////////
// FileIO.java
// Illustrates file IO and tokenization using String.split()
//////////////////////////////////////////////////////////////////////////////
//Alejandro Aguilar aaguil10

import java.io.*;
import java.util.Scanner;

public class Sparse{
   public static void main(String[] args) throws IOException{
      Scanner in = null;
      PrintWriter out = null;
      String line = null;
      int lineNumber = 0;

      if(args.length < 2){
         System.out.println("Usage: FileIO infile outfile");
         System.exit(1);
      }

      in = new Scanner(new File(args[0]));
      out = new PrintWriter(new FileWriter(args[1]));

      Matrix A = null;
      Matrix B = null;
      int n = 0;
      int a = 0;
      int b = 0;
      int count = 0;

      while( in.hasNextLine() ){
         lineNumber++;
         line = in.nextLine()+" ";    // add extra space so split works right
         if(lineNumber == 1){
            int[] val = getValues(line);
            n = val[0];
            a = val[1];
            b = val[2];
            A = new Matrix(n);
            B = new Matrix(n);

         }else{
            if(a < -1){
               count++; 
            }
            if(b < -1){
               break;
            }
            if(count == 0){
               readLine(line,A);
               a--;   
            }
            if(count > 0 ){
               readLine(line,B);
               b--;
            }
         }
      }
      out.println("A has " + A.getNNZ() + " non-zero entries:");
      out.println(A);

      out.println("B has " + B.getNNZ() + " non-zero entries:");
      out.println(B);

      out.println("(1.5)*A =");
      Matrix C = A.scalarMult(1.5);
      out.println(C);

      out.println("A+B =");
      Matrix D = A.add(B);
      out.println(D);

      out.println("A+A =");
      Matrix E = A.add(A);
      out.println(E);

      out.println("B-A =");
      Matrix F = B.sub(A);
      out.println(F);

      out.println("A-A =");
      Matrix G = A.sub(A);
      out.println(G);

      out.println("Transpose(A) =");
      Matrix H = A.transpose();
      out.println(H);

      out.println("A*B =");
      Matrix I = A.mult(B);
      out.println(I);

      out.println("B*B =");
      Matrix J = B.mult(B);
      out.println(J);

      out.println();

      in.close();
      out.close();
   }

   static void readLine(String line, Matrix A){
      int row;
      int column;
      double data;

      String[] values  = line.split("\\s+");
      if(values.length == 3){
         row = Integer.parseInt(values[0]);
         column = Integer.parseInt(values[1]);
         data = Double.parseDouble(values[2]);
         A.changeEntry(row,column,data);
      }


   }


   static int[] getValues(String line){
      String[] values = line.split("\\s+");;
      int[] thethree = new int[3];
      int j = 0;
      for(int i = 0; i < values.length;i++){
         if(values[i] != " "){
            System.out.println(values[i]);
            thethree[j++] =  Integer.parseInt(values[i]);
         }
      }
      return thethree;
   }







}
