#include <VirtualWire.h>
#include <LiquidCrystal.h>
#include <Ultrasonic.h>

#define tx            8 
#define TRIGGER_PIN   6
#define ECHO_PIN      7

Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int s1= 10;
int s2= 9 ;
int x =0;
int i1 =0;
int i2 =0;
double velocidade = 0;
char Valor_CharMsg[4];
float cmMsec1;
float cmMsec2; 
double all[] = {velocidade , cmMsec2 ,cmMsec1 ,i1 ,i2};
void setup() {

    Serial.begin(9600);
    lcd.begin(16, 2); 
    pinMode(s1, INPUT);
    pinMode(s2, INPUT);
    lcd.clear();
    //vw_set_tx_pin(tx); // define a porta que nos iremos usar 
    //vw_setup(2000);
}

void loop() {
  i1 =digitalRead (s1);
  i2 =digitalRead (s2);
  float cmMsec1,cmMsec2, inMsec;
  long microsec = ultrasonic.timing();
  cmMsec1 = ultrasonic.convert(microsec, Ultrasonic::CM);
    Serial.print("- CM1: ");
    Serial.println(cmMsec1);
    Serial.println(i1);
    Serial.println(i2);
    delay(3000);
  microsec = ultrasonic.timing();
  cmMsec2 = ultrasonic.convert(microsec, Ultrasonic::CM);
    Serial.print("- CM2: ");
    Serial.println(cmMsec2);
    Serial.println(i1);
    Serial.println(i2);
  if(i1 == HIGH && i2 == LOW){
    lcd.setCursor(0,0);
    lcd.print(cmMsec1);
    lcd.setCursor(0,1);
    lcd.print("normal "); 
    }else  if(i1 == LOW  && i2 == LOW){
    lcd.setCursor(0,0);
    lcd.print(cmMsec1);
    lcd.setCursor(0,1);
    lcd.print("alerta "); 
    }else  if(i1 == LOW && i2 == HIGH){
    lcd.setCursor(0,0);
    lcd.print(cmMsec1);
    lcd.setCursor(0,1);
    lcd.print("critico"); 
    }else  if(i1 == HIGH && i2 == HIGH){
    lcd.setCursor(0,0);
    lcd.print(cmMsec1); 
    lcd.setCursor(0,1);
    lcd.print("irineu "); 
    }
  velocidade = ((cmMsec2-cmMsec1)/3);
  //Serial.println(velocidade);
  if (velocidade <0){
    Serial.print("Enchendo ");
    Serial.println((velocidade)*-1);  
    }else if( velocidade > 0) {
    Serial.print("esvaziando"); 
    Serial.println(velocidade);     
    }
     
      itoa(all,Valor_CharMsg,10); 
      vw_send((uint8_t*)Valor_CharMsg, strlen(Valor_CharMsg));
      vw_wait_tx();
      Serial.println(Valor_CharMsg); // escreve o valor da mensagem na tela 
    }
