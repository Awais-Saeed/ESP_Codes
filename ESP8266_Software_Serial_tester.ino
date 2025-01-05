// ESP8266 Software Serial tester
/*
  * Serial monitor also uses Rx Tx (UART0). Those cannot be used for UART communication.
  * ESP8266 has a second UART1 (Serial1) but the issue is that Rx cannot be used as it is reserved for some other function.
  * So, Serial1.avaiable() will not work.
  * Only Tx cannot be used
  * So, need to use some other pins. 
  * Install EspSoftwareSerial from library manager or install ZIP from
  * https://github.com/plerup/espsoftwareserial 
*/

#include <SoftwareSerial.h>

// Rx = GPIO 14 (D5) - I tested in NodeMCU Amica ESP
// Tx = GPIO 12 (D6) - I tested in NodeMCU Amica ESP
SoftwareSerial swSer(14, 12);  

// for loopback test, connect D5 to D6

// for RS232 shield connect
// ESP8266 pin D6 TXD to TTL/RS232 Tx
// ESP8266 pin D5 RXD to TTL/RS232 Rx
// for loopback test connect 9-pin D_type connector pins 2 Tx to 3 Rx (pin 5 is GND)
// connect GND pins together and VCC to 5V

void setup() {
  Serial.begin(9600);     //Initialize hardware serial with 9600 baudrate
  swSer.begin(9600);      //Initialize software serial with 9600 baudrate
  Serial.println("\nESP8266 Software serial tester started");
 }

void loop() {
  while (swSer.available() > 0) {  //wait for data at software serial
    Serial.write(swSer.read());    //Send data received from software serial to hardware serial    
  }
  while (Serial.available() > 0) { //wait for data at hardware serial
    swSer.write(Serial.read());    //send data received from hardware serial to software serial
  }
}

