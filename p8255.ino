/*
   Readable example(See also optimised example) of arduino interfacing a 8255
   Karel Reinhard 2014
 */
int d0 = 2;
int d1 = 3;
int d2 = 4;
int d3 = 5;
int d4 = 6;
int d5 = 7;
int d6 = 8;
int d7 = 9;
int cs = 12;
int rd = 11;
int wr = 10;
int res = A2;
int a0 = A0;
int a1 = A1;
//Declare the dataport to loop over it when setting bits
int outData[8]={d0,d1,d2,d3,d4,d5,d6,d7};
byte porta,portb,portc =B0000000; 

// the setup routine runs once when you press reset:
void setup() {     
  // initialize the digital pins as outputs.
  pinMode(a0, OUTPUT);   
  pinMode(a1, OUTPUT);     
  pinMode(res, OUTPUT);    
  pinMode(d0, OUTPUT);     
  pinMode(d1, OUTPUT);     
  pinMode(d2, OUTPUT);     
  pinMode(d3, OUTPUT);     
  pinMode(d4, OUTPUT);     
  pinMode(d5, OUTPUT);     
  pinMode(d6, OUTPUT);     
  pinMode(d7, OUTPUT);     
  pinMode(cs, OUTPUT);     
  pinMode(rd, OUTPUT);
  pinMode(wr, OUTPUT);
  
  pio8255init();
}

void pio8255init(){
 //Start 8255 init sequence
  digitalWrite(res, HIGH);
  digitalWrite(res, LOW);
  digitalWrite(wr, HIGH);
  
  /*
    Set the byte on the data line to init the 8255
    Set port c to output
  */
  digitalWrite(d0, LOW); 
  //Set port b to output
  digitalWrite(d1, LOW);
  //Set port b to mode 0
  digitalWrite(d2, LOW);
  //Set port c to output 4bit
  digitalWrite(d3, LOW);
  //Set port a to output
  digitalWrite(d4, LOW);
  //Set port a to mode 0
  digitalWrite(d5, LOW);
  digitalWrite(d6, LOW);
  digitalWrite(d7, HIGH);
  //End of the byte
  
  //Handshake with 8255 to pick up the data
  //Chip handshaking Port a0->high a1->high and set wr->low and the high
  digitalWrite(a0, HIGH);
  digitalWrite(a1, HIGH);
  digitalWrite(wr, LOW);
  digitalWrite(wr, HIGH);
  digitalWrite(rd, HIGH);
}

//port is 8255 A|B|C, pin 0(lsb) to 7(msb) ,highlow=true|false
//6,212 KHz setPort 6,059 KHz setPin (Writing 1 and 0 means x2)
void setPin(char port,int pin, boolean highlow){
  byte data;
  if('A'==port){
     data=(highlow)?porta | B00000001<<pin : porta & B11111110<<pin;
   }else if('B'==port){
     data=(highlow)?portb | B00000001<<pin : portb & B11111110<<pin;
   }else if('C'==port){
     data=(highlow)?portc | B00000001<<pin : portc & B11111110<<pin;
   }
  
  setPort(port,data);
}

void setPort(char port, byte data){
   //With the char A|B|C you can set the according ports on the 8255.
   //Track change to support bit switching with porta, portb, portc.
  if('A'==port){
    digitalWrite(a0, LOW);
    digitalWrite(a1, LOW);
    porta=data;
   }else if('B'==port){
    digitalWrite(a0, HIGH);
    digitalWrite(a1, LOW);
     portb=data;
   }else if('C'==port){
    digitalWrite(a0, LOW);
    digitalWrite(a1, HIGH);
     portc=data;
   }
   //Chip handshaking Port cs->low wr->low 
   digitalWrite(cs, LOW);
   digitalWrite(wr, LOW);
   //iterate through bit mask
   int i=0;
   for (byte mask = B00000001; mask>0; mask <<= 1) { 
     if (data & mask){ // if bitwise AND resolves to true
     digitalWrite(outData[i],HIGH);
    }else{ //if bitwise and resolves to false
     digitalWrite(outData[i],LOW);
    }
    i++;
   }
   //Chip handshaking Port cs->high wr->high 
   digitalWrite(wr, HIGH);
   digitalWrite(cs, HIGH);
   //Chip handshaking Port a0->low a1->low
   digitalWrite(A0, LOW);
   digitalWrite(A1, LOW);
}

void loop(){ 
  //Kit like walk the leds forward
  for (byte mask = B10000000; mask>0; mask >>= 1) {
    setPort('B', mask);
    delay(100);
  }
  //And walk back
  for (byte mask = B00000001; mask>0; mask <<= 1) {
    setPort('B', mask);
    delay(100);
  }
  setPin('C',7,HIGH);
  setPin('A',7,HIGH);
  delay(5);
  setPin('A',7,LOW);
  setPin('A',4,HIGH);
}
