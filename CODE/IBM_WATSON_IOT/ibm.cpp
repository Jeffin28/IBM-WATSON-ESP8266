#include <ESP8266WiFi.h>
#include <PubSubClient.h> 
#include <ArduinoJson.h>
#include "ibm.h" 
#include "random.h"

/*++++++ IBM_WATSON credential & parameters +++++++*/
#define ORG           "Bluemix id"
#define DEVICE_TYPE   "IBM DEVICE TYPE"
#define DEVICE_ID     "IBM DEVICE_ID"
#define TOKEN         "IBM TOKEN"

char server    []   =  ORG ".messaging.internetofthings.ibmcloud.com";
char authMethod[]   = "use-token-auth";
char token     []   = TOKEN;
char clientId  []   = "d:" ORG ":" DEVICE_TYPE ":" DEVICE_ID;

const char publishTopic [] = "iot-2/evt/status/fmt/json";
const char responseTopic[] = "iotdm-1/response";
const char manageTopic  [] = "iotdevice-1/mgmt/manage";
const char updateTopic  [] = "iotdm-1/device/update";
const char rebootTopic  [] = "iotdm-1/mgmt/initiate/device/reboot";
/*++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*++++++++++ class and object declerations +++++++++*/
WiFiClient wifiClient;
PubSubClient client(server, 1883, callback, wifiClient);
/*++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*++++++++++++++ Function declerations +++++++++++++*/
void mqttConnect(void);
void publishData(void);
void client_loop(void);
void initManagedDevice(void);
void handleUpdate(byte* payload); 
void callback(char* topic, byte* payload, unsigned int payloadLength);
/*++++++++++++++++++++++++++++++++++++++++++++++++++*/

int publishInterval = 30000; 
long lastPublishMillis;

/*+++++++++++++++For Mqtt connection +++++++++++++++*/
/*++++++++++++++++++++++++++++++++++++++++++++++++++*/
void mqttConnect(void)
{
	 if (!!!client.connected()) 
	 {
	   Serial.print("connecting MQTT client to "); 
	   Serial.println(server);
	   while (!!!client.connect(clientId, authMethod, token))
	   {
	     Serial.print(".");
	     delay(500);
	   }
     Serial.println("MQTT connected");     
	 }
}
/*++++For initialise & subscribing the system +++++++*/
/*++++++++++++++++++++++++++++++++++++++++++++++++++*/
void initManagedDevice(void) 
{
	 if (client.subscribe("iotdm-1/response")) 
	   Serial.println("subscribe to responses OK");
	 else 
	   Serial.println("subscribe to responses FAILED");
	
	 if (client.subscribe(rebootTopic)) 
	   Serial.println("subscribe to reboot OK");
	 else 
	   Serial.println("subscribe to reboot FAILED");
	
	 if (client.subscribe("iotdm-1/device/update")) 
	   Serial.println("subscribe to update OK");
	 else 
	   Serial.println("subscribe to update FAILED");
	   
	 StaticJsonBuffer<300> jsonBuffer;
	 JsonObject& root = jsonBuffer.createObject();
	 JsonObject& d = root.createNestedObject("d");
	 JsonObject& metadata = d.createNestedObject("metadata");
	 metadata["publishInterval"] = publishInterval;
	 JsonObject& supports = d.createNestedObject("supports");
	 supports["deviceActions"] = true;
	
	 char buff[300];
	 root.printTo(buff, sizeof(buff));
	 Serial.println("publishing device metadata:"); 
	 Serial.println(buff);
	 
	 if(client.publish(manageTopic, buff)) 
	   Serial.println("device Publish ok");
	 else 
	   Serial.print("device Publish failed:");
}
/*++++++++++++++++ For data publish ++++++++++++++++*/
/*++++++++++++++++++++++++++++++++++++++++++++++++++*/
void publishData(void) 
{
	 String payload = "{\"d\":{\"counter\":";
	 payload += millis() / 1000;
	 payload += "}}";
	
	 Serial.print("Sending payload: "); 
	 Serial.println(payload);
	
	 if (client.publish(publishTopic, (char*) payload.c_str())) 
	   Serial.println("Publish OK");
	 else 
	   Serial.println("Publish FAILED");
}
/*+++++++++++++++For mqtt callback +++++++++++++++++*/
/*++++++++++++++++++++++++++++++++++++++++++++++++++*/
void callback(char* topic, byte* payload, unsigned int payloadLength) 
{
	 Serial.print("callback invoked for topic: ");
	 Serial.println(topic);
	
	 if (strcmp (responseTopic, topic) == 0) 
	   return; 
	 if (strcmp (rebootTopic, topic) == 0) 
	 {
	   Serial.println("Rebooting...");
	   ESP.restart();
	 }
	 if (strcmp (updateTopic, topic) == 0) 
	   handleUpdate(payload);
}
/*+++++++++ For received message handling ++++++++++*/
/*++++++++++++++++++++++++++++++++++++++++++++++++++*/
void handleUpdate(byte* payload) 
{
	 StaticJsonBuffer<300> jsonBuffer;
	 JsonObject& root = jsonBuffer.parseObject((char*)payload);
	 if (!root.success()) 
	 {
	   Serial.println("handleUpdate: payload parse FAILED");
	   return;
	 }
	 Serial.println("handleUpdate payload:"); 
	 root.prettyPrintTo(Serial); 
	 Serial.println();
	
	 JsonObject& d = root["d"];
	 JsonArray& fields = d["fields"];
	 for (JsonArray::iterator it = fields.begin(); it != fields.end(); ++it) 
	 {
	   JsonObject& field = *it;
	   const char* fieldName = field["field"];
	   if (strcmp (fieldName, "metadata") == 0) 
	   {
	     JsonObject& fieldValue = field["value"];
	     const char* cloud_to_device = fieldValue["cloud to device"];
	     Serial.printf("cloud to device msg : %s\n",cloud_to_device);
       blinkLED(); 
	   }
	 }
}
/*+ For maintain server connection and msg callback +*/
/*++++++++++++++++++++++++++++++++++++++++++++++++++*/
void client_loop(void)
{
   if (!client.loop()) 
   {
     mqttConnect();
     initManagedDevice();
   }
}
