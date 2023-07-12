#ifndef SHOW_SCREEN_H
#define SHOW_SCREEN_H
#include "Arduino.h"

void Begin_Lcd();
void Show_Data_Menu();
void Show_Data(float BatteryTemp,float Voltage,float Power_Amps,float Iginition_Amps);
void Clear_ScrData_Show_Temperature_Menu_Faults();
void Show_Menu_Faults(float BatteryTemp,float Voltage,float Power_Amps,float Iginition_Amps);
void Show_Set_Up_Menu(int show_screen,int index,float BatteryTemp,float Voltage_Bottom_Limit, float Voltage_Upper_Limit,float Power_Amps_Limit,float Iginition_Amps_Limit);

#endif