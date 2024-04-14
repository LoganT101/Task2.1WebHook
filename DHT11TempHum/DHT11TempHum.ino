#include "arduino_secrets.h"
// DHT sensor library - Version: Latest 
#include <DHT.h>
#include <DHT_U.h>
#include <WiFiNINA.h>
#include "ThingSpeak.h"


#include "thingProperties.h"

unsigned long myChannelNumber = atol(SECRET_CH_ID);
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

WiFiClient client;

#define DHTPIN 2     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  delay(1500); 

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  WiFi.begin(SSID, PASS);
  
  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
 */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
  
  ThingSpeak.begin(client);
  dht.begin();
  
}

void loop() {
  ArduinoCloud.update();
  // Wait 6 secs between readgins
  delay(6000);


  humidity = dht.readHumidity();
  temperature = dht.readTemperature();

  // Update ThingSpeak fields
  ThingSpeak.setField(1, temperature);
  ThingSpeak.setField(2, humidity);
  
  // Write data to ThingSpeak
  ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

  
}



/*
  Since Temperature is READ_WRITE variable, onTemperatureChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onTemperatureChange()  {
  // Add your code here to act upon Temperature change
}

/*
  Since Humidity is READ_WRITE variable, onHumidityChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onHumidityChange()  {
  // Add your code here to act upon Humidity change
}