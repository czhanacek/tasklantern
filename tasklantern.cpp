#include <CapacitiveSensor.h>



CapacitiveSensor   cs_4_2 = CapacitiveSensor(2,22);  
CapacitiveSensor   cs_4_3 = CapacitiveSensor(3,24); 
 bool state = false;
 bool touchedbottom = false;
  bool touchedtop = false;
 bool prevTouched = false;
 long touchAvg = 700;
  long touchCount = 1;
 long prevTime = millis();
 bool ledsAndStatesTop[] = {
      true,
      false,
      false,
      false,
      false
    };
     bool ledsAndStatesBottom[] = {
      true,
      false,
      false,
      false,
      false
    };
 int curLedTop = 0;
  int curLedBottom = 0;

void showLeds(void) {
  for(int i = 7; i < 12; i++) {
    if(ledsAndStatesBottom[i - 7]) {
      digitalWrite(i, HIGH);
    }
    else {
      digitalWrite(i, LOW);
    }
  }
  for(int i = 30; i < 35; i++) {
    if(ledsAndStatesTop[i - 30]) {
      digitalWrite(i, HIGH);
    }
    else {
      digitalWrite(i, LOW);
    }
  }
}


void ledUpBottom(void) {
  ledsAndStatesBottom[curLedBottom] = false;
  if(curLedBottom == 4) {
    curLedBottom = 0;
  }
  else {
    curLedBottom++;
  }
  ledsAndStatesBottom[curLedBottom] = true;
  
}

void ledUpTop(void) {
  ledsAndStatesTop[curLedTop] = false;
  if(curLedTop == 4) {
    curLedTop = 0;
  }
  else {
    curLedTop++;
  }
  ledsAndStatesTop[curLedTop] = true;
  
}

void setup()                    
{

   cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
    cs_4_3.set_CS_AutocaL_Millis(0xFFFFFFFF); 
    Serial.begin(9600);
    pinMode(10, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(8, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(30, OUTPUT);
    pinMode(31, OUTPUT);
    pinMode(32, OUTPUT);
    pinMode(33, OUTPUT);
    pinMode(34, OUTPUT);

    
}

void loop()                    
{
     showLeds();
     
    
    long total1 =  cs_4_2.capacitiveSensor(30);
    long total2 = cs_4_3.capacitiveSensor(30);
   
    
    
  
    if(total1 > 800) {
      touchedbottom = true;
      Serial.println("touch started");
     
     
    }
    else if(total1 < 800 && touchedbottom == true) {
      ledUpBottom();
      Serial.println("touch ended");
      touchedbottom = false;
       
      
    }

     if(total2 > 800) {
      touchedtop = true;
    }
    else if(total2 < 800 && touchedtop == true) {
      ledUpTop();
      touchedtop = false;
    }
   delay(10);
     
}




