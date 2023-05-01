#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include "gpio.h"

char buff[64];
char aux[8];
char* str;
int f_val;
char val;

char* path(int gpio, char* file)
{
  sprintf(aux, "%d", gpio); // Convert int to string

  strcpy(buff, "/sys/class/gpio/gpio");	// Init the buff path
  strcat(buff, aux);
  strcat(buff, "/");
  strcat(buff, file);

  str = " ";
  str=buff;
  return str;	// Return the path
}

void simpleBBB_GPIOset(int gpio, int d_val) //  	Set Direction     0 - OUTPUT      ----      1 - INPUT
{
	f_val = open(path(gpio, "direction"), O_RDWR);
	switch (d_val)
	{
		case 0:
    		write(f_val, "out", 3);
			break;
		case 1:
    		write(f_val, "in", 2);
			break;
		default:
			printf("Not a valid GPIO direction\n");
	}
    close(f_val);
}

void simpleBBB_GPIOwrite(int gpio, bool l_val) //   Write Digital Logic    false - Low      ----      true - High
{
	f_val = open(path(gpio, "val"), O_RDWR);

	if (l_val)
    	write(f_val, "1", 1);
	else
    	write(f_val, "0", 1);

    close(f_val);
}

int simpleBBB_GPIOread(int gpio) //     Read GPIO val      0 (Low)    ----     1 (High)
{
	f_val = open(path(gpio, "val"), O_RDONLY, 0);
    read(f_val, &val, 1);
    close(f_val);

	return (val - '0');
}
