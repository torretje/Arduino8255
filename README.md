Arduino8255
===========

Arduino interfacing a pio 8255.
<br/>Check for some more information http://www.torretje.nl/Projects/8255

Expand arduino with this golden oldie 82c55a.

###Wiring arduino to the 8255.

The numbers are the arduino pins the variable names are the 8255 pins

int d0 = 2;<br/>
int d1 = 3;<br/>
int d2 = 4;<br/>
int d3 = 5;<br/>
int d4 = 6;<br/>
int d5 = 7;<br/>
int d6 = 8;<br/>
int d7 = 9;<br/>
int cs = 12;<br/>
int rd = 11;<br/>
int wr = 10;<br/>
int res = A2;<br/>
int a0 = A0;<br/>
int a1 = A1;<br/>

###Usage
Copy the .ino file into the Aruino editor.
With setport you can write a byte to one of the 8255 ports A,B or C in one call.<br/>
And with setPin you can write a bit to one of the 8255 24 pins.<br/>
See below code an code example.

###Example usage
```C
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
```
