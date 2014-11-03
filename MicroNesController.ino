#include <SoftwareSerial.h>

//The clockPin is used to clock the serial chip in the NES controller (OUTPUT)
const int clockPin = 2;
//The latchPin is used to latch the buttons to lock their state for reading (OUTPUT)
const int latchPin = 3;
//The dataPin is used to read the states of each button of the NES controller (INPUT)
const int dataPin = 4;
//The switchProfilePin is a button used to change the current profile used by the Arduino Micro (INPUT)
const int switchProfilePin = 5;
//The nesProfiles array elements corralate with the following buttons on a 
//NES controller in the order they are clocked in.
//buttonStates[0] == "a"
//buttonStates[1] == "b"
//buttonStates[2] == "Select"
//buttonStates[3] == "Start"
//buttonStates[4] == "Up"
//buttonStates[5] == "Down"
//buttonStates[6] == "Left"
//buttonStates[7] == "Right"
int buttonStates [8] = {1,1,1,1,1,1,1,1};
//The gameSwitch variable is used to pick which contorller profile to be used.
int gameSwitch = 0;
//The profileSize variable is used to determine the size of the double array
//and to loop gameswitch back to zero when it equals profileSize.  Change this number to reflect the number of
//profiles being used.
const int profileSize = 2;
//Match the elements in the arrays here with the buttonStates array to set up proper us
char nesProfiles[profileSize][8] = {
                                    {'z', 'x', KEY_RIGHT_SHIFT, KEY_RETURN, KEY_UP_ARROW, KEY_DOWN_ARROW, KEY_LEFT_ARROW, KEY_RIGHT_ARROW},
                                    {KEY_RETURN, KEY_BACKSPACE, KEY_DELETE, KEY_ESC, KEY_UP_ARROW, KEY_DOWN_ARROW, KEY_LEFT_ARROW, KEY_RIGHT_ARROW}
                                   };
//The following 3 lines are used with a Parallax LCD screen with a backpack to display which profile is in use.
//profileNames is used to display the profile being used.
char* profileNames[profileSize] = {"NES Emulator", "Pac-Man Champ"};
const int txPin = 6;
SoftwareSerial printName = SoftwareSerial(255, txPin);

void setup(){
 pinMode(clockPin, OUTPUT);
 pinMode(latchPin, OUTPUT);
 pinMode(dataPin, INPUT);
 pinMode(switchProfilePin, INPUT);
 Keyboard.begin();
 printName.begin(2400); //I'm using a LCD screen from Parallax to output to the current profile in use.
 delay(100);
 displayNESProfile();
}

void loop(){ 
 
 
 if(digitalRead(switchProfilePin) == HIGH)
   changeNESProfile(); 
 
 readNESController();
 for(int i = 0; i<8; i++){
   if (buttonStates[i] == 0)
      Keyboard.press(keyboardSwitch(i));
   else
      Keyboard.release(keyboardSwitch(i));
 }
}

void readNESController(){
  digitalWrite(latchPin, HIGH);
  digitalWrite(latchPin, LOW);

  for(int i = 0; i < 8; i++){
    buttonStates[i] = digitalRead(dataPin);
    
    digitalWrite(clockPin, HIGH);      
    digitalWrite(clockPin, LOW);
  }  
}

//remove this function and replace the call with the return instead.
char keyboardSwitch(int button){
      return nesProfiles[gameSwitch][button];
}

void changeNESProfile(){
  gameSwitch = gameSwitch + 1;
  if(gameSwitch >= profileSize)
    gameSwitch = 0;
  delay(350);
  
  displayNESProfile();
}

void displayNESProfile(){
  //Writes a raw hex value to clear screen
  printName.write(12);
  delay(5);
  printName.print(profileNames[gameSwitch]);
}
