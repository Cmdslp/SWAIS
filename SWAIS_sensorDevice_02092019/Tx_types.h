#define SENSOR_PIN A5 // Pin of the conected sensor
#define SEND_LED 13 // Info LED

//#define F_CPU 8000000UL
byte old_ADCSRA;
const int RX = 3;
const int TX = 4;
volatile int f_wdt=1;
