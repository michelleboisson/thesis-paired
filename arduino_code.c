#include <SoftwareSerial.h>

//uno
int bluetoothTx = 2;  // TX-O pin of bluetooth mate, Arduino D2
int bluetoothRx = 3;  // RX-I pin of bluetooth mate, Arduino D3

int button = 7;
int digitalLED = 12;
boolean sendData = false;
int dataFromBT;
boolean bluetoothReady = false;

int prevVal = 0, val = 0;

long lastButtonPush = 0;        // will store last time button was pushed
long interval = 3000;           // time to wait for next push, interval at which to blink (milliseconds)

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

void setup()
{
  Serial.begin(9600);  // Begin the serial monitor at 9600bps
  pinMode(digitalLED, OUTPUT);  
  pinMode(button, INPUT);

  bluetooth.begin(115200);  // The Bluetooth Mate defaults to 115200bps
  bluetooth.print("$$$");  // Enter command mode
  delay(100);  // Short delay, wait for the Mate to send back CMD
  bluetooth.println("U,9600,N");  // Temporarily Change the baudrate to 9600, no parity
  // 115200 can be too fast at times for NewSoftSerial to relay the data reliably
  bluetooth.begin(9600);  // Start bluetooth serial at 9600
}

void loop()
{
  unsigned long currentMillis = millis();
  if(bluetooth.available())  // If the bluetooth sent any characters
  {
    Serial.println("bt available");
    //bluetoothReady = true;
    dataFromBT = (char)bluetooth.read();
    
    // Send any characters the bluetooth prints to the serial monitor
    Serial.print("-------------- bt data: ");
    Serial.println(dataFromBT);
 
     //if (dataFromBT != '1') {
      Serial.println("-------------GOT IT------------------");
      // Turn on LEFD
      digitalWrite(digitalLED, HIGH);
    //}
  }else{
    //Serial.println("bluetooth not available");
    digitalWrite(digitalLED, LOW);
  }
    
  //int analogValue = analogRead(analogPin);
  int val = digitalRead(button);

  Serial.println(val);
  //bluetooth.println(val);
  
  if (sendData == false) {
    if (val == 1){
      if (currentMillis - lastButtonPush > interval){
        lastButtonPush = currentMillis;
        bluetooth.println(val);
        Serial.print("pot value: ");
        Serial.println(val);
        sendData = true;
      }
      sendData = false;
    }
  }
  
  
  delay(100);

}
