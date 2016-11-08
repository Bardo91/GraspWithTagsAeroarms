/*
 * Vision Sensor UDP Interface class
 * 
 * Author: Alejandro Suarez Fernandez-Miranda
 * Date: 20 October 2016
 *
 * Copyright (c) Alejandro Suárez Fernández-Miranda - University of Seville
 */

#include "VisionSensorUDPInterface.h"


/* Constructor */
VisionSensorUDPInterface::VisionSensorUDPInterface()
{
	socketServer = -1;
	packetID = 0;
	gettimeofday(&t0, NULL);
}


/* Destructor */
VisionSensorUDPInterface::~VisionSensorUDPInterface()
{
	if(socketServer != -1)
		close(socketServer);
}


/* Create and init the UDP socket for sending the data */
int VisionSensorUDPInterface::connect(const char * host_IP_address, int port)
{
	int error = 0;
	
	
    socketServer = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (socketServer < 0)
    {
	    error = 1;
    	cout << endl << "ERROR: [in VisionSensorUDPInterface::connect] could not open socket." << endl;
    }
    else
    {
    	server = gethostbyname(host_IP_address);
    	if (server == NULL)
    	{
	    	error = 1;
    	    close(socketServer);
    	    cout << "ERROR: [in VisionSensorUDPInterface::connect] could not get host by name." << endl;
    	}
    	else
    	{
    		bzero((char*)&addrServer, sizeof(addrServer));
    		addrServer.sin_family = AF_INET;
    		bcopy((char*)server->h_addr, (char*)&addrServer.sin_addr.s_addr, server->h_length);
	    	addrServer.sin_port = htons(port);
    	}
    }
    
    // Set initial time stamp
	gettimeofday(&t0, NULL);
    
    
    return error;
}

	
/* Release UDP port */
void VisionSensorUDPInterface::disconnect()
{
	if(socketServer != -1)
		close(socketServer);
}

	
/* Send simulated data (only for debug) */
void VisionSensorUDPInterface::sendData()
{
	VISION_SENSOR_DATA_PACKET dataPacket;
	struct timeval t1;
	double t = 0;
	int n = 0;
	int m = 0;
	
	
	// Set the fields of the data packet
	packetID++;
	dataPacket.packetID = packetID;
	gettimeofday(&t1, NULL);
	t = (t1.tv_sec - t0.tv_sec) + 1e-6*(t1.tv_usec - t0.tv_usec);
	dataPacket.timeStamp = (float)t;
		
	for(n = 0; n < 3; n++)
	{
		dataPacket.leftArmGoalPosition[n] = leftArmGoalPosition[n];
		dataPacket.rightArmGoalPosition[n] = rightArmGoalPosition[n];
		for(m = 0; m < 3; m++)
		{
			dataPacket.leftArmGoalOrientation[n][m] = leftArmGoalOrientation[n][m];
			dataPacket.rightArmGoalOrientation[n][m] = rightArmGoalOrientation[n][m];
		}
	}
		
	// Send data
	if(sendto(socketServer, (char*)&dataPacket, sizeof(VISION_SENSOR_DATA_PACKET), 0, (struct sockaddr*)&addrServer, sizeof(addrServer)) < 0)
		cout << endl << "ERROR: could not send data" << endl;
}



