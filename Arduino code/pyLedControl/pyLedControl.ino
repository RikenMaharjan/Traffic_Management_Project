#define redpin1  6
#define greenpin1  9
#define redpin2  3
#define greenpin2  5
#define redpin3  10
#define greenpin3  11

int turn = 0;

void setup() 
   { 
      Serial.begin(9600); 
      pinMode(redpin1,OUTPUT);
      pinMode(redpin2,OUTPUT);
      pinMode(greenpin1,OUTPUT);
      pinMode(greenpin2,OUTPUT);
      pinMode(redpin3,OUTPUT);
      pinMode(greenpin3,OUTPUT);
      Serial.println("Connection established...");
                      analogWrite(redpin1,255);
                      analogWrite(greenpin1,255);
                      analogWrite(redpin2,255);
                      analogWrite(greenpin2,255);
                      analogWrite(redpin3,255);
                      analogWrite(greenpin3,255);
      Serial.flush();
   }
 
void loop() 
{ 
  Serial.flush();
              if(Serial.available())
              {
                char den = Serial.read();
                
                 delay(20); 
                 int bval = turn%3;
                 delay(10);
                           if(bval==0)
                           {
                                            Serial.println("LANE 1 : ");
                                            analogWrite(redpin1,255);
                                            analogWrite(greenpin1,0);
                                            analogWrite(redpin2,0);
                                            analogWrite(greenpin2,255);
                                            analogWrite(redpin3,0);
                                            analogWrite(greenpin3,255);
                                            if (den == 'H')
                                            {
                                                delay(10000);
                                            }
                                            else if (den == 'M') 
                                            {
                                                delay(8000);
                                            }
                                            else if(den == 'L')
                                            {
                                               delay(5000);
                                            }
                                            
                                            Amber(1);
                           }
                           if(bval==1)
                           {
                                            Serial.println("LANE 2 : ");
                                            analogWrite(redpin1,0);
                                            analogWrite(greenpin1,255);
                                            analogWrite(redpin2,255);
                                            analogWrite(greenpin2,0);
                                            analogWrite(redpin3,0);
                                            analogWrite(greenpin3,255);
                                            if (den == 'H')
                                            {
                                                delay(10000);
                                            }
                                            else if (den == 'M') 
                                            {
                                                delay(8000);
                                            }
                                            else if(den == 'L')
                                            {
                                               delay(5000);
                                            }
                                            Amber(2);
                          }
                          if(bval==2)
                          {
                                            Serial.println("LANE 3 : ");
                                            analogWrite(redpin1,0);
                                            analogWrite(greenpin1,255);
                                            analogWrite(redpin2,0);
                                            analogWrite(greenpin2,255);
                                            analogWrite(redpin3,255);
                                            analogWrite(greenpin3,0);
                                            if (den == 'H')
                                            {
                                                delay(10000);
                                            }
                                            else if (den == 'M') 
                                            {
                                                delay(8000);
                                            }
                                            else if(den == 'L')
                                            {
                                               delay(5000);
                                            }
                                            Amber(0);
                          }
              Serial.println("NEXT");
              turn=turn+1;
              if(turn>2)turn=0;
                      while(!Serial.available())
                      {
                                          analogWrite(redpin1,255);
                                          analogWrite(greenpin1,255);
                                          analogWrite(redpin2,255);
                                          analogWrite(greenpin2,255);
                                          analogWrite(redpin3,255);
                                          analogWrite(greenpin3,255);
                                          Amber(turn);
                                          delay(500);
                      }
              
              }
      
}

void Amber(int lane)
{
  switch (lane)
  {
          case 0:
                              analogWrite(redpin1,55);
                              analogWrite(greenpin1,130);
                              analogWrite(redpin2,0);
                              analogWrite(greenpin2,255);
                              analogWrite(redpin3,0);
                              analogWrite(greenpin3,255);
          break;
          case 1:
                              analogWrite(redpin1,0);
                              analogWrite(greenpin1,255);
                              analogWrite(redpin2,55);
                              analogWrite(greenpin2,130);
                              analogWrite(redpin3,0);
                              analogWrite(greenpin3,255);
          break;
          case 2:
                              analogWrite(redpin1,0);
                              analogWrite(greenpin1,255);
                              analogWrite(redpin2,0);
                              analogWrite(greenpin2,255);
                              analogWrite(redpin3,55);
                              analogWrite(greenpin3,130);
          break;
          
  }

}
