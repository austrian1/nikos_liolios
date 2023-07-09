/*
this program contains  3 adrresable temperature sensors 
one humidity sensor and temperature 
one Pressure sensor
one voltage sensor 
one Power_Ampsage hall sensor 
this program is used for a car to monitor some data it can also be used for other purposes such as :
Monitor different machines temperature sensitive
Can switch on air condition or stuff like that 
*/
/*
version 3 
dynamo current 
Battery starter current
buzzer 
buttons
battery temperature
battery voltage 
power generator Power_Am

*/

#include "OneWire.h"                                                                                //  Library for adressable temperature
#include "DallasTemperature.h"                                                                      //  Library for adressable temperature
#include "DHT.h"                                                                                    //  Library for in car temperature and humudity
#include "menu_logic.h"                                                                      
#include "ACS712.h"                                                                                 //  Library for Power_Ampsage sensor
#include "show_screen.h"
#include "alarm_lib.h"
#define DHTPIN 6                                                                                    //  Define pin for dht sensor humudity and temperature
#define ONE_WIRE_BUS 4                                                                              //  Define pin for adressable temperature sensor
#define DHTTYPE DHT11                                                                               //  Define which dht sensor i have 

DHT dht(DHTPIN, DHTTYPE);                                                                           //  Define library name used pin and type
OneWire oneWire(ONE_WIRE_BUS);                                                                      //  Define for onewire library which pin it will use
DallasTemperature sensors(&oneWire);                                                                //  Define what will library use
//ACS712 sensor(ACS712_30A, A2);                                                                      //  Define libary which sensor i have and which pin Power_Ampsage
int numberOfDevices;  // Number of temperature devices found                                        //  Decleration of variable for number of sensors

//DeviceAddress Battery , Oil , Water;                                                               //  It can find adresses for temperature sensor automaticaly i use manual

DeviceAddress Battery = { 0x28, 0xAC, 0xDA, 0x81, 0xE3, 0xED, 0x3C, 0x48 };                          //  Three decleration of adresses for temperature sensor
//DeviceAddress Oil = { 0x28, 0x91, 0x33, 0x81, 0xE3, 0x50, 0x3C, 0x4D };
//DeviceAddress Water = { 0x28, 0xFF, 0x64, 0x1F, 0x45, 0xD9, 0x2B, 0x09 };

//parameters


//  various parameteres for program



const int Voltage_Sensor = A0;                                                                      //  The pin for voltage sensor                            INPUT
const int Power_Generator_Sensor =A2;                                                               //  The pin for  amps power genarator sensor              INPUT
const int Ignition_Sensor =A4;                                                                      //  The pin for  amps ignition sensor                     INPUT
float R1 = 30000.0;                                                                                 //  Resistor 1 for voltage divider
float R2 = 7500.0;                                                                                  //  Resistor 2 for voltage divider 


//Variables used in program for calculations
float Voltage = 0.0;
float BatteryTemp = 0;
float Power_Amps=0;
float Iginition_Amps=0;



void setup() {
  Serial.begin(115200);                                                                                   //  Serial baud Rate for debugging
  Begin_Lcd();
  dht.begin();                                                                                            //  Dht sensor start
  sensors.begin();                                                                                        //  Adressable temperature sensor start
  //int zero = sensor.calibrate();                                                                          //  Zeroing Power_Ampsage sensor
  delay(500);                                                                                             //  Delay some time for setting up
  Set_Up_Button();
  Set_up_Buzzer();                                                                               //  Buzer Output
 // pinMode(A2,INPUT_PULLUP);
  Data_Acquisition();                                                                                     //  Gives first Data
  Show_Data_Menu();                                                                                //  Show menu and data
  Menu_Set_Up();
}

void loop() {
  Non_blocking_change_of_Menu(BatteryTemp,Voltage,Power_Amps,Iginition_Amps);                                                                          //  Show menu without blocking code. So data is always calculated
  Data_Acquisition();                                                                                     //  Data acquisition on loop. Keeps bringing new data
  Alarm_conditions(BatteryTemp,Voltage,Power_Amps,Iginition_Amps);                                                                                     //  Checking data for alarm coditions so buzzer is on
  Alarm();                                                                                                //  If alarm condition fullfilled sets the Alarm on
  
}




//  Function for Data . 
void Data_Acquisition() {

  sensors.requestTemperatures();
  BatteryTemp          =   sensors.getTempC(Battery);
  Voltage             =   Voltage_Sensor_Logic();
  Power_Amps          =   Power_generator_Amps();
  Iginition_Amps      =   Ignition_Amps();
}



float Voltage_Sensor_Logic()                                                                              //Voltage calculation
{

  uint16_t  value           =   analogRead(Voltage_Sensor);                                               //Raw data 0-1023
  float     vOUT            =   (value * 5.0) / 1024.0;
  float     Voltage         =   vOUT / (R2/(R1+R2));                                                      //Voltage divider calculation
  
  return Voltage;

}





float Power_generator_Amps()
{

  uint16_t  amps_raw_values   =   analogRead(Power_Generator_Sensor); //reads value from input pin and assigns to variable
  float     ampsValue         =   ((amps_raw_values*5)); //conversion equation to convert analog reading to psi
  
  
  return ampsValue;

}

float Ignition_Amps()
{

  uint16_t  amps_raw_values   =   analogRead(Ignition_Sensor); //reads value from input pin and assigns to variable
  float     ampsValue         =   ((amps_raw_values*5)); //conversion equation to convert analog reading to psi
  
  
  return ampsValue;

}



