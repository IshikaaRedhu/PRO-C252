
#include<WiFi.h>
#include<HTTPClient.h>

//  wifi credentials
const char ssid[] = "wifi name";
const char password[] = "password;

//  API url
String api = "http://192.168.1.32:5000/add";


HTTPClient http;


const int potpin = 34;

void setup()
{
  Serial.begin(115200);
  Serial.print("Connecting to : ");
  Serial.println(ssid);
  WiFi.begin(ssid , password);
  while (WiFi.status()  !=  WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println("Connected with Wifi !");
}

void loop()
{

  int pot = analogRead(potpin);
  Serial.print("Pot Val : ");
  Serial.println(pot);

  if (WiFi.status()  ==  WL_CONNECTED)
  {
        
    http.begin(api);

    http.addHeader("Content-Type" , "application/json");

    String info = "{\"potentiometer\" : " + String(pot) + "}";

    int http_code = http.POST(info);

    if (http_code  >  0)
    {
      String response = http.getString();
      Serial.print("Response code : ");
      Serial.print(http_code);
      Serial.print('\t');
      Serial.print("Message from Server : ");
      Serial.println(response);
    }

    else
    {
      Serial.print("ErrorCode : ");
      Serial.println(http_code);
    }

    http.end();
  }

  else
  {
    Serial.print("Not connected with Wi-Fi : ");
    Serial.println(ssid);
  }


  delay(1000);

}
