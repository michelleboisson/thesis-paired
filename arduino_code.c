#include <SoftwareSerial.h>

//uno
int bluetoothTx = 3;  // TX-O pin of bluetooth mate, Arduino D2
int bluetoothRx = 2;  // RX-I pin of bluetooth mate, Arduino D3

int analogPin = A0;
int digitalLED = 12;
boolean sendData = true;
int dataFromBT;

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

void setup()
{
  Serial.begin(9600);  // Begin the serial monitor at 9600bps
  pinMode(digitalLED, OUTPUT);

  bluetooth.begin(115200);  // The Bluetooth Mate defaults to 115200bps
  bluetooth.print("$$$");  // Enter command mode
  delay(100);  // Short delay, wait for the Mate to send back CMD
  bluetooth.println("U,9600,N");  // Temporarily Change the baudrate to 9600, no parity
  // 115200 can be too fast at times for NewSoftSerial to relay the data reliably
  bluetooth.begin(9600);  // Start bluetooth serial at 9600
}

void loop()
{
  if(bluetooth.available())  // If the bluetooth sent any characters
  {
    Serial.println("bt available");
    dataFromBT = (char)bluetooth.read();

    // Send any characters the bluetooth prints to the serial monitor
    Serial.print("-------------- bt data: ");
    Serial.println(dataFromBT);

     if (dataFromBT == '1') {
      Serial.println("-------------GOT IT------------------");
      // Turn on LEFD
      digitalWrite(digitalLED, HIGH);
    }
  }
// if (dataFromBT == '0') {
    // Turn off LED
  //    digitalWrite(13, LOW);
    //} else




   /* else{
      // Turn off LED
      digitalWrite(13, LOW);
    }
    */

  int analogValue = analogRead(analogPin);
  bluetooth.println(analogValue);
  Serial.print("pot value: ");
  Serial.println(analogValue);
  //delay(1000);

}
