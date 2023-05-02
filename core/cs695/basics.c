#include <stdio.h>
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h> 
#include <unistd.h>
#include "basics.h"
#include "data/bme280/bme280.h"

char buff[100];
char* str;
void welcome_msg()
{
    printf("\n					----  BeagleBone Black -- Apache Server  --");
    #ifdef HTTP	
    // Printf in shell
    	printf("  HTTP  ----\n\n");	
    #endif
} 

void d_collect_msg(long* m)
{
    printf("---------------------------------------------------------------------------------------------------------------\n");
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

//waits for a specified amount of time in microseconds
void udelay_basics (long desiredDelay)
{
    usleep(desiredDelay);
}

//returns current time in seconds
long take_time_basics()
{
    time_t tim;
    time(&tim);
    return tim;
}
