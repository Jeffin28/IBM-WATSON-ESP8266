#ifndef __IBM_H
#define __IBM_H

extern void mqttConnect(void);
extern void publishData(void);
extern void client_loop(void);
extern void initManagedDevice(void);
extern void handleUpdate(byte* payload); 
extern void callback(char* topic, byte* payload, unsigned int payloadLength);

#endif
