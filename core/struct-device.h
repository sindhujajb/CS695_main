#ifndef STRUCT_DEVICE_H_
//this prevents header file from being included multiple times in same program
#define STRUCT_DEVICE_H_
#include <stdio.h>
#include <stdbool.h>

struct device {
   const char *id;
   //this pointer represents the IP address of a server that device communicaties with
   const char *address;
   //this pointer represents the port number for the server 
   int address_port;
   //this pointer represents a topic or channel for sending and recieving the data
   const char *top;
   //name of wifi network that device is connected to
   const char *ssid_wifi;
   //password of wifi network that device is connected to
   const char *pass_wifi;
   //represents whether each of 12 different sensors is enabled or disabled
   bool isEnable[12];
   // Sensors Data String
   char d[12][10];   
   //Sensors Names
   const char *s_name[30];   
   bool isConnected[12];
   long interv;
   char json[1023];
}; 
#endif
