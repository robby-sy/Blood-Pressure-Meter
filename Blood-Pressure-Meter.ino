#define ENA 5
#define IN1 6
#define IN2 7
float data_sensor, Vout, P;
void setup() {
  Serial.begin(9600);
  digitalWrite(ENA, HIGH);
}

void loop() {
  data_sensor = analogRead(A1);
  Vout = (data_sensor / 1023.00 * 5000) / 11;
  P = (Vout - 0.04 * 5000) / (0.0018 * 5000);
  Serial.println(P);
  if (P > 20) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    while (true) {
      data_sensor = analogRead(A1);
      Vout = (data_sensor / 1023.00 * 5000) / 11;
      P = (Vout - 0.04 * 5000) / (0.0018 * 5000);
      Serial.println(P);
    }
  }
  else {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
  }
}

void sensor() {
  data_sensor = analogRead(A1);
  Vout = (data_sensor / 1023.00 * 5000) / 11;
  P = (Vout - 0.04 * 5000) / (0.0018 * 5000);
}
