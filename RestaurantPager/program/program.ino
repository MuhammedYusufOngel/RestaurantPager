//Buzzer pin
const int buzzerPin = 2;
//These letters are explained on the home page.
const int segmentG = 6;
const int segmentF = 5;
const int segmentE = 10;
const int segmentD = 9;
const int segmentPoint = 7;
const int segmentC = 8;
const int segmentB = 3;
const int segmentA = 4;
//Button pin
const int button = 11;

//numberGlobal is number that we want to show
int numberGlobal = 0;
//We need that, i will explain later.
int repeatNumber = 0;

//Variable that checks whether the button is pressed or not
bool isClick = false;

unsigned long previousMillis = 0;
const long interval = 1000; // 1 saniye
long counter = 0;

//This function provides that we don't need write these codes again to show number
void writeNumber(uint8_t g, uint8_t f, uint8_t e, uint8_t d, uint8_t c, uint8_t b, uint8_t a)
{
	digitalWrite(segmentG,g);
	digitalWrite(segmentF,f);
	digitalWrite(segmentE,e);
	digitalWrite(segmentD,d);
	digitalWrite(segmentC,c);
	digitalWrite(segmentB,b);
	digitalWrite(segmentA,a);
	digitalWrite(segmentPoint, HIGH);
}

//We give number parameter and this function display that number.
void displayNumber(int number)
{
  if(number == 0)
  {
    writeNumber(HIGH, LOW, LOW, LOW, LOW, LOW, LOW);
  }

  if(number == 1)
  {
    writeNumber(HIGH, HIGH, HIGH, HIGH, LOW, LOW, HIGH);
  }

  else if(number == 2)
  {
    writeNumber(LOW, HIGH, LOW, LOW, HIGH, LOW, LOW);
  }

  else if(number == 3)
  {
    writeNumber(LOW, HIGH, HIGH, LOW, LOW, LOW, LOW);
  }

  if(number == 4)
  {
    writeNumber(LOW, LOW, HIGH, HIGH, LOW, LOW, HIGH);
  }

  if(number == 5)
  {
    writeNumber(LOW, LOW, HIGH, LOW, LOW, HIGH, LOW);
  }

  else if(number == 6)
  {
    writeNumber(LOW, LOW, LOW, LOW, LOW, HIGH, LOW);
  }

  else if(number == 7)
  {
    writeNumber(HIGH, HIGH, HIGH, HIGH, LOW, LOW, LOW);
  }

  else if(number == 8)
  {
    writeNumber(LOW, LOW, LOW, LOW, LOW, LOW, LOW);
  }

  else if(number == 9)
  {
    writeNumber(LOW, LOW, HIGH, LOW, LOW, LOW, LOW);
  }
}

//Thanks to this function, we check whether the button is pressed or not.
void control()
{
  //If the button is pressed, this means that the customer's meal is prepared. 
  if(digitalRead(button) == 1)
  {
    repeatNumber++;
    
    //We need that variable because we want to isClick is true or false just one time. 
    if(repeatNumber == 1)
    {
      isClick = !isClick;
    }
  }

  else 
  {
    repeatNumber = 0;
  }
}

void setup()
{
  //When we run program we want to different random values.
  randomSeed(analogRead(0));

	pinMode(buzzerPin, OUTPUT);
	pinMode(segmentG, OUTPUT);
	pinMode(segmentF, OUTPUT);
	pinMode(segmentE, OUTPUT);
	pinMode(segmentD, OUTPUT);
	pinMode(segmentPoint, OUTPUT);
	pinMode(segmentC, OUTPUT);
	pinMode(segmentB, OUTPUT);
	pinMode(segmentA, OUTPUT);
	pinMode(button, INPUT);

  //We assign random value to numberGlobal.
  numberGlobal = random(9);
}

void loop()
{
  unsigned long currentMillis = millis();
  control();

  //Eğer isClick is true the buzzer beeps and seven segment display flash.
	if(isClick)
	{
    if (currentMillis - previousMillis >= interval) {
        //Every one second these processes are done.

        counter++;
        //Buzzer beeps & stops and seven segment display flashes with counter
        if(counter % 2 == 0)
        {
          noTone(buzzerPin);
          writeNumber(HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH);
        }

        else
        {
          tone(buzzerPin, 1000);
          displayNumber(numberGlobal);
        }
        
        //Update timestamp
        previousMillis = currentMillis;
    }

    control();
	}

	else
	{
		displayNumber(numberGlobal);
		noTone(buzzerPin);
	}


}