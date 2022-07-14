#include <Keyboard.h>
#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel strip = Adafruit_NeoPixel(6, 7, NEO_GRB + NEO_KHZ800);

byte inputs[] = {2,3,4};          //declaring inputs and outputs
byte outputs[] = {5,6};

char layout[2][3] = {               //layout grid for characters
  {'l',']','='},
  {'7','8','9'},
};

bool keyDown[2][3];

void setup() {
  for(int i=0; i<2; i++){    //declaring all the outputs and setting them high
    pinMode(outputs[i],OUTPUT);
    digitalWrite(outputs[i],HIGH);
  }
  for(int i=0; i<3; i++){     //declaring all the inputs and activating the internal pullup resistor
    pinMode(inputs[i],INPUT_PULLUP);
  }

  Serial.begin(9600);               //establishing Serial link and initializing keyboard
  Serial.println("Connected");
  Keyboard.begin();

  strip.begin();                    //initializing LEDs and setting them all to white
  for (int i = 0; i<6; i++){
    strip.setPixelColor(i,50,50,50);
  }
  strip.show();
}

void loop() {
  for (int i=0; i<2; i++)
  {    
    digitalWrite(outputs[i],LOW);   //setting one row low
    delayMicroseconds(5);           //giving electronics time to settle down
    
    for(int j=0; j<3; j++)
    {
      if(digitalRead(inputs[j]) == LOW)
      {
        keyPressed(i,j);            //calling keyPressed function if one of the inputs reads low
      }
      else if(keyDown[i][j] == true)   //resetting the key if it is not pressed any more
      {  
        resetKey(i,j);
      }
    }
    digitalWrite(outputs[i],HIGH);
    delayMicroseconds(500);         //setting the row high and waiting 0.5ms until next cycle
  }
}

//if a key is pressed, this Funtion is called and outputs to serial the key location, it also sends the keystroke if not already done so
void keyPressed(int row, int col){
  Serial.print("Output: "); 
  Serial.print(row);
  Serial.print(" Input: ");
  Serial.print(col);
  Serial.print(" ");
  Serial.println(layout[row][col]);

  if(keyDown[row][col] == false){         //if the function is called for the first time for this key
    Keyboard.write(layout[row][col]);
    keyDown[row][col] = true;
  }
}

void resetKey(int row, int col){ //resetting the variables after key is released
  keyDown[row][col] = false;
}
