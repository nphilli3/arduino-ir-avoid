/* Source code for obstacle avoiding robot using freeduino (Arduino Nano alternative) and IR sensor module  
 * Includes code for handling a corner situation to a small extent 
 * This code does not resume to the path before deviation
 */

int left_sensor = 0;                                             //variable for left sensor
int right_sensor = 0;                                            //variable for right sensor
int value;                                                       //variable for temporary value
int corner;                                                     // state variable for corner situation  
void setup()
{
  pinMode(5, OUTPUT);                                         //setting the digital pins to output mode for 
  pinMode(4, OUTPUT);                                          //contorlling the motor  driver 
  pinMode(3, OUTPUT);    
  pinMode(2, OUTPUT);  
  Serial.begin(9600);
  
}

void loop()
{
  value = analogRead(3);                                    // reading the values returned from sensor                                                             
  left_sensor = map(value, 4, 437, 0, 255);                 //     mapping it into a desirable range 
  value = analogRead(4);
  right_sensor = map(value, 4, 429, 0, 255);
  
  Serial.print(" Sensor Left  = ");                       // printing the values of both sensor into 
  Serial.print(left_sensor);                              // serial monitor for inspection     
  Serial.print(" Sensor Right = ");      
  Serial.println(right_sensor);
  
   // use this commented code alone if you donâ€™t need corner handling 

  /*  if(left_sensor<100 && right_sensor<100)
   *   reverse();
   *  else if(right_sensor<100)
      left();
      else if(left_sensor<100)
      right();
      else
      forward();
      delay(10);
   */

// The code below checks for changes in the sensor values , decides if it should move left ,right ,forward or backwards
// This code handles corner situation also

  if(left_sensor<100 && right_sensor<100)
  {
   if(corner==0)
   {
   corner = 1;
   reverse();
   delay(1000);
   left();
   delay(30);
   while(left_sensor<100)
   {
     left();
     delay(500);
     if(right_sensor>left_sensor)
     left();
     break;
   }
   }
   if(corner==1)
   {
   corner = 2;
   reverse();
   delay(2000);
   left();
   delay(30);
   while(left_sensor<100)
   {
     left();
     delay(500);
     if(right_sensor>left_sensor)
     left();
     break;
   }
   }
     if(corner==2)
   {
   corner = 0;
   reverse();
   delay(2000);
   right();
   delay(1000);
   while(right_sensor<100)
   {
     right();
     delay(500);
     if(right_sensor>left_sensor)
     right();
     break;
   }
   }
  } 
  else if(right_sensor<100)
  left();
  else if(left_sensor<100)
  right();
  else
  forward();
  delay(10);
}


// function for moving both motors forward


void forward(){
  digitalWrite(5, LOW); 
  digitalWrite(4, HIGH); 
  digitalWrite(3, LOW); 
  digitalWrite(2, HIGH);
}


// function for moving both motors backwards

void reverse(){
  digitalWrite(5, HIGH); 
  digitalWrite(4, LOW); 
  digitalWrite(3, HIGH); 
  digitalWrite(2, LOW);
}

// function for moving left motor forward and right motor backwards for turning the robot to right side

void right(){
  digitalWrite(5, LOW); 
  digitalWrite(4, HIGH); 
  digitalWrite(3, HIGH); 
  digitalWrite(2, LOW);
}


// function for moving right motor forward and left motor backwards for turning the robot to left side

void left(){
  digitalWrite(5, HIGH); 
  digitalWrite(4, LOW); 
  digitalWrite(3, LOW); 
  digitalWrite(2, HIGH);
}                                  

