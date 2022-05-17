/*
 *  ID : Lalit21dedha@gmail.com
 *  Pass: 12345678
 */
//#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


char auth[] = "gGtQji7cgbe-3IcqsRYsgQCT7wRJjUry"; 
char ssid[] = "AndroidAP";  
char pass[] = "87654321";  

bool ON_OFF=0;
WidgetLED led1(V0);
WidgetLED led2(V1);

char cmd_arr1[100];
int cmd_count1;
char inchar=0,t;
int Soil,Rain,temp,humi;

void serial_get_command()
{
  inchar=0;
  if(Serial.available() > 0)
  {
    inchar = Serial.read();    
    if(inchar == '<')
    {
      cmd_count1=0;
      while(inchar != '>' && cmd_count1<80)
      {
        if(Serial.available() > 0)
        {
          inchar = Serial.read();
          cmd_arr1[cmd_count1++] = inchar;
          cmd_arr1[cmd_count1] = '\0';
        }        
      }
      if(inchar == '>')
      {
        cmd_count1--;
        cmd_arr1[cmd_count1] = '\0';
        
        if(cmd_arr1[0]=='A')
        {cmd_arr1[0]='0';Soil = atoi(cmd_arr1);Blynk.virtualWrite(V2, Soil);}
        else if(cmd_arr1[0]=='B')
        {cmd_arr1[0]='0';Rain = atoi(cmd_arr1);Blynk.virtualWrite(V3, Rain);}
        else if(cmd_arr1[0]=='C')
        {cmd_arr1[0]='0';temp = atoi(cmd_arr1);Blynk.virtualWrite(V4, temp);}
        else if(cmd_arr1[0]=='D')
        {cmd_arr1[0]='0';humi = atoi(cmd_arr1);Blynk.virtualWrite(V5, humi);}
        else if(cmd_arr1[0]=='X')
        {cmd_arr1[0]='0';led2.on();led1.off();Blynk.notify("Water Pump On");}
        else if(cmd_arr1[0]=='Y')
        {cmd_arr1[0]='0';led2.off();led1.on();Blynk.notify("Water Pump OFF");}
        else
        {
          
        }
      }
    }
  }
}

void setup()
{
  Serial.begin(9600); // See the connection status in Serial Monitor
  pinMode(5,OUTPUT);
  digitalWrite(5,LOW);
  Blynk.begin(auth, ssid, pass);
  // Setup a function to be called every second
  delay(2000);
  led2.off(); // ON
  led1.on();  // OFF
  digitalWrite(5,HIGH);
}

BLYNK_CONNECTED()
{
 digitalWrite(5,HIGH);
}

void loop()
{  
  Blynk.run(); // Initiates Blynk
  if(!Blynk.connected())
  {
    digitalWrite(5,LOW);
    //Serial.println("Reconnecting ... ");
    Blynk.connect();
  }
  serial_get_command();
}
