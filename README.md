# IBM-WATSON-ESP8266
### Interfacing with ESP8266

**IBM WATSON** iot platform is cloud-hosted service that is designed to simplify and derive the value from your IoT devices. Using their device management service, we can perform device actions like rebooting or updating firmware, receive device diagnostics and metadata, or perform bulk device addition and removal. They use an industry-standard MQTT protocol. First of all, we need to have an iot console for the communication with ESP8266.If you don't have an account please refer the documentation in **DOC** folder.

<p align="center">
  <img src="IMG/Screenshot%20(53).png" width="400" align="center">
</p 

<p align="center"><p align="center">

<div align="center">I have used the device side method from the given archiecture of IBM WATSON communication</div>
 
### Steps :
1. Download the repo.
2. For those who have already created a `ibm watson` console [Click here For ibm login](https://cloud.ibm.com/login).
3. **For those who doesn't have ibm console 😇** open the **DOC** folder for ibm console creation and read the document __IBM_WATSON__.pdf carefully and do it 👍.
4. Open **LIB** folder then place the `ArduinoJson`(5.13.5) and `PubSubClient`(2.7.0) folders into your arduino local dierectory folder (`libraries`) from the downloaded repo.
5. After the console creation and library allocation move on for source code side.It can be found in **CODE** folder. 
6. We need to change credentials in **global.h** and **ibm.cpp** before the code simulation so open the `CODE` folder

in `global.h`:

**Provide your ssid and password of WIFI router here:**

<p align="center">
  <img src="IMG/Screenshot%20(49).png" width="700" align="center">
</p 
  
in `ibm.cpp`:   
  
**Please enter Organization ID (Bluemix ID), Device type and ID, Authentication token here from step 8.Don’t change any other options below it:**

<p align="center">
  <img src="IMG/Screenshot%20(50).png" width="700" align="center">
</p 

* After the prescribed changes from **step 6**,compile the code.
* Next upload the code with Arduino IDE and restart the module once again after uploading completed.
* I have tested in esp8266 core version `2.4.2`.
* For doing `publish` and `subscribe`refer the last page of **IBM_WATSON.pdf** documentation and enjoy 😃 !!.
* Output debug can be seen in serial monitor with `9600`baudrate [refer the document]:  

for `publish`   :
  
<p align="center">
<img src="IMG/Screenshot%20(52).png" width="800" align="center">
</p 
  
for `subscribe` : 
  
<p align="center">
<img src="IMG/Screenshot%20(47).png" width="800" align="center">
</p 
  
