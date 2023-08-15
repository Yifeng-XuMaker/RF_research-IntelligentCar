#include <SPI.h>
#include <RF24.h>
RF24 radio(9 , 10); 
const byte address[6] = "00001"; 

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.setAutoAck(true);
  radio.enableDynamicPayloads();
  radio.startListening(); 
}

void loop() {
  if (radio.available()) {
    
    int Data[2];
    radio.read(&Data, sizeof(Data));
    Serial.print(Data[0]);
    Serial.print(", ");
    Serial.println(Data[1]);
    delay(10);
    
  }

}
