    /*
    Adafruit Arduino - Lesson 4. 8 LEDs and a Shift Register
    */
     
//    #define pinBotonMais 3
//    #define pinBotonMenos 2
    
    int pinBotons[]={3,2};
    int ultimoEstadoBoton[]={LOW,LOW};
    int estadoBoton[]={LOW,LOW};
    
//    int estadoBotonMais;
//    int estadoBotonMenos;
//    int ultimoEstadoBotonMais=LOW;
//    int ultimoEstadoBotonMenos=LOW;
    
    long ultimoDebounce=0;
    long retardoDebounce=20;
    
    int latchPin = 5;
    int clockPin = 6;
    int dataPin = 4;
    
    int programa=0;
    
    byte leds = 0;
     
    void setup()
    {
    for (int i=0;i<2;i++)
    {
      pinMode(pinBotons[i],INPUT);
    }
    pinMode(latchPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    
    Serial.begin(9600);
    }
     
void loop()
{
  
  lecturaBotons();
 
   
    switch (programa) 
    {
       case 0:
         apagados();
         break;
       
       case 1:
         acesos();
         break;
       
       case 2:
         encendidoProgresivo();
         break;
       
       case 3:
         encendidoProgresivoInverso();
         break;
       
       case 4:
         encendidoAlterno();
         break;
       
       case 5:
         kitt();
         break;
       
       default:
         apagados();
         break;
     
      }
    
}

    void lecturaBotons()
    {
      for (int i=0;i<2;i++)
      {
      int lectura=digitalRead(pinBotons[i]);

      if (lectura!=ultimoEstadoBoton[i]) 
        {
          ultimoDebounce=millis();
          }
    
      if ((millis()-ultimoDebounce)>retardoDebounce) 
        {
          if (lectura!=estadoBoton[i]) 
          {
            estadoBoton[i]=lectura;
            
            if (estadoBoton[i]==HIGH) 
            {
              if (i==0)
              {
              programa=programa+1;
              if (programa>5)
                  {
                    programa=0;
                  }
              }
              if(i==1)
              {
                programa=programa-1;
                if (programa<0)
                  {
                    programa=5;
                  }
              }
              
              Serial.println("programa");
              Serial.println(programa);
              }
            }
          }
       ultimoEstadoBoton[i]=lectura;
      }
    
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
  
  void acesos()
  {
    leds=255;
    updateShiftRegister();
  }
  
  void encendidoProgresivo() 
  {
      leds = 0;
      updateShiftRegister();
      delay(100);
      for (int i = 0; i < 8; i++)
      {
      lecturaBotons();
      bitSet(leds, i);
      updateShiftRegister();
      delay(100);
      }
    }
    void encendidoProgresivoInverso() 
  {
      leds = 0;
      updateShiftRegister();
      delay(100);
      for (int i = 0; i < 8; i++)
      {
      lecturaBotons();
      bitSet(leds, 7-i);
      updateShiftRegister();
      delay(100);
      }
    }
    
     void encendidoAlterno() 
  {
      leds = B10101010;
      updateShiftRegister();
      delay(100);
      leds=B01010101;
      updateShiftRegister();
      delay(100);
      
    }
    void kitt() 
  {
      for (int i = 0; i < 8; i++)
      {
      lecturaBotons();
      leds=0;
      bitSet(leds, i);
      updateShiftRegister();
      delay(100);
      }
      for (int i = 1; i < 7; i++)
      {
      lecturaBotons();
      leds=0;
      bitSet(leds, 7-i);
      updateShiftRegister();
      delay(100);
      }
    }
    
//    
