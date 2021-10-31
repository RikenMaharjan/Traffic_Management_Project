//MEGA -  master code
//note : any single value is of one byte 
#include "RTClib.h"
#include<Wire.h>
#include <LiquidCrystal.h>
#define slave1 8
#define slave2 9
#define slave3 1
#define slave4 2
#define deviceAddress 0x68


RTC_DS3231 rtc;     //the object rtc is created from the class RTC_DS3231
char daysOfTheWeek[7][4] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};


int count = 0;// represents time for each density value
//const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

uint8_t buffer[14] ;
uint8_t* buffer_at1;
uint8_t* buffer_end1 = buffer + sizeof(buffer);
uint8_t* buffer_at2;
uint8_t* buffer_end2 = buffer + sizeof(buffer);

const uint32_t ambulance1 = 2002437;
const uint32_t ambulance2 = 15942363;
const uint32_t ambulance3 = 10678194;
const uint32_t bus1 = 2002477;
 
String checksum1;
boolean tagfound1 = false;
String checksum2;
boolean tagfound2 = false;

boolean emergency1 = false;
boolean emergency3 = false;

const byte w=0,x=1,y=2,z=3,p=4,q=5,r=6;  /* w=none , x=lane1 , y=lane2 , z=lane3*/
byte ss=0,mi=0,hh=0,t1=5,t2=10,t3=15,t4=25;

void setup() 
{
    
    Wire.begin();// declared as master
    
    //lcd.begin(16, 2);
    //lcd.print("Rfids Ready");
    
    //while (! rtc.begin())   //DS3231 is intialized
    
              //initialization failed
    
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));//auto update from computer time
    //rtc.adjust(DateTime(2018, 4, 10, 12, 35, 17));//set date-time manualy:yr,mo,dy,hr,mn,sec

              //checking if DS3231 Module is preset
              Wire.beginTransmission (deviceAddress);
              //Wire.write(0x0E); //pointing Control Register
              //Wire.write(0x80);
              byte busStatus = Wire.endTransmission();
              if (busStatus == 0)
              {
                Serial.println("DS3231 Clock Module is Present...!");
              }
              else
              {
                Serial.println("Ds3231 Clock Module is not Present...!");
                while (1);  //wait for ever
              }
    
    Serial.begin(9600);
    Serial.println("Serial Ready");
    Serial1.begin(9600);
    Serial.println("RFID1 Ready");
    Serial2.begin(9600);
    Serial.println("RFID2 Ready");
    delay(20);
    Serial.flush();
    Serial1.flush();
    Serial2.flush();
    delay(20);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////

/*void lcd_clean()
{
        lcd.setCursor(0,0);
        lcd.print('                                ');
        lcd.setCursor(0,1);
        lcd.print('                                ');
        lcd.setCursor(0,0);
}*/

//////////////////////////////////////////////////////////////////////////////////////////////////


/*void lcd_display(int l,char den)
{
  lcd_clean();
  if(den == 'H'){count = 10;}
  else if(den == 'M'){count = 8;}
  else if(den == 'L'){count = 5;}
  else{count = 5;}
  lcd.setCursor(0,0);
  lcd.print("LANE:");
  lcd.print(l);
  lcd.print(" DENSITY:");
  lcd.print(den);
  lcd.setCursor(0,1);
  lcd.print("                ");
  lcd.setCursor(0,1);
  lcd.print("Wait for :");
  delay(10);
  for(int i=1; i<=count ; i++)
  {
    lcd.setCursor(10,1);
    Serial.print(i);
    lcd.print(i);
    delay(998);
  }
  
  Serial.println();
  delay(100);
  lcd_clean();
  lcd.setCursor(0,0);
  lcd.print(" NORMAL FUNCTION ");
  lcd.setCursor(0,1);
  lcd.print("                ");
  delay(10);
}
*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//* for pathA

void Emergency_lane1()
{
   //-----------------SEND DATA FROM RFID1 TO SLAVE1 AND ALERT SLAVE 2 & SLAVE 3 ------------------------------
       //only for path A 
        Serial1.flush();
        Wire.beginTransmission(slave1);
        Wire.write(x);// sends one byte i.e. : 1 to lane1 of slave1
        Wire.endTransmission();
        delay(2);
        
        Wire.beginTransmission(slave2);
        Wire.write(r);// sends one byte i.e. : 6 to lane3 of slave2
        Wire.endTransmission();
        delay(2);
        
        Wire.beginTransmission(slave3);
        Wire.write(q);// sends one byte i.e. : 5 to lane2 of slave3
        Wire.endTransmission();
        delay(2);
          
        //making sure of execution of this function
        Serial.println("Emergnecy Signal sent to junctions 1 , 2and 3 ");
        Serial.println();
        Serial.flush();
       delay(5);
     emergency1 = true;
        
}

void Emergency_lane3()
{
  //-----------------SEND DATA FROM RFID2 TO SLAVE2 AND ALERT SLAVE4 ----------------------
        //only for path A
        Serial2.flush();
        Wire.beginTransmission(slave2);
        Wire.write(z);// sends one byte i.e. : 3 to lane 3 of slave 2
        Wire.endTransmission();
        delay(2);
        
        Wire.beginTransmission(slave4);
        Wire.write(q);// sends one byte i.e. : 5 to lane 2 of slave 4
        Wire.endTransmission();
        delay(2);
        
        //making sure of execution of this function
        Serial.println("Emergnecy Signal sent to junctions 2 and 4 ");
        Serial.println();
        Serial.flush();
       delay(5);
     emergency3 = true;
  
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

byte readI2C(int address) // for each byte read from slave(*address) 
{
  // Define a variable to hold byte of data
  byte bval=88;
  //long entry = millis();
  Wire.requestFrom(address, 1); //request 1 byte from slave address
  //delay(100);
  if(Wire.available())bval = Wire.read();
  return bval;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////

void den_slave1()
{
        Serial.println(" Received density data of lane 1 of slave1");
        char den = readI2C(slave1);
        Serial.print("density level : ");
        Serial.println(den);

        if(den == 'H'){count = 10;}
        else if(den == 'M'){count = 8;}
        else if(den == 'L'){count = 5;}
        else{count = 5;}
        
        Serial.print("LANE:");
        Serial.print(" 1");
        Serial.print(" DENSITY:");
        Serial.println(den);
        Serial.print("Wait for :");
        Serial.print(count);
        Serial.println(" sec");
        delay(998);
        for(int i=1; i<=count ; i++)
        {
          Serial.print(i);
          delay(998);
        }
        Serial.println();
        Serial.flush();
}


void den_slave3()
{       
        Serial.println(" Received density data of lane 3 of slave 2 ");
        char den = readI2C(slave2);
        Serial.print("density level  : ");
        Serial.println(den);
        if(den == 'H'){count = 10;}
        else if(den == 'M'){count = 8;}
        else if(den == 'L'){count = 5;}
        else{count = 5;}
        
        Serial.print("LANE:");
        Serial.print(" 3");
        Serial.print(" DENSITY:");
        Serial.println();
        Serial.print("Wait for :");
        Serial.print(count);
        Serial.println(" sec");
        delay(998);
        for(int i=1; i<=count ; i++)
        {
          Serial.print(i);
          delay(998);
        }
        Serial.println();
        Serial.flush();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

void rfid1()// rfid in lane 1
{   
    Serial1.flush();
    delay(50);
    if (Serial1.available())
    {
        Serial.println();
        Serial.println("---------------------------------------------------------------");
        Serial.println("                Processing rfid1");
        buffer_at1 = buffer;
        delay(10);
        while ( buffer_at1 < buffer_end1 )
        {
            *buffer_at1++ = Serial1.read();
        }
        tagfound1 = true;
        Serial1.end();
        Serial1.begin(9600);
        delay(20);
    }
 
    if (tagfound1)
    {  
        Serial.println("------tag 1 found------");
        //order = ?
        //lcd_clean();
        //delay(10);
        //lcd.print("tag 1 found");
        //delay(10);
        
        buffer_at1 = buffer;
        uint32_t result1 = 0;
 
        // Skip the preamble  -  intial bit position
        ++buffer_at1;
        // Accumulate the checksum, starting with the first value
        uint8_t checksum1 = rfid_get_next1();
        // We are looking for 4 more values
        int i = 4;
        while(i--)
        {
            // Grab the next value
            uint8_t value1 = rfid_get_next1();
            // Add it into the result
            result1 <<= 8;
            result1 |= value1;
            // Xor it into the checksum
            checksum1 ^= value1;
        }
        // Pull out the checksum from the data
        uint8_t data_checksum1 = rfid_get_next1();
 
        // Print the result
        Serial.print("RFID_reader_Tag1: ");
        Serial.print(result1);
        
        //lcd.setCursor(0,1);
        //lcd.print(result1);
        delay(5);
        
        if ( checksum1 == data_checksum1 )
            Serial.println(" OK ");
        else
            Serial.println(" CHECKSUM FAILED");
        // We're done processing, so there is no current value
       
       delay(10);
        if(result1 == ambulance1){
              //lcd.setCursor(0,0);
              //lcd.print("                ");
              //lcd.setCursor(0,0);
              //lcd.print("Ambulance1");
              //delay(10);
              Serial.println(" : AMBULANCE-1 detected at JUNCTION-1");
              Serial.println(" : AMBULANCE-1 will reach AREA-1 at approx 15 sec");
              Emergency_lane1();
              real_time(3); 
                                
        }
        else if(result1 == ambulance2){
              //lcd.setCursor(0,0);
              //lcd.print("                ");
              //lcd.setCursor(0,0);
              //lcd.print("Ambulance2");
              //delay(10);
              Serial.println(" : AMBULANCE-2 detected at JUNCTION-1");
              Serial.println(" : AMBULANCE-2 will reach AREA-2 at approx 25 sec");
              Emergency_lane1();
              real_time(4);
                    
        }
        else if(result1 == ambulance3){
              //lcd.setCursor(0,0);
              //lcd.print("                ");
              //lcd.setCursor(0,0);
              //lcd.print("Ambulance3");
              //delay(10);
              Serial.println(" : AMBULANCE-3 detected at JUNCTION-1");
              Serial.println(" : AMBULANCE-3 will reach AREA - 3 at approx 15 sec");
              Emergency_lane1();  
              real_time(3); 
              
                    
        }
        else if(result1 == bus1){
              //lcd.setCursor(0,0);
              //lcd.print("                ");
              //lcd.setCursor(0,0);
              //lcd.print("BUS - 1");
              //delay(10);
              Serial.println(" : BUS-1 detected near JUNCTION-1");
              Serial.println(" : BUS-1 will reach AREA-1 at approx 15 sec");
              real_time(3); 
              Serial.println(" : BUS-1 will reach AREA-2 at approx 25 sec");
              real_time(4); 
              Serial.println(" : BUS-1 will reach AREA-3 at approx 15 sec");
              real_time(3); 
                        
        }
        else
        {
          real_time(0);
        }
       
       
    tagfound1 = false;
    }
    
    Serial1.flush();
    delay(20);
    
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

void rfid2() // rfid 2 in lane 3
{  
  Serial2.flush();
  delay(50);  
    if (Serial2.available())
    {
        Serial.println();
        Serial.println("---------------------------------------------------------------");
        Serial.println("                     processing rfid2");
        buffer_at2 = buffer;
        delay(10);
        while ( buffer_at2 < buffer_end2 )
        {
            *buffer_at2++ = Serial2.read();
        }
        tagfound2 = true; 
        Serial2.end();
        Serial2.begin(9600);
        delay(50);
    }
 
    if (tagfound2)
    {
        Serial.println("------tag 2 found------");
               
        buffer_at2 = buffer;
        uint32_t result2 = 0;
 
        // Skip the preamble
        ++buffer_at2;
        // Accumulate the checksum, starting with the first value
        uint8_t checksum2 = rfid_get_next2();
        // We are looking for 4 more values
        int i = 4;
        while(i--)
        {
            // Grab the next value
            uint8_t value2 = rfid_get_next2();
            // Add it into the result
                    result2 <<= 8;
                    result2 |= value2;
            // Xor it into the checksum
            checksum2 ^= value2;
        }
        // Pull out the checksum from the data
        uint8_t data_checksum2 = rfid_get_next2();
 
        // Print the result
        Serial.print("RFID_reader_Tag2: ");
        Serial.print(result2);
        delay(5);
        
        if ( checksum2 == data_checksum2 )
            Serial.println(" OK   ");
    
        else
            Serial.println(" CHECKSUM FAILED");
        // We're done processing, so there is no current value
        
        delay(10);
        if(result2 == ambulance1){
                          
        Serial.println(" : AMBULANCE-1 detected at JUNCTION-2");
        Serial.println(" : AMBULANCE-1 will reach AREA-1 at approx 5 sec");
        Emergency_lane3();
        real_time(1);
        }
        
        else if(result2 == ambulance2){
          
        Serial.println(" : AMBULANCE-2 detected at JUNCTION-2");
        Serial.println(" : AMBULANCE-2 will reach AREA-2 at approx 15 sec");
        Emergency_lane3();
        real_time(3);            
        }
        else if(result2 == ambulance3){
            
        Serial.println(" : AMBULANCE-3 detected at JUNCTION-2");
        Serial.println(" : AMBULANCE-3 will reach AREA-3 at approx 25 sec");
        Emergency_lane3();
        real_time(4);            
        }
        else if(result2 == bus1)
        {           
            Serial.println(" : BUS-1 detected at JUNCTION-2");
            Serial.println(" : BUS-1 will reach AREA-1 at approx 5 sec");
            real_time(1);
            Serial.println(" : BUS-1 will reach AREA-2 at approx 15 sec");
            real_time(2); 
            Serial.println(" : BUS-1 will reach AREA-3 at approx 25 sec");
            real_time(3);
                        
        }
        else{
            real_time(0);
            }
    tagfound2 = false;
    }
    
  Serial2.flush();
  delay(20);
  
}

void real_time(int d)
{
  Wire.beginTransmission(deviceAddress); //START, Roll Cal
  Wire.write(0x00); //set SEC Register address
  Wire.endTransmission(); //Execute the above queued data, ACK, STOP

  Wire.requestFrom(deviceAddress, 3);   //SEC, MIN, and HRS to read from RTC as BCD
    ss = bcd2bin(Wire.read()); // get seconds
    mi = bcd2bin(Wire.read()); // get minutes
    hh = bcd2bin(Wire.read()); // get hours
  
  if (hh<10) Serial.print("0"); 
  Serial.print(hh,DEC);
  Serial.print(":");
  
  if (mi<10) Serial.print("0");
  Serial.print(mi,DEC);
  Serial.print(":");
  
  if (ss<10) Serial.print("0");
  Serial.print(ss,DEC);

    switch(d)
    {
      case 1:
            Serial.print("   After 5 sec --->  ");

            if (hh<10) Serial.print("0"); 
            Serial.print(hh,DEC);
            Serial.print(":");
            
            if (mi<10) Serial.print("0");
            Serial.print(mi,DEC);
            Serial.print(":");
            
            if (ss<10) Serial.print("0");
            Serial.print(ss + t1,DEC);
            Serial.println();
            break;
      case 2:
            Serial.print("   After 10 sec --->  ");

            if (hh<10) Serial.print("0"); 
            Serial.print(hh,DEC);
            Serial.print(":");
            
            if (mi<10) Serial.print("0");
            Serial.print(mi,DEC);
            Serial.print(":");
            
            if (ss<10) Serial.print("0");
            Serial.print(ss + t2,DEC);
            Serial.println();
            break;
      case 3:
              Serial.print("   After 15 sec --->  ");

              if (hh<10) Serial.print("0"); 
              Serial.print(hh,DEC);
              Serial.print(":");
              
              if (mi<10) Serial.print("0");
              Serial.print(mi,DEC);
              Serial.print(":");
              
              if (ss<10) Serial.print("0");
              Serial.print(ss + t3,DEC);
              Serial.println();
              break;
      case 4:
              Serial.print("   After 25 sec --->  ");

              if (hh<10) Serial.print("0"); 
              Serial.print(hh,DEC);
              Serial.print(":");
              
              if (mi<10) Serial.print("0");
              Serial.print(mi,DEC);
              Serial.print(":");
              
              if (ss<10) Serial.print("0");
              Serial.print(ss + t4,DEC);
              Serial.println();
              break;
    default:
              break;
  }
  

}

byte bcd2bin(byte x)
{
  // converts from binary-coded decimal to a "regular" binary number
  return ((((x >> 4) & 0xF) * 10) + (x & 0xF)) ;
}
 
uint8_t rfid_get_next1(void)
{
    // sscanf needs a 2-byte space to put the result but we
    // only need one byte.
    uint16_t hexresult1;
    // Working space to assemble each byte
    static char byte_chars1[3];
    // Pull out one byte from this position in the stream
    snprintf(byte_chars1,3,"%c%c",buffer_at1[0],buffer_at1[1]);
    sscanf(byte_chars1,"%x",&hexresult1);
    buffer_at1 += 2;
    return static_cast<uint8_t>(hexresult1);
}
 
uint8_t rfid_get_next2(void)
{
    // sscanf needs a 2-byte space to put the result but we
    // only need one byte.
    uint16_t hexresult2;
    // Working space to assemble each byte
    static char byte_chars2[3];
    // Pull out one byte from this position in the stream
    snprintf(byte_chars2,3,"%c%c",buffer_at2[0],buffer_at2[1]);
    sscanf(byte_chars2,"%x",&hexresult2);
    buffer_at2 += 2;
    return static_cast<uint8_t>(hexresult2);
}

/*void Rtc()
{     
      
      //lcd.setCursor(8,1);
      //lcd.print(Clock.getHour(h12, PM), DEC); //24-hr
      //lcd.print(":");
      //lcd.print(Clock.getMinute(), DEC);
      //lcd.print(":");
      //lcd.print(Clock.getSecond(), DEC);
      //lcd_clean();
      
      Clock.begin();
      Serial.print(Clock.getHour(h12, PM), DEC); //24-hr
      Serial.print(":");
      Serial.print(Clock.getMinute(), DEC);
      Serial.print(":");
      Serial.println(Clock.getSecond(), DEC);
      Clock.end();
      
}
*/
void loop()
{ 
  Serial.flush();
  if(Serial1.available())rfid1();
  //if(emergency1)den_slave1();
  delay(2);
  Serial1.flush();
  
  if(Serial2.available())rfid2();
  //if(emergency3)den_slave3();
  delay(2);
  Serial2.flush();

  emergency1 = false;
  emergency3 = false;
}
