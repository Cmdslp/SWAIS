void configLoRa() {
  
  LoraSerialFlush();
  LoraSerial.write("AT+IPR=9600\r\n");
  delay(200);
  LoraSerial.write("AT+BAND=915000000\r\n");
  delay(200);
  LoraSerial.write("AT+NETWORKID=0\r\n");
  delay(200);
  LoraSerial.write("AT+ADDRESS=1\r\n");
  delay(200);
  LoraSerial.write("AT+PARAMETER=10,7,1,7\r\n");
  delay(200);
  LoraSerial.write("AT+MODE=0\r\n");
  delay(200);
  while (LoraSerial.available() > 0) {
    Serial.write(LoraSerial.read());
  }
  delay(200);
  LoraSerialFlush();
}

void sleepLora() {
  LoraSerialFlush();
  LoraSerial.write("AT+MODE=1\r\n");
  delay(200);
  while (LoraSerial.available() > 0) {
    Serial.write(LoraSerial.read());
  }
  delay(200);
  LoraSerialFlush();
 
}

int moistureSensor() {
  analogReference(EXTERNAL);
  Serial.print("Valor no pino sensor: ");
  Serial.println(analogRead(SENSOR_PIN));
  
  int soilMoisture = map(analogRead(SENSOR_PIN), 0, 1023, 100, 0);
   Serial.println(soilMoisture);
  return (soilMoisture);
}

// Read VCC
int readVcc() {
  long result;
  // Read 1.1V reference against AVcc
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  delay(2); // Wait for Vref to settle
  ADCSRA |= _BV(ADSC); // Convert
  while (bit_is_set(ADCSRA, ADSC));
  result = ADCL;
  result |= ADCH << 8;
  result = 1126400L / result; // Back-calculate AVcc in mV
  //Serial.println(result);
  return result;
}

void powerSaver2() {
  // disable ADC
  old_ADCSRA = ADCSRA;
  ADCSRA = 0;
  set_sleep_mode (SLEEP_MODE_PWR_DOWN);
  power_adc_disable(); // ADC converter
  power_spi_disable(); // SPI
  power_twi_disable(); // TWI (I2C)
  sleep_bod_disable();
  power_timer1_disable();
  power_timer2_disable();
  sleep_enable();
  sleep_cpu ();
  sleep_mode();
  
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
