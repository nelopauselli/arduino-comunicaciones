#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>


int msg[1];
RF24 radio(9,10);
const uint64_t pipe = 0xE8E8F0F0E1LL;
int lastmsg = 1;

volatile bool send = false;


void setup(void) {
  Serial.begin(9600);
  radio.begin();

  pinMode(3, INPUT);
  attachInterrupt(digitalPinToInterrupt(3), trigger_send, FALLING);
  
  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);
  
  pinMode(5, OUTPUT);
  digitalWrite(5, LOW);

  modoReceptor();
}

void modoReceptor(){
  Serial.println("Modo receptor");
  radio.openReadingPipe(1, pipe);
  radio.startListening();
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
}

void modoEmisor(){
  Serial.println("Modo emisor");
  radio.stopListening();
  radio.openWritingPipe(pipe);
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
}

void trigger_send(){
  send = true;
  Serial.println("trigger");
}

void loop(void){
  if(send){
    send = false;
    modoEmisor();
    msg[0] = 22;
    radio.write(msg, 1);
    delay(10);
    Serial.println("Mensaje enviado");
    modoReceptor();
    delay(100);
  }
  
  if (radio.available()){
    bool done = false;
      
    while (!done){
      done = radio.read(msg, 2); 
      lastmsg = msg[0];
      
      Serial.println(lastmsg);
     }
   }
}
