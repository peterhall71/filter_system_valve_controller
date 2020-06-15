

// photoresistor: https://www.adafruit.com/product/161
int sensorPinPhoto = A0;    // select the input pin for the photoresistor
int sensorValuePhoto = 0;   // variable to store the value coming from the sensor
int limitValuePhoto = 600;

// red led
// select the pin for the LED
int ledPin = 2;

// current sensor: Onset CTV-A 20Amp
int sensorPinCurrent = A1;  // select the input pin for the current sensor
int sensorValueCurrent = 0;   // variable to store the value coming from the current sensor


void setup() {
  
  // initialize digital ledPin as an output.
  pinMode(ledPin, OUTPUT);

  // initialize serial:
  Serial.begin(9600);
  
}

void loop() {

  // read the value from the sensors:
  sensorValuePhoto = analogRead(sensorPinPhoto);
  sensorValueCurrent = analogRead(sensorPinCurrent);

  // print readings to serial
  Serial.print("Photoresistor: ");
  Serial.println(sensorValuePhoto);
  Serial.print("Current Sensor: ");
  Serial.println(sensorValueCurrent);

  if (sensorValuePhoto < limitValuePhoto) {

    // turn the LED on (HIGH is the voltage level), wait for one second
    digitalWrite(ledPin, HIGH);
    delay(1000);
    
  }
  
  // turn the LED off by making the voltage LOW, wait for one second
  digitalWrite(ledPin, LOW);

  delay(1000);

}
