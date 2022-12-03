int sensorPin = A0;  // pin sensor
int powerPin = 8;    // untuk pengganti VCC

#define pom 2
 
void setup() {
  pinMode (pom, OUTPUT);  
  Serial.print("Nilai kelembaban: ");
  Serial.println(bacaSensor());
  // baca setiap 2 detik
  delay(2000);
}
 
void loop() {
  // Nyalain pom
  digitalWrite(pom, LOW);//NO=NYALA
  // delay 2 detik
  delay(2000);
  digitalWrite(pom, HIGH);
  // Kasi Delay 2 detik
  delay(10000);
  
  Serial.print("Nilai kelembaban: ");
  Serial.println(bacaSensor());
  // baca setiap 2 detik
  delay(2000);
  // hidupkan power
  digitalWrite(powerPin, HIGH);
  delay(500);
}


int bacaSensor() {
  // baca nilai analog dari sensor
  int nilaiSensor = analogRead(sensorPin);
  digitalWrite(powerPin, LOW);
  // makin lembab maka makin tinggi nilai outputnya
 return 1023 - nilaiSensor;
}
