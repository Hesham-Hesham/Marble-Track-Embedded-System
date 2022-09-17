#include<Servo.h>



//pins
#define prox_pin  8


#define pb1 2
#define pb2 4
#define pb3 7
#define pb4 10
#define pb5 12
#define pb6 13


//Servos
Servo lift;
Servo shoot;
Servo gate;



//Proximity sensor
int prox; //state
bool cond=false;
int j=0;  //counter

//push buttons
int b1; //auto
int b2; //manual
int b3; //bluetooth
int b4; //gate
int b5; //lift
int b6; //shoot


//bluetooth
char inputByte;

void setup() {

pinMode(prox_pin,INPUT);
pinMode(pb1,INPUT);
pinMode(pb2,INPUT);
pinMode(pb3,INPUT);
pinMode(pb4,INPUT);
pinMode(pb5,INPUT);
pinMode(pb6,INPUT);


  lift.attach(9);
  shoot.attach(5);
  gate.attach(11);

  Serial.begin(9600);

//resetting servos

   gate.write(10); //closed
    delay(200);
  lift.write(96); //closed
    delay(200);
  shoot.write(13); //closed
    delay(200);
}

void loop() {  
  
  //push buttons
  b1=digitalRead(pb1);
  b2=digitalRead(pb2);
  b3=digitalRead(pb3);
  b4=digitalRead(pb4);
  b5=digitalRead(pb5);
  b6=digitalRead(pb6);

  //read from proximity sensor
  prox = digitalRead(prox_pin);

  if(b1 == 1){ //auto
    if(prox==0){    
      delay(1500);
      gate_open(); 
      delay(1000);
      lifting();
      shooting();
     }
  }
  
   if(b1 == 0 && b2 == 1  && b3==0){  //manual
    if(b4==1){   //gate
      gate_open();
    }
    
    if(b5==1){   //lift
      lifting();
    }

    if(b6==1){    //shoot
      shooting();
    }
  }
  

  if(b1==0 && b2==0 && b3==1){  //bluetooth
    while(Serial.available()>0){
      inputByte= Serial.read(); //read from bluetooth
      if (inputByte=='a' || inputByte=='A'){  //gate
      delay(1500);
      gate_open();
      }
      else if (inputByte=='b' || inputByte=='B'){ //Lift
        lifting();
      } 
      else if (inputByte=='c' || inputByte=='C') { //Shoot
        shooting();
      }
    }
  }

//AMR BALEGH HAMDY RAGAB 18P2301 69 420
                                                        delay(3000); 
//AMR BALEGH HAMDY RAGAB 18P2301 69 420 ZEB KOS TEEZ A7A
}

void lifting(){
   for(int i=96;i>=10;i--){  //up
    lift.write(i);
    delay(15);
    }

    delay(1000);
    
   for(int i=10;i<=96;i++){ //down
    lift.write(i);
    delay(15);
    }
}


void gate_open(){
    gate.write(60); //open
    delay(400); //measured
    gate.write(10); //closed
    delay(100); //hole
}


void shooting (){
    shoot.write(99);
    delay(500);
    shoot.write(13);
}


int proximity(){
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
