#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#define DHTPIN 9
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
#include <Servo.h>
Servo servo;
Servo servo1;
#define trigPin 2
#define echoPin 3
LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x3F, 16 column and 2 rows27or3F
int light =5;
int fan = 6;
int fire = 11;
int pump = 4;
int buzzar = 7;
int pHInputPin = A0;
int moisture = A1;
int fire_read;
int mois_read;
int sensorValue;
long duration;
long distance;
int count=0;
int count1=1;
// Define the voltage range of the pH sensor (0-5V)
float calibration_value = 21.34;
int phval = 0;
unsigned long int avgval;
int buffer_arr[10],temp;
void setup() {
Serial.begin(9600);
//pinMode(pHInputPin,INPUT);
pinMode(fire,INPUT);
pinMode(light,OUTPUT);
pinMode(fan,OUTPUT);
pinMode(buzzar,OUTPUT);
pinMode(trigPin,OUTPUT);
pinMode(echoPin,INPUT);
pinMode(moisture,INPUT);
pinMode(pump,OUTPUT);
servo.attach(10);
servo1.attach(12);
dht.begin(); // initialize the sensor
lcd.init(); // initialize the lcd
lcd.begin(16,2);
lcd.backlight(); // open the backlight
}
void loop() {
// put your main code here, to run repeatedly:
sensorValue = analogRead(pHInputPin);
fire_read = digitalRead(fire);
mois_read = analogRead(moisture);
Serial.print("moisture");
Serial.println( mois_read);
float humi = dht.readHumidity(); // read humidity
float tempC = dht.readTemperature(); // read temperature
lcd.clear();
lcd.setCursor(0, 0); // start to print at the first row
lcd.print("T:");
lcd.print(tempC); // print the temperature
Serial.print("temp");
Serial.println(tempC);

if(tempC > 37){
phsensor();
digitalWrite(fan,HIGH);
digitalWrite(light,LOW);
lcd.setCursor(0, 1); // start to print at the first row
lcd.print("Temp Is High");
}
if(tempC < 32){
phsensor();
digitalWrite(fan,LOW);
digitalWrite(light,HIGH);
}


if(fire_read == LOW){
phsensor();
digitalWrite(buzzar,LOW);
}
if(fire_read == HIGH){
digitalWrite(buzzar,HIGH);
lcd.setCursor(0, 1); // start to print at the first row
lcd.print("FIRE Detected");
delay(1500);
}


if(mois_read > 250){
phsensor();
digitalWrite(pump,LOW);
}
if(mois_read <250){
phsensor();
digitalWrite(pump,HIGH);
}


digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance= duration*0.034/2;
Serial.print("distance ");
Serial.println(distance);
Serial.print(" cm");

if(distance <7){
phsensor();
servo.write(30);
//digitalWrite(buzzar,LOW);
}
if(distance > 7){
phsensor();
servo.write(100);
delay(2000);
//digitalWrite(buzzar,HIGH);
}


phsensor();
math();
delay(500);
}



void phsensor(){
sensorValue = analogRead(A0);
float pH = (sensorValue * 5.0 / 1024.0)+1.8;
// Print the pH value to the serial monitor
Serial.print("pH = ");
Serial.println(pH);
lcd.setCursor(9, 0); // start to print at the first row
lcd.print("pH:");
lcd.print(pH);
// Wait for a short time before taking the next reading
delay(100);


if(pH > 5){
  lcd.setCursor(0, 1);
lcd.print("Ph lvl Normal");
delay(500);
}
if(pH < 5){
lcd.setCursor(0, 1);
lcd.print("Ph lvl Abnormal");
delay(500);
}

delay(500);
}
void math(){
Serial.println(count1);
count1 = count++;
if(count<11){
servo1.write(126);
}
if(count>10){
servo1.write(0);
count=0;
count1=0;
delay(1000);
}
}
