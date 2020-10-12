#include "ibm.h" 
#include "random.h"

void setup() 
{
   Serial.begin(9600);
   pinMode(2,OUTPUT);
   set_wifi();
   mqttConnect();
   initManagedDevice();
}

void loop() 
{
   client_loop();
   if(Serial.readString()=="send") 
      publishData();        
}
