#define led 2
#define button 4
//String inString = "off";
unsigned char* inString = 'a';
int val = LOW;
int val2 = LOW;


void setup() {
  Serial.begin(250000);
  Serial.setTimeout(1);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  pinMode(led, OUTPUT);
  pinMode(button, INPUT);
  digitalWrite(button, HIGH);
}

void loop() {
    //Almacenamiento de valor pasado
  val2 = val;
  val = digitalRead(button);
  
  if(val==HIGH && val2!=val){
    Serial.println("input en alto");
  }else if(val==LOW && val2!=val){
    Serial.println("input en bajo");
  }
  
  if (Serial.available() > 0) {
    //inString = String(Serial.readString());
    Serial.readBytes(inString,1);
    Serial.print(inString+": ");
      
    if(inString==char('o')){
      Serial.println("LED ON");
      digitalWrite(led, HIGH);
    }else if(inString==char('f')){
      Serial.println("LED OFF");
      digitalWrite(led, LOW);
    }
    else{
      Serial.println("Comando inválido");
    }
  }
}
