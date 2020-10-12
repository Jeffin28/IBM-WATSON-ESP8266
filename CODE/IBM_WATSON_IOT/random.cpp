#include <ESP8266WiFi.h>
#include "random.h"
#include "global.h"

/*+++++++++++++++++++Fn declaration++++++++++++++++++*/
void set_wifi(void);
void blinkLED(void);
/*+++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*+++++++++++For initiating wifi connect+++++++++++++*/
/*+++++++++++++++++++++++++++++++++++++++++++++++++++*/
void set_wifi(void)
{
  Serial.println("WiFi Initiating |^^^-^^^| ");
  WiFi.mode(WIFI_STA);
  WiFi.disconnect(); 
  WiFi.begin(WLAN_SSID,WLAN_PASS);
  digitalWrite(2, HIGH);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    digitalWrite(2, millis()>>8&1);  
    delay(250);
  }
  digitalWrite(2, LOW);
  Serial.println("WiFi connected");
}
/*+++++++++++++++For led indication+++++++++++++++++*/
/*+++++++++++++++++++++++++++++++++++++++++++++++++++*/
void blinkLED(void)
{
    digitalWrite(2, HIGH);
    delay(500);
    digitalWrite(2, LOW);
}
