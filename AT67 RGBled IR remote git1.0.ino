/*AT67 RGBled IR remote V8*/
//přidání regulace jasu
//regulace jasu nefunguje, osekám kód na míň barev


/*IR remote*/
#include <IRremote.h>
int IRpin = 10;

IRrecv IR(IRpin); //vytvoření objektu IR(název zvolen), příkaz IRrecv je dán
decode_results cmd;   // decode_results příkaz z knihovny IR, cmd je zvolený název
String myCom;

//RGB led

int redPin = 5;
int greenPin = 3;
int bluePin = 9;

int Rval;    //pro nastavení hodnot jasu
int Gval;
int Bval;


int step = 25; // o kolik se bude měnit jas při zmáčknutí tlačítka up down
int brightC = 100; //koeficient jasu, musí být vyplněn, 100 dává velké hodnoty o dva řády vyšší než max

int dt = 100; //delay


void setup()    {
    Serial.begin(9600);
    IR.enableIRIn();    //case sensitive
    //chybí nastavení pinu IRpin a já nevím, proč se tam nedává

    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);

}

void loop()
//R remote
//tlačítka namapována správně
    {
    while (IR.decode (& cmd) == 0)    {
    }
   
   // Serial.println(cmd.value, HEX);
    delay(dt);
    IR.resume(); 

    if (cmd.value==0xFFA25D)    {    //hodnotu FFA25D jsme vyčetli dříve, že je přiřazena tlačítku power
        myCom="pwr";        
    }

    if (cmd.value==0xFF629D)    {    
        myCom="v+";
    }

    if (cmd.value==0xFFE21D)    {    
        myCom="func/stop";
    }

    if (cmd.value==0xFF22DD)    {    
        myCom="rw";
    }

    if (cmd.value==0xFF02FD)    {    
        myCom="play";
    }

    if (cmd.value==0xFFC23D)    {    
        myCom="ff";
    }

    if (cmd.value==0xFFE01F)    {    
        myCom="down";
    }

    if (cmd.value==0xFFA857)    {    
        myCom="v-";
    }

    if (cmd.value==0xFF906F)    {    
        myCom="up";
    }

    if (cmd.value==0xFF6897)    {    
        myCom="zero";
    }

    if (cmd.value==0xFF9867)    {    
        myCom="eq";
    }

    if (cmd.value==0xFFB04F)    {    
        myCom="st/rept";
    }

    if (cmd.value==0xFF30CF)    {    
        myCom="one";
    }

    if (cmd.value==0xFF18E7)    {    
        myCom="two";
    }

    if (cmd.value==0xFF7A85)    {    
        myCom="three";
    }

    if (cmd.value==0xFF10EF)    {    
        myCom="four";
    }

    if (cmd.value==0xFF38C7)    {    
        myCom="five";
    }

    if (cmd.value==0xFF5AA5)    {    
        myCom="six";
    }

    if (cmd.value==0xFF42BD)    {    
        myCom="seven";
    }

    if (cmd.value==0xFF4AB5)    {    
        myCom="eight";
    }

    if (cmd.value==0xFF52AD)    {    
        myCom="nine";
    }
//až sem to funguje

//zde začíná část s nastavováním RGB led
//nejprve nastavím mezní hodnoty


if (Rval > 255)    {
    Rval = 255;
    }
if (Rval < 0)    {
    Rval = 0;
    }

if (Gval > 255)    {
    Gval = 255;
    }
 if (Gval < 0)    {
    Gval = 0;
    }

if (Bval > 255)    {
    Bval = 255;
    }
 if (Bval < 0)    {
    Bval = 0;
    }

//koeficient jasu
IR.resume();
if (myCom == "up") {
   brightC = (round(brightC + step));

   if (brightC > 100)    {
    brightC  = 100;
   }

    //toto je nově nastaveno a přesunuto
    analogWrite(redPin, (Rval * brightC / 100));
    analogWrite(greenPin, (Gval * brightC / 100));
    analogWrite(bluePin, (Bval * brightC / 100));
     
}

if (myCom == "down") {
   brightC = (round(brightC - step));

   if (brightC < 0)    {
    brightC = 0;
   }

    //toto je nově nastaveno a přesunuto
    analogWrite(redPin, (Rval * brightC / 100));
    analogWrite(greenPin, (Gval * brightC / 100));
    analogWrite(bluePin, (Bval * brightC / 100));
    
} 


//tady nastavím barvy
//rozsvítit
if (myCom == "pwr") {
    Rval = (255 * brightC / 100);
    Gval = (255 * brightC / 100);
    Bval = (255 * brightC / 100);

    analogWrite(redPin, Rval);
    analogWrite(greenPin, Gval);
    analogWrite(bluePin, Bval);
}  

//red max
if (myCom == "one") {
    Rval = (255 * brightC / 100);
    Gval = (0 * brightC / 100);
    Bval = (0 * brightC / 100);

    analogWrite(redPin, Rval);
    analogWrite(greenPin, Gval);
    analogWrite(bluePin, Bval);
}  

//vypnout
if (myCom == "func/stop") {
    Rval = (0 * brightC / 100);
    Gval = (0 * brightC / 100);
    Bval = (0 * brightC / 100);

    analogWrite(redPin, Rval);
    analogWrite(greenPin, Gval);
    analogWrite(bluePin, Bval);
}  

Serial.print(myCom);
Serial.print(" R");
Serial.print(Rval);
Serial.print(" G");
Serial.print(Gval);
Serial.print(" B");
Serial.print(Bval);
Serial.print(" brightC ");
Serial.println(brightC);

//V8

    }    