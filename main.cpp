/*

    Slider widget on V0
    Value display on V2
    External led pin is the Relay
    Internal led is the indication for power
 */
#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL3pDOLBYCX"
#define BLYNK_TEMPLATE_NAME "Smart_coaster"
#define BLYNK_AUTH_TOKEN "QNWhcb7n0HRngjKfiVJEdUm6l3JOBhK5"
#include <BlynkSimpleEsp32.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 4 
#define EXTERNAL_LED_PIN 5
#define INTERNAL_LED_PIN 2

int it,tempC,internalLedState;
OneWire oneWire(ONE_WIRE_BUS);  
DallasTemperature sensor(&oneWire);
char auth[] = "QNWhcb7n0HRngjKfiVJEdUm6l3JOBhK5";
char ssid[] = "a1";
char pass[] = "12345678";

BLYNK_CONNECTED() {
 
  Blynk.syncAll();

  
  int value = millis() / 1000;
  Blynk.virtualWrite(V2, value);
}

BLYNK_WRITE(V0)
{
 
  it = param.asInt();
  Blynk.virtualWrite(V2,it);
  sensor.requestTemperatures();
  tempC = sensor.getTempCByIndex(0); 
  Blynk.virtualWrite(V3, tempC);
  internalLedState = digitalRead(2);
  Serial.print("Slider Value: ");
  Serial.println(it);
  Serial.print("Temperature: ");
  Serial.println(tempC);
}
 

BlynkTimer timer;
void setup()
{
  
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
   pinMode(EXTERNAL_LED_PIN, OUTPUT);
   pinMode(INTERNAL_LED_PIN, OUTPUT);
 
  digitalWrite(EXTERNAL_LED_PIN, HIGH);
  BLYNK_WRITE();
  BLYNK_CONNECTED();
}

void loop()
{
  Blynk.run();
  delay(5000);
  checkConditions();

}
void checkConditions() {

  

  if (it > tempC && internalLedState == 1) {
    
    digitalWrite(EXTERNAL_LED_PIN, LOW);
    delay(30000);
    digitalWrite(EXTERNAL_LED_PIN, HIGH);
  } else {
   
    digitalWrite(EXTERNAL_LED_PIN, HIGH);
  }
}
