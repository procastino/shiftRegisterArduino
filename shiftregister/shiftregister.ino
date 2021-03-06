    /*
    From Adafruit lesson, improved to patterned LED lights controlled by two pushbuttons
    */
     
//definimos botons e variables precisas
    
    int pinBotons[]={3,2};
    int ultimoEstadoBoton[]={LOW,LOW};
    int estadoBoton[]={LOW,LOW};
        
    long ultimoDebounce=0;
    long retardoDebounce=20;

//variables para as saídas do arduino para o 74HC595    
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
     
//O loop consiste en facer a lectura dos botóns e chamar ao programa correspondente
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
       
       case 6:
         alternativoTodos();
         break;
       
       default:
         apagados();
         break;
     
      }
    
}


//función de lectura dos botóns con Debounce

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
              if (programa>6)
                  {
                    programa=0;
                  }
              }
              if(i==1)
              {
                programa=programa-1;
                if (programa<0)
                  {
                    programa=6;
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
    
//función que manda os datos do byte leds ao shiftregister para que este defina o estado dos LED
  void updateShiftRegister()
  {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, leds);
  digitalWrite(latchPin, HIGH);
  }

// funcións para os patróns, explícanse por si mesmas co nome
  
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
    
    void alternativoTodos()
    {
      leds=B11111111;
      updateShiftRegister();
      delay(100);
      leds=B00000000;
      updateShiftRegister();
      delay(100);
    }
    

