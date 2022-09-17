#include<Servo.h>


//pins

#define rel_r  2
#define rel_g  3
#define s0  4
#define s1  5
#define s2  6
#define s3  7
#define out 12
#define prox_pin  8
#define buzzer  13


int prox;

//Servos
Servo gate_in;
Servo gate_out;
Servo sorter;

//Global variables for functions
int frequency=0;  // for color function
int path;         // for color function
int j=0;          // for proximity sensor function
int color_inf;    // for color function

bool cond=false;

void setup() {
  //color sensor 
  pinMode(s0,OUTPUT);
  pinMode(s1,OUTPUT);
  pinMode(s2,OUTPUT);
  pinMode(s3,OUTPUT);
  pinMode(out,INPUT);
  //buzzer
  pinMode(buzzer, OUTPUT);
  //proximity
  pinMode(prox_pin,INPUT);
  //relay
  pinMode(rel_r, OUTPUT);
  pinMode(rel_g, OUTPUT);

  //color sensor frequency
  digitalWrite(s0,HIGH);
  digitalWrite(s1,LOW);

  //open relay circuit
  digitalWrite(rel_r,HIGH);
  digitalWrite(rel_g,HIGH);


  gate_in.attach(9);
  gate_out.attach(10);
  sorter.attach(11);

   //reset servos positions
   gate_in.write(10); //closed
   gate_out.write(55);  //closed
   sorter.write(25);    //neutral


  buzz_start();

  Serial.begin(9600);
}

void loop() {

  prox=digitalRead(prox_pin);   //get reading from proximity sensor

  
  path = getcolor();
  Serial.println(path);
  if((prox==0)&&(path==3)){  //first gate
    gate_in.write(50); //open
    delay(400);
    gate_in.write(10);  //close
    delay(200);
  }
  
  delay(800);
  path = getcolor();  //get reading from color sensor
  delay(50);

  if(path==2){    //orange
    orange();
    delay(800);
  }
  
  if(path==1){  //green
    green();
    delay(800);
  }
    //Serial.println(path);

}

int getcolor() {

  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  frequency = pulseIn(out, LOW);
  int r = frequency;   //Red value
  Serial.print("R= ");
  Serial.print(r);
  Serial.print("  ");
  delay(50);

  
  digitalWrite(s2, HIGH);
  digitalWrite(s3, HIGH);
  frequency = pulseIn(out, LOW);
  int g = frequency;    //Green value
  Serial.print("G= ");
  Serial.print(g);
  Serial.print("  ");
  delay(50);

  
  digitalWrite(s2, LOW);
  digitalWrite(s3, HIGH);
  frequency = pulseIn(out, LOW);
  int b = frequency;    //Blue value
  Serial.print("B= ");
  Serial.print(b);
  Serial.println("  ");
  delay(50);


  if( (r<220) && (r>160) &&  (g<165) && (g>100) && (b<185) && (b>145)  ){
    color_inf = 1; // green ball

  }
  else if( (r<105) && (r>60) && (g<245) && (g>190) && (b<180) && (b>150)){
    color_inf = 2; // Orange ball

  
  }
    else if( (r<159) && (r>130) && (g<180) && (g>160) && (b<155) && (b>120) ){
    color_inf = 3; // floor color
    
  }
        
 }

  Serial.println(color_inf);
  //Serial.println(prox);
 // delay(400);

  return color_inf;  
}
}
void orange(){


    sorter.write(10); //orange path
    
    digitalWrite(rel_r, LOW); //red on
    digitalWrite(rel_g, HIGH);//green off
    delay(200);
    gate_out.write(10); //open
    delay(1000);
    gate_out.write(55); //close
    delay(1500);
    //buzz_o(); //buzzer melody for orange path
    sorter.write(25);   //neutral

    //both relays off
    //digitalWrite(rel_r, HIGH);
    //digitalWrite(rel_g, HIGH);
    //  path = 3;

    

        /*FOR DEBUGGING*/
 /*
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(100); 
*/

}

void green(){
 
    sorter.write(45); //green path
    
    digitalWrite(rel_r, HIGH); //red off
    digitalWrite(rel_g, LOW);//green on
    delay(200);
    gate_out.write(10); //open
    delay(1000);
    gate_out.write(55); //close
    //buzz_g();           //buzzer melody for green path
    //delay(300);
    delay(1500);
    sorter.write(25);   //neutral

    //both relays off
    //digitalWrite(rel_r, HIGH);
    //digitalWrite(rel_g, HIGH);
     // path = 3;

    /*FOR DEBUGGING*/
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(100); 
    /*FOR DEBUGGING*/

}

void resv_check(){ //balls resevoir check
  
  gate_in.write(50); //open
  delay(400);
  gate_in.write(10);  //close
  delay(200);
  
}

int proximity(){  //Balls counter
  int reading=digitalRead(prox_pin);
  if(reading==0&&cond==false){ //counter
    j++;
    cond=true;
  }else if(reading==1){
    cond=false;
  }
  Serial.println(j);
  return reading;
}


//buzzer tones
void buzz_o(){  //buzzer orange melody //1750 ms
  tone(buzzer,760  ,100);
  delay(100);
  tone(buzzer,720,100);
  delay(150);
  tone(buzzer,680,100);
  delay(150);
  tone(buzzer,620,150);
  delay(300);
  
  tone(buzzer,650,200);
  delay(300);
  
  tone(buzzer,1020,80);
  delay(300);
  tone(buzzer,1020,80);
  delay(150);
  tone(buzzer,1020,80);
  delay(300);
}

void buzz_g(){ //buzzer tone green  //700 ms

tone(buzzer,760,50);
delay(350);
tone(buzzer,660,80);
delay(300);
tone(buzzer,520,80);
delay(150);
tone(buzzer,580,80);
delay(150);
tone(buzzer,480,80);
delay(500);
}


void buzz_start(){  //buzzer start melody
  tone(buzzer,660,100);
  delay(150);
  tone(buzzer,660,100);
  delay(300);
  tone(buzzer,660,100);
  delay(300);
  tone(buzzer,510,100);
  delay(100);
  tone(buzzer,660,100);
  delay(300);
  tone(buzzer,770,100);
  delay(550);
  tone(buzzer,380,100);
  delay(575);
}
