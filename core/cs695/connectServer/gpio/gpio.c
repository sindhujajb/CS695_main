#include <stdio.h>
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
//to access GPIO pins on BeagleBone
#include <simpleBBB_GPIO.h>
#include <string.h>
#include <fcntl.h>
// GPIO 17 Raspberry Pi 3/4
#define GREEN_LED 60
// GPIO 2 Raspberry Pi 3/4
#define RED_LED 48

void init_LEDs();
void led_GPIO(int, int);
bool read_GPIO(int);

char buff[64];
char aux[8];
char* str;
int f_val;
char val;

//initializes GPIO pins of two LEDs
void init_LEDs()
{
    // LEDs
	simpleBBB_GPIOset(GREEN_LED, 0);
	simpleBBB_GPIOset(RED_LED, 0);
    simpleBBB_GPIOwrite(GREEN_LED, 1);
    simpleBBB_GPIOwrite(RED_LED, 1);
    usleep(1000000);
    simpleBBB_GPIOwrite(GREEN_LED, 0);
    simpleBBB_GPIOwrite(RED_LED, 0);
}

void led_GPIO(int led, int mode)
{
    if (led == 0)
		simpleBBB_GPIOwrite(GREEN_LED, mode);
    else
		simpleBBB_GPIOwrite(RED_LED, mode);
}

bool read_GPIO(int pin)
{
    if (simpleBBB_GPIOread(pin))
		return true;
    else
		return false;
}

char* path(int gpio, char* file)
{
  sprintf(aux, "%d", gpio);
  strcpy(buff, "/sys/class/gpio/gpio");
  strcat(buff, aux);
  strcat(buff, "/");
  strcat(buff, file);
  str = " ";
  str=buff;
  return str;
}

void simpleBBB_GPIOset(int gpio, int d_val)
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

void simpleBBB_GPIOwrite(int gpio, bool l_val)
{
	f_val = open(path(gpio, "val"), O_RDWR);
	if (l_val)
    	write(f_val, "1", 1);
	else
    	write(f_val, "0", 1);
    close(f_val);
}

int simpleBBB_GPIOread(int gpio)
{
	f_val = open(path(gpio, "val"), O_RDONLY, 0);
    read(f_val, &val, 1);
    close(f_val);
	return (val - '0');
}

