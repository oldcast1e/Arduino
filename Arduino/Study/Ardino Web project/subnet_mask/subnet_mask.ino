#include <WiFi.h>
int status = WL_IDLE_STATUS;     // the Wifi radio's status

//SSID of your network
char ssid[] = "iptime";
//password of your WPA Network
char pass[] = "";

IPAddress ip;
IPAddress subnet;
IPAddress gateway;

void setup()
{
  WiFi.begin(ssid);
  Serial.begin(9600);
  if ( status != WL_CONNECTED) {
    Serial.println("Couldn't get a wifi connection");
    while(true);
  }
  // if you are connected, print out info about the connection:
  else {

    // print your subnet mask:
    subnet = WiFi.subnetMask();
    Serial.print("NETMASK: ");
    Serial.println(subnet);

  }
}

void loop () {
}
