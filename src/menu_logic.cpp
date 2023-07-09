#include "Arduino.h"
#include "show_screen.h"
#include "alarm_lib.h"

const int Button = 5;                                                                               //  The pin for button for changing the screen in demand  INPUT


const int Refresh_Rate = 5000;                                                                      //  Refresh rate : the time amount that the screen is changing the data

bool Alarm_array[6];
uint32_t initial_time = 0;
uint32_t final_time = 0;
uint8_t number_of_faults=0;
uint8_t previous_number_of_faults=0;
bool time = true;
bool show_temp = false;
bool show_rest_data = true;
bool cycle_done = false;
bool play_temp=true;
bool play_rest_data=false;
bool first_run=true;
bool data_alarm_read=false;


bool general_alarm_condition();
bool  temp_alarm_condition();
bool rest_data_alarm_condition();


bool general_alarm_condition(){

  if(Battery_Temp_Alarm()==false && Voltage_Alarm()==false  && Power_Amps_Alarm()==false && Iginition_Amps_Alarm()==false)
  {
    for(int i=0; i<4; i++){
      Alarm_array[i]=false;
      number_of_faults=0;
      previous_number_of_faults=0;
    }
    return false;

  }else{
    
    if(Engine_Temp_Alarm()==true){
      Alarm_array[0]=true;
    }else Alarm_array[0]=false;

    if(Water_Temp_Alarm()==true){
      Alarm_array[1]=true;
    }else Alarm_array[1]=false;

    if(Voltage_Alarm()==true){
      Alarm_array[2]=true;
    }else Alarm_array[2]=false;

    if(Oil_Temp_Alarm()==true){
      Alarm_array[3]=true;
    }else Alarm_array[3]=false;
    
    for(int i=0; i<4; i++){
      if(Alarm_array[i]==true){
        number_of_faults++;
        if(number_of_faults>3){
          number_of_faults=4;
        }
      }
    }
    return true;
  } 
  if(number_of_faults > previous_number_of_faults){
    data_alarm_read = false;
    previous_number_of_faults=number_of_faults;
  }

}

bool  temp_alarm_condition(){

  if(Engine_Temp_Alarm()==true || Water_Temp_Alarm()==true || Oil_Temp_Alarm()==true){

    return true;

  }

}
bool rest_data_alarm_condition(){

if(Amper_Alarm()==true || Oil_Pressure_Alarm()==true || Voltage_Alarm()==true){

    return true;

  }

}



void Set_Up_Button(){
  pinMode(Button, INPUT_PULLUP);                                                                          //  Input pullup the button. No floating
}

void Button_Logic()                                                                                       //Button logic. If pressed changes the time have passed above the limit
{
  if(general_alarm_condition()==false){
    if (digitalRead(Button) == LOW) {
    
      final_time = Refresh_Rate + 1;
      delay(100);

    }
  }

}
bool Button_Logic_Alarm_State()
{
  if(general_alarm_condition()==true){
    
    if (digitalRead(Button) == LOW) {
    
      delay(100);
      return true;
    }else return false;
  
  }
}
// Function for non blocking changing the shown data 
void Non_blocking_change_of_Menu(float BatteryTemp,float Voltage,float Power_Amps,float Iginition_Amps) {
                                                                                                    
    Show_Data_Menu();
    Show_Data( BatteryTemp,  Voltage, Power_Amps, Iginition_Amps);
  
  if( data_alarm_read==false){
    if(general_alarm_condition()==true ){ 
      Clear_Screen();
      while(temp_alarm_condition()==true && data_alarm_read==false){
        while(temp_alarm_condition()==true && Button_Logic_Alarm_State()==false){
          Show_Data_Menu_Faults();
          Show_Menu_Faults(BatteryTemp, Voltage, Power_Amps, Iginition_Amps);       
        }
        data_alarm_read=true;
      } 
    }
  }
}






