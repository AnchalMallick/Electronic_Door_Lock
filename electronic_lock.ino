#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>
#define pwdLength 7

//declare and initialize the pos variable
int pos=0;


//servo connected this pin of arduino
int servoPin = 9; 

//create a Servo object
Servo doorUnlocker;

//create LCD object
LiquidCrystal LCD(A0,A1,A2,A3,A4,A5);

//constants for row and column sizes
const byte rows = 4;
const byte cols = 4;
//array to store the correct password
char Password[pwdLength] = "B*94DA";

//array to represent keys on the kaypad
char hexaKeys[rows][cols] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

//connections to Arduino
byte rowPins[rows] = {7,6,5,4};
byte colPins[cols] = {3,2,11,10};

//create Keypad object
Keypad customKeypad = Keypad(makeKeymap(hexaKeys),rowPins,colPins,rows,cols);

//array to store the password entered by the user
char dataPassword[pwdLength];
                             
void setup()
{                                                          
  //setup Serial monitor                           
  Serial.begin(9600);
  LCD.begin(16,2);
  doorUnlocker.attach(servoPin);
}
                             
void loop(){
      LCD.clear();
      LCD.setCursor(0,0);
      //prompt the user to enter the password
      LCD.print("Enter 6 char PWD:");
      int c = 0;
  
      while(1){
        
        //get key value if pressed
        char customKey = customKeypad.getKey();
        //if a key is pressed
        if (customKey){
          
           //display the password as entered by the user
           LCD.setCursor(c,1);
           LCD.print("*");
          
           //if the last character of the password is being entered
           if (c==pwdLength-2){
             
             //displaying the 6th character of the password entered
             LCD.setCursor(c,1);
             LCD.print("*");
             //storing the keypressed in the dataPassword array
             dataPassword[c] = customKey;
             delay(1000);
             LCD.clear();
             LCD.setCursor(0,0);
             Serial.println(dataPassword);
             
             //comparing if the password entered matches the actual password
             if (!strcmp(dataPassword,Password)){
               LCD.print("You're Welcome");
               //unlocking the door
               doorUnlocker.write(0);
               delay(5000);
               int counter = 0;
               //locking again in 5 seconds  
               while(counter<5){
                 
                 LCD.clear();
                 LCD.setCursor(0,0);
                 LCD.print("Locking in");
                 LCD.setCursor(0,1);
                 int time_left = 5-counter;
                 LCD.print(time_left);
                 LCD.setCursor(2,1);
                 LCD.print("seconds");
                 delay(1000);
                 counter = counter+1;
               }
               //locking the door
               LCD.clear();
               doorUnlocker.write(90);
               delay(2000);
             }
             //if password entered does not match the actual password
             else{
               LCD.print("Wrong Password!");
               delay(2000);
               LCD.setCursor(0,1);
               LCD.print("Try Again");
               delay(2000);
             }
             break;
             
           }
           //storing the characters entered in the dataPassword array
           dataPassword[c] = customKey;
           //incrementing the counter
           c = c+1;
          
        }
        
      }
}
 
                             
