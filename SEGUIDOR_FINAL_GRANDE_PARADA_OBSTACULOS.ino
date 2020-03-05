#include "AFMotor.h"
#include "Ultrasonic.h"

int velocidade = 120,
    sensorInfraE,
    sensorInfraC,
    sensorInfraD,
    distanciaE,
    distanciaC,
    distanciaD;

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

HC_SR04 sensorE(40, 41);
HC_SR04 sensorC(42, 43);
HC_SR04 sensorD(44, 45);

void setup() {
  pinMode(46, INPUT);
  pinMode(48, INPUT);
  pinMode(50, INPUT);

  Serial.begin(9600);
}

//FUNÇÕES
void distancia() {
  distanciaE = sensorE.distance();
  distanciaC = sensorC.distance();
  distanciaD = sensorD.distance();
}

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

//ANTIHORARIO LEVE
void antihorarioleve() {
  motor1.run(RELEASE);
  motor2.setSpeed(120);
  motor2.run(BACKWARD);
  motor3.setSpeed(120);
  motor3.run(FORWARD);
  motor4.setSpeed(120);
  motor4.run(FORWARD);
}

//HORARIO LEVE
void horarioleve() {
  motor1.setSpeed(120);
  motor1.run(FORWARD);
  motor2.setSpeed(120);
  motor2.run(FORWARD);
  motor3.run(RELEASE);
  motor4.setSpeed(120);
  motor4.run(BACKWARD);
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
  sensorInfraE = digitalRead(46);
  sensorInfraC = digitalRead(48);
  sensorInfraD = digitalRead(50);

  distancia();
  
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

  while(distanciaE < 25 || distanciaC < 40 || distanciaD < 25) {
    parar();
    distancia();
  }
}
