//Alejandro Aguilar aaguil10@ucsc.edu


class Matrix{

   private class Entry{

   //fields
   int column;
   double data;

    //constructor
    Entry(int _column, double _data){
       column = _column;
       data = _data;

    }

    public boolean equals(Entry X){
       return (this.column == X.column);
    }

    public String toString(){
       String str = "";
       str = "(" + column + ", " + data + ")";
       return str;
    }

   }

   //fileds
   int length;
   int NNZ;
   List[] rows;

   //constructor
   Matrix(int n){
      length = n;
      NNZ = 0;
      rows = new List[n];
      for(int i = 0; i < length; i++){
         rows[i] = new List();
      } 
   }

   //access functions
   int getSize(){
   // Returns n, the number of rows and columns of this Matrix
      return length;
	}
   
   int getNNZ(){
   // Returns the number of non-zero entries in this Matrix
      return NNZ;    
   }
   
   public boolean equals(Object x){
   // overrides Object's equals() method
      Matrix M = null;
      boolean eq = false;

      if(x instanceof Matrix){
         M = (Matrix) x;
         if(this.getSize() != M.getSize()){
            return false;
         }
         for(int i = 0; i < getSize();i++){
            boolean flag = true;
            if(rows[i].length() == M.rows[i].length()){
               rows[i].moveTo(0);
               M.rows[i].moveTo(0);
               while(flag && rows[i].getIndex() >= 0){
                  Entry a = (Entry) rows[i].getElement();
                  Entry b = (Entry) M.rows[i].getElement();
                  flag = a.equals(b);
                  rows[i].moveNext();
                  M.rows[i].moveNext();
               }
               return flag;
            }else{
               return false;
            }        
         }
         return false;
      }else{
         return false;
      } 
   }
 
   //Manipulation Procedures
   
   void makeZero(){
   // sets this Matrix to the zero state
      for(int i = 0; i < getSize(); i++){
         this.rows[i].clear();
      }
      length = 0;
      NNZ = 0;

   }
   
   Matrix copy(){
   // returns a new Matrix having the same entries as this Matrix
       Matrix theTwin = new Matrix(getSize());
       for(int i = 0; i < getSize(); i++){
           if(rows[i].length() > 0){
              for(rows[i].moveTo(0); rows[i].getIndex() >= 0; 
                  rows[i].moveNext()){
                 Entry leEntry = (Entry) rows[i].getElement();
                 theTwin.changeEntry(i+1,leEntry.column, leEntry.data);
              }
           }
       }
      return theTwin;
   }
   
   void changeEntry(int i, int j, double x){
   // changes ith row, jth column of this Matrix to x
   // pre: 1<=i<=getSize(), 1<=j<=getSize()
      
      if(i <= 0 || i > this.getSize()){
         System.err.println("changeEntry() ERROR: i<0 || i>this.getSize()");
         System.exit(1);
      }
      if(j <= 0 || j > this.getSize()){
         System.err.println("changeEntry() ERROR: j<0 || j>this.getSize()");
         System.exit(1);
      }
      if(x == 0){
         return;
      }
      Entry myEntry = new Entry(j,x);
      if(rows[i-1].length() == 0){
         rows[i-1].append(myEntry);
         NNZ++;
         return;
      }
      for(rows[i-1].moveTo(0); rows[i-1].getIndex() >= 0; rows[i-1].moveNext()){
         Entry leEntry = (Entry) rows[i-1].getElement();
            if(checkNext(rows[i-1]) == false){
               if(leEntry.column < myEntry.column){
                  rows[i-1].append(myEntry);
                  NNZ++;
                  return;
               } 
                if(leEntry.column == myEntry.column){
                  this.replaceEntry(myEntry, i);
                  return;
               }
               if(leEntry.column > myEntry.column){
                  rows[i-1].insertBefore(myEntry);
                  NNZ++;
                  return;
               }
            }else{
               if(leEntry.column < myEntry.column){
                  continue;
               }
               if(leEntry.column == myEntry.column){
                   replaceEntry(myEntry, i);
                   return;
               }
               if(leEntry.column > myEntry.column){
                  rows[i-1].insertAfter(myEntry);
                  NNZ++;
                  return;
               }
            }
      }
   }
   
    private void replaceEntry(Entry myEntry, int i){
       Entry leEntry = (Entry) rows[i-1].getElement();
       if(myEntry.data == 0){
          rows[i-1].delete();
          return;
       }
       leEntry.column = myEntry.column;
       leEntry.data = myEntry.data;
       
    }

    private boolean checkNext(List A){
       //Returns true if there false if next is null
       if(A.getIndex() < 0){
          System.err.println("In checkNext(), cursor == null");
          System.exit(1);
       }
       A.moveNext();
       if(A.getIndex() < 0){
          A.moveTo(A.length()-1);
          return false;
       }else{
          A.movePrev();
          return true;
       }
    }


    Matrix scalarMult(double x){
    // returns a new Matrix that is the scalar product of this Matrix with x
       Matrix myMatrix = new Matrix(getSize());
       for(int i = 0; i < getSize(); i++){
          if(rows[i].length() > 0){
             for(rows[i].moveTo(0); rows[i].getIndex() >= 0; 
                 rows[i].moveNext()){
                Entry myEntry = (Entry) rows[i].getElement();
                Entry leEntry = new Entry(myEntry.column, x * myEntry.data);
                myMatrix.changeEntry(i+1,leEntry.column,leEntry.data);
             }
          }
       }
       return myMatrix;
    }
	
   Matrix add(Matrix B){
   // returns a new Matrix that is the sum of this Matrix with M
   // pre: getSize()==M.getSize(i)
       if(getSize() != B.getSize()){
          System.err.println("ERROR: Matrix.add(), getSize() != M.getSize()");
          System.exit(1);
       }
       Matrix M;
       if(this.equals(B)){
          M = this.copy();
       }else{
          M = B;
       }
       Matrix myMatrix = new Matrix(getSize());
          for(int i = 0; i < getSize(); i++){
             if(rows[i].length() > 0 || M.rows[i].length() > 0){
                rows[i].moveTo(0);
                M.rows[i].moveTo(0);
                while(rows[i].getIndex() >= 0 || M.rows[i].getIndex() >= 0){
                   if(rows[i].getIndex() < 0){   //Insert rest
                      addRest(M.rows[i], myMatrix, i);
                      continue;
                   }
                   if(M.rows[i].getIndex() < 0){
                      addRest(rows[i], myMatrix, i);
                      continue;
                   }                      
                   Entry zero = new Entry(1,0);
                   Entry a = null;  //Initulize entrys
                   Entry b = null;

                   if(rows[i].getIndex() >= 0){ 
                      a = (Entry) rows[i].getElement();
                   }else{
                      a = zero;
                   }
                   if(M.rows[i].getIndex() >= 0){
                      b = (Entry) M.rows[i].getElement();
                   }else{
                     b = zero;
                   }

                   if(a.column == b.column){
                      int column = a.column;
                      double data = a.data + b.data;
                      myMatrix.changeEntry(i+1,column,data);
                      M.rows[i].moveNext();
                      rows[i].moveNext();
                   }
                   else if(a.column < b.column){
                      myMatrix.changeEntry(i+1,a.column,a.data);
                      rows[i].moveNext();
                   }
                   else if(a.column > b.column){
                      myMatrix.changeEntry(i+1,b.column,b.data);
                      M.rows[i].moveNext();
                   }
                } 
             }
          }
      return myMatrix;
   }

   private void addRest(List A, Matrix M, int i){
      while(A.getIndex() >= 0){
         Entry a = (Entry) A.getElement();
         M.changeEntry(i+1,a.column,a.data);
         A.moveNext();
      }
   }

   private void subRest(List A, Matrix M, int i){
      while(A.getIndex() >= 0){
         Entry a = (Entry) A.getElement();
         M.changeEntry(i+1,a.column,a.data * -1);
         A.moveNext();
      }
   }
   
	
   Matrix sub(Matrix B){
   // returns a new Matrix that is the difference of this Matrix with M
   // pre: getSize()==M.getSize()

       if(getSize() != B.getSize()){
          System.err.println("ERROR: Matrix.sub(), getSize() != M.getSize()");
          System.exit(1);
       }
       Matrix M;
       if(this.equals(B)){
          M = this.copy();
       }else{
          M = B;
       }
       Matrix myMatrix = new Matrix(getSize());
          for(int i = 0; i < getSize(); i++){
             if(rows[i].length() > 0 || M.rows[i].length() > 0){
                rows[i].moveTo(0);
                M.rows[i].moveTo(0);
                while(rows[i].getIndex() >= 0 || M.rows[i].getIndex() >= 0){
                   if(rows[i].getIndex() < 0){
                      subRest(M.rows[i], myMatrix, i);
                      continue;
                   }
                   if(M.rows[i].getIndex() < 0){
                      addRest(rows[i], myMatrix, i);
                      continue;
                   }
                   Entry zero = new Entry(1,0);
                   Entry a = null;
                   Entry b = null;

                   if(rows[i].getIndex() >= 0){
                      a = (Entry) rows[i].getElement();
                   }else{
                      a = zero;
                   }
                   if(M.rows[i].getIndex() >= 0){
                      b = (Entry) M.rows[i].getElement();
                   }else{
                     b = zero;
                   }

                   if(a.column == b.column){
                      int column = a.column;
                      double data = a.data - b.data;
                      myMatrix.changeEntry(i+1,column,data);
                      M.rows[i].moveNext();
                      rows[i].moveNext();
                   }
                   else if(a.column < b.column){
                      myMatrix.changeEntry(i+1,a.column,a.data);
                      rows[i].moveNext();
                   }
                   else if(a.column > b.column){
                      myMatrix.changeEntry(i+1,b.column,b.data * -1);
                      M.rows[i].moveNext();
                   }
                }
             }
          }
      return myMatrix;
   }
	
   Matrix transpose(){
   // returns a new Matrix that is the transpose of this Matrix
      Matrix trans = new Matrix(this.length);
      int j = 0;
      for(int i = 0; i < length; i++){
        if(rows[i].length() > 0){
           for(rows[i].moveTo(0); rows[i].getIndex() >= 0; rows[i].moveNext()){
              Entry temp = (Entry) rows[i].getElement();
              trans.changeEntry(temp.column,i+1, temp.data);
           }
        }
      }
      return trans;
   }
	
   Matrix mult(Matrix M){
   // returns a new Matrix that is the product of this Matrix with M
   // pre: getSize()==M.getSize()
      if(getSize() != M.getSize()){
         System.err.println("mutl() ERROR, getSize()==M.getSize()");
         System.exit(1);
      }
      Matrix B;
      if(this.equals(M)){
         B = this.copy();
      }else{
         B = M;
      }
      B = B.transpose();
      Matrix tmp = new Matrix(getSize());

      for(int i = 0; i < getSize(); i++){
         for(int j = 0; j < getSize(); j++){
            if(rows[i].length() > 0 && B.rows[j].length() > 0){
               Entry c = new Entry(j+1,dot(rows[i],B.rows[j]));
               tmp.changeEntry(i+1,c.column, c.data);
            }
         }
      }
      return tmp;
   }

	
    //Other Functions
	
   public String toString(){
   // overrides Object's toString() method
      if(length < 0){
         System.err.println("ERROR: in Matrix.toSring() length < 0");
         System.exit(1);  
      }
      String str = "";
      for(int i = 0; i < length; i++){
         if(rows[i].length() > 0){
            str += (i+1) + ": " + rows[i] + " \n";
         }
      }
    return str;
   }
   
   private static double dot(List A, List B){
      double result = 0;
         A.moveTo(0);
         B.moveTo(0);
         int i = 0;
         Entry P = (Entry) A.getElement();
         Entry Q = (Entry) B.getElement();
         while(A.getIndex() >= 0 || B.getIndex() >= 0){
            if(A.getIndex() < 0){
               return result;
            }
            if(B.getIndex() < 0){
               return result;
            }
            P = (Entry) A.getElement();
            Q = (Entry) B.getElement();
            if(P.column == Q.column){
               result += P.data * Q.data;
               A.moveNext();
               B.moveNext();
            }
            else if(P.column < Q.column){
               A.moveNext();
            }
            else if(P.column > Q.column){
               B.moveNext();
            }else{
               System.out.println("WTF?");
               return result;
            }
         }
      return result;
   }


   


}
