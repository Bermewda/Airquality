
#include <ESP8266WiFi.h>
#define PWM D0
#define FAN D1                  
const char* ssid = "ssid";               
const char* password = "password";     
unsigned char status_fan = 0;       
WiFiServer server(80);              

int gas;

void setup() {
  Serial.begin(115200);             
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);           
  while (WiFi.status() != WL_CONNECTED)     
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");    
  server.begin();                   
  Serial.println("Server started");
  Serial.println(WiFi.localIP());           

  pinMode(PWM, INPUT);
  pinMode(FAN, OUTPUT);
}




void loop() {
  WiFiClient client = server.available();       
  if (!client) {            
    return;
  }

  Serial.println("new client");
  while (!client.available())
  {
    delay(1);
  }
  String req = client.readStringUntil('\r');        
  Serial.println(req);              
  client.flush();



  if (req.indexOf("/off") != -1)
  {
    status_fan = 0;
    digitalWrite(FAN, 0);         
    Serial.println("OFF");
  }
  else if (req.indexOf("/on") != -1)
  {
    status_fan = 1;
    digitalWrite(FAN, 1);       
    Serial.println("ON");
  }
  gas = getPWM();
  if (gas > 800) {
    while (gas > 450) {
      gas = getPWM();
      digitalWrite(FAN, 1);
    }
    digitalWrite(FAN, 0);
  }
  




  //HTML
  String web = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";

  
  web += "<html>\r\n";
  web += "<head>\r\n";
  web += "<style>\r\n";
  web += "body {margin:0;}\r\n";
  
  web += "ul {\r\n";
  web += "  list-style-type: none;\r\n";
  web += "  margin: 0;\r\n";
  web += "  padding: 0;\r\n";
  web += "  overflow: hidden;\r\n";
  web += "  background-color: #333;\r\n";
  web += "  position: fixed;\r\n";
  web += "  top: 0;\r\n";
  web += "  width: 100%;\r\n";
  web += "}\r\n";
  
  web += "li {\r\n";
  web += "  float: left;\r\n";
  web += "}\r\n";
  
  web += "li a {\r\n";
  web += "  display: block;\r\n";
  web += "  color: white;\r\n";
  web += "  text-align: center;\r\n";
  web += "  padding: 14px 16px;\r\n";
  web += "  font-family: 'Franklin Gothic Medium', 'Arial Narrow', Arial, sans-serif;\r\n";
  web += "}\r\n";
  
  web += "p {\r\n";
  web += "    background-color: whitesmoke;\r\n";
  web += "    padding: 50px;\r\n";
  web += "    margin: 50px 400px 0px 400px ;\r\n";
  web += "    font-size:200%;\r\n";
  web += "    text-align: center;\r\n";
  web += "    font-family: 'Franklin Gothic Medium', 'Arial Narrow', Arial, sans-serif;\r\n";
  web += "    box-shadow: 0 8px 16px 0 rgba(0,0,0,0.2), 0 6px 20px 0 rgba(0,0,0,0.19);\r\n";
  web += "    display:inline-block;\r\n";
      
  web += "}\r\n";
  
  web += "#btn1{\r\n";
  web += "    background-color: #4CAF50;\r\n";
  web += "    color: white;\r\n";
  web += "    border:2px solid #4CAF50;\r\n";
  web += "    text-align: center;\r\n";
  web += "    font-size: 16px;\r\n";
  web += "    padding: 16px 32px;\r\n";
  web += "    margin: 4px 2px;\r\n";
  web += "    font-family: 'Franklin Gothic Medium', 'Arial Narrow', Arial, sans-serif;\r\n";
  web += "    cursor: pointer;\r\n";
  web += "}\r\n";
  web += "#btn1:hover {\r\n";
  web += "    background-color:  rgb(44, 92, 46);\r\n";
  web += "    color: white;\r\n";
  web += "    border:2px solid rgb(44, 92, 46);\r\n";
  web += "    text-align: center;\r\n";
  web += "    font-size: 16px;\r\n";
  web += "    padding: 16px 32px;\r\n";
  web += "    margin: 4px 2px;\r\n";
  web += "    font-family: 'Franklin Gothic Medium', 'Arial Narrow', Arial, sans-serif;\r\n";
  web += "    cursor: pointer;\r\n";
  web += "}\r\n";
  
  web += "#btn1:active{\r\n";
  web += "    background-color: whitesmoke;\r\n";
  web += "    color: lightgray;\r\n";
  web += "    border:2px solid lightgray;\r\n";
  web += "    text-align: center;\r\n";
  web += "    font-size: 16px;\r\n";
  web += "    padding: 16px 32px;\r\n";
  web += "    margin: 4px 2px;\r\n";
  web += "    font-family: 'Franklin Gothic Medium', 'Arial Narrow', Arial, sans-serif;\r\n";
  web += "    cursor: pointer;\r\n";
  web += "}\r\n";
  
  web += "#btn2{\r\n";
  web += "    background-color: #ff6666;\r\n";
  web += "    color: white;\r\n";
  web += "   border:2px solid #ff6666;\r\n";
  web += "    text-align: center;\r\n";
  web += "    font-size: 16px;\r\n";
  web += "    padding: 16px 32px;\r\n";
  web += "    margin: 4px 2px;\r\n";
  web += "    font-family: 'Franklin Gothic Medium', 'Arial Narrow', Arial, sans-serif;\r\n";
  web += "    cursor: pointer;\r\n";
  web += "}\r\n";
  web += "#btn2:hover {\r\n";
  web += "    background-color: #b33d3d;\r\n";
  web += "    color: white;\r\n";
  web += "    border:2px solid #b33d3d;\r\n";
  web += "    text-align: center;\r\n";
  web += "    font-size: 16px;\r\n";
  web += "    padding: 16px 32px;\r\n";
  web += "    margin: 4px 2px;\r\n";
  web += "    font-family: 'Franklin Gothic Medium', 'Arial Narrow', Arial, sans-serif;\r\n";
  web += "    cursor: pointer;\r\n";
  web += "}\r\n";
  
  web += "#btn2:active{\r\n";
  web += "    background-color: whitesmoke;\r\n";
  web += "    color: lightgray;\r\n";
  web += "    border:2px solid lightgray;\r\n";
  web += "    text-align: center;\r\n";
  web += "    font-size: 16px;\r\n";
  web += "    padding: 16px 32px;\r\n";
  web += "    margin: 4px 2px;\r\n";
  web += "    font-family: 'Franklin Gothic Medium', 'Arial Narrow', Arial, sans-serif;\r\n";
  web += "    cursor: pointer;\r\n";
  web += "}\r\n";
  web += "</style>\r\n";
  web += "<meta http-equiv=\"refresh\" content=\"5\">\r\n";
  web += "</head>\r\n";
  
  web += "<body style=\"background-color:gainsboro\">\r\n";
  web += "<ul>\r\n";
  web += "  <li><a> DASHBOARD </a></li>\r\n";
  web += "</ul>\r\n";
  web += "<br><br><br>\r\n";
  web += "<center><p>";
  web += "<b>Cabondioxide</b><br>";
  web += gas;
  web += " ppm</p></center>\r\n";
  web += "<center><p>FAN<br>\r\n";
  web += "<a href=\"/on\"><button id=\"btn1\">ON</button></a>\r\n";
  web += "<a href=\"/off\"><button id=\"btn2\">OFF</button></a>\r\n";
  web += "</p></center>\r\n";
  web += "</body>\r\n";
  web += "</html>\r\n";

  client.print(web);    //ส่ง HTML Code ไปยัง client
}


int getPWM()
{
  //wait for PWM start
  while (digitalRead(PWM) == LOW);
  //wait for PWM end
  long startTime = micros();
  while (digitalRead(PWM) == HIGH);
  long duration = micros() - startTime;
  //from datasheet
  //CO2 ppm = 5000 * (Th - 2ms) / (Th + Tl - 4ms)
  //  given Tl + Th = 1004
  //        Tl = 1004 - Th
  //        = 5000 * (Th - 2ms) / (Th + 1004 - Th -4ms)
  //        = 5000 * (Th - 2ms) / 1000 = 2 * (Th - 2ms)
  long co2ppm = 5 * ((duration / 1000) - 2);
  Serial.println(co2ppm);
  return co2ppm;
}
