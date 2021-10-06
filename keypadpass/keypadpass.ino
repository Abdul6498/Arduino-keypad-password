
#include <Keypad.h>
#include <LiquidCrystal.h>
const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {3, 2 ,1 ,0 }; //connect to the row pinouts of the keypad
byte colPins[COLS] = {6, 5, 4}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
LiquidCrystal lcd(12, 11, 10, 9,8, 7);
int redled = 13;
int greenled = A0;
char* ourcode = "1234";
int currentposition = 0;
void setup() {
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 4);
  // Print a message to the LCD.
  lcd.setCursor(0,0);
  displaycodeenteryscreen();
  pinMode(redled , OUTPUT);
  pinMode(greenled , OUTPUT);
  digitalWrite(redled , LOW);
  digitalWrite(greenled , LOW);
  
}

void loop() {
  int i;
  char key = keypad.getKey();
  if(int(key) !=0){
  lcd.setCursor(8,3);
  lcd.print("    ");
  lcd.setCursor(8,3);
  for(i=0; i<=currentposition; ++i)
  {
  lcd.print("*");
  }
  if(key == ourcode[currentposition])
  {
  ++currentposition;
  if(currentposition == 4)
  {
  unlockdoor();
  currentposition = 0;
  }
  }
  else{
  invalidcode();
  currentposition = 0;
  }
  
  }
}

void displaycodeenteryscreen(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Let's Make It");
  lcd.setCursor(0,1);
  lcd.print("EIM project...");
  lcd.setCursor(0,2);
  lcd.print("Enter CODE: ");
}

/*void clearscreen(){
  lcd.setCursor(0,0);
  lcd.print("                ");
  lcd.setCursor(0,1);
  lcd.print("                ");
    lcd.setCursor(0,2);
  lcd.print("                ");
    lcd.setCursor(0,3);
  lcd.print("                ");
}*/
void unlockdoor()
{
  digitalWrite(greenled , HIGH);
lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("************");
  lcd.setCursor(0,1);
  lcd.print("ACCESS GRANTED");
  lcd.setCursor(0,2);
  lcd.print("WELCOME");
  lcd.setCursor(0,3);
  lcd.print("************");
  delay(5000);
  digitalWrite(greenled,LOW);
  displaycodeenteryscreen();
}
void invalidcode(){
  digitalWrite(redled , HIGH);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("************");
  lcd.setCursor(0,1);
  lcd.print("ACCESS DENIED");
  lcd.setCursor(0,2);
  lcd.print("INVALID CODE");
  lcd.setCursor(0,3);
  lcd.print("************");
  delay(5000);
  digitalWrite(greenled,LOW);
  displaycodeenteryscreen();

}

