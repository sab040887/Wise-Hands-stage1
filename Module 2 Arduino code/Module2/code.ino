
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8);
const byte addresses[][6] = {"00001", "00002"};

boolean backlight = true;
int contrast=50;

int menuitem = 1;
int page = 1;

volatile boolean up = false;
volatile boolean down = false;
volatile boolean middle = false;

int downButtonState = 0;
int upButtonState = 0;  
int selectButtonState = 0;          
int lastDownButtonState = 0;
int lastSelectButtonState = 0;
int lastUpButtonState = 0;

Adafruit_PCD8544 display = Adafruit_PCD8544(6, 7, 8);

void setup() {

  pinMode(5, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(2,OUTPUT);
   radio.openWritingPipe(addresses[1]); // 00001
  radio.openReadingPipe(1, addresses[0]); // 00002
  radio.setPALevel(RF24_PA_MIN);

  digitalWrite(2,LOW); //Turn Backlight ON
  
  Serial.begin(9600);
  
  display.begin();      
  display.setContrast(contrast); //Set contrast to 50
  display.clearDisplay(); 
  display.display();   
}

void loop() {
  
  drawMenu();

  downButtonState = digitalRead(5);
  selectButtonState = digitalRead(4);
  upButtonState =   digitalRead(3);
 
  checkIfDownButtonIsPressed();
  checkIfUpButtonIsPressed();
  checkIfSelectButtonIsPressed();
update();
 
   
  }

  void checkIfDownButtonIsPressed()
  {
    if (downButtonState != lastDownButtonState) 
  {
    if (downButtonState == 0) 
    {
      down=true;
    }
    delay(50);
  }
   lastDownButtonState = downButtonState;
  }

void checkIfUpButtonIsPressed()
{
  if (upButtonState != lastUpButtonState) 
  {
    if (upButtonState == 0) {
      up=true;
    }
    delay(50);
  }
   lastUpButtonState = upButtonState;
}

void checkIfSelectButtonIsPressed()
{
   if (selectButtonState != lastSelectButtonState) 
  {
    if (selectButtonState == 0) {
      middle=true;
    }
    delay(50);
  }
   lastSelectButtonState = selectButtonState;
}

  
  void drawMenu()
  {
    
  if (page==1) 
  {    
    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(10, 0);
    display.print("AUTISM CARE");
    display.drawFastHLine(0,10,83,BLACK);
    display.setCursor(0, 15);
   
    if (menuitem==1) 
    { 
      display.setTextColor(WHITE, BLACK);
    }
    else 
    {
      display.setTextColor(BLACK, WHITE);
    }
    display.print(">Flip Count");
    display.setCursor(0, 25);
   
    if (menuitem==2) 
    {
      display.setTextColor(WHITE, BLACK);
    }
    else 
    {
      display.setTextColor(BLACK, WHITE);
    }    
    display.print(">Light: ");
    
    if (backlight) 
    {
      display.print("ON");
    }
    else 
    {
      display.print("OFF");
    }
    display.display();
    
    if (menuitem==3) 
    { 
      display.setTextColor(WHITE, BLACK);
    }
    else 
    {
      display.setTextColor(BLACK, WHITE);
    }  
    display.setCursor(0, 35);
    display.print(">Reset");
    display.display();
  }
  
    
    
 
  else if (page==2) 
  {
    
    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(15, 0);
    display.print("FLIP COUNT");
    display.drawFastHLine(0,10,83,BLACK);
    display.setCursor(15, 15);
    display.print("SET COUNT");
    display.setTextSize(2);
    display.setCursor(30, 30);
    display.print(contrast);
 
    display.setTextSize(2);
    display.display();
  }
  
  }

  void resetDefaults()
  {
    contrast = 0;
    setContrast();
    backlight = true;
    turnBacklightOn();
  }

  void setContrast()
  {
    display.setContrast(contrast);
    display.display();
  }

  void turnBacklightOn()
  {
    digitalWrite(2,LOW);
  }

    void turnBacklightOff()
  {
    digitalWrite(2,HIGH);
  }


byte key() {
//right 5 - 0
//up 3 - 98
//down 4 - 254
//left 2  - 408 (редко 409)
//select 1  - 640 (бывает и 642)
//rst - RESET
int val=analogRead(0);
if (val<50)  return 3; 
else if (val<20)  return 2; 
else if (val<400)  return 1; 
else if (val<500)  return 2; 
else if (val<800)  return 1; 
else   return 0; 
}
