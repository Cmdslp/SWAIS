#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include "Rx.h"


void setup() {
  Serial.begin(9600);
  LoraSerial.begin(9600);
  pinMode(RCV_LED_PIN, OUTPUT);
  pinMode(SIZE_ERR_PIN, OUTPUT);
  pinMode(SEND_LED_PIN, OUTPUT);
  configLoRa();
  resetLoRa();
  delay(200);

}
void(* resetFunc) (void) = 0; //declare reset function @ address 0

void loop() {

  //O LoRa recebeu uma MSG
  if (LoraSerial.available()) {

    digitalWrite(RCV_LED_PIN, HIGH);

    //Grava a string enviada pelos nós sensores
    incomingString = LoraSerial.readString();
    digitalWrite(RCV_LED_PIN, LOW);

    //Sub String com apenas os valores dos sensores recebidos pelo LoRa
    String tmpString = incomingString.substring(10, (incomingString.length() - 10)); //-->> ATENÇÃO AOS VALORES MAIORES QUE 2 CASAS  11 ATÉ 10

    // Constroi a string final com todos os campos necessários
    String finalString = tmpString + ",\"rssi\":\"" + incomingRSSIsignal(incomingString) + "\",\"s_add\":\"" + incomingSensorAdress(incomingString) + "\"}";
    Serial.println("-------------------------------------------------------------");
    //Serial.print(incomingString);
    //delay(500);
    //Serial.println(tmpString);
    //delay(500);
    Serial.println(finalString);
    delay(100);
    Serial.println("-------------------------------------------------------------");

    //Enquanto o numero de sensores que se encontram ao alcançe for menor que o número máx de sensores permitidos
    // Decompõe a finalString num objeto JSON e cria uma coleção de sensores (Struct Sensores)
    if (sensorCount < MAX_NUM_SENSORS) {
      deserializeIncomingString(finalString);

      Serial.print("Total sensors in range: ");
      Serial.println(sensorCount);

      // Depois da coleção de sensores totalmente (ou não) preenchida (MAX 5),
      // Verifica cada um dos diferentes tipos de sensores (RS, SH, AT) e escolhe os com melhor RSSI
      betterRSsensors();
      betterSHsensors();
      betterATsensors();
      resetCount++;
    }

    // Decompõe a finalString do melhor nó sensor após verificação do endereço
    parseCurrentValues(finalString);

    // Limpa Strings e Buffers
    LoraSerialFlush();
    serialFlush();
    incomingString = "";
  }

  if (resetCount > RESET_COUNT){
    Serial.print("RESETING...");
    delay(500);
    resetFunc();  //call reset
  }
  //Serial.println(inputIOPTrainSensorValue);
}
