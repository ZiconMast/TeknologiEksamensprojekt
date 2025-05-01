const int uvSensorPin = A0;
const int relayPin = 7;

unsigned long timerStart = 0;
bool timerActive = false;

const unsigned long delayTime = 900000; // 15 minutter

void setup() {
  Serial.begin(9600);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW); // Starter med relæ SLUKKET (lampen slukket)
}

void loop() {
  int uvAnalogValue = analogRead(uvSensorPin);
  float voltage = (uvAnalogValue / 1023.0) * 5.0;
  float uvIndex = voltage * 10.0;

  Serial.print("UV-indeks: ");
  Serial.println(uvIndex, 2);

  if (uvIndex >= 3.0 && !timerActive) {
    timerActive = true;
    timerStart = millis();
    digitalWrite(relayPin, HIGH); // TÆNDER relæet = lampen tændes via NO
    Serial.println("Lampen TÆNDES i 15 minutter");
  }

  if (timerActive && millis() - timerStart >= delayTime) {
    timerActive = false;
    digitalWrite(relayPin, LOW); // SLUKKER relæet = lampen slukker
    Serial.println("15 minutter gået – lampen SLUKKES");
  }

  delay(500);
}
