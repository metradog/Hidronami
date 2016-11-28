#include <OneWire.h>
#include <DallasTemperature.h>

volatile int NbTopsFan;
int Calc;
int hallsensor = 2;
void rpm ()
{
NbTopsFan++;
}







// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 4 // sensor Temperatura

#define hallsensor 2 // Sensor caudalimetro

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

// arrays to hold device address
DeviceAddress insideThermometer;

void setup(void)
{
  Serial.begin(9600);
  sensors.begin();
   pinMode(hallsensor, INPUT);
  attachInterrupt(0, rpm, RISING);
  
  if (!sensors.getAddress(insideThermometer, 0)) 
    Serial.println("Unable to find address for Device 0"); 
  sensors.setResolution(insideThermometer, 12);
 
}


void printTemperature(DeviceAddress deviceAddress) // Función que imprime una temperatura en el sensor
{
  float tempAsString = sensors.getTempC(deviceAddress);
//  String a; 
//  char temp[10];
//  dtostrf(tempC, 2, 1, temp);
//  String tempAsString = String(temp);
  //Serial.println("insideThermometer " + tempAsString);
  Serial.println(tempAsString);
  delay(1000);
}

void loop(void)
{ 
  
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~ Modo Temperatura  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 // Serial.print ("Temperatura\r\n"); 
  sensors.requestTemperatures(); // Envía La Señal Hidrica
  printTemperature(insideThermometer); // Print Temperatura
  //Serial.print ("\r\n");



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~ Modo Caudalimetro ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  NbTopsFan = 0;
sei();
delay (1000);
cli();
Calc = (NbTopsFan * 60 / 5.5); // Mide por minutos
//Calc = (NbTopsFan  / 5.5); // Mide por segundo

//Serial.print ("Caudalimetro\r\n"); 
Serial.print (Calc, DEC);
//Serial.print ("Litros/min\r\n"); // Mide por minutos
Serial.print ("\r\n");

//Serial.print (" Litros/Seg\r\n"); // Mide por segundo
;
}
