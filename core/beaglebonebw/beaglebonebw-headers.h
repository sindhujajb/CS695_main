#ifndef RASPI_3_4_HEADERS_H
#define RASPI_3_4_HEADERS_H

#include "basics.h"
#include "peripherals/gpio/gpio.h"
#include "sensors/internal/internal.h"
#include "sensors/bme280/bme280.h"


#ifdef MICROCONTROLLER
	#include "wifi/wifi.h"
#endif

#ifdef HTTP
	#include "protocols/http/http.h"
#endif



#endif
