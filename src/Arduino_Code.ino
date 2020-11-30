#include <EEPROM.h>
#include <IRremote.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(1,2,4,5,6,7);
#define RECV_PIN A5
#define motorA1 6
#define motorA2 7
#define motorB1 8
#define motorB2 10
#define ledB A0
#define ledR A1
#define ledG A2
#define ledY A3
#define buzzer A4
int ObstaclePin = 13;
int Obstacle = HIGH;
String x;
String y="NO";
int *Action=(int*)malloc(sizeof(int)), *Step=(int*)malloc(sizeof(int)), i=0,k=0;
//int Action[30], i=0;
int a=0, b=1, d=0,j=0,l=0;
int zz=0;
int ttmmpp=0;

bool boolBouton = 0 ;

int codeType;
int codeLen;
// pour recevoir sur l'ir PIN 11
IRrecv irrecv(RECV_PIN);
decode_results results;

// pour envoyer sur l'ir PIN 3
IRsend irsend;
 
void setup()
{  
  lcd.begin(16,2);
  
 
  irrecv.enableIRIn(); // Start the receiver
  pinMode( motorA1 , OUTPUT);
  pinMode( motorA2 , OUTPUT);
  
  pinMode( motorB1 , OUTPUT);
  pinMode( motorB2 , OUTPUT);

  pinMode(buzzer, OUTPUT);
  pinMode(ledB, OUTPUT);
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledY, OUTPUT);
  //Serial.begin(9600);

//  lcd.setCursor(0,0);
//  lcd.print("Welcome!");
//  delay(2000);
//  lcd.clear();
//  lcd.setCursor(0,0);
//  lcd.print("Choose a mode:");
//  delay(2000);
//  lcd.setCursor(0,0);
//  lcd.print("1) real time");
//  lcd.setCursor(0,1);
//  lcd.print("2) enter path");

   Stop();
}
 
void loop()
{
 
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("choisir un mode ");
 lcd.setCursor(0,1);
 lcd.print("(1,2,3,4)");
  
  while(y=="NO")
  { receiveCode(); }
  
  detect_obst();

  if(y=="61d6c837") // bouton=(1)
  {
      lcd.clear();
       lcd.setCursor(0,0);
      lcd.println("mode1"); 
      lcd.setCursor(0,1);
      lcd.println(" entrer chemin "); 
      lcd.blink(); //Displays the blinking LCD cursor 
      delay(4000); 
    
    receiveCode();
    if(x=="61d6aa55"){
      lcd.clear();
       lcd.setCursor(0,0);
      lcd.println("Ahead"); 
       Ahead();
    }
     
    else if(x=="61d618e7"){
        lcd.clear();
       lcd.setCursor(0,0);
      lcd.println("Back"); 
      Back();}
    else if(x=="61d69a65"){
        lcd.clear();
       lcd.setCursor(0,0);
      lcd.println("Right"); 
      Right();
    }
    else if(x=="61d6a857"){
          lcd.clear();
       lcd.setCursor(0,0);
      lcd.println("Left"); 
        Left();
    }
     else if(x=="61d628d7")
      Stop();
  }


//----------------------------------------2mode-------------------------------------------

  else if(y=="61d60af5") //bouton=(2)
  {
       lcd.clear();
      lcd.println("mode2");
    while(a!=b)
    { receiveCode();}
    b++;
    if(x=="61d6aa55")      //ahead (1)
    {
      lcd.clear();
       lcd.setCursor(0,0);
      lcd.println("Ahead"); 
      Action=(int*)realloc(Action,(i+1)*sizeof(int));
      Step=(int*)realloc(Step,(k+1)*sizeof(int));      
      Action[i++]=1;
      while(a!=b)
      { receiveCode();}
      b++;
      if(x=="61d6c837") Step[k++]=1;
      else if(x=="61d60af5") Step[k++]=2;
      else if(x=="61d64ab5") Step[k++]=3;
      else if(x=="61d66a95") Step[k++]=4;
      else if(x=="61d6d827") Step[k++]=5;
      else if(x=="61d65aa5") Step[k++]=6;
      else if(x=="61d63ac5") Step[k++]=7;
      else if(x=="61d61ae5") Step[k++]=8;
      else if(x=="61d67a85") Step[k++]=9;
      else Step[k++]=0;
    }
    else if(x=="61d69a65") //right (2)
    {
      lcd.clear();
       lcd.setCursor(0,0);
      lcd.println("right"); 
      Action=(int*)realloc(Action,(i+1)*sizeof(int));   
      Action[i++]=2;
    }
    else if(x=="61d6a857") //left (3)
    {
      lcd.clear();
       lcd.setCursor(0,0);
      lcd.println("left"); 
      Action=(int*)realloc(Action,(i+1)*sizeof(int)); 
      Action[i++]=3;
    }
    else if(x=="61d618e7") //back (4)tà)
    {
      lcd.clear();
       lcd.setCursor(0,0);
      lcd.println("back"); 
      Action=(int*)realloc(Action,(i+1)*sizeof(int));
      //Step=(int*)realloc(Step,(i+1)*sizeof(int));      
      Action[i++]=4;
    }
    else if(x=="61d6906f") //GO (->||)
    {
      execute_path();
      y="NO";
    }
  }

  else if(y=="61d64ab5") ///////////////////////////////////////////////////////////////////////////////////bouton=(3)
  {
       lcd.clear();
      lcd.println("mode3");
    while(a!=b)
    { receiveCode();}
    b++;
    if(x=="61d6aa55")      //ahead (1)
    {
      EEPROM[i++]=1;
      while(a!=b)
      { receiveCode();}
      b++;
      if(x=="61d6c837") EEPROM[i++]=1;
      else if(x=="61d60af5") EEPROM[i++]=2;
      else if(x=="61d64ab5") EEPROM[i++]=3;
      else if(x=="61d66a95") EEPROM[i++]=4;
      else if(x=="61d6d827") EEPROM[i++]=5;
      else if(x=="61d65aa5") EEPROM[i++]=6;
      else if(x=="61d63ac5") EEPROM[i++]=7;
      else if(x=="61d61ae5") EEPROM[i++]=8;
      else if(x=="61d67a85") EEPROM[i++]=9;
      else EEPROM[i++]=0;
    }
    else if(x=="61d69a65") //right (2)
      EEPROM[i++]=2;
    else if(x=="61d6a857") //left (3)
      EEPROM[i++]=3;
    else if(x=="61d618e7") //back (4)tà)
      EEPROM[i++]=4;
    else if(x=="61d6906f") //GO (->||)
    {
      EEPROM[30]=i;
      Serial.print("Path stored succesfully");  // serial monitor
      y="NO";
    }
  }

  else if(y=="61d66a95") ///////////////////////////////////////////////////////////////////////////////////bouton=(4)
  {
       lcd.clear();
      lcd.println("mode4");
    while(a!=b)
    { receiveCode();} // the number of path
    b++;
    if(x=="61d6c837")      //path number (1)
    {
      i=EEPROM[30];
      for(int j=0; j<i; j++){
        if(EEPROM[j]==1)
        {
          j++;
          Action=(int*)realloc(Action,(zz+1)*sizeof(int));
          Step=(int*)realloc(Step,(k+1)*sizeof(int));      
          Action[zz++]=1;
          if(EEPROM[j]==1) Step[k++]=1;
          else if(EEPROM[j]==2) Step[k++]=2;
          else if(EEPROM[j]==3) Step[k++]=3;
          else if(EEPROM[j]==4) Step[k++]=4;      
          else if(EEPROM[j]==5) Step[k++]=5;
          else if(EEPROM[j]==6) Step[k++]=6;
          else if(EEPROM[j]==7) Step[k++]=7; 
          else if(EEPROM[j]==8) Step[k++]=8;
          else if(EEPROM[j]==9) Step[k++]=9;
          else Step[k++]=0;
          if(1) j++;     
        }
        else if(EEPROM[j]==2)
        {
          j++;
          Action=(int*)realloc(Action,(zz+1)*sizeof(int)); 
          Action[zz++]=2;
        }
        else if(EEPROM[j]==3)
        {
          j++;
          Action=(int*)realloc(Action,(zz+1)*sizeof(int)); 
          Action[zz++]=3;
        }
        else if(EEPROM[j]==4)
        {
          j++;
          Action=(int*)realloc(Action,(zz+1)*sizeof(int));
          //Step=(int*)realloc(Step,(k+1)*sizeof(int));      
          Action[zz++]=4;
        }
      }
    }
    execute_path();
    y="NO";
  }
  else y="NO";
}



void receiveCode(){

   detect_obst();

  // catch IR
  if (irrecv.decode(&results))
    {
      //recupere le type de codage, la logueur
      int codeType = results.decode_type;
      int codeLen = results.bits;
    Serial.println("-------------------");
    Serial.print("ValueHex ");   
    Serial.println(String(results.value, HEX));
    Serial.print("ValueDec ");  
    Serial.println(results.value);
    Serial.print("CodeLen ");  
    Serial.println(codeLen);

    if(y=="NO"){
       y=String(results.value, HEX);
       x=""; //x ne contient rien.
       ttmmpp=0;
       if(y=="61d6c837" || y=="61d60af5" || y=="61d64ab5" || y=="61d66a95")
          led_BRGY();
    }
    else{
       x=String(results.value, HEX);
       a++;
    }
 //-------------------------------------------------------------------------------------- affectation des signalisations
    buzzer_seule();
    if(x=="61d6aa55" || x=="61d618e7" || x=="61d69a65" || x=="61d6a857" || x=="61d628d7")
       ledB_seule();
    else if(y=="61d60af5" &&(x=="61d6c837" || x=="61d60af5" || x=="61d64ab5" || x=="61d66a95" || x=="61d6d827" || x=="61d65aa5" || x=="61d63ac5" || x=="61d61ae5" || x=="61d67a85" || x=="61d628d7"))
       ledB_seule();
    else if((y=="61d60af5" && x=="61d6906f") || (y=="61d64ab5" && x=="61d6906f")){
      if(ttmmpp==0){
        ledG_seule();
        ttmmpp++;
      }
    }
    else if(y=="61d66a95" &&(x=="61d6c837" || x=="61d60af5" || x=="61d64ab5" || x=="61d66a95")){
      if(ttmmpp==0){
        ledG_seule();
        ttmmpp++;
      }
    }
    else if(x=="61d650af"){
       ledY_seule();
       y="NO";
    }
 //--------------------------------------------------------------------------------------
     irrecv.resume(); // Receive the next value
  }
}

void execute_path(){
  
    detect_obst();

  Serial.println(i);
  for(int j=0;j<i;j++)
  {
    if(Action[j]==1)
    {
      Ahead();
      delay(1000*Step[d]); // Step[d]*Pas
      d++;
      Stop();
      delay(250);
      Serial.println("ahead");
    }
    else if(Action[j]==2)
    {
      Right();
      delay(1800); //Rotation 90 deg
      Stop();
      delay(250);  
      Serial.println("right");
    }
    else if(Action[j]==3)
    {
      Left();
      delay(1800); //Rotation 90 deg
      Stop();
      delay(250);
      Serial.println("left");
    }
    else if(Action[j]==4)
    {
      Back();
      delay(1000); //1Pas
      Stop();
      delay(250);
      Serial.println("back");
    }
  }
}

void Ahead(){
  Serial.println("ahead2");
  digitalWrite( motorA1 , HIGH);
  digitalWrite( motorA2 , LOW);

  digitalWrite( motorB1 , HIGH);
  digitalWrite( motorB2 , LOW);
}

void Right(){
  digitalWrite( motorA1 , HIGH);
  digitalWrite( motorA2 , LOW);

  digitalWrite( motorB1 , LOW);
  digitalWrite( motorB2 , HIGH);
}

void Left(){
  digitalWrite( motorA1 , LOW);
  digitalWrite( motorA2 , HIGH);

  digitalWrite( motorB1 , HIGH);
  digitalWrite( motorB2 , LOW);
}

void Back(){
  digitalWrite( motorA1 , LOW);
  digitalWrite( motorA2 , HIGH);

  digitalWrite( motorB1 , LOW);
  digitalWrite( motorB2 , HIGH);
}

void Stop(){
  digitalWrite( motorA1 , LOW);
  digitalWrite( motorA2 , LOW);

  digitalWrite( motorB1 , LOW);
  digitalWrite( motorB2 , LOW);
}

void buzzer_seule(){
  digitalWrite(buzzer,HIGH);
  delay(100);
  digitalWrite(buzzer,LOW);
}

void ledB_seule(){
  digitalWrite(ledB,HIGH);
  delay(100);
  digitalWrite(ledB,LOW);
}
void ledR_seule(){
  digitalWrite(ledR,HIGH);
  delay(100);
  digitalWrite(ledR,LOW);
}
void ledG_seule(){
  digitalWrite(ledG,HIGH);
  delay(100);
  digitalWrite(ledG,LOW);
}
void ledY_seule(){
  digitalWrite(ledY,HIGH);
  delay(100);
  digitalWrite(ledY,LOW);
}

void led_BRGY(){
  digitalWrite(ledB,HIGH);
  digitalWrite(ledR,HIGH);
  digitalWrite(ledG,HIGH);
  digitalWrite(ledY,HIGH);
  delay(100);
  digitalWrite(ledB,LOW);
  digitalWrite(ledR,LOW);
  digitalWrite(ledG,LOW);
  digitalWrite(ledY,LOW);
}
void detect_obst(){

Obstacle = digitalRead(ObstaclePin);
if(Obstacle == LOW) // Si Obstacle == LOW ==> Presence d'un obstacle(LED jaune)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.println("Attention Un obstacle");
    while(Obstacle == LOW){
      Stop();
      ledR_seule();
      buzzer_seule();
    }
  }
}
