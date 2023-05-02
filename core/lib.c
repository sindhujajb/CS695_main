#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "struct-device.h"
#include "config.h"
#include "devices.h"

void init_LEDs();
void led_GPIO(int, int);
bool read_GPIO(int);
//this functions sets the device ID, sensor names,measurement interval fields, wifi credentials and sensor enable flags based on type of device used 
void config(struct device *alpha)
{
    /* User assignments */
    alpha->id = temp;
    alpha->isEnable[0] = isEnable_VoltageIntern;
    alpha->isEnable[1] = isEnable_TemperatureExtern;
    alpha->isEnable[2] = isEnable_Humidity;
    alpha->isEnable[3] = isEnable_Pressure;

    alpha->s_name[0] = "InternalVoltage";
    alpha->s_name[1] = "Temperature";
    alpha->s_name[2] = "Humidity";
    alpha->s_name[3] = "Pressure";
    alpha->interv = intv;
}

//initializes LED lights, system's internal temperature sensor and BME280 sensor
void initPeripherals(long* counter)
{
    // Initialize counter
    *counter = 0;	
    #ifdef SHELLPRINT
    // Printf in shell
    	welcome_msg();	
    #endif
    init_LEDs();
    // init_i2c(); // Not necesary in BBB
    init_bme280(true);
}

//LED Blink function-> led: 0 Green LED, 1 Red LED - iter: iterations quantity - usec: delay time in usec
void led_blinks(int pin, int iterate, int unit_sec)	
{
     int i;
     for (i=0;i<iterate;i++)
     {
		 led_GPIO(pin, 1);
		 udelay_basics (unit_sec);
		 led_GPIO(pin, 0);
		 udelay_basics (unit_sec);
     }
}

//initializes BME280 sensor
void pnp_sensors()
{
    init_bme280(false);

}

//reads data from system's internal temperature sensor and BME280 sensor and stores it
void getData(struct device *alpha, long *count)
{
    int i;
    ++(*count);
    #ifdef SHELLPRINT	// Printf in shell
	d_collect_msg( count );
	print_sensors_state();
    #endif
    /* GET DATA INTERNAL TEMPERATURE */
    strcpy(alpha->d[0], get_internal());
    /* GET DATA BME280 */
    if (check_bme280())
    {
		for (i=0; i<3; i++)
	   	    strcpy(alpha->d[i+1], get_bme280(i));
    }
    else
    {
		for (i=0; i<3; i++)
			strcpy(alpha->d[i+1], "0");
    }
}

//creates json object containing data read by system and device id stored
void generateJson(struct device *alpha)
{
    int i, beta;
    strcpy(alpha->json, "{\"Apache server\":[");
    beta = 0;
    strcat(alpha->json, "{\"sensor\":\"Internal\",\"data\":[");
    for (i=0;i<1;i++)
    {
		if (alpha->isEnable[i+0])
		{
			if (beta != i) strcat(alpha->json, ",");
			strcat(alpha->json, "{\"");
			strcat(alpha->json, alpha->s_name[i+0]);
			strcat(alpha->json, "\":\"");
			strcat(alpha->json, alpha->d[i+0]);
			strcat(alpha->json, "\"}");
		}
	else
	    beta++;
    }
    strcat(alpha->json, "]}");
    //enabled - adds new json object to json string  not enabled - beta variable is incremented
    if (check_bme280())
    {
		beta = 0;
		strcat(alpha->json, ",{\"sensor\":\"Environmental\",\"data\":[");
		for (i=0;i<3;i++)
		{
			if (alpha->isEnable[i+1])
			{
				if (beta != i) strcat(alpha->json, ",");
				strcat(alpha->json, "{\"");
				strcat(alpha->json, alpha->s_name[i+1]);
				strcat(alpha->json, "\":\"");
				strcat(alpha->json, alpha->d[i+1]);
				strcat(alpha->json, "\"}");
			}
			else
			beta++;
		}
		strcat(alpha->json, "]}");
    }
    #ifdef SHELLPRINT
    //Printf in shell
    	print_json(alpha->json);
    #endif
}

void t_delay(long desiredDelay, long actualDelay)
{
	if (actualDelay >= desiredDelay)
    // To prevent crashes		
		actualDelay = desiredDelay;
    // Time set by user  minus  loss time by operation 
    udelay_basics ( (desiredDelay - actualDelay) * 1000000 );	
}

long take_time()
{
    return take_time_basics();
}
