int btn = D8;
void setup() {
  // put your setup code here, to run once:
  pinMode(btn, INPUT);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(btn) == HIGH){
    Serial.println("ON");
  } else {
    Serial.println("OFF");
  }
  delay(1000);
}
