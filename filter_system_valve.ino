// load libraries
#include <SPI.h>
#include <Adafruit_BLE_UART.h>

// Adafruit METRO 320 Analog Input Curve
// 0    = 0.0V
// 668  = 3.3V
// 1010 = 5.0V

// Adafruit nRF8001 Board
// Connect CLK/MISO/MOSI to hardware SPI
// Adafruit SPI Pins: CLK = 13, MISO = 12, MOSI = 11
#define ADAFRUITBLE_REQ 10
#define ADAFRUITBLE_RDY 2   // This should be an interrupt pin, on METRO 328 thats #2
#define ADAFRUITBLE_RST 9
Adafruit_BLE_UART BTLEserial = Adafruit_BLE_UART(ADAFRUITBLE_REQ, ADAFRUITBLE_RDY, ADAFRUITBLE_RST);
aci_evt_opcode_t laststatus = ACI_EVT_DISCONNECTED; // Initiate laststatus variable

// red 5mm led: https://www.adafruit.com/product/297
// select the pin for the LED
int ledPin = 3;

// current sensor: Onset CTV-A 20Amp
// output 0 - 2.5V
int sensorPinCurrent = A1;    // select the input pin for the current sensor
int sensorValueCurrent = 0;   // variable to store the value coming from the current sensor
int limitValueCurrent = 500;  // threshold for valve actuation


void setup() {
  
  // initialize digital ledPin as an output
  pinMode(ledPin, OUTPUT);

  // initialize serial
  Serial.begin(9600);

  // initialize bluetooth and set device name
  BTLEserial.setDeviceName("valveCT"); /* 7 characters max! */
  BTLEserial.begin();
  
}

void loop() {

  // Bluetooth Status____________

  // tell the nRF8001 to do whatever it should be working on
  BTLEserial.pollACI();

  // ask what is our current bluetooth status
  aci_evt_opcode_t status = BTLEserial.getState();
  
  // if the status changed....
  if (status != laststatus) {
    // print it out!
    if (status == ACI_EVT_DEVICE_STARTED) {
        Serial.println(F("* Advertising started"));
    }
    if (status == ACI_EVT_CONNECTED) {
        Serial.println(F("* Connected!"));
    }
    if (status == ACI_EVT_DISCONNECTED) {
        Serial.println(F("* Disconnected or advertising timed out"));
    }
    // oK set the last status change to this one
    laststatus = status;
  }

  // Sensor Reading and Reporting______________________

  // read value from analog pins
  sensorValueCurrent = analogRead(sensorPinCurrent);

  // print readings to UART
  if (status == ACI_EVT_CONNECTED) {

    // set message
    String d = "Current: " + String(sensorValueCurrent) + "\n";

    // We need to convert the line to bytes, no more than 20 at this time
    uint8_t sendbuffer[20];
    d.getBytes(sendbuffer, 20);
    char sendbuffersize = min(20, d.length());

    // write the data
    BTLEserial.write(sendbuffer, sendbuffersize);
  }

  // Valve Actuation__________________

  if (sensorValueCurrent < limitValueCurrent) {
    // turn the LED on (HIGH is the voltage level), wait for one second
    digitalWrite(ledPin, HIGH);
    delay(5000);
  }
  
  // turn the LED off by making the voltage LOW, wait for ten seconds
  digitalWrite(ledPin, LOW);
  delay(10000);

}
