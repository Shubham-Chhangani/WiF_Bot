/* © Robocell,CCA */
/* This code is given during Autonomous robotics workshop organised  by Robocell,CCA on 14 & 15th September,2019. */
/* Follow us on https://www.facebook.com/ccanitd.in/ 
/* For queries/help mail us at robocell@ccanitd.in 
 * Visit us at-www.ccanitd.in*/

/* FUNCTIONING:
 *This is the code for smart bot controlled wirelessly using wifi  */

/*SETUP:
 * 1.Go to playstore and install Wifi RC Car ESP8266.
 * 2.connect your mobile to the network hosted by Nodemcu.
 * 3.Go to settings of the application and enter the ip address.
 * 4.set the commands in the application.
 * HAVE FUN.............
 */
 
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// SSID parameters
const char *ssid = "Hasan";                      /*Set as your team name.*/
const char *password = "Hasan12345";                  /*set password.*/

IPAddress ip(192, 168, 4, 1);               /* IP Address-Enter the same ip in the app.*/
IPAddress netmask(255, 255, 255, 0);      
const int port = 80; // Port
ESP8266WebServer server (port);


/* define L298N or L293D motor control pins */
int leftMotorBackward = D1;                 /* (D1) -> IN1  */
int leftMotorForward = D2;                  /* (D2) ->IN2   */
int rightMotorForward = D3;                 /* (D3) -> IN3   */
int rightMotorBackward = D4;                /* (D4) -> IN4  */




void setup() {
  
  Serial.begin(115200);                     
 
  pinMode(D5, OUTPUT);                      /* LED pin*/

   // Setup AP
  WiFi.mode(WIFI_AP); 
  WiFi.softAPConfig(ip, ip, netmask);
  WiFi.softAP(ssid, password);

  
  // Declaration of motors
  pinMode(leftMotorForward, OUTPUT);
  pinMode(rightMotorForward, OUTPUT); 
  pinMode(leftMotorBackward, OUTPUT);  
  pinMode(rightMotorBackward, OUTPUT);


  // Start Server
  server.on("/", HTTP_GET, handleRoot);
  server.begin();
  
}



void loop() {

  server.handleClient();

}


void handleRoot() {
  if (server.hasArg("State")) {
    String value = server.arg("State");
    Serial.println("Value = " + value);
    server.send(200, "text / plain", "Request received");
    
    if (value.equals("F")) {
      forward();
      server.send(200, "text / plain", "Forward");
    }
    else  if (value.equals("B")) {
      backward();
      server.send(200, "text / plain", "Backward");
    }
    else  if (value.equals("L")) {
      left();
      server.send(200, "text / plain", "Turn Left");
    }
    else  if (value.equals("R")) {
     right();
      server.send(200, "text / plain", "Turn Right");
    }
    else  if (value.equals("S")) {
      stop();
      server.send(200, "text / plain", "Stop");
    }
     else  if (value.equals("ON")) {
      ON();
      server.send(200, "text / plain", "ON");
    }
     else  if (value.equals("OFF")) {
      OFF();
      server.send(200, "text / plain", "OFF");
    }
  }
}



/*************** FORWARD *******************/
void forward(void)   
{
  digitalWrite(leftMotorForward,HIGH);
  digitalWrite(rightMotorForward,HIGH);
  digitalWrite(leftMotorBackward,LOW);
  digitalWrite(rightMotorBackward,LOW);
}

/*************** BACKWARD *******************/
void backward()   
{
  digitalWrite(leftMotorBackward,HIGH);
  digitalWrite(rightMotorBackward,HIGH);
  digitalWrite(leftMotorForward,LOW);
  digitalWrite(rightMotorForward,LOW);
}

/*************** TURN LEFT *******************/
void left()   
{
  digitalWrite(rightMotorForward,HIGH);
  digitalWrite(leftMotorBackward,LOW);
  digitalWrite(rightMotorBackward,LOW);
  digitalWrite(leftMotorForward,LOW);
}



/*************** TURN RIGHT *******************/
void right()   
{
  digitalWrite(leftMotorForward,HIGH);
  digitalWrite(leftMotorBackward,LOW);
  digitalWrite(rightMotorForward,LOW);
  digitalWrite(rightMotorBackward,LOW);
}


/*************** STOP *******************/
void stop()   
{
  digitalWrite(leftMotorForward,LOW);
  digitalWrite(leftMotorBackward,LOW);
  digitalWrite(rightMotorForward,LOW);
  digitalWrite(rightMotorBackward,LOW);
}
/*************** ON *******************/
void ON()   
{
  digitalWrite(D5,HIGH);
}
/*************** OFF *******************/
void OFF()   
{
  digitalWrite(D5,LOW);
}
