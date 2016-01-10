//////////////////////////////////////////////////////////////////////////////
// FileIO.java
// Illustrates file IO and tokenization using String.split()
//////////////////////////////////////////////////////////////////////////////
//Alejandro Aguilar aaguil10@ucsc.edu


import java.io.*;
import java.util.Scanner;

class Lex{
   public static void main(String[] args) throws IOException{
      Scanner in = null;
      PrintWriter out = null;
      String line = null;
      String[] token = null;
      int lineNumber = 0;

      if(args.length < 2){
         System.err.println("Usage: FileIO infile outfile");
         System.exit(1);
      }

      in = new Scanner(new File(args[0]));
      out = new PrintWriter(new FileWriter(args[1]));

      while( in.hasNextLine() ){           //reads in each line into an array
         lineNumber++;
         in.nextLine();
      }
      in.close();
      String[] item = new String[lineNumber];
      in = new Scanner(new File(args[0]));
      int count = 0;
      while( in.hasNextLine() ){
         item[count++] = in.nextLine();
      }
      in.close();

      List myList = sortArray(item,lineNumber);
     
      for(myList.moveTo(0); myList.getIndex()>=0; myList.moveNext()){
         out.println(item[myList.getElement()]);
      }

      out.close();
   }

   public static List sortArray(String[] line, int nubele){
      List myList = new List();
      myList.append(0);
      int i = 0;
      String key;   
      for(int j = 1; j < nubele; j++){
         key = line[j];
         myList.moveTo(j - 1);
         if(myList.getIndex() >= 0){
            //moves corsor to the rigth until it hits something biger than it's
            //self
            if(key.compareTo(line[myList.getElement()]) >= 0){
               while(key.compareTo(line[myList.getElement()]) >= 0
                     && myList.getIndex() < myList.length()-1){
                  myList.moveNext();
               }
               if(key.compareTo(line[myList.getElement()]) < 0){
                  myList.insertBefore(j);
               }else{
                  myList.insertAfter(j);
               }
               //moves cursor to the left until it finds something smaller it's
               //self
            }else{
               while(key.compareTo(line[myList.getElement()]) < 0
                     && myList.getIndex() > 0){
                  myList.movePrev();
               }
               if(key.compareTo(line[myList.getElement()]) >= 0){
                  myList.insertAfter(j);
               }else{
                  myList.insertBefore(j);
               }
            }

         }else{
            System.err.println("In sortarray, cursor is unidentified");
            System.exit(1);
         } 

      }
      return myList;
 

   }


}
