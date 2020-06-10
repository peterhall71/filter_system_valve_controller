
// photoresistor: https://www.adafruit.com/product/161


int sensorPin = A0;    // select the input pin for the photoresistor
int ledPin = 2;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor
int limitValue = 500;


void setup() {
  
  // initialize digital ledPin as an output.
  pinMode(ledPin, OUTPUT);

  // initialize serial:
  Serial.begin(9600);
  
}

void loop() {

  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);

  // print reading to serial
  Serial.print(sensorValue);
  Serial.println();

  if (sensorValue < limitValue) {

    // turn the LED on (HIGH is the voltage level), wait for one second
    digitalWrite(ledPin, HIGH);
    delay(5000);

    // turn the LED off by making the voltage LOW, wait for one second
    digitalWrite(ledPin, LOW);

  }

  delay(1000);

}
