#define SERVER_SOCKET_PORT 80
//#define PRINT_STRING_GOT_DATA
#define PRINT_HEX_GOT_DATA
//#define PRINT_DEC_GOT_DATA

#include <WiFi.h>

// Wifi settings
const char* ssid = "len12-75";
const char* password = "doc12345";

WiFiServer server(SERVER_SOCKET_PORT);
String currentLine;

void setup() {
    Serial.begin(115200);
    Serial.println("Connecting to Wifi");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(IpAddress2String(WiFi.localIP()));
    Serial.println("Port: " + String(SERVER_SOCKET_PORT));
    server.begin();
}

void loop() {
    WiFiClient client = server.available();
    if (client) { 
        Serial.println("Client connected");
        while (client.connected()) { 
            while (client.available()) {
                char c = client.read(); 
                #ifdef PRINT_STRING_GOT_DATA
                    Serial.print(String({c}));
                #endif
                #ifdef PRINT_DEC_GOT_DATA
                    Serial.print(String(c));
                #endif
                #ifdef PRINT_HEX_GOT_DATA
                    Serial.print("0x"); 
                    Serial.print(c, HEX); 
                    Serial.print(" "); 
                #endif
            }
        }

        client.stop();
        Serial.println("");
        Serial.println("Client disconnected.");
        Serial.println("");
    }
}