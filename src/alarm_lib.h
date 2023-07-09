#ifndef ALARM_LIB_H
#define ALARM_LIB_H
#include "Arduino.h"

void Alarm_conditions(float EngineTemp,float OilTemp,float WaterTemp,float InsideTemp,float Voltage,float Power_Amps,float Iginition_Amps);
void Alarm();
void Set_up_Buzzer();
bool Engine_Temp_Alarm();
bool Water_Temp_Alarm();
bool Voltage_Alarm();
bool Oil_Temp_Alarm();
bool Oil_Pressure_Alarm();
bool Iginition_Amps_Alarm();
void Menu_Set_Up();
#endif