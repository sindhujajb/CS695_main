#include <stdio.h>
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h> 
#include <unistd.h>
#include "basics.h"
#include "sensors/bme280/bme280.h"

char buff[100];
char* str;

void welcome_msg()
{
    printf("\n					----  BeagleBone Black -- Apache Server  --");
    
    #ifdef HTTP	
    	printf("  HTTP  ----\n\n");	// Printf in shell
    #endif
   
} 

void d_collect_msg(long* m)
{
    printf("---------------------------------------------------------------------------------------------------------------\n");
    printf ("Data collect - %ld\n", *m);
}

void print_sensors_state()
{
	printf ("   Sensors Detection:  ||	");
	print_bme280();
	
}

void print_json(char* jsn)
{
    printf("\nJSON: %s\n", jsn);
    printf("\n	Sending Data to Apache Server...\n");
}

void udelay_basics (long desiredDelay)
{
    usleep(desiredDelay);
}

long take_time_basics()
{
    time_t tim;
    time(&tim);
    return tim;
}
