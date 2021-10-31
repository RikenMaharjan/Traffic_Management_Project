//coding of junction 1 - uno1
#include <NewPing.h>
#include<Wire.h>

#define slave1 8
#define slave2 9
#define slave3 1
#define slave4 2

#define redpin1  6
#define greenpin1  9
#define redpin2  3
#define greenpin2  5
#define redpin3  10
#define greenpin3  11

//global variables representing waiting time
int D0,D1,D2;
volatile int flag1,flag2,flag3,flag_tot;
volatile int alert1,alert2,alert3,alert_tot;

volatile int bcount ;

// variables to represent density
byte den_lane[3];
char den[3];
float distance0,distance1,distance2;
const byte w=0,x=1,y=2,z=3,p=4,q=5,r=6; /* w=none , x=lane1 , y=lane2 , z=lane3, and only alert keys for  p=lane1 , q=lane2 , r=lane3*/

//sensor 0
#define TRIGGER_PIN_0  2
#define ECHO_PIN_0     2

// Sensor 1
#define TRIGGER_PIN_1  4
#define ECHO_PIN_1     4

// Sensor 2
#define TRIGGER_PIN_2  7
#define ECHO_PIN_2     7

// Maximum Distance is 205 cm
#define MAX_DISTANCE 205

// Create objects for ultrasonic sensors
NewPing sensor0(TRIGGER_PIN_0, ECHO_PIN_0, MAX_DISTANCE);
NewPing sensor1(TRIGGER_PIN_1, ECHO_PIN_1, MAX_DISTANCE);
NewPing sensor2(TRIGGER_PIN_2, ECHO_PIN_2, MAX_DISTANCE);

void receiveEvent()
{
      
     flag1=0;
     flag2=0;
     flag3=0;
     alert1=0;
     alert2=0;
     alert3=0;
     
      Serial.println();
      Serial.println("------------------------------------------------------");
      Serial.print("                    ReceiveEvent Activated : ");
      while(Wire.available())
      {
          byte c = Wire.read();//recieve byte representing a lane
          delay(10);
          if (c == x)               //x=1 , activate flag 1 for lane 1 of slave
           {
              bcount = 1 ;
              flag1 = 1 ;   
           }
           else if( c == y)         //y=2 , activate flag 2 for lane 2 of slave
           {
              bcount = 2 ;
              flag2 = 1 ;
           }
           else if( c == z)         //z=3 , activate flag 3 for lane 3 of slave
           {
              bcount = 3 ;
              flag3 = 1 ;
           }
           else if (c == p)         //p=1 , alert 1 for lane 1 of slave
           {
              
              alert1 = 1 ;   
           }
           else if( c == q)         //q=2 , alert 2 for lane 2 of slave
           {
              
              alert2 = 1 ;
           }
           else if( c == r)         //r=3 , alert 3 for lane 3 of slave
           {
              
              alert3 = 1 ;
           }
           else
           {
                bcount = 0;
                flag1=0;
                flag2=0;
                flag3=0;
                alert1=0;
                alert2=0;
                alert3=0;
                
            }
           
      }
    flag_tot = flag1+flag2+flag3;  
    alert_tot = alert1+alert2+alert3;  
    
    Serial.print("bcount/emergency at lane: ");
    Serial.println(bcount);
    Serial.print("flag1 = ");
    Serial.println(flag1);
    Serial.print("flag2 = ");
    Serial.println(flag2);
    Serial.print("flag3 = ");
    Serial.println(flag3);
    Serial.print("total flag value: ");
    Serial.println(flag_tot);
    Serial.println();
    delay(5);
    if(alert_tot !=0)
    {
        Serial.print("alert at lane: ");
        Serial.println(bcount);
        Serial.print("alert1 = ");
        Serial.println(alert1);
        Serial.print("alert2 = ");
        Serial.println(alert2);
        Serial.print("alert3 = ");
        Serial.println(alert3);
        Serial.print("total alert value: ");
        Serial.println(alert_tot);
        Serial.println();
        
        if(alert1 != 0)Serial.println("prioritized vehile may arrive in approx 15 sec from lane 1 of junction 1");
        if(alert2 != 0)Serial.println("prioritized vehile may arrive in approx 15 sec from lane 2 of junction 1");
        if(alert3 != 0)Serial.println("prioritized vehile may arrive in approx 15 sec from lane 3 of junction 1");
     }
     Serial.println();
     delay(5);
    Serial.flush();
}

void requestEvent()
{
     // req_time1();
     // delay(10);
     // req_time2();
     // delay(10);
     // req_time3();
     //  delay(10);
                             
      // Define a byte to hold data
      Serial.println("---------------------------------------------------------------");
      Serial.println("                  Request event activated");
      
      //updates all lane density values
      
      byte bval ;
      Serial.print("density of this lane in byte representation = "); 
          switch (bcount) 
          {
                  case 0:// for density in non lane X
                    bval = 88;
                    Serial.println(bval);
                    Wire.write(bval);
                    break;
                    
                  case 1://for density in lane 1
                    bval = den_lane[0];
                    Serial.println(bval);
                    Wire.write(bval);
                    break;
                    
                  case 2://for density in lane 2
                    bval = den_lane[1];
                    Serial.println(bval);
                    Wire.write(bval);
                    break;
                    
                  case 3://for density in lane 3
                    bval = den_lane[2];
                    Serial.println(bval);
                    Wire.write(bval);
                    break;
                    
                  // Send response back to Master
         }
  delay(10);
  Serial.println("where, H = 72 ; M = 77 ; L = 76 ; X = 88");
  Serial.println();
  Serial.flush();
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void Display_density()
{
    req_time1();
    Serial.print(200-distance0);
    Serial.println("m covered in lane 1"); 
    delay(10);
        
    req_time2();
    Serial.print(200-distance1);
    Serial.println("m covered in lane 2"); 
    delay(10);
    
    req_time3();
    Serial.print(200-distance2);
    Serial.println("m covered in lane 3");
    delay(10);
    
    Serial.println();
    Serial.println("Values of all lane density of junction 1 in byte ");
    Serial.println("LANE  :  DENSITY");
    
    Serial.print("1 : ");  
    Serial.print(den_lane[0]);
    Serial.print(" ");
    Serial.println(den[0]);
    
    Serial.print("2 : ");
    Serial.print(den_lane[1]);
    Serial.print(" ");
    Serial.println(den[1]);
    
    Serial.print("3 : ");
    Serial.print(den_lane[2]);
    Serial.print(" ");
    Serial.print(den[2]);
    
    Serial.println();
    Serial.flush();
    delay(10);
}

////////////////////////////////////////////////////////////////////////////////////////////

void time_tracker(int led,int D)
{ 
  int l = 1;
  RE:
           switch(led)
                {
                    case 1:
                      analogWrite(redpin1,0);
                      analogWrite(greenpin1,200);
                      analogWrite(redpin2,200);
                      analogWrite(greenpin2,0);
                      analogWrite(redpin3,200);
                      analogWrite(greenpin3,0);
                      break;
                      
                    case 2:
                      analogWrite(redpin1,200);
                      analogWrite(greenpin1,0);
                      analogWrite(redpin2,0);
                      analogWrite(greenpin2,200);
                      analogWrite(redpin3,200);
                      analogWrite(greenpin3,0);
                      break;
                      
                    case 3:
                      analogWrite(redpin1,200);
                      analogWrite(greenpin1,0);
                      analogWrite(redpin2,200);
                      analogWrite(greenpin2,0);
                      analogWrite(redpin3,0);
                      analogWrite(greenpin3,200);
                      break;
                }
          while(l<=D && flag_tot==0)
          {
            delay(995);
                if(flag_tot != 0)
                {
                   led_interrupt(bcount);
                   goto RE;
                }
                Serial.print(l);
            l++;
          }
     Serial.println();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void led_interrupt(int a)
{
  delay(100);
  Serial.flush();
  led_off();
  Serial.println("                                     LED INTERRUPTED");
  int count = 0;
  if(den[a] == 'H'){count = 10;}
  else if(den[a] == 'M'){count = 8;}
  else if(den[a] == 'L'){count = 5;}
  else{count = 5;}
  
          Serial.flush();
          if(flag1 !=0)
          {
                Serial.println("              lane 1 : led green");
                analogWrite(6,0);
                analogWrite(9,200);
                for(int j=1;j<=count;j++)
                {delay(995);Serial.print(j);}
          }
          else if(flag2 !=0)
          {
                Serial.println("               lane 2 : led green");
                analogWrite(3,0);
                analogWrite(5,200);            
                for(int j=1;j<=count;j++)
                {delay(995);Serial.print(j);}
          }
          else if(flag3 !=0)
          {
                Serial.println("              lane 3 : led green"); 
                analogWrite(10,0);
                analogWrite(11,200);
                for(int j=1;j<=count;j++)
                {delay(995);Serial.print(j);}
          }
          Serial.println();
          led_off();
          flag1 = 0;
          flag2 = 0;
          flag3 = 0;
          flag_tot = 0;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////

void led_off()
{ 
  analogWrite(redpin1,0);
  analogWrite(greenpin1,0);
  analogWrite(redpin2,0);
  analogWrite(greenpin2,0);
  analogWrite(redpin3,0);
  analogWrite(greenpin3,0);
  Serial.println("---------------------------------------------------");
  delay(5);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

void req_time1()
{
  // Read sensors in CM 
  // Sensor 0
  distance0 = sensor0.ping_cm();
  delay(5);
  if (distance0 > 200 ) {
    distance0 = 200;
  }
  D0=0;
        if (distance0 >= 200 || distance0 <=2 ) 
        {
          den_lane[0] = 'X';
          den[0] = 'X';
          //Serial.println("--------lane 1 Out of range---------");
          D0 = 5;
        }
        else if(distance0 < 200 && distance0 >= 100)
        {
          den_lane[0] = 'L';// byte <= value
          den[0] = 'L';
          D0 = 5;
        }
        else if(distance0 < 100 && distance0 >= 50)
        {
          den_lane[0] = 'M';// byte <= value
          den[0] = 'M';
          D0 = 8;
        }
        else if(distance0 < 50 && distance0 >2)
        {
          den_lane[0] = 'H';// byte <= value
          den[0] = 'H';
          D0 = 10;
        }
        delay(5);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void req_time2()
{
  // Sensor 1
  distance1 = sensor1.ping_cm();
  delay(5);
  if (distance1 > 200 ) {
    distance1 = 200;
  }
  D1=0;
        if (distance1 >= 200 || distance1 <=2 ) 
        {
          den_lane[1] = 'X';
          den[1] = 'X';
          //Serial.println("--------lane 2 Out of range---------");
          D1 = 5;
        }
        else if(distance1 < 200 && distance1 >= 100)
        {
          den_lane[1] = 'L';// byte <= value
          den[1] = 'L';
          D1 = 5;
        }
        else if(distance1 < 100 && distance1 >= 50)
        {
          den_lane[1] = 'M';// byte <= value
          den[1] = 'M';
          D1 = 8;
        }
        else if(distance1 < 50 && distance1 >2)
        {
          den_lane[1] = 'H';// byte <= value
          den[1] = 'H';
          D1 = 10;
        }
        delay(5);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////

void req_time3()
{
  // Sensor 2
  distance2 = sensor2.ping_cm();
  delay(5);
  if (distance2 > 200 ) {
    distance2 = 200;
  }
  D2=0;
        if (distance2 >= 200 || distance2 <=2 ) 
        {
          den_lane[2] = 'X';
          den[2] = 'X';
          //Serial.println("--------lane 3 Out of range---------");
          D2 = 5;
        }
        else if(distance2 < 200 && distance2 >= 100)
        {
          den_lane[2] = 'L';// byte <= value
          den[2] = 'L';
          D2 = 5;
        }
        else if(distance2 < 100 && distance2 >= 50)
        {
          den_lane[2] = 'M';// byte <= value
          den[2] = 'M';
          D2 = 8;
        }
        else if(distance2 < 50 && distance2 >2)
        {
          den_lane[2] = 'H';// byte <= value
          den[2] = 'H';
          D2 = 10;
        }
        delay(5);
}



///////////////////////////////////////////////////////////////////////////////////////////////

void setup() 
{
  Wire.begin(slave1);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  delay(2);
  Serial.begin(9600);
  //initialize pins
  pinMode(redpin1,OUTPUT);
  pinMode(redpin2,OUTPUT);
  pinMode(greenpin1,OUTPUT);
  pinMode(greenpin2,OUTPUT);
  pinMode(redpin3,OUTPUT);
  pinMode(greenpin3,OUTPUT);
  
}

void loop()
{
  // put your main code here, to run repeatedly: 
    /*Serial.println();
    Serial.print("flag1 = ");
    Serial.println(flag1);
    Serial.print("flag2 = ");
    Serial.println(flag2);
    Serial.print("flag3 = ");
    Serial.println(flag3);
    Serial.println();
    Serial.flush();
    delay(5);
    */
    Display_density();// for each lane in junction 
     
    delay(5);
    if(flag1 == 0 && flag2 == 0 && flag3==0 )
    Serial.println("                       no communtcation took place");
    Serial.println();
    led_off();
    //-----------------------------------NORM_FUNCTIONING----------------------------------
                      Serial.flush();
                    
                                              if(flag_tot != 0)
                                              {
                                                 led_interrupt(bcount);
                                                 delay(5);
                                              }
                                              
                      req_time1();
                      delay(10);
                      Serial.println("lane 1 On :");
                      Serial.print("Wait for :");
                      Serial.print(D0);
                      Serial.println(" sec");
                      time_tracker(1,D0);
                      led_off();
                    
                                              if(flag_tot != 0)
                                              {
                                                 led_interrupt(bcount);
                                                 delay(5);
                                              }
                    
                                            
                      req_time2();
                      delay(10);
                      Serial.println("lane 2 OPEN : ");
                      Serial.print("Wait for :");
                      Serial.print(D1);
                      Serial.println(" sec");
                      time_tracker(2,D1);
                      led_off();
                    
                                              if(flag_tot != 0)
                                              {
                                                   led_interrupt(bcount);
                                                   delay(5);   
                                              }
                                              
                      req_time3();
                      delay(10);
                      Serial.println("lane 3 OPEN : ");
                      Serial.print("Wait for :");
                      Serial.print(D2);
                      Serial.println(" sec");
                      time_tracker(3,D2);
                      led_off();
                      Serial.println();
     //-----------------------------------------------------------------------------------------------
Serial.flush();
}
