int left_sensor = 0;  //variable for left sensor
int right_sensor = 0; //variable for right sensor
int value;            //variable for temporary value
//int corner;         // state variable for corner situation 
int pmw = 150;	     //variable for Pulse Width Modulation for Motors

void setup()
{
  pinMode(11, OUTPUT);    //setting the digital pins to output mode for 11
  pinMode(10, OUTPUT);   //contorlling the motor  driver 
  pinMode(9, OUTPUT);    
  pinMode(6, OUTPUT);
  pinMode(4, OUTPUT);   //setting the output for LED 1
  pinMode(3, OUTPUT);   //setting the output fo LED 2
  Serial.begin(9600);
  
}

void loop(){

  value = analogRead(0);   // reading the values returned from sensor                                                             
  left_sensor = map(value, 4, 437, 0, 255);  //     mapping it into a desirable range 
  value = analogRead(1);
  right_sensor = map(value, 4, 429, 0, 255);
  
  Serial.print(" Sensor Left  = ");          // printing the values of both sensor into 
  Serial.print(left_sensor);                 // serial monitor for inspection     
  Serial.print(" Sensor Right = ");      
  Serial.println(right_sensor);
  
   // use this commented code alone if you donâ€™t need corner handling 
//  if(left_sensor<100 && right_sensor<100)
//    reverse();
//  else if(right_sensor<100)
//    left();
//  else if(left_sensor<100)
//     right();
//  else
//    forward();
//    delay(10);
 

// The code below checks for changes in the sensor values , decides if it should move left ,right ,forward or backwards
// This code handles corner situation also

  if(left_sensor<100 && right_sensor<100){
//   if(corner==0){
//     corner = 1;
     reverse();
     delay(1000);
     left();
     delay(400);
     while(left_sensor<100){
       left();
       delay(100);
//       if(right_sensor>left_sensor)
//       left();
       break;
       }
     }
//   if(corner==1){
//     corner = 2;
//     reverse();
//     delay(2000);
//     left();
//     delay(30);
//     while(left_sensor<100){
//       left();
//       delay(500);
//       if(right_sensor>left_sensor)
//       left();
//       break;
//       }
//     }
//   if(corner==2){
//     corner = 0;
//     reverse();
//     delay(2000);
//     right();
//     delay(1000);
//     while(right_sensor<100){
//       right();
//       delay(500);
//       if(right_sensor>left_sensor)
//       right();
//       break;
//       }
//     }
//  } 
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
  digitalWrite(4, HIGH);
  digitalWrite(3, HIGH);
  analogWrite(11, 0); 
  analogWrite(10, pmw); 
  analogWrite(9, 0); 
  analogWrite(6, pmw);
}


// function for moving both motors backwards

void reverse(){
  digitalWrite(4, LOW);
  digitalWrite(3, LOW);
  analogWrite(11, pmw); 
  analogWrite(10, 0); 
  analogWrite(9, pmw); 
  analogWrite(6, 0);
}

// function for moving left motor forward and right motor backwards for turning the robot to right side

void right(){
   digitalWrite(4, LOW);
  digitalWrite(3, HIGH);
  analogWrite(11, 0); 
  analogWrite(10, pmw); 
  analogWrite(9, pmw); 
  analogWrite(6, 0);
}


// function for moving right motor forward and left motor backwards for turning the robot to left side

void left(){
  digitalWrite(4, HIGH);
  digitalWrite(3, LOW);
  analogWrite(11, pmw); 
  analogWrite(10, 0); 
  analogWrite(9, 0); 
  analogWrite(6, pmw);
}                                  

