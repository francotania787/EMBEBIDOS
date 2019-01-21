int pin=A0;
int val=0;
char start='0';
int medida;

void setup() {
  Serial.begin(9600);

}

void loop() {
  val = analogRead(A0);
    medida = map(val,0,1023,0,100);
    Serial.println(medida);
delay(1000);
}
