/*
 * Vision Sensor UDP Interface class
 * Author: Alejandro Suarez Fernandez-Miranda
 * Date: 20 October 2016
 *
 * Copyright (c) Alejandro Suárez Fernández-Miranda - University of Seville
 */


#ifndef VISION_SENSOR_UDP_INTERFACE_H_
#define VISION_SENSOR_UDP_INTERFACE_H_


// Standard library
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/time.h>



// Structures
typedef struct
{
	uint8_t header[2];					// "VS" character sequence
	uint8_t packetID;
	float timeStamp;
	float leftArmGoalPosition[3];
	float rightArmGoalPosition[3];
	float leftArmGoalOrientation[3][3];
	float rightArmGoalOrientation[3][3];
	uint8_t checksum;
} VISION_SENSOR_DATA_PACKET;


// Namespaces
using namespace std;


class VisionSensorUDPInterface
{
public:
	/**************** PUBLIC VARIABLES *****************/
	
	float leftArmGoalPosition[3];
	float rightArmGoalPosition[3];
	float leftArmGoalOrientation[3][3];
	float rightArmGoalOrientation[3][3];


	/***************** PUBLIC METHODS *****************/

	/* Constructor */
	VisionSensorUDPInterface();

	/* Destructor */
	~VisionSensorUDPInterface();
	
	/* Create and init the UDP socket for sending the data */
	int connect(const char * host_IP_address, int port);
	
	/* Release UDP port */
	void disconnect();
	
	/* Send simulated data */
	void sendData();



private:
	/***************** PRIVATE VARIABLES *****************/

    struct sockaddr_in addrServer;
    struct hostent * server;
    struct timeval t0;
    int socketServer;
    int portNum;
    uint8_t packetID;


	/***************** PRIVATE METHODS *****************/



};

#endif


