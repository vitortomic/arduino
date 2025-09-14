#define buzzerPin 3 // Or any other digital pin you used
#define trigPin 4  // HC-SR04 Trigger
#define echoPin 5  // HC-SR04 Echo
#define rgbRedPin 8
#define rgbGreenPin 9
#define rgbBluePin 10

int distance;

void setRGBColor(bool red, bool green, bool blue) {
  digitalWrite(rgbRedPin, red);
  digitalWrite(rgbGreenPin, green);
  digitalWrite(rgbBluePin, blue);
}

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(rgbRedPin, OUTPUT);
  pinMode(rgbGreenPin, OUTPUT);
  pinMode(rgbBluePin, OUTPUT);
  Serial.begin(9600);
  distance = 100;
}

void loop() {
  long duration;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;
  
  if (distance > 15) {
    // Green LED - safe distance
    setRGBColor(LOW, HIGH, LOW);
    noTone(buzzerPin);
  } else if (distance >= 5 && distance <= 15) {
    // Yellow LED - caution distance
    setRGBColor(HIGH, HIGH, LOW);
    tone(buzzerPin, 1000);
  } else if (distance >= 0 && distance <= 4) {
    // Red LED - danger distance
    setRGBColor(HIGH, LOW, LOW);
    tone(buzzerPin, 2000);
  }
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(100);
}
