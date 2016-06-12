//Empty string declaration
String morse;
// Instantiate Fan to node D0
const int Fan = D0;
// button connected to digital pin 10
const int buttonPin = A0;
// Length of a dash in ms
const int dash = 300;
// length of a dot in ms
const int dot = 100;
// state of the button this iteration
byte current_button = LOW;
// previous state of the button
byte old_button = LOW;
// start of a pressed event
unsigned long int start_high;
// end of a pressed event
unsigned long int stop_high;
// start of a non-pressed event
unsigned long int start_low;
// end of a non-pressed event
unsigned long int stop_low;

// The setup() method runs once,
// when the sketch starts
void setup() {
// initialize the button pin as an input:
pinMode(buttonPin, INPUT);
// initialize the fan pin as an output:
pinMode(Fan, OUTPUT);
// Set up serial communication
Serial.begin(9600);
}

byte read_button(byte pin, byte ref_value) {
  // observed the state of the button
  byte current_button = digitalRead(pin);
  // There is a LOW -> HIGH transition
  // or a HIGH -> LOW transition
  if (((ref_value == LOW) && (current_button == HIGH)) || ((ref_value == HIGH) && (current_button == LOW))) {
    // wait for a while (5ms)
    delay(5);
    // update the state of the button
    current_button = digitalRead(pin);
  }
return(current_button);
}

void loop() {
// Read the current state
current_button = read_button(buttonPin, old_button);
// LOW -> HIGH transition
if ((old_button== LOW) && (current_button== HIGH)) {
  // Update timing
  start_high = millis();
  stop_low = start_high;
  }

// HIGH-> LOW transition
if ((old_button== HIGH) && (current_button== LOW)) {
  // Update timing
  stop_high = millis();
  start_low = stop_high;

  // detect dashs and dots
  if ((stop_high - start_high) >= dash) {
    morse = morse + "-";
    Serial.write("\nMorse:" + morse);
    //Serial.print(morse);
    } else {
      if ((stop_high - start_high) >= dot) {
        morse = morse + ".";
        Serial.write("\nMorse:" + morse);
        //Serial.print(".");
    }
  }
}
old_button = current_button;

//Motor Speed of Fan correlates to input {0-9}
if (morse.length() >= 5){
  //Number 0
  if (morse == "-----"){
    analogWrite(Fan, 0);
    Serial.write("\nFan Speed: 0");
    morse="";
  //Number 1
  }else if (morse == ".----"){
    analogWrite(Fan, .11*255);
    Serial.write("\nFan Speed: 1");
    morse="";
  //Number 2
  }else if (morse == "..---"){
    analogWrite(Fan, .22*255);
    Serial.write("\nFan Speed: 2");
    morse="";
  //Number 3
  }else if (morse == "...--"){
    analogWrite(Fan, .33*255);
    Serial.write("\nFan Speed: 3");
    morse="";
  //Number 4
  }else if (morse == "....-"){
    analogWrite(Fan, .44*255);
    Serial.write("\nFan Speed: 4");
    morse="";
  //Number 5
  }else if (morse == "....."){
    analogWrite(Fan, .55*255);
    Serial.write("\nFan Speed: 5");
    morse="";
  //Number 6
  }else if (morse == "-...."){
    analogWrite(Fan, .66*255);
    Serial.write("\nFan Speed: 6");
    morse="";
  //Number 7
  }else if (morse == "--..."){
    analogWrite(Fan, .77*255);
    Serial.write("\nFan Speed: 7");
    morse="";
  //Number 8
  }else if (morse == "---.."){
    analogWrite(Fan, .88*255);
    Serial.write("\nFan Speed: 8");
    morse="";
  //Number 9
  }else if (morse == "----."){
    analogWrite(Fan, 255);
    Serial.write("\nFan Speed: 9");
    morse="";
  }else{
    morse = "";
  }
}
}
