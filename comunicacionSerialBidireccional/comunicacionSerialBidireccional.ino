#define led 2
#define button 4
String inString = "off";
int val = LOW;
int val2 = LOW;


void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  pinMode(led, OUTPUT);
  pinMode(button, INPUT);
  digitalWrite(button, HIGH);
}

void loop() {
  val2 = val;
  val = digitalRead(button);
  
  if(val==HIGH && val2!=val){
    Serial.println("input en alto");
  }else if(val==LOW && val2!=val){
    Serial.println("input en bajo");
  }
  
  if (Serial.available() > 0) {
    inString = String(Serial.readString());   // get incoming byte:
    Serial.print(inString+": ");
      
    if(inString==String("on")){
      Serial.println("LED ON");
      digitalWrite(led, HIGH);
    }else if(inString==String("off")){
      Serial.println("LED OFF");
      digitalWrite(led, LOW);
    }
    else{
      Serial.println("Comando inválido");
    }
  }

}
