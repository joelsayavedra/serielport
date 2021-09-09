#define led 2
#define button 4
#define LM35 A0
String inString = "off";
float lecturaAnalogica = 0;
int val = LOW;
int val2 = LOW;
String palabros[5];

void setup() {
  Serial.begin(250000);
  Serial.setTimeout(1);

  pinMode(led, OUTPUT);
  pinMode(button, INPUT);
  pinMode(LM35, INPUT);
  digitalWrite(button, HIGH);
  
  while (!Serial) {
    ; // Espera a que el puerto serie se conecte. Sólo es necesario para el puerto USB nativo;
  }
}



void loop(){  
  //lectura de la entrada digital definido como "button"
  leeBoton();

  //lectura de información recibida por puerto serie
  leeSerie();
}

int separaStrings(String cadena){
  char separador = ' ';
  int lastIndex = -1;
  int inicioPalabro=0;
  int indicePalabro = 0;

  // Serial.println("1.- Cadena: -"+cadena+"-");
  // Serial.println("primera aparición del caracter: "+String(cadena.indexOf(separador)));
  // Serial.println("última aparición del caracter: "+String(cadena.lastIndexOf(separador)));

  if(cadena.lastIndexOf(separador)!=-1){
    if(cadena.lastIndexOf(separador)!=cadena.indexOf(separador)){
      // Serial.println("   ---   Caso 1   ---   ");
      do{
        lastIndex = cadena.indexOf(separador,lastIndex+1);
        palabros[indicePalabro]=cadena.substring(inicioPalabro,lastIndex);
        // Serial.println("-"+palabros[indicePalabro]+"-");
        indicePalabro++;
        inicioPalabro=lastIndex+1;
        // Serial.println("Rastreo de variables -> indicePalabro:"+String(indicePalabro)+"   inicioPalabro:"+String(inicioPalabro)+"   lastIndex:"+String(lastIndex));
      }while (cadena.lastIndexOf(separador)!=cadena.indexOf(separador,lastIndex+1));
      lastIndex = cadena.indexOf(separador,lastIndex+1);
      palabros[indicePalabro]=cadena.substring(inicioPalabro,lastIndex);
      // Serial.println("-"+palabros[indicePalabro]+"-");
      indicePalabro++;
      inicioPalabro=lastIndex+1;
      // Serial.println("Rastreo de variables -> indicePalabro:"+String(indicePalabro)+"   inicioPalabro:"+String(inicioPalabro)+"   lastIndex:"+String(lastIndex));
      palabros[indicePalabro]=cadena.substring(inicioPalabro);
      // Serial.println("-"+palabros[indicePalabro]+"-");
      // Serial.println("Rastreo de variables -> indicePalabro:"+String(indicePalabro)+"   inicioPalabro:"+String(inicioPalabro)+"   lastIndex:"+String(lastIndex));
      return indicePalabro+1;
    }else{
      // Serial.println("   ---   Caso 2   ---   ");

      int indexPalabro = 0;
      int indiceSeparacion = cadena.indexOf(separador);
      palabros[0]=cadena.substring(0,indiceSeparacion);
      palabros[1]=cadena.substring(indiceSeparacion+1);
      // Serial.println("-"+palabros[0]+"-");
      // Serial.println("-"+palabros[1]+"-");
      return 2;
    }
  }else{
    // Serial.println("   ---   Caso 3   ---   ");
    palabros[0]=cadena;
    return 1;
    // Serial.println("-"+palabros[0]+"-");
  }
  // Serial.println("2.- Cadena: -"+cadena+"-");
}

void ledOn(){
  Serial.print(inString+": ");
  Serial.println("LED ON");
  digitalWrite(led, HIGH);
}

void ledOff(){
  Serial.print(inString+": ");
  Serial.println("LED OFF");
  digitalWrite(led, LOW);
}

void parpadea(int n){
  if(n<0){
    Serial.println("Por favor, ingresa un valor positivo");
  }else{
    Serial.println("Led parpadeando "+inString+" veces");
    for(int i=0;i<n;i++){
      digitalWrite(led, HIGH);
      delay(100);
      digitalWrite(led, LOW);
      delay(100);
    }
  }

}

void leeSensor(){
  lecturaAnalogica = analogRead(LM35);
  float temp=(lecturaAnalogica*500)/1023;
  Serial.println(temp);
}

void mueveMotor(int cm){
  if(cm==0){
    Serial.println("Por favor, ingresa un valor diferente de 0");
  }else{
    if(cm<0){
      cm=-cm;
      Serial.println("Moviendo motor "+ String(cm) + " centímetros en sentido contrario...");
    }else{
       Serial.println("Moviendo motor "+ String(cm) + " centímetros...");
    }
    delay(cm*1000);
    Serial.println("listo");
  }


}

void leeSerie(){
    if (Serial.available() > 0) {
    inString = String(Serial.readString());   //Lee la cadena 
    int palabras = separaStrings(inString);

    if(palabras==1){
      if(inString=="on"){
        ledOn();      
      }else if(inString=="off"){
        ledOff();
      }else if(inString=="sensor"){
        leeSensor();
      }else{
        Serial.println("\""+inString+"\""+" No es un comando válido");
      }
    }else if(palabras==2){
      if (palabros[0]=="motor"){
        int cm = palabros[1].toInt();
        if(cm!=0 && palabros[1]==String(cm)){
          mueveMotor(cm);
        }else{
          Serial.println("Datos de avance inválidos");
        }
      }
      if (palabros[0]=="led"){
        int veces = palabros[1].toInt();
        if(veces!=0 && palabros[1]==String(veces)){
          parpadea(veces);
        }else{
          Serial.println("Debes ingresar un número entero");
        }
      }
    }else{
      Serial.println("\""+inString+"\""+" No existe un comando con tantos palabros");
    }
  }
}

void leeBoton(){
  //Almacenamiento de valor pasado
  val2 = val;
  val = digitalRead(button);
  
  if(val==HIGH && val2!=val){
    Serial.println("input en alto");
  }else if(val==LOW && val2!=val){
    Serial.println("input en bajo");
  }
}

/*
  // Declaración de una función que permite pasarle otra función
  // como parámetro y, a su vez, un parámetro para esta función.
void funcionSerie(void (*funcion)(int num),String cadena,int num){
  if(inString==String(cadena)){
    (*funcion)(num);
  }
}

  // Así se llama
      funcionSerie(parpadea,String(num),num);

  // Declaración de una función que permite pasarle otra función (sin argumentos)
  // como parámetro.
void funcionSerie(void (*funcion)(),String cadena){
  if(inString==String(cadena)){
    (*funcion)();
  }
}
*/
