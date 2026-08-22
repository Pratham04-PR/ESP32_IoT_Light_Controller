#include<WiFi.h>
#include<WebServer.h>
#include<Preferences.h>

const int Relay_pin = 23;
const char* ssid = "Room_Lights";
const char* password = "12345678";
WebServer server(80);
Preferences preferences;

bool lightState = false;

String handleControls() {

  String controls = "";

  controls += "<h1>Room Lights</h1>";
  controls += "<p class=\"deviceStatus\">● ESP32 Online</p>";

  if (lightState) {
    controls += "<p class=\"status on\">Status: Lights On</p>";
  }
  else {
    controls += "<p class=\"status off\">Status: Lights Off</p>";
  }

  if (lightState) {
    controls += "<button class=\"offButton\" onclick=\"sendCommand('/off')\">TURN OFF</button>";
  }
  else {
    controls += "<button class=\"onButton\" onclick=\"sendCommand('/on')\">TURN ON</button>";
  }

  return controls;
}

void handleRoot() {

  String page = "<html>";
  page += "<head>";
  page += "<style>";


  page += "body {text-align:center; }";
  page += "button { width: 80%; font-size: 25px; padding: 15px; border: none; border-radius: 10px; margin: 10px; }";

  page += ".status { font-size: 24px; }";
  page += ".on {color: green; font-weight: bold; }";
  page += ".off{color: gray; font-weight: bold; }";

  page += ".onButton { background-color: green; color: white; }";
  page += ".offButton { background-color: red; color: white; }";
  page += ".deviceStatus { color: green; font-size: 18px; font-weight: bold; }";
  page += "</style>";

  page += "<script>";

  
  page += "function sendCommand(command) {";
  page += "fetch(command)";
  page += ".then(response => {";
  page += "if (!response.ok) {";
  page += "throw new Error(\"HTTP error\");";
  page += "}";
  page += "return response.text();";
  page += "})";
  page += ".then(data => {";
  page += "document.getElementById(\"page\").innerHTML = data;";
  page += "})";
  page += ".catch(error => {";
  page += "document.getElementById(\"page\").innerHTML = '<p>ESP32 connection error</p>';";
  page += "});";
  page += "}";

  page += "</script>";
  page += "</head>";

  page += "<body>";
  page += "<div id = \"page\">";

  page += handleControls();

  page += "</div>";
  page += "</body>";
  page += "</html>";


  server.send(200, "text/html", page);
}

void setLight(bool state) {

  lightState = state;

  if (lightState) {
    digitalWrite(Relay_pin, LOW);
  }
  else {
    digitalWrite(Relay_pin, HIGH);
  }
}
void handleOn() {

  setLight(true);

  preferences.putBool("lightState", true);

  server.send(200, "text/html", handleControls());
}

void handleOff() {

  setLight(false);

  preferences.putBool("lightState", false);

  server.send(200, "text/html", handleControls());
}


void setup() {
  pinMode(Relay_pin, OUTPUT);

  Serial.begin(115200);
  preferences.begin("room", false);
  lightState = preferences.getBool("lightState", false);

  setLight(lightState);

  
  WiFi.softAP(ssid, password);
  Serial.println("WiFi started");

  Serial.println("Getting WiFi's IP address....");

  Serial.println(WiFi.softAPIP());
  server.on("/", handleRoot);
  Serial.println("Route created");

  server.on("/on", handleOn);
  Serial.println("ON route created");

  //  Serial.println("Lights ON");

  server.on("/off", handleOff);
  Serial.println("OFF route created");

  //  Serial.println("Lights Off");
  server.begin();
  Serial.println("Server started");
}
void loop () {
  server.handleClient();
}
