#define RCV_LED_PIN 13      //Green LED
#define SIZE_ERR_PIN 7      // Red LED
#define SEND_LED_PIN 9      // Blue LED 
#define VALVE_PIN 10        // Solenoid valve    
#define MAX_NUM_SENSORS 5   // Number max of sensor that can be saved
#define RESET_COUNT 10      // Number max of iterations before reset
SoftwareSerial LoraSerial(2, 3); //RX TX

// STRUCT OF A SENSOR
struct Sensor {
  int s_address;
  String  s_type;
  float  s_value;
  int s_rssi;
};

// SENSORS ARRAY
Sensor collection[MAX_NUM_SENSORS];

//GLOBAL VARIABLES
String incomingString = "";
String incomingStringSize = "";
const int interval = 5000;
const char* sensorType = "";
int sensorCount = 0;
int resetCount = 0;
int betterRSSignalId = 0;
int betterRSSignalStregth = -100;
int betterSHSignalId = 0;
int betterSHSignalStregth = -100;
int betterATSignalId = 0;
int betterATSignalStregth = -100;

// UNIQUE ADDRESS OF BEST SENSORS
int bestRSsensorAddress;
int bestATsensorAddress;
int bestSHsensorAddress;

// NEEDED INPUT VARIABLES FOR IOPT TOOLS
int inputIOPTrainSensorValue = 0;
char* inputIOPTrainSensorType = "";

char* inputIOPTSoilHumiditySensorType = "";
float inputIOPTSoilHumiditySensorValue = 0;

float inputIOPTambientTemperatureSensorValue = 0;
char* inputIOPTambientTemperatureSensorType = "";
