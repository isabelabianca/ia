/*

JOGO DA MEMORIA - COM ARDUINO E SERIAL



Arnaldo Viana @2021

inspirado em: http://jeknowledge.github.io/academy-articles/jogo-da-memoria
*/

String recebido;
String sequenciaNumerica = "";
int led;
long numeroGerado;
char stateGame = 0;
int sequencia;


void setup() {
  // Iniciar comunicacao serie
  Serial.begin(9600);
  // Definir LEDs como OUTPUTs pinos 7, 8, 9 e 10
  for(int led = 7; led <= 10; led++){
    pinMode(led, OUTPUT);
  }
  // Definir a seed do gerador de números aleatórios
  randomSeed(analogRead(0));

}
/*
stateGame = 0 -- inicio do jogo
stateGame = 1 -- jogo nivel1
stateGame = 2 -- jogo nivel2
stateGame = 3 -- jogo nivel3
stateGame = 4 -- fim de jogo "Game over"
stateGame = 5 -- jogar novamente?
*/
void loop() {
  switch (stateGame) {
    case 0:
      // inicio de jogo
      Serial.println("* INICIO *");
      Serial.println("Comecar? (s/n)");
      leserial();
      if (recebido.equalsIgnoreCase("s")){
        stateGame = 1;
        Serial.println("Jogo começando...");
        piscaled(700,3);
      } else {
        stateGame = 3;
        Serial.println("Jogo não iniciado"); 
        piscaled(300,5);     
      }
      break;
    case 1:
      // Nivel 1 
      Serial.println("* Nivel 1 *");
      geraSequencia(1000, 4); 
      leserial();
      if (recebido == sequenciaNumerica){
        stateGame = 2;
        Serial.println("Parabens! proximo nivel.");
        piscaled(1000,3);
      } else {
        stateGame = 4;
        Serial.println("Errooooo!!!"); 
        piscaled(300,5);     
      }
      break;
    case 2:
      // Nivel 2 
      Serial.println("* Nivel 2 *");
      geraSequencia(1000, 6); 
      leserial();
      if (recebido == sequenciaNumerica){
        stateGame = 3;
        Serial.println("Parabens! proximo nivel.");
        piscaled(1000,3);
      } else {
        stateGame = 4;
        Serial.println("Errooooo!!!"); 
        piscaled(300,5);     
      }
      break;
     case 3:
      // Nivel 3 
      Serial.println("* Nivel 3 *");
      geraSequencia(1000, 8); 
      leserial();
      if (recebido == sequenciaNumerica){
        stateGame = 3;
        Serial.println("Parabens! proximo nivel.");
        piscaled(1000,3);
      } else {
        stateGame = 4;
        Serial.println("Errooooo!!!"); 
        piscaled(300,5);     
      }
      break;
    case 4:
      // Game over!!!
      Serial.println("Game Over"); 
      piscaled(100,5);
      stateGame = 5;
      break;
    case 5:
      Serial.println("jogar novamente? (s/n)"); 
      leserial();
      if (recebido.equalsIgnoreCase("s")){
        stateGame = 1;
        Serial.println("Jogo comecando...");
        piscaled(1000,3);
      } else {
        stateGame = 5;
        Serial.println("Jogo nao iniciado"); 
        piscaled(300,5);     
      }
      break;
  }
}

void leserial(){

  Serial.println("* Insera sua resposta *");

  // Aguardar a resposta do usuario
  while (Serial.available() == 0)
  {}

  // Guardar o valor introduzido pelo utilizador no Serial Monitor numa String user
  if (Serial.available())
  {
    recebido = Serial.readString();
  }
}

void piscaled(int tempo, int vezes){
  for(int i = 0;i < vezes; i++){
    for(int led = 7; led <= 10; led++){
      digitalWrite(led, HIGH);
    }
    delay(tempo);
    for(int led = 7; led <= 10; led++){
      digitalWrite(led, LOW);
    }
    delay(tempo);
  }
}

void geraSequencia (int tempo, int sequencia){
  // Criar uma lista de inteiros com o tamanho que e passado como argumento
  int ordemLeds[sequencia];

  // Gerar sequencia aleatoria
  for (int i = 0; i < sequencia; i++){
    numeroGerado = random(1, 5);
    ordemLeds[i] = numeroGerado;
  }

  // Inicialmente, a String sequenciaNumerica é uma String vazia
  sequenciaNumerica = "";

  // Pisca os LEDs na sequencia gerada
  for (int j = 0; j < sequencia; j++){
    led = ordemLeds[j];
    if (led == 1){
      digitalWrite(7, HIGH);
      delay(tempo);
      digitalWrite(7, LOW);
      delay(tempo);
    }else if (led == 2){
      digitalWrite(8, HIGH);
      delay(tempo);
      digitalWrite(8, LOW);
      delay(tempo);
    }else if (led == 3){
      digitalWrite(9, HIGH);
      delay(tempo);
      digitalWrite(9, LOW);
      delay(tempo);
    }else if (led == 4){
      digitalWrite(10, HIGH);
      delay(tempo);
      digitalWrite(10, LOW);
      delay(tempo);
    }
    // Converte a lista numa String   
    sequenciaNumerica = sequenciaNumerica + led;
  }
}
