#ifndef _CONFIG_H
#define _CONFIG_H

/* ----- CONFIG FILE ----- */
// Devices used
const char* temp = "BeagleBoneB-HTTP";
// Enable Sensors 
bool isEnable_VoltageIntern = true;
// true: Enable  --  false: Disable
bool isEnable_TemperatureExtern = true;	
bool isEnable_Humidity = true;		
bool isEnable_Pressure = true;
//Time in seconds  
long intv = 10;    
#endif
