int trigPin = A0;
int echoPin = A1;
int buzzPin = 12;
float distanceCm;
int ledGreenPin = 11;
int ledRedPin = 10;
boolean buzzOn;
unsigned long previousMillis = 0;
const long buzzInterval = 1000;
void setup() {
  pinMode(ledGreenPin, OUTPUT);
    pinMode(ledRedPin, OUTPUT);

  pinMode(buzzPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Lee la duración del eco en microsegundos
  long pingTravelTime = pulseIn(echoPin, HIGH);

  // Convierte la duración del eco en centímetros
  distanceCm = (pingTravelTime / 2) / 29.1;  // Dividido por 29.1 para obtener cm

  Serial.print("Distancia: ");
  Serial.print(distanceCm);
  Serial.println(" cm");
  delay(100);  // Puedes ajustar el tiempo de espera según tus necesidades
  unsigned long currentMillis = millis();
  if (distanceCm <= 10) {
    if (!buzzOn) {
      buzzOn = true;
      previousMillis = currentMillis;
      tone(buzzPin, 2500);
    }
    if (currentMillis - previousMillis >= buzzInterval) {
      noTone(buzzPin);
      buzzOn = false;
    }
  } else {
    noTone(buzzPin);  // Apaga el buzzer si la distancia es mayor que 10 cm
    delay(600);
    buzzOn = false;

  }if(distanceCm <= 10){
    digitalWrite(ledRedPin, HIGH);
    digitalWrite(ledGreenPin, LOW);

  }else{
digitalWrite(ledRedPin, LOW);
digitalWrite(ledGreenPin, HIGH);
  }
  
}
