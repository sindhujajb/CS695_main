#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "internal.h"

char buff[400];
char *str;
float number;
FILE *fptr; 

void init_internal(bool ft)
{
		// Not necessary in Raspberry Pi
}

char* get_internal() 
{
    str = "";	

    if ((fptr = fopen("/sys/bus/iio/devices/iio:device0/in_voltage1_raw","r")) == NULL)
	return "NULL";
    
    fscanf(fptr,"%f", &number);
    fclose(fptr);
    sprintf(buff, "%.2f", (number / 1000) );	
    str = buff;
    return str;    
}
