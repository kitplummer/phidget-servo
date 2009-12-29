#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "phidget21.h"

// Handlers
int AttachHandler(CPhidgetHandle SERV, void *userptr)
{
	int serialNo;
	const char *name;

	CPhidget_getDeviceName (SERV, &name);
	CPhidget_getSerialNumber(SERV, &serialNo);
	//printf("%s %10d attached!\n", name, serialNo);

	return 0;
}

int DetachHandler(CPhidgetHandle SERV, void *userptr)
{
	int serialNo;
	const char *name;

	CPhidget_getDeviceName (SERV, &name);
	CPhidget_getSerialNumber(SERV, &serialNo);
	//printf("%s %10d detached!\n", name, serialNo);

	return 0;
}

int ErrorHandler(CPhidgetHandle SERV, void *userptr, int ErrorCode, const char *Description)
{
	printf("Error handled. %d - %s\n", ErrorCode, Description);
	return 0;
}

int PositionChangeHandler(CPhidgetServoHandle SERV, void *usrptr, int Index, double Value)
{
	//printf("Motor: %d > Current Position: %f\n", Index, Value);
	return 0;
}

//Display the properties of the attached phidget to the screen.  We will be displaying the name, serial number and version of the attached device.
int display_properties(CPhidgetServoHandle phid)
{
	int serialNo, version, numMotors;
	const char* ptr;

	CPhidget_getDeviceType((CPhidgetHandle)phid, &ptr);
	CPhidget_getSerialNumber((CPhidgetHandle)phid, &serialNo);
	CPhidget_getDeviceVersion((CPhidgetHandle)phid, &version);

	CPhidgetServo_getMotorCount (phid, &numMotors);

	//printf("%s\n", ptr);
	//printf("Serial Number: %10d\nVersion: %8d\n# Motors: %d\n", serialNo, version, numMotors);

	return 0;
}

int servo_simple(int pos)
{
	int result;
	const char *err;

	//Declare an servo handle
	CPhidgetServoHandle servo = 0;

	//create the servo object
	CPhidgetServo_create(&servo);

	//Set the handlers to be run when the device is plugged in or opened from software, unplugged or closed from software, or generates an error.
	CPhidget_set_OnAttach_Handler((CPhidgetHandle)servo, AttachHandler, NULL);
	CPhidget_set_OnDetach_Handler((CPhidgetHandle)servo, DetachHandler, NULL);
	CPhidget_set_OnError_Handler((CPhidgetHandle)servo, ErrorHandler, NULL);

	//Registers a callback that will run when the motor position is changed.
	//Requires the handle for the Phidget, the function that will be called, and an arbitrary pointer that will be supplied to the callback function (may be NULL).
	CPhidgetServo_set_OnPositionChange_Handler(servo, PositionChangeHandler, NULL);

	//open the servo for device connections
	CPhidget_open((CPhidgetHandle)servo, -1);

	//get the program to wait for an servo device to be attached
	//printf("Waiting for Servo controller to be attached....");
	if((result = CPhidget_waitForAttachment((CPhidgetHandle)servo, 10000)))
	{
		CPhidget_getErrorDescription(result, &err);
		printf("Error waiting for attachment: %s\n", err);
		return 0;
	}

	//Display the properties of the attached servo device
	//display_properties(servo);

	//change the motor position
	//valid range is -22 to 232
    CPhidgetServo_setPosition (servo, 0, pos);
    usleep(1000000);
	CPhidgetServo_setEngaged (servo, 0, 0);

	//since user input has been read, this is a signal to terminate the program so we will close the phidget and delete the object we created
	//printf("Closing...\n");
	CPhidget_close((CPhidgetHandle)servo);
	CPhidget_delete((CPhidgetHandle)servo);

	//all done, exit
	return 0;
}

int main(int argc, char* argv[])
{
    if (argc != 2) {
        printf("Error with command");
        return 1;
    } else {
        int pos = atoi((argv[1]));
        printf("Success moving to %i", pos);
	    servo_simple(pos);
	    return 0;
    }
}

