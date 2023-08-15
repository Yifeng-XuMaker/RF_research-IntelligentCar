#include <SPI.h>
#include <RF24.h>
RF24 radio(9, 10); 
const byte address[6] = "00001"; 

void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.setAutoAck(true);
  radio.enableDynamicPayloads();
  radio.stopListening();

}

void loop() {
   int Data[2];
   Data[0]=123;
   Data[1]=789; 
   radio.write(&Data, sizeof(Data));
   delay(10);

}
