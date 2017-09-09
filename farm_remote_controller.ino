//this code is to run a remotely situated controller to moniter the drip irrigation,depending upon the requirement of the crop at the farther farm.
//include libraries 
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
//configure the ssid and passwd for connectivity
#define WLAN_SSID       "Theta"
#define WLAN_PASS       "tarunsriram"

//configure the details of the mqtt broker 

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   
#define AIO_USERNAME    "manojsurya"
#define AIO_KEY         "8b0e88bd397d4d9cb6f840f111922282"
//preprocessive directives
#define temp_optimum
#define temp_not_optimum 
//variables
int moisture_value=0;
int temp_value=0;
//constants for costumization for different crops
const int moisture_threshold=450;
const int temperature_threshold=25;
//Wifi client
WiFiClient client;
//init the client with details of the mqtt broker
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
//variables to hold the reference to the feed in the broker
Adafruit_MQTT_Subscribe moisture_controller = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/moisture");
Adafruit_MQTT_Subscribe temperature_controller = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/temperature");
//call MQTT_connect() function

void MQTT_connect();

void setup() {
  Serial.begin(115200);//serial object
  delay(10);
  pinMode(D0,OUTPUT);//init pins
  pinMode(D1,OUTPUT);
  pinMode(D2,OUTPUT);
  pinMode(D3,OUTPUT);



  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);                                 //connect to wifi ,of given ssid and passwd
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());

  mqtt.subscribe(&moisture_controller);//instantiating

  //mqtt.subscribe(&temperature_controller);
}



void loop() {
  
  MQTT_connect();


 Adafruit_MQTT_Subscribe *subscriptionForMoisture;//reference to subscription
  while ((subscriptionForMoisture = mqtt.readSubscription(5000))) {//read the subscription
    if (subscriptionForMoisture == &moisture_controller) {
      moisture_value=atoi((char *)moisture_controller.lastread);//str->int
      Serial.print(F("Got: "));
      Serial.println(moisture_value);
    }
    if(moisture_value>moisture_threshold)
    {
      digitalWrite(D2,HIGH);//valve ON
      digitalWrite(D3,LOW);
    }
    else
    {
      digitalWrite(D2,LOW);//valve OFF
      digitalWrite(D3,LOW);
    }
  }
  
 /* Adafruit_MQTT_Subscribe *subscriptionForTemp;
  while ((subscriptionForTemp = mqtt.readSubscription(5000))) {
    if (subscriptionForTemp == &temperature_controller) {
      temp_value=atoi((char *)temperature_controller.lastread);
      Serial.print(F("Got: "));
      Serial.println(temp_value);
    }
    if(temp_value>temperature_threshold){
      digitalWrite(D0,HIGH);//for temperature more than threshold DANGER!!!!!!!
      digitalWrite(D1,LOW);
      }
    else{
      digitalWrite(D0,LOW);//Safe temperature
      digitalWrite(D1,HIGH);
    }
  }
*/


}


void MQTT_connect() {//function to set up MQTT protocol
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}
