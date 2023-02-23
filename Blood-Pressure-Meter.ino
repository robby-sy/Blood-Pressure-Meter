#define ENA 5
#define IN1 6
#define IN2 7
float data_sensor, Vout, P, Pmmhg, Yin, Yinn, Dy, Sistolik, Diastolik,New_bloodPress, Last_bloodPress;
int tresh;
bool rise, disp_stats;
void setup() {
  Serial.begin(115200);
  digitalWrite(ENA, HIGH);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  disp_stats = false;
}

void loop() {
  data_sensor = analogRead(A1);
  Vout = ((data_sensor / 1023.00) * 5000) / 11 ;
  P = (Vout - 0.04 * 5000) / (0.0018 * 5000);
  Pmmhg = P * 7.500617;
  Yin = (0.99 * Yinn) + (0.01 * Pmmhg);
  //Serial.print(Yin);
  //Serial.print(" ");
  //Serial.println(Pmmhg);
  if (Yin > 150) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    delay(1000);
    while (true) {
      data_sensor = analogRead(A1);
      Vout = (data_sensor / 1023.00 * 5000) / 11.3;
      P = (Vout - 0.04 * 5000) / (0.0018 * 5000);
      Pmmhg = P * 7.500617;
      Yin = ((0.97 * Yinn) + (0.03 * Pmmhg));
      Dy = Yin - Yinn;
      if (Yin > 60) {
        tresh = 3;
      }
      else {
        tresh = 10;
      }
      if (Dy * 100 > tresh) {
        rise = true;
        //Serial.print(80);
        //Serial.print(" ");
      }
      else if (Dy * 100 < 0 && rise == true) {
        //Serial.print(50);
        //Serial.print(" ");
        getData(Pmmhg);
        Serial.print(Sistolik);
        Serial.print(" ");
        Serial.println(Diastolik);
        rise = false;
      }
      else {
        //Serial.print(20);
        //Serial.print(" ");
      }
      Yinn = Yin;
      delay(10);
      //Serial.print(Yin);
      //Serial.print(" ");
      //Serial.println(Pmmhg);
      if (Pmmhg < 40) {
        digitalWrite(13, LOW);
        disp_stats = true;
        break;
      }
    }
  }
  else {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
  }
  if (disp_stats) {
    while (true) {
      Serial.print(Sistolik);
      Serial.print(" ");
      Serial.println(Diastolik);
    }
  }
  Yinn = Yin;
  delay(10);
}

void getData(float Blood_Press) {
  New_bloodPress = Blood_Press;
  if (New_bloodPress - Last_bloodPress > 10) {
    Sistolik = New_bloodPress;
    Serial.print("masuk");
    Serial.print(" ");
  }
  Last_bloodPress = New_bloodPress;
  Diastolik = New_bloodPress;
}
