#include <SoftwareSerial.h>
#include <Ultrasonic.h>

//Criando função de parar o robô
void parar(){
    //Desligando os motores
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
}

//Definindo direções
#define FRENTE 'F'
#define PARE 'S'
#define RE 'B'
#define ESQUERDA 'L'
#define DIREITA 'R'
#define FRENTE_ESQUERDA 'G'
#define FRENTE_DIREITA 'H'
#define RE_ESQUERDA 'I'
#define RE_DIREITA 'J'

//Definindo pinos do ultrassom
#define ECHO 10
#define TRIGGER 11

Ultrasonic ultrassom(TRIGGER, ECHO);

char direcao;
SoftwareSerial mySerial(4, 5);

//Definindo velocidade da curva
int velCurvaDireita = 127;
int velCurvaEsquerda = 127;

int distancia;

void setup() {
  //Definindo pinos do motor da direita
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);

  //Definindo pinos do motor da esquerda
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);

  //Definindo bluetooth
  Serial.begin(9600);
  mySerial.begin(9600);
  mySerial.setTimeout(5);

  //Definindo a distancia
  distancia = ultrassom.read();

  pinMode(13, OUTPUT);
  direcao = PARE;
}

void loop() {
  if (mySerial.available()) {
    direcao = mySerial.read();
  }

  int leitura = ultrassom.read();
  if(leitura > 2){
    distancia = leitura;
  }
  Serial.println(distancia);

  switch(direcao){
    case PARE:
      parar();
      break;
    case FRENTE:
      if(distancia > 30){
        //Motor direito
        digitalWrite(6, LOW); //Negativo
        digitalWrite(7, HIGH); //Positivo

        //Motor esquerdo
        digitalWrite(8, HIGH); //Positivo
        digitalWrite(9, LOW); //Negativo
        break;
      }else{
        parar();
        break;
      }
    case RE:
      //Motor direito
      digitalWrite(6, HIGH); //Negativo
      digitalWrite(7, LOW); //Positivo

      //Motor esquerdo
      digitalWrite(8, LOW); //Positivo
      digitalWrite(9, HIGH); //Negativo
      //Serial.println("RE");
      break;
    case DIREITA:
      //Motor esquerdo
      digitalWrite(8, HIGH); //Positivo
      digitalWrite(9, LOW); //Negativo
      //Serial.println("DIREITA");
      break;
    case ESQUERDA:
      //Motor direito
      digitalWrite(6, LOW); //Negativo
      digitalWrite(7, HIGH); //Positivo
      //Serial.println("ESQUERDA");
      break;
    case FRENTE_ESQUERDA:
      if(distancia > 30){
        //Motor direito
        digitalWrite(6, LOW); //Negativo
        digitalWrite(7, HIGH); //Positivo

        //Motor esquerdo
        digitalWrite(8, HIGH); //Positivo
        analogWrite(9, 255 - velCurvaEsquerda);
        //Serial.println("Dobrando a esquerda");
        break;
      }else{
        parar();
        break;
      }
    case FRENTE_DIREITA:
      if(distancia > 30){
        //Motor esquerdo
        digitalWrite(8, HIGH); //Positivo
        digitalWrite(9, LOW); //Negativo

        //Motor direito
        digitalWrite(7, HIGH); // Positivo
        analogWrite(6, 255 - velCurvaDireita); //Negativo
        break;
      }else{
        parar();
        break;
      }
    case RE_ESQUERDA:
      //Motor esquerdo
      digitalWrite(8, LOW); //Positivo
      digitalWrite(9, HIGH); //Negativo

      //Motor direito
      digitalWrite(7, LOW); // POsitivo
      analogWrite(6, velCurvaDireita); // Negativo
      break;
    case RE_DIREITA:
      //Motor direito
      digitalWrite(6, HIGH); //Negativo
      digitalWrite(7, LOW); //Positivo

      //Motor esquerdo
      digitalWrite(8, LOW); //Positivo
      analogWrite(9, velCurvaEsquerda); //Negativo
  }
  
}