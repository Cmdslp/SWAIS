// ADDRESS 1 MODULE
#include <avr/sleep.h>
#include <avr/wdt.h>
//#include <avr/interrupt.h>
#include <avr/power.h>
#include "Tx_types.h"
#include <ArduinoJson.h>
#include <SoftwareSerial.h>

SoftwareSerial LoraSerial(RX, TX); // LoRa UART comunication Tx and RxS
void(* resetFunc) (void) = 0; //declare reset function @ address 0

ISR(WDT_vect) {
  /* set the flag. */
  if (f_wdt == 0)
  {
    f_wdt = 1;
  }
}


void setup() {
  
  pinMode(SENSOR_PIN, INPUT);  //Sensor Input
  pinMode(SEND_LED, OUTPUT);  //Transmiting
  pinMode(RX, INPUT);
  pinMode(TX, OUTPUT);
  
  LoraSerial.begin(9600);
  Serial.begin(9600);
  configLoRa();

  /* Clear the reset flag. */
  MCUSR &= ~(1 << WDRF);
  /* In order to change WDE or the prescaler, we need to
     set WDCE (This will allow updates for 4 clock cycles). */
  WDTCSR |= (1 << WDCE) | (1 << WDE);
  /* set new watchdog timeout prescaler value */
  WDTCSR = 1 << WDP0 | 1 << WDP3; /* 8.0 seconds */
  /* Enable the WD interrupt (note no reset). */
  WDTCSR |= _BV(WDIE);
}

void loop() {
  if (f_wdt == 1) {

    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& root = jsonBuffer.createObject();
    root["s_type"] = "SH";
    root["s_value"] = moistureSensor();
    Serial.print(readVcc()); // readVcc();
    Serial.println(" mV");
    String tempString;
    root.printTo(tempString);
    delay(500);
    //Serial.println(tempString);
    String stringToSend = "AT+SEND=0," + String(tempString.length()) + "," + tempString;
    digitalWrite(SEND_LED, HIGH);
    LoraSerial.println(stringToSend);
    delay(500);
    digitalWrite(SEND_LED, LOW);
    Serial.println(stringToSend);
    Serial.print("Entering Sleep mode... ");
    sleepLora();
    f_wdt = 0;
    powerSaver2();
    delay(10000);
    sleep_disable();
    power_all_enable();
    delay(100);
    Serial.print("Awaking... ");
    delay(100);
    LoraSerialFlush();
    serialFlush();
    resetFunc();
       
  }
}
