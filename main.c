#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "config.h"
#include "core/lib.h"
#include "core/struct-device.h"


struct device d;

long number, init_t;

int main ()
{	
    config(&d);			
    initPeripherals(&number);	
    connectNetwork(&d, true);	

    while (1)
    {	
	    init_t = take_time();

	    pnp_sensors();		

	    getData(&d, &number);

	    generateJson(&d);


	    t_delay(dev.interv, take_time() - init_t);  /* compensated delay */
    }    
    return 0;
}
