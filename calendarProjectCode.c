#include <Adafruit_NeoPixel.h>
const int openCalendarButtonPin = 5;
const int tabButtonPin = 3;
const int EnterButton = 4;
const int TimerButton = 2;
const int WeeksPotent = 0;
int openLastButtonState = HIGH;
int EnterLastButtonState = HIGH;
int tabLastButtonState = HIGH;
int TimerLastButton = HIGH;
bool currentWeekFlag = false;
float counter = 0;
float timeNow =0;
int currentWeekState = 0;
int redColor = 0;
int greenColor = 0;
int blueColor = 0;
float milis = 0;
int switchPin = 12;
int isOn=LOW;
 //keboard needs to be on english!
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(4, 8, NEO_GRB + NEO_KHZ800);

void setup()
{
  pinMode(openCalendarButtonPin, INPUT_PULLUP);
  pinMode(EnterButton, INPUT_PULLUP);
  pinMode(tabButtonPin, INPUT_PULLUP);
  pinMode(TimerButton, INPUT_PULLUP);
  pixels.begin();
  Serial.begin(9600);

}

void loop()
{
isOn= digitalRead(switchPin);
if(isOn == HIGH)
{
 int analogReading0 = analogRead(0);
 int analogReading1 = analogRead(1);
  
 int Digitalreading = digitalRead(openCalendarButtonPin);
 if (Digitalreading != openLastButtonState) 
  {
    if (Digitalreading == LOW)
	{
      openCalendar(); 
    }
  }
openLastButtonState = Digitalreading;
  
Digitalreading = digitalRead(EnterButton);
if(Digitalreading != EnterLastButtonState)
{
 if(Digitalreading == LOW)
  {
	Serial.println("keyboard.press(ENTER)");
    delay(100);
   	Serial.println("keyboard.releaseAll()");
    delay(100);
  }

}
EnterLastButtonState = Digitalreading;

Digitalreading = digitalRead(tabButtonPin);
if(Digitalreading !=tabLastButtonState)
{
	if(Digitalreading == LOW)
    {
		Serial.println("keyboard.press(TAB)");
        delay(100);
   	 	Serial.println("keyboard.releaseAll()");
        delay(100);
    }
}
tabLastButtonState = Digitalreading;
  
checkAndChangeWeeks(analogReading0);
Digitalreading = digitalRead(TimerButton);
if(Digitalreading !=TimerLastButton)
{
	if(Digitalreading == LOW)
	{
		counter = GetCounterFromUser()*60;
		timeNow=millis();
    	Serial.println(counter);
	} 
}
TimerLastButton = Digitalreading;

if(counter > 0)
  {
  milis = millis();
  counter =counter - (((milis-timeNow)/1000)/60);
  Serial.println(counter);  
  testAndChangeLEDBasedOnCounter();
  }
  else 
  {
 	 turnOffColors();
	for(int i = 0; i < 4;i++)
	{
   		
   	 	pixels.setPixelColor(i, pixels.Color(redColor,greenColor,blueColor)); 
   		pixels.show();
    }
  }
}	
else if(isOn == LOW)
{
    counter=0;
	setColor();
  	for(int i = 0;i < 4;i++)
	{
    	
   	 pixels.setPixelColor(i, pixels.Color(redColor,greenColor,blueColor));
   	 pixels.show(); 
	 delay(100);
	}
  
}
  
	

}


void testAndChangeLEDBasedOnCounter()
{
  if (counter > 60*60)
  {
	 setRedColor();

  	for(int i = 0; i < 4;i++)
	{
   	 	pixels.setPixelColor(i, pixels.Color(redColor,greenColor,blueColor));
   		pixels.show(); 
    }
  }
  else if(counter > 30*60 && counter <60*60)
  {
	 setYellowColor();
  	for(int i = 0;i < 4;i++)
	{
  	  pixels.setPixelColor(i, pixels.Color(redColor,greenColor,blueColor)); 
   	  pixels.show();
    }
  }
 else if(counter <15*60)
	{

	setGreenColor();

  		for(int i = 0;i < 4;i++)
		{
   		 pixels.setPixelColor(i, pixels.Color(redColor,greenColor,blueColor));
   		 pixels.show(); 
		}
 	}

}


void checkAndChangeWeeks(int analogReading)
{
  delay(100);
  int val = map(analogReading, 0, 1023, 0, 700);
  int difference = 0;
  int valToBeChecked = val/100;

  if((currentWeekState) != valToBeChecked)
  {
    difference = valToBeChecked - currentWeekState;
    currentWeekState = valToBeChecked;
  }
  
  if(difference < 0)
  {
    
    for(int i = 0; i > difference; i--)
    {
      Serial.println("keyboard.press(K)");
      delay(100);
      Serial.println("keyboard.releaseAll()");
      delay(100);
     
    }
     
  }
  
  if(difference > 0)
  {

      for(int i = 0; i< difference; i++)
    {
        Serial.println("keyboard.press(J)");
        delay(100);
     	Serial.println("keyboard.releaseAll()");
        delay(100);
      }
      
  }

}



int GetCounterFromUser()
{
  bool flagIsPressed = false;
  while(!flagIsPressed)
  {
	int analogReading1 = analogRead(1);
  	int val = map(analogReading1, 0, 1023, 0, 90);
 	 int Digitalreading = digitalRead(TimerButton);
	if(Digitalreading !=TimerLastButton)
	{
		if(Digitalreading == LOW)
		{

			flagIsPressed = true;
		} 
	}
    return val;
  }

}

void openCalendar()
{
  Serial.println("keyboard.press(KEY_LEFT_GUI)");
  delay(100); 
  Serial.println("keyboard.press('r')");  
  delay(100); 
  Serial.println("keyboard.releaseAll()");
  delay(100);
  Serial.println("keyboard.println('chrome')");
  delay(5000); 
  Serial.println("keyboard.println('https://calendar.google.com')");
  delay(2000);
}


void setColor()
{
  redColor = random(0, 255);
  greenColor = random(0,255);
  blueColor = random(0, 255);
}
void setRedColor()
{
   redColor = 255;
  greenColor = 0;
  blueColor = 0;
  
}
void setGreenColor()
{
  redColor = 0;
  greenColor = 255;
  blueColor = 0;
  
}
void setYellowColor()
{
  redColor = 255;
  greenColor = 255;
  blueColor = 0;
  
}

void turnOffColors()
{
    redColor = 0;
  greenColor = 0;
  blueColor = 0;
}
