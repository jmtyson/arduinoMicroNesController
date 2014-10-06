int clockPin = 2;
int latchPin = 3;
int dataPin = 4;
//The buttonStates array elements corralate with the following buttons on a 
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
//Use configSwitch to pick which keyboard configuration you want to use.
//ganeSwitch == 0 is based on my configuration for Nestopia (using the nesEmulator array).
int gameSwitch = 0;
//Match the elements in the arrays here with the buttonStates array to set up proper us
char nesEmulator [8] = {'z', 'x', KEY_RIGHT_SHIFT, KEY_RETURN, KEY_UP_ARROW, KEY_DOWN_ARROW, KEY_LEFT_ARROW, KEY_RIGHT_ARROW};

void setup(){
 pinMode(clockPin, OUTPUT);
 pinMode(latchPin, OUTPUT);
 pinMode(dataPin, INPUT);
 Keyboard.begin();
}

void loop(){ 
  
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

char keyboardSwitch(int button){
  switch (gameSwitch){
    case 0:
      return nesEmulator[button];
      break;    
  }
}
