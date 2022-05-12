/* 
Andriely França
Carrinho com dois motores de passo controlado por controle remoto
*/

// bibliotecas pra cotrole dos motores de passo e letura do senor infra vermelho  
#include <Stepper.h> 
#include <IRremote.h> 

// variavel para guardar os códgos lidos 
float Codigo; 
// variavel para controle dos passos do motor
const int passos = 500; 

// variaveis para leitura do infra vermelho
IRrecv irrecv(2); 
decode_results results;  

//Utilizando as portas digitais para conexao ao motor
Stepper motorDir(passos,8,10,9,11); 
Stepper motorEsq(passos ,3,5,4,6);  
int buz = 7;
int farol = 12;
void setup() 
{ 
 // Velocidade inicial do motor (MAX 100)
 motorDir.setSpeed(60);
 motorEsq.setSpeed(60);
 //inicia a leitura do senor infra vermelho
 irrecv.enableIRIn();
 // defiindo as saídas do motor e da buzina
 pinMode(buz,OUTPUT);
 pinMode(farol,OUTPUT);
} 
 
void loop() {
 // cerifica se o senso IR recebeu algum código
 if (irrecv.decode(&results)) 
 { 
 Codigo = (results.value); 
 // executa umafução deacorso com o código lido
 if (Codigo == 16718055)  
 { 
 Frente(); 
 } 
 
 else if (Codigo == 16730805)  
 { 
 Atras(); 
 Buzina();
 } 
 
 else if (Codigo == 16734885) 
 { 
 Direita(); 
 } 
 
 else if (Codigo == 16716015)  
 { 
 Esquerda(); 
 } 
 
 else if(Codigo == 0xFF02FD)
 {
 Buzina();
 }
 else if(Codigo == 0xFF02)
 {
 AcenderFarol();
 }
 else if(Codigo == 0xFF02F)
 {
 ApagarFarol();
 }
 //  finaliz a leitura do IR e reinca o loop
 irrecv.resume();
 
 } 
} 

// funções de control do carrinho
void Frente(){
 motorDir.step(-2); 
 motorEsq.step(2);
 delay(2);
}
void Atras(){
 motorDir.step(2); 
 motorEsq.step(-2);
 delay(2);
}
void Esquerda(){
 motorDir.step(2); 
 delay(2);
}
void Direita(){
 motorEsq.step(2);
 delay(2);
}
void Buzina(){
  digitalWrite(buz, HIGH);
  delay(50);
  digitalWrite(buz, LOW);
}
void AcenderFarol(){
  digitalWrite(farol, HIGH);
}
void ApagarFarol(){
  digitalWrite(farol, LOW);
}
