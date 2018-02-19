//Constants 
const int motorPin = 3;
const int hygrometer = A0;  //Hygrometer sensor analog pin output at pin A0 of Arduino
const int noWaterSpeed = 0;
const int waterSpeed = 10;
const bool debug = true;

void setup() { 
  pinMode(motorPin, OUTPUT);
  Serial.begin(9600);
  while (! Serial);
  Serial.println("Setting up");
} 
 
void loop() { 
  int soilHumidity = readSoilHumidityPercentage();
  bool shouldWaterPlant = soilHumidity <= 50;
  shouldWaterPlant ?  turnPumpOn() : turnPumpOff();
  delay(2000); //Read every 2 sec.
} 

int readSoilHumidityPercentage() {
  int rawValue = analogRead(hygrometer);   //Read analog value 
  Serial.print("raw value: ");
  Serial.print(rawValue);
  Serial.print("\n");
  int constrainedValue = constrain(rawValue,40,1000);  //Keep the ranges!
//    int constrainedValue = constrain(rawValue,400,1023);  //Keep the ranges!
  Serial.print("constrained value: ");
  Serial.print(constrainedValue);
  Serial.print("\n");
  Serial.print("\n");
  int humidityPercent =  map(constrainedValue,40,1000,100,0);  //Map value : 400 will be 100 and 1023 will be 0
// int humidityPercent =  map(constrainedValue,400,1023,100,0);  //Map value : 400 will be 100 and 1023 will be 0
  logSoilHumidity(humidityPercent);
  return humidityPercent;
}

void turnPumpOn() {
  logWatering();
  digitalWrite(motorPin, waterSpeed);
}

void turnPumpOff() {
  digitalWrite(motorPin, noWaterSpeed);
}

void logSoilHumidity(int humidity) {
  Serial.print("Soil humidity: ");
  Serial.print(humidity);
  Serial.print("%\n");
}

void logWatering() {
    Serial.print("Watering plant at speed:  ");
    Serial.print(waterSpeed);
    Serial.print("\n");
    Serial.print("\n");
}

