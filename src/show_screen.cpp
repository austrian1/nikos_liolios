#include "Arduino.h"
#include "show_screen.h"
#include "LiquidCrystal.h" 
#include "alarm_lib.h"

const int rs = 12, en = 11, d4 = 10, d5 = 9, d6 = 8, d7 = 7;                                        //  Decleration of pins for lcd screen
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); 
uint32_t initial_time2=0;
uint32_t elapsed_time=0;

//variables
bool shown_voltage=false;
bool start_time=true;
//paremeter
uint32_t threshold_time=1000;
// Create degree symbol for lcd screen
byte degreeSymbol[8] = {
  0b00111,
  0b00101,
  0b00111,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
};



void Begin_Lcd(){

lcd.begin(20, 4);  //20 columns 4 rows                                                                  //  Lcd screen start
lcd.createChar(7, degreeSymbol);                                                                        //  Lcd creat degree symbol at number 7 

}
//  Set up the Menu and what the screen will show for primary data such as temperatures of engine , oil, water, inside temperature
void Show_Data_Menu() {
  lcd.setCursor(0, 0);                                                                                    //  Setting where the cursor will be. Positios 0-19
  lcd.print("Bat  Temp:");                                                                               //  Printing the String at the desired position from above

  lcd.setCursor(17, 0);                                                                                   //  Setting the Cursor to 17 position
  lcd.print(" ");                                                                                         //  Printing "  " at a position. if 3 digits numbers occur 
                                                                                                          //  3 digits shown. If then 2 digits occur the thirds is cleared by " "
  lcd.setCursor(18, 0);                                                                                   //  Setting the Cursor to 18 position
  lcd.write(7);                                                                                           //  Printing the Deggre symbol
  
  lcd.setCursor(19, 0);                                                                                   //  The same logic
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("Voltage");

  lcd.setCursor(17, 1);
  lcd.print(" ");

  lcd.setCursor(19, 1);
  lcd.print("V");

  lcd.setCursor(0, 2);
  lcd.print("Amp Dyn:");

  lcd.setCursor(17, 2);
  lcd.print(" ");

 
  lcd.setCursor(19, 2);
  lcd.print("A");

  lcd.setCursor(0, 3);
  lcd.print("Amp Ign:");
  
  lcd.setCursor(17, 3);
  lcd.print(" ");

  lcd.setCursor(19, 3);
  lcd.print("A");

}





void Show_Data(float BatteryTemp,float Voltage,float Power_Amps,float Iginition_Amps) {                   //  Shows the data with one floating digit
  lcd.setCursor(12, 0);
  lcd.print(BatteryTemp,1);

  lcd.setCursor(12, 1);
  lcd.print( Voltage,1);

  lcd.setCursor(12, 2);
  lcd.print(Power_Amps,1);

  lcd.setCursor(12, 3);
  lcd.print(Iginition_Amps,1);
}




void Show_Data_Menu_Faults(){

  Show_Data_Menu();

}


void Show_Menu_Faults(float BatteryTemp,float Voltage,float Power_Amps,float Iginition_Amps){

  Show_Data( BatteryTemp, Voltage, Power_Amps,Iginition_Amps);

}





void Clear_Screen(){
  lcd.clear();
}

void Show_Set_Up_Menu(int show_screen,int index,float Battery_Temp_Limit,float Voltage_Bottom_Limit, float Voltage_Upper_Limit,float Power_Amps_Limit,float Iginition_Amps_Limit){
  lcd.setCursor(index,19);
  lcd.print("<");
  if(show_screen==0){
    
    lcd.setCursor(0,0);
    lcd.print("Bat Temp Lim :");
    lcd.setCursor(0,14);
    lcd.print(Battery_Temp_Limit);
    
    lcd.setCursor(1,0);
    lcd.print("Volt Bot Lim :");
    lcd.setCursor(0,15);
    lcd.print(Voltage_Bottom_Limit);

    lcd.setCursor(2,0);
    lcd.print("Volt Up Lim :");
    lcd.setCursor(0,14);
    lcd.print(Voltage_Upper_Limit);

    lcd.setCursor(3,0);
    lcd.print("Pow Amp Lim :");
    lcd.setCursor(0,13);
    lcd.print(Power_Amps_Limit);

  }
  
  if(show_screen==1){
    lcd.setCursor(0,0);
    lcd.print("Ign Amp Lim :");
    lcd.setCursor(0,13);
    lcd.print(Iginition_Amps_Limit);


    lcd.setCursor(1,0);
    lcd.print("");

    lcd.setCursor(2,0);
    lcd.print("");

    lcd.setCursor(3,0);
    lcd.print("");
  }

}



