#include <SoftwareSerial.h>

SoftwareSerial gsm(2, 3);   // RX, TX for SIM800L
SoftwareSerial gps(4, 5);   // RX, TX for GPS

int buttonPin = 7;
int buzzer = 8;

String latitude = "";
String longitude = "";

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);

  Serial.begin(9600);
  gsm.begin(9600);
  gps.begin(9600);

  delay(2000);
}

void loop() {
  readGPS();

  if (digitalRead(buttonPin) == LOW) {
    triggerSOS();
  }
}

void readGPS() {
  while (gps.available()) {
    char c = gps.read();
    Serial.write(c);
    // (Basic parsing — you can improve using TinyGPS++)
  }
}

void triggerSOS() {
  digitalWrite(buzzer, HIGH);

  String message = "HELP! I am in danger.\nLocation: https://maps.google.com/?q=" 
                   + latitude + "," + longitude;

  sendSMS("+91XXXXXXXXXX", message);
  makeCall("+91XXXXXXXXXX");

  delay(10000);
  digitalWrite(buzzer, LOW);
}

void sendSMS(String number, String msg) {
  gsm.println("AT+CMGF=1");
  delay(1000);
  gsm.println("AT+CMGS=\"" + number + "\"");
  delay(1000);
  gsm.println(msg);
  gsm.write(26); // CTRL+Z
  delay(5000);
}

void makeCall(String number) {
  gsm.println("ATD" + number + ";");
  delay(10000);
  gsm.println("ATH");
}
