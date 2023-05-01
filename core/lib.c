#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "struct-device.h"
#include "config.h"
#include "devices.h"


void config(struct device *alpha)
{   
    /* User assignments */
    alpha->id = temp;
        
   

  

    #ifdef MICROCONTROLLER
        alpha->ssid_wifi = ssid_WiFi;
        alpha->pass_wifi = pass_WiFi;
    #endif

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

void initPeripherals(long* counter) 
{
    *counter = 0;		// Init counter
    
    #ifdef SHELLPRINT
    	welcome_msg();	// Printf in shell
    #endif
	
    init_LEDs();
    // init_i2c(); // Not necesary in BBB
	
	init_internal(true);
    init_bme280(true);
}


void led_blinks(int pin, int iterate, int unit_sec)	// LED Blink function-> led: 0 Green LED, 1 Red LED - iter: iterations quantity - usec: delay time in usec
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

void connectNetwork(struct device *alpha, bool first_t)
{	
	#ifdef MICROCONTROLLER			
	if (first_t)
	{				
		while ( !connectAttempt(alpha->ssid_wifi, alpha->pass_wifi) )    /* Attempt to connect to the network via WiFi, in RaspberryPi only check connection to the network. */
		{
			 led_blinks(0, 1, 600000);	// Blink in green GREEN - ERROR 0 (No WiFi connection);
			 led_blinks(1, 1, 600000);	// Blink in green RED - ERROR 0 (No WiFi connection);
		}
	}
	#endif
	if ( !init_socket(alpha->address, alpha->address_port,first_t) )     /* Check Endpoint */
	{	
		udelay_basics ( 100000 );
		led_blinks(1, 3, 70000);	// Blink in green RED - ERROR 1 (Bad connection with the endpoint);
		#ifdef MICROCONTROLLER
			restart_basic();
		#endif
	}
}

void pnp_sensors()
{
    init_bme280(false);
    
}


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
		 
	strcat(alpha->json, "],\"device\": \"");
	strcat(alpha->json, alpha->id);
	strcat(alpha->json, "\",\"timestamp\": \"0\"}");
	
    #ifdef SHELLPRINT	
    	print_json(alpha->json);	// Printf in shell
    #endif
}


void t_delay(long desiredDelay, long actualDelay) 
{  
	if (actualDelay >= desiredDelay)		/* To prevent crashes */
		actualDelay = desiredDelay;
    udelay_basics ( (desiredDelay - actualDelay) * 1000000 );	/* Time set by user  minus  loss time by operation */ 
}

long take_time() 
{  
    return take_time_basics();
}


