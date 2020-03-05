#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "AFMotor.h"
#include "Ultrasonic.h"

int velocidade = 120,
    sensorInfraE,
    sensorInfraC,
    sensorInfraD;
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);
const int LED = D0;
const int LM35 = A0; // Define o pino que lera a saída do LM35
float temperatura; // Variável que armazenará a temperatura medida
char auth[] = "11gJ_iX5m-EqK_xKwGnDwewtWtYOwYKr";
char ssid[] = "Robertdvieira";
char pass[] = "arobed39";

void setup() {
  pinMode(46, INPUT);
  pinMode(48, INPUT);
  pinMode(50, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(LM35, INPUT);
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
}

//FUNÇÕES
//FRENTE
void frente(int vel) {
  motor1.setSpeed(vel);
  motor1.run(FORWARD);
  motor2.setSpeed(vel);
  motor2.run(FORWARD);
  motor3.setSpeed(vel);
  motor3.run(FORWARD);
  motor4.setSpeed(vel);
  motor4.run(FORWARD);
}

//DIREITA
void direita(int vel) {
  motor1.setSpeed(vel);
  motor1.run(FORWARD);
  motor2.setSpeed(vel);
  motor2.run(FORWARD);
  motor3.setSpeed(vel * 0.7);
  motor3.run(FORWARD);
  motor4.setSpeed(vel * 0.7);
  motor4.run(FORWARD);
}

//ESQUERDA
void esquerda(int vel) {
  motor1.setSpeed(vel * 0.7);
  motor1.run(FORWARD);
  motor2.setSpeed(vel * 0.7);
  motor2.run(FORWARD);
  motor3.setSpeed(vel);
  motor3.run(FORWARD);
  motor4.setSpeed(vel);
  motor4.run(FORWARD);
}

//HORARIO
void horario() {
  motor1.setSpeed(255);
  motor1.run(FORWARD);
  motor2.setSpeed(255);
  motor2.run(FORWARD);
  motor3.setSpeed(255);
  motor3.run(BACKWARD);
  motor4.setSpeed(255);
  motor4.run(BACKWARD);
}

//ANTIHORARIO
void antihorario() {
  motor1.setSpeed(255);
  motor1.run(BACKWARD);
  motor2.setSpeed(255);
  motor2.run(BACKWARD);
  motor3.setSpeed(255);
  motor3.run(FORWARD);
  motor4.setSpeed(255);
  motor4.run(FORWARD);
}

//TRAS
void tras(int vel) {
  motor1.setSpeed(vel);
  motor1.run(BACKWARD);
  motor2.setSpeed(vel);
  motor2.run(BACKWARD);
  motor3.setSpeed(vel);
  motor3.run(BACKWARD);
  motor4.setSpeed(vel);
  motor4.run(BACKWARD);
}

//PARAR
void parar() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void loop() {
  Blynk.run();
  
  sensorInfraE = digitalRead(46);
  sensorInfraC = digitalRead(48);
  sensorInfraD = digitalRead(50);
  
  temperatura = (float(analogRead(LM35))*3/(1023))/0.01;
  
  Blynk.virtualWrite(V0, temperatura);

  if(sensorInfraE == 1 && sensorInfraC == 1 && sensorInfraD == 0) { //DIREITA
    horario();
  }
  else if(sensorInfraE == 1 && sensorInfraC == 0 && sensorInfraD == 0) { //DIREITA LEVE
    frente(velocidade);
  }
  else if(sensorInfraE == 0 && sensorInfraC == 0 && sensorInfraD == 0) { //FRENTE
    frente(velocidade);
  }
  else if(sensorInfraE == 0 && sensorInfraC == 0 && sensorInfraD == 1) { //ESQUERDA LEVE
    frente(velocidade);
  }
  else if(sensorInfraE == 0 && sensorInfraC == 1 && sensorInfraD == 1) { //ESQUERDA
    antihorario();
  }
  else if(sensorInfraE == 1 && sensorInfraC == 1 && sensorInfraD == 1) { //TRAS
    tras(velocidade);
  }
  else { //PARAR
    parar();
  }
}
