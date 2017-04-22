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
 
void setup(void){
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(pipe);
}
 
void loop(void){

  Serial.println("Enviando...");
  for (int x=0;x<255;x++)
  {     
    msg[0] = x;
    radio.write(msg, 1);
    Serial.print(x);Serial.print(", ");
  }
  
  Serial.println("");
  Serial.println("Enviado");
  delay(1000);
}
