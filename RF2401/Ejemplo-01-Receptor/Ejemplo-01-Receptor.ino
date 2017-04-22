// Gracias Prometec por el tutorial!
// referencia:
//  * http://www.prometec.net/nrf2401/
//  * http://shanes.net/simple-nrf24l01-with-arduino-sketch-and-setup/
// Libreria:
// RF24 libraries by maniacbug (https://github.com/maniacbug/RF24)

#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>

int msg[1];
RF24 radio(9,10);
const uint64_t pipe = 0xE8E8F0F0E1LL;
int lastmsg = 1;
 
void setup(void){
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1,pipe);
  radio.startListening();
  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);
}
 
void loop(void){
  if (radio.available()){
    bool done = false;  
      
    while (!done){
      done = radio.read(msg, 2); 
      lastmsg = msg[0];
      
      if(lastmsg==26){
        digitalWrite(4, HIGH);
      } else if (lastmsg==123){
        digitalWrite(4, LOW);
      }
            
      Serial.println(lastmsg);
     }
   }
}
