/* TEMPERATURE MONITOR THAT WHEN A HIGH TEMPERATURE
IS DETECTED (baselineTemp in celsius) ACTIVATES AN ALARM (BLINKING LEDS)
TO LET USERS KNOW THERE IS A HIGH RISK. THEY CAN DISARM IT BY
PUSHING THE BUTTON AND THEN THE SYSTEM RESETS AUTOMATICALLY
*/


int baselineTemp = 60; //Temperature that activates the alarm
int celsius=0;
int buttonState=LOW;//output of the button
const int buttonPin=7;

void setup()
{
  Serial.begin(9600);
  
  //temperature sensor and button as inputs
  pinMode(A0, INPUT);
  pinMode(buttonPin, INPUT);
  
  //LED's as outputs
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
}

void loop()
{
  // measure temperature in Celsius
  float InputValue=analogRead(A0);  
  float Volts =(InputValue/1024.0)*5.0-0.5;//Conversion InputValue from bits to vold and add -0.5V offset
  celsius=round(Volts*100);//Conversion to Celsius
  
  //print temperature in celsius in the monitor
  Serial.print("Temperature Check: ");
  Serial.print(celsius);
  Serial.println(" C ");
  
   
  //when temperature is below baselineTemp turn off all LED's
  if (celsius < baselineTemp) {
    Serial.println("Temperature is at a safe level");
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
  }
  
  //when temperature is over baselineTemp turn on all LED's
  if (celsius >= baselineTemp) {
    
    Serial.println("Warning: Temperature too high");
    Serial.println("Push the button to turn off the alarm!");
    buttonState=digitalRead(buttonPin);
   
    while(buttonState==LOW){
      blink();
      delay(100);
      buttonState=digitalRead(buttonPin);         
    }
    Serial.println("The system has been disarmed.");
 
    
  }
  Serial.println();
  
  //reset
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW); 
  
  
  delay(1000); // Wait for 100ms to take the next measurement
}

//blinking LEDs
void blink(){
  static bool state=HIGH;
      digitalWrite(2, state);
      digitalWrite(3, state);
      digitalWrite(4, state);
      if(state==LOW)
        state=HIGH;
      else
        state=LOW;
    
}
  