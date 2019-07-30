void parseCurrentValues(String finalStrings) {
  StaticJsonBuffer<200> jsonBuffer;

  //Get the root object in the jsonBuffer
  JsonObject& root = jsonBuffer.parseObject(finalStrings);
  Serial.println(finalStrings);

  //Verify possibly deserilazation errors
  if (root == JsonObject::invalid()) {
    return;
  }

  // Verify if  the address of the incomming sensor  its the same of to the best sensor
  // saved on the collection. If yes, saves IOT variables and print the type and the value of that sensor

  if (root["s_add"] == bestRSsensorAddress) {
    inputIOPTrainSensorValue = root["s_value"];
    inputIOPTrainSensorType = root["s_type"];
    Serial.print(inputIOPTrainSensorType);
    Serial.print(" IOPT Value: ");
    Serial.println(inputIOPTrainSensorValue);

  }

  if (root["s_add"] == bestSHsensorAddress) {
    inputIOPTSoilHumiditySensorValue = root["s_value"];
    inputIOPTSoilHumiditySensorType = root["s_type"];
    Serial.print(inputIOPTSoilHumiditySensorType);
    Serial.print(" IOPT Value: ");
    Serial.println(inputIOPTSoilHumiditySensorValue);

  }

  if (root["s_add"] == bestATsensorAddress) {
    inputIOPTambientTemperatureSensorValue = root["s_value"];
    inputIOPTambientTemperatureSensorType = root["s_type"];
    Serial.print(inputIOPTambientTemperatureSensorType);
    Serial.print(" IOPT Value: ");
    Serial.println(inputIOPTSoilHumiditySensorValue);
  }

  jsonBuffer.clear();

}

void deserializeIncomingString(String finalStrings) {

  StaticJsonBuffer<200> jsonBuffer;

  //Get the root object in the jsonBuffer
  JsonObject& root = jsonBuffer.parseObject(finalStrings);

  //Verify possibly deserilazation errors
  if (root == JsonObject::invalid()) {
    return;
  }

  //Verify eatch unique sensor address and compares if exits in the collection
  // If incomming sensor address exists in the collection, ignores and exit the function
  for (int j = 0; j < sensorCount; j++) {
    if (collection[j].s_address == incomingSensorAdress(incomingString))
      return;
  }

  // If not, adds the new sensor to the collection
  collection[sensorCount].s_address = incomingSensorAdress(incomingString);
  collection[sensorCount].s_type = (char*)root["s_type"];
  collection[sensorCount].s_value = root["s_value"];
  collection[sensorCount].s_rssi = incomingRSSIsignal(incomingString);

  printStruct();
  sensorCount++;
  jsonBuffer.clear();
}


//Check Rain Sensor
void betterRSsensors(){

  for (int j = 0; j < sensorCount; j++) {

    //Check if is RS
    if (collection[j].s_type == "RS") {

      //Check if current has better signal
      if (collection[j].s_rssi > betterRSSignalStregth) {
        betterRSSignalId = j;
        betterRSSignalStregth = collection[j].s_rssi;
        bestRSsensorAddress = collection[j].s_address;

      }
    }

  }
  Serial.println("Best Rain Sensor Sensor located on index " + (String)betterRSSignalId + " as a RSSI of " + (String)betterRSSignalStregth);

}


//Check Soil Humidity Sensor
void betterSHsensors() {

  for (int j = 0; j < sensorCount; j++) {

    //Check if is HS
    if (collection[j].s_type == "SH") {

      //Check if current has better signal
      if (collection[j].s_rssi > betterSHSignalStregth) {
        betterSHSignalId = j;
        betterSHSignalStregth = collection[j].s_rssi;
        bestSHsensorAddress = collection[j].s_address;

      }
    }

  }
  Serial.println("Best Soil Humidity Sensor located on index " + (String)betterSHSignalId + " as a RSSI of " + (String)betterSHSignalStregth);

}

//Check Ambient Temperature Sensor
void betterATsensors() {

  for (int j = 0; j < sensorCount; j++) {

    //Check if is AT
    if (collection[j].s_type == "AT") {

      //Check if current has better signal
      if (collection[j].s_rssi > betterATSignalStregth) {
        betterATSignalId = j;
        betterATSignalStregth = collection[j].s_rssi;
        bestATsensorAddress = collection[j].s_address;
      }
    }

  }
  Serial.println("Best Ambient Temperature Sensor located on index " + (String)betterATSignalId + " as a RSSI of " + (String)betterATSignalStregth);

}

// Print the intire array of struct sensor
void printStruct() {
  for (int i = 0; i < sensorCount + 1; i++) {
    Serial.println();
    Serial.println("Sensors Struct position [" + (String)i + "]");
    Serial.println("   s_type: " + (String)collection[i].s_type );
    Serial.println("   s_value: " + (String)collection[i].s_value );
    Serial.println("   s_rssi: " + (String)collection[i].s_rssi );
    Serial.println("   s_address: " + (String)collection[i].s_address );
  }
}


void resetLoRa() {
  pinMode(11, INPUT);  // this sets the PIN to a tri-state (high impedance)
  digitalWrite(11, LOW); // Ensures the pin's internal pullup is not enabled
  // When the pinMode is set to OUTPUT the pin state will be LOW
  pinMode(11, OUTPUT);  // sets the pin from tri-state to LOW
  delay(200);
  pinMode(11, INPUT);// returns the pin to tri-state
}

void configLoRa() {
  LoraSerial.write("AT+BAND=915000000\r\n");
  delay(200);
  LoraSerial.write("AT+IPR=9600\r\n");
  delay(200);
  LoraSerial.write("AT+NETWORKID=0\r\n");
  delay(200);
  LoraSerial.write("AT+ADDRESS=0\r\n");
  delay(200);
  LoraSerial.write("AT+PARAMETER=10,7,1,7\r\n");
  delay(200);
  LoraSerial.write("AT+MODE=0\r\n");
  delay(200);
  while (LoraSerial.available() > 0) {
    Serial.write(LoraSerial.read());
  }
  LoraSerial.write("AT+BAND?\r\n");
  delay(200);
  LoraSerial.write("AT+IPR?\r\n");
  delay(200);
  LoraSerial.write("AT+NETWORKID?\r\n");
  delay(200);
  LoraSerial.write("AT+ADDRESS?\r\n");
  delay(200);
  while (LoraSerial.available() > 0) {
    Serial.write(LoraSerial.read());
  }
  LoraSerial.write("AT+PARAMETER?\r\n");
  delay(200);
  LoraSerial.write("AT+MODE?\r\n");
  delay(200);
  while (LoraSerial.available() > 0) {
    Serial.write(LoraSerial.read());
  }
  LoraSerialFlush();
  delay(200);
}


void serialFlush() {
  while (Serial.available() > 0) {
    char t = Serial.read();
  }
}


void LoraSerialFlush() {
  while (LoraSerial.available() > 0) {
    char t = LoraSerial.read();
  }
}


int incomingStrSize(String inString) {
  int sz = inString.substring(7, 10).toInt();
  if (sz != (inString.length() - 20) ) {
    digitalWrite(SIZE_ERR_PIN, HIGH);
  } else {
    digitalWrite(SIZE_ERR_PIN, LOW);
  }
  return (sz);
}



int incomingRSSIsignal(String inString) {
  return (inString.substring((inString.length() - 8), (inString.length() - 5))).toInt();
}

int incomingSNRsignal(String inString) {
  return (inString.substring((inString.length() - 4), (inString.length() - 1))).toInt();
}

int incomingSensorAdress(String inString) {
  return (inString.substring(5, 6).toInt());
}
