//Constants 
const int motorPin = 3;
const int hygrometer = A0;  //Hygrometer sensor analog pin output at pin A0 of Arduino
const int noWaterSpeed = 0;
const int waterSpeed = 10;
const bool debug = true;
const unsigned long default_delay = 1200000; //60000 * 20; //20 minutes
const int wet = 40;
const int dry = 1000;
const int hundred_percent = 100;
const int zero_percent = 0;
const unsigned long watering_period = 2000; //2 seconds

void setup() { 
  pinMode(motorPin, OUTPUT);
  Serial.begin(9600);
  while (! Serial);
  Serial.println("Setting up");
} 
 
void loop() { 
  int soilHumidity = readSoilHumidityPercentage();
  bool shouldWaterPlant = soilHumidity <= 50;
  shouldWaterPlant ?  waterPlant() : turnPumpOff();
  Serial.print(default_delay);
  delay(default_delay); //Read every 20 mins ater watering or turning off pump
} 

int readSoilHumidityPercentage() {
  int rawValue = analogRead(hygrometer);   //Read analog value 
  int constrainedValue = constrain(rawValue,wet,dry); //constrain values to within the wettest value and driest value
  int humidityPercent =  map(constrainedValue, wet, dry, hundred_percent, zero_percent);  //Map value : wet will be 100 and dry will be 0
  logSoilHumidity(rawValue, constrainedValue, humidityPercent);
  return humidityPercent;
}

void waterPlant() {
  logWatering();
  turnPumpOn();
  delay(watering_period); //0nly water for set period of time
  turnPumpOff(); // then turn off pump
}

void turnPumpOn() {
  digitalWrite(motorPin, waterSpeed);
}

void turnPumpOff() {
  digitalWrite(motorPin, noWaterSpeed);
}

void logSoilHumidity(int rawValue, int constrainedValue,int humidity) {
  Serial.print("raw value: ");
  Serial.print(rawValue);
  Serial.print("\n");
  Serial.print("constrained value: ");
  Serial.print(constrainedValue);
  Serial.print("\n");
  Serial.print("Soil humidity: ");
  Serial.print(humidity);
  Serial.print("%\n");
}

void logWatering() {
    Serial.print("Watering plant at speed:  ");
    Serial.print(waterSpeed);
    Serial.print("\n");
}

