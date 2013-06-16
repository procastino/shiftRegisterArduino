    /*
    Adafruit Arduino - Lesson 4. 8 LEDs and a Shift Register
    */
     
    #define pinBotonMais 3
    #define pinBotonMenos 2
    
    int estadoBotonMais;
    int estadoBotonMenos;
    int ultimoEstadoBotonMais=LOW;
    int ultimoEstadoBotonMenos=LOW;
    
    long ultimoDebounce=0;
    long retardoDebounce=50;
    
    int latchPin = 5;
    int clockPin = 6;
    int dataPin = 4;
    
    int programa=0;
    
    byte leds = 0;
     
    void setup()
    {
    pinMode(pinBotonMais, INPUT);
    pinMode(pinBotonMenos, INPUT);
    pinMode(latchPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    
    Serial.begin(9600);
    }
     
void loop()
{
    int lecturaMais=digitalRead(pinBotonMais);

    if (lecturaMais!=ultimoEstadoBotonMais) {
      ultimoDebounce=millis();
      }
    
    if ((millis()-ultimoDebounce)>retardoDebounce) 
    {
      if (lecturaMais!=estadoBotonMais) 
      {
        estadoBotonMais=lecturaMais;
        
        if (estadoBotonMais==HIGH) 
        {
          programa=programa+1;
          Serial.println("programa");
          Serial.println(programa);
          }
        }
      }
    
    ultimoEstadoBotonMais=lecturaMais;
    
    
    int lecturaMenos=digitalRead(pinBotonMenos);

    if (lecturaMenos!=ultimoEstadoBotonMenos) 
    {
      ultimoDebounce=millis();
    }
    
    if ((millis()-ultimoDebounce)>retardoDebounce) 
    {
      if (lecturaMenos!=estadoBotonMenos) 
      {
        estadoBotonMenos=lecturaMenos;
        
        if (estadoBotonMenos==HIGH) 
        {
          programa--;
          Serial.println("programa");
          Serial.println(programa);
        }
      }
    }
    
    ultimoEstadoBotonMenos=lecturaMenos;
    
    switch (programa) 
    {
       case 0:
         apagados();
         break;
       
       case 1:
         encendidoProgresivo();
         break;
     
      
      }
    
}

    void lecturaBoton(int pinBoton)
    {
      int lectura=digitalRead(pinBoton);

    if (lectura!=ultimoEstadoBotonMais) {
      ultimoDebounce=millis();
      }
    
    if ((millis()-ultimoDebounce)>retardoDebounce) 
    {
      if (lectura!=estadoBotonMais) 
      {
        estadoBotonMais=lectura;
        
        if (estadoBotonMais==HIGH) 
        {
          programa=programa+1;
          Serial.println("programa");
          Serial.println(programa);
          }
        }
      }
    
    ultimoEstadoBotonMais=lectura;
    
    }
    
    
    void updateShiftRegister()
    {
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, leds);
    digitalWrite(latchPin, HIGH);
    }
    
  void apagados()
  {
    leds=0;
    updateShiftRegister();
  }
  
  void encendidoProgresivo() 
  {
      leds = 0;
      updateShiftRegister();
      delay(500);
      for (int i = 0; i < 8; i++)
      {
      bitSet(leds, i);
      updateShiftRegister();
      delay(500);
      }
    }
//    
