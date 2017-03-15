#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <String.h>

//static const int RXPin = 2, TXPin = 3;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
//SoftwareSerial ss_gps(2, 3);
//SoftwareSerial ss_gsm(4,5);

void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
  
  for (uint32_t baud_r = 9600; baud_r <= 230400; baud_r += 9600 )
  {

    Serial.println(baud_r);
    Serial3.begin(baud_r);
    Serial3.println("AT");
    
    smartDelay(2000);

      if (Serial3.find("OK"))
      {
        Serial.println("Success : ");
       // Serial.println(baud_r);
        Serial3.println("AT+GPS=1");
        Serial.println("AT+GPS=1");
        smartDelay(5000);
        if (Serial3.find("OK"))
        {
          Serial.println(Serial3.readString());
          Serial.println(millis());
          Serial3.println("ATE1");  
           get_IMEI();
        }
        break;
      }
   }  
}

void loop ()
{
  /*Serial.print('\n');*/
  Serial.println(" Entered loop function ");
  smartDelay(10000);
}

static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do
  {
    while (Serial1.available())
      gps.encode(Serial1.read());
  } while (millis() - start < ms);
}

String get_IMEI()
{
  Serial.println("\nEntered get-IMEI program.");
  Serial3.println("AT+CGSN");
  Serial.println("Printed to GSM");
  smartDelay(1000);
  if ( Serial3.available() )
  {
    String IMEI = Serial3.readString();
    Serial.println(IMEI);
    IMEI.remove(0,11);
    IMEI.remove(15,17);
    Serial.println("FINAL STRING:");
    Serial.println(IMEI);
    Serial.println(IMEI.length());
  }  
}


