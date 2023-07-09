#ifndef MENU_LOGIC_H
#define MENU_LOGIC_H
#include "Arduino.h"

void Non_blocking_change_of_Menu(float BatteryTemp,float Voltage,float Power_Amps,float Iginition_Amps);
void Button_Logic();
void Set_Up_Button();
bool Button_Logic_Alarm_State();
#endif