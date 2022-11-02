#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// WiFi
const char *ssid = "Alfamart Biclatan"; // Enter your WiFi name
const char *password = "Jollib33parin";  // Enter WiFi password

// MQTT Broker
const char *mqtt_broker = "broker.hivemq.com"; // Enter your WiFi or Ethernet IP
const char *topic = "aeraterta/testing";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);
void setup() 
  {
    Serial.begin(115200);                                                                                       //Set software serial baud to 115200
    WiFi.begin(ssid, password);                                                                                 //Connecting to a WiFi network
    Serial.print("Connecting to WiFi..");
    while (WiFi.status() != WL_CONNECTED) 
      {
        delay(500);
        Serial.print(".");
      }
    Serial.println("");
    Serial.println("Connected to the WiFi network");
    
    //connecting to a mqtt broker
    client.setServer(mqtt_broker, mqtt_port);
    //client.setCallback(callback);
    
    while (!client.connected()) 
      {
        String client_id = "esp8266-client-";
        client_id += String(WiFi.macAddress());
        
        Serial.printf("The client %s connects to mosquitto mqtt broker\n", client_id.c_str());
        
        if (client.connect(client_id.c_str())) 
          {
            Serial.println("Public emqx mqtt broker connected");
          } 
        else 
          {
            Serial.print("failed with state ");
            Serial.print(client.state());
            delay(2000);
          }
      }
    
    client.publish(topic, "Hello From ESP8266!");                                                               //Publish test data
  }
  
void loop() 
  {
    client.loop();
  }
