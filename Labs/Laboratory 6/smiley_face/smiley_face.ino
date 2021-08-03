const int row[] = {6 , 11 , A5 , 9 , 5 , A4 , 4 , A2};
const int col[] = {10 , 3 , 2 , 7 , A3 , 8 , 12 , 13};

int matrix[8][8] = {
  {0 , 0 , 0 , 0 , 0 , 0 , 0 , 0} , 
  {0 , 0 , 0 , 0 , 0 , 0 , 0 , 0} , 
  {0 , 0 , 1 , 0 , 0 , 1 , 0 , 0} , 
  {0 , 0 , 1 , 0 , 0 , 1 , 0 , 0} , 
  {0 , 0 , 1 , 0 , 0 , 1 , 0 , 0} , 
  {0 , 0 , 0 , 0 , 0 , 0 , 0 , 0} ,
  {0 , 1 , 0 , 0 , 0 , 0 , 1 , 0} ,
  {0 , 0 , 1 , 1 , 1 , 1 , 0 , 0} ,
};

void smileyFace()
{
  for(int i = 0 ; i < 8 ; i++)
  {
    for(int j = 0 ; j < 8 ; j++)
        digitalWrite(col[j] , matrix[i][j]); //light up the columns with 1s
    digitalWrite(row[i] , LOW);
    delay(1);
    digitalWrite(row[i] , HIGH);
  }
  
}


void setup() {
   for(int i = 0 ; i < 8 ; i++)
   {
      pinMode(row[i] , OUTPUT);
      pinMode(col[i] , OUTPUT);
   }
   //in a matrix the current flows from col (cathode) to row(anode). if col is low and row is high the current flows and the led is bright. if col is high the current can't flow through the diode
   for(int i = 0 ; i < 8 ; i++)
   {
      digitalWrite(col[i] , LOW); //if we put high on a cathode the current doesnt flow
      digitalWrite(row[i] , HIGH); //turn off the matrix
   }
}

void loop() {
  smileyFace();

}
