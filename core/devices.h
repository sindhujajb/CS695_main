#ifndef _DEVICES_H_
#define _DEVICES_H_


#ifdef BBBW
	#include "beaglebonebw/beaglebonebw-headers.h"
#endif
#ifdef MYDEVICE
	#include "my-device/my-device-headers.h"
#endif
#ifdef ESP32
	#include "ESP32/ESP32-headers.h"
#endif

#endif
