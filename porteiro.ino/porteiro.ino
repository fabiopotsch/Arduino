#include <Stepper.h> // Incluindo a biblioteca do Motor de Passo

#define PORTA_FECHADA 0
#define PORTA_ABERTA 1

#define sensorDeVibracao 8

#define motor1 2
#define motor2 3
#define motor3 4
#define motor4 5

const int stepsPerRevolution = 65; // Numero de passo por volta
Stepper myStepper(stepsPerRevolution, motor1,motor2,motor3,motor4); // Faz a inicialização da Biblioteca usando as portas 8,9,10,11

int estado = 0; //estado da porta

int leituraSensorDeVibracao;

int led = 9;
int luz = 0;
int fade = 15;

void setup() {
  Serial.begin(9600);
  
  pinMode(sensorDeVibracao, INPUT);

  myStepper.setSpeed(300); // velocidade do motor definida em 300

}

void acendeLed(){
  analogWrite(led, luz);
  luz = luz + fade;
  if(luz == 0 || luz == 255){
    fade = -fade;
  }
}

void loop() {
  leituraSensorDeVibracao = digitalRead(sensorDeVibracao);
  Serial.println(estado);

  if(leituraSensorDeVibracao == 1){
    switch(estado){
      case PORTA_FECHADA:
        for (int i = 0; i < 10; i++){
                myStepper.step(-stepsPerRevolution); // sentido horario
                
        }
        estado = PORTA_ABERTA;
        break;
      case PORTA_ABERTA:
        for (int i = 0; i < 10; i++){
              myStepper.step(stepsPerRevolution); // sentido anti-horario
                
        }
        estado = PORTA_FECHADA;
        break;
    }
  }
  acendeLed();
  delay(200);

}
