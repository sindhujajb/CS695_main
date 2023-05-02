#include <stdio.h>
#include <string.h>
#include <stdbool.h>
//includes the function declarations and definitions for configuring the device
#include "config.h" 
#include "core/lib.h"
//defining the struct device data types and its functions
#include "core/struct-device.h"

struct device d;
long number, init_t;
int main ()
{
    config(&d);
    initPeripherals(&number);
    while (1)
    {
	    init_t = take_time();
        //collects data from sensors connected to device
	    pnp_sensors();
        //retrieves data from external source
	    getData(&d, &number);
        //formats the data in JSON format
	    generateJson(&d);
        //compensated delay 
	    t_delay(d.interv, take_time() - init_t);  /* compensated delay */
    }
    return 0;
}