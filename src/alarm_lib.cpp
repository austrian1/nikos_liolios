#include "Arduino.h"
#include "alarm_lib.h"
#include "show_screen.h"
cont int Button_Plus =3;
const int Button_Minus =2;
const int Button_Enter =1;
const int Buzzer = 3;                                                                               //  The pin for alarm buzzer  OUTPUT
//Alarm limits. I can change them accordingly to my needs. Low limits for testing my system                                                                                   
float Voltage_Bottom_Limit= 3;                                                                      //  Voltage low limit alarm
float Voltage_Upper_Limit= 14;                                                                      //  Voltage maximum limit alarm
float Water_Temp_Limit=30;    //105                                                                 //  Water low limit alarm
float Oil_Temp_Limit=30;      //100                                                                 //  Water high limit alarm
float Battery_Temp_Limit=30; //100                                                                   //  Engine high limit alarm. We could use a low Limit but there is no need
float Power_Amps_Limit=5;                                                                         // limit of oil pressure Power_Amps
float Iginition_Amps_Limit =50;                                                                              //  Iginition_Ampsage draw

bool alarm=false;
bool voltage_alarm=false;
bool water_alarm=false;
bool oil_alarm=false;
bool battery_temp_alarm=false;
bool power_amps_alert=false;
bool Iginition_Amps_alarm=false;
bool start=false;
bool leave_button=false;
uint start_time=0;
uint elapsed_time=0;
uint8_t index=0;

int show_screen=0;
//parameters
const int menu_set_up_time =3000;
const uint16_t pressed_button =100;
const int screen_limit=3;
const int Max_Battery_Temp_Limit=120;
const int LOW_Battery_Temp_Limit=80;
void Set_up_Buzzer(){
  pinMode(Buzzer ,OUTPUT); 
  digitalWrite(Buzzer,HIGH);                                                                              //  Buzer High --> off. Gets activate with low
}


void Alarm_conditions(float BatteryTemp,float Voltage,float Power_Amps,float Iginition_Amps)                                                                 //  Alarm conditions
{
  
  if(BatteryTemp>Battery_Temp_Limit ){                                                    //  If limit is overcomed set the logic alarm true and engine alarm true
    alarm=true;
    battery_temp_alarm=true;
  }else{
    battery_temp_alarm=false;
  }

  if(Voltage>Voltage_Upper_Limit || Voltage<Voltage_Bottom_Limit ){                    // The same here || --> or symbol one of two 
    alarm=true;
    voltage_alarm=true;
  }
  else{
   voltage_alarm=false;
  }

  if(Power_Amps>Power_Amps_Limit){                                                       //  The same here
    alarm=true;
    power_amps_alert=true;
  }
  else{
    power_amps_alert=false;
  }

  if(Iginition_Amps>Iginition_Amps_Limit){                                                       //  The same here
    alarm=true;
    Iginition_Amps_alarm=true;
  }
  else{
    Iginition_Amps_alarm=false;
  }

}

void Alarm()                                                                                              //Set the Alarm on 
{

  if (alarm==true){                                                                                       //Set the alarm is true 
    digitalWrite(Buzzer,LOW);
  }

  if(battery_temp_alarm==false  && voltage_alarm==false &&  Iginition_Amps_alarm==false && power_amps_alert==false ){              //Set the alarm of is everything is ok
    digitalWrite(Buzzer,HIGH);
  }
  
}

//Returning booleans values for showing the value at the screen

bool Battery_Temp_Alarm(){
  if(battery_temp_alarm==true){
    return true;
  }else return false;
}


bool Voltage_Alarm(){
  if(voltage_alarm==true){
    return true;
  }else return false;
}

bool Power_Amps_Alarm(){
  if(power_amps_alert==true){
    return true;
  }else return false;
}

bool Iginition_Amps_Alarm(){
  if(Iginition_Amps_alarm==true){
    return true;
  }else return false;
}


void Menu_Set_Up(){
  if(digitalRead(Button_Enter)==LOW && leave_button=false ){
    if(start==false){
      start_time=millis();
      start=true;
      leave_button=true;
    }
    elapsed_time=millis()-start_time;
    if(elapsed_time>menu_set_up_time){
      while(digitalRead(Button_Enter)==LOW && leave_button==true){
        Show_Set_Up_Menu(show_screen);
      }
      while(digitalRead(Button_Enter)==HIGH){
        Choose_Menu();
        changing_price();
        Show_Set_Up_Menu(show_screen);
        Show_Settings(show_screen, index, Battery_Temp_Limit, Water_Temp_Limit, Power_Amps_Limit, Iginition_Amps_Limit, Voltage_Bottom_Limit, Voltage_Upper_Limit, Inside_Temp_Upper_Limit, Inside_Temp_Bottom_Limit);
        Show_variables();
        start_time=millis();
        elapsed_time=millis();
        leave_button=false;
      }
    }
  }
}

void changing_price(){

  if(Plus==true){

    if(index==0){
      Battery_Temp_Limit++;
      if(Battery_Temp_Limit>Max_Battery_Temp_Limit){
          Battery_Temp_Limit=LOW_Battery_Temp_Limit;
      }
    }

    if(index==1){
      Water_Temp_Limit++;
      if(Water_Temp_Limit>Max_Water_Temp_Limit){
          Water_Temp_Limit=LOW_Water_Temp_Limit;
      }
    }

    if(index==2){
      Power_Amps_Limit++;
      if(Power_Amps_Limit>Max_Power_Amps_Limit){
          Power_Amps_Limit=LOW_Power_Amps_Limit;
      }
    }

    if(index==3){
      Iginition_Amps_Limit++;
      if(Iginition_Amps_Limit>Max_Iginition_Amps_Limit){
          Iginition_Amps_Limit=LOW_Iginition_Amps_Limit;
      }
    }

    if(index==4){
      Voltage_Bottom_Limit++;
      if(Voltage_Bottom_Limit>Max_Voltage_Bottom_Limit){
          Voltage_Bottom_Limit=LOW_Voltage_Bottom_Limit;
      }
    }

    if(index==5){
      Voltage_Upper_Limit++;
      if(Voltage_Upper_Limit>Max_Voltage_Upper_Limit){
          Voltage_Upper_Limit=LOW_Voltage_Upper_Limit;
      }
    }

    if(index==6){
      Inside_Temp_Upper_Limit++;
      if(Inside_Temp_Upper_Limit>Max_Inside_Temp_Limit){
          Inside_Temp_Upper_Limit=LOW_Inside_Temp_Limit;
      }
    }

    if(index==7){
      Inside_Temp_Bottom_Limit++;
      if(Inside_Temp_Bottom_Limit>Max_Inside_Temp_Limit){
          Inside_Temp_Bottom_Limit=LOW_Inside_Temp_Limit;
      }
    }

  }


  if(Minus==true){
    
    if(index==0){
      Battery_Temp_Limit--;
      if(Battery_Temp_Limit<LOW_Battery_Temp_Limit){
          Battery_Temp_Limit=MAX_Battery_Temp_Limit;
      }
    }

    if(index==1){
      Water_Temp_Limit--;
      if(Water_Temp_Limit<LOW_Water_Temp_Limit){
          Water_Temp_Limit=MAX_Water_Temp_Limit;
      }
    }

    if(index==2){
      Power_Amps_Limit--;
      if(Power_Amps_Limit<LOW_Power_Amps_Limit){
          Power_Amps_Limit=MAX_Power_Amps_Limit;
      }
    }

    if(index==3){
      Iginition_Amps_Limit--;
      if(Iginition_Amps_Limit<LOW_Iginition_Amps_Limit){
          Iginition_Amps_Limit=MAX_Iginition_Amps_Limit;
      }
    }

    if(index==4){
      Voltage_Bottom_Limit--;
      if(Voltage_Bottom_Limit<LOW_Voltage_Bottom_Limit){
          Voltage_Bottom_Limit=MAX_Voltage_Bottom_Limit;
      }
    }

    if(index==5){
      Voltage_Upper_Limit--;
      if(Voltage_Upper_Limit<LOW_Voltage_Upper_Limit){
          Voltage_Upper_Limit=MAX_Voltage_Upper_Limit;
      }
    }

    if(index==6){
      Inside_Temp_Upper_Limit--;
      if(Inside_Temp_Upper_Limit<LOW_Inside_Temp_Limit){
          Inside_Temp_Upper_Limit=MAX_Inside_Temp_Limit;
      }
    }

    if(index==7){
      Inside_Temp_Bottom_Limit--;
      if(Inside_Temp_Bottom_Limit<LOW_Inside_Temp_Limit){
          Inside_Temp_Bottom_Limit=MAX_Inside_Temp_Limit;
      }
    }


  }
}


bool Plus(){

  if(digitalRead(Button_Plus)==LOW && digitalRead(Button_Minus)==HIGH){ 
    delay(pressed_button);
    return true;
  }else{
    return false;

  }

}

bool Minus(){
  if(digitalRead(Button_Minus)==LOW && digitalRead(Button_Plus)==LOW){
   
    delay(pressed_button);
    return true;
  }else{
    return false;
  }
}

void Choose_Menu(){
  if(digitalRead(Button_Minus)==LOW && digitalRead(Button_Plus)==LOW){
    delay(pressed_button);
    index++;
    if(show_screen==0){
      if(index>3){
      
      index=0;
      show_screen=1;
      }
    }
    if(show_screen==1){
      if(index>3){
      
      index=0;
      show_screen=0;
      }
    }
  } 
}
//6 alarms
