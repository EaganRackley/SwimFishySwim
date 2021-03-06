// ControllerWin.cpp
// Provides implementation for Wii controllers (i.e. WiiMote)
// Author(s): Eagan Rackley

#include "globals.h"
#include "SFSHeaders.h"
#include "IControllers.h"

#ifdef PLATFORM_IS_WIN

#include "ControllerWin.h"

const double kPi = 3.1415926;

// Variables to track our single instance and whether or not it's been created ...	
static IControllers *globalSingleInstance;

 /// <summary>
 /// This is the test subject object used to test the observer pattern
 /// </summary>
 ControllerWin::ControllerWin(int screenWidth, int screenHeight) 
 {
 	mySubject = new Subject(this);
	
	myMotionIndex = 0;
	
 }
 
 ///<summary> 
 /// This should be implemented as a singleton object so that anything using an IController 
 /// can use a single initialized instance!
 ///</summary>
 IControllers* ControllerWin::getSingleInstance(int screenWidth, int screenHeight)
 {
	if(globalSingleInstance == NULL)
	{		
		globalSingleInstance = new ControllerWin(screenWidth, screenHeight);	
	}
	
	return globalSingleInstance;
 }

 /// <summary>
 /// This is the test subject object used to test the observer pattern
 /// </summary>	
 ControllerWin::~ControllerWin() 
 {	
 	
 }
 
 ///<summary>
 /// Gets rid of the single instance object used by this class ...
 ///</summary>
 void ControllerWin::dispose()
 {
	delete mySubject;
	delete globalSingleInstance;
	globalSingleInstance = NULL;
	//WPAD_Shutdown();
 }
 
 
 ///<summary>
 /// A call to this will update all of the most recent controller states ...
 ///</summary>
 void ControllerWin::updateControllerStates()
 {
	unsigned int controllerType = 0;
	int index = 0;
	
	// Call to update controller Wii states ...
	
	//WPAD_ScanPads();
	//WPAD_ReadPending(WPAD_CHAN_ALL, countevs);
	
	// Probe each of our controllers for status.
	// [status == ready] get the latest object representing
	// each controllers current state.
	for(index = 0; index < MAXIMUM_CONTROLLERS; index++)
	{
		//wiiMoteStatus[index] = (CONTROLLER_STATUS)WPAD_Probe(index, &controllerType);
		
		/*if(wiiMoteStatus[index] == CONTROLLER_READY)
		{
			wiiMotes[index] = WPAD_Data(index);
			// Now that we know we have a controller, let's check for the nunchuck.
			// If it's not available, then indicate an error state since we require both...
			if(wiiMotes[index]->exp.type != WPAD_EXP_NUNCHUK)
			{
				wiiMoteStatus[index] = CONTROLLER_NOT_READY;
			}
		}*/
	}	
	
 }
 
 ///<summary>
 /// Returns true if button code for controller ID is active, else false
 ///</summary>		
 bool ControllerWin::checkButtonPress(int controllerID, CONTROLLER_BUTTONS code)
 {
	ASSERT(controllerID <= MAXIMUM_CONTROLLERS);	
	// If the controller specified is in a READY state, then do a bitwise and
	// to see if the button code is set ...
	/*if(wiiMoteStatus[controllerID] == CONTROLLER_READY)
	{		
		//debugPrint("WiiMoteCode: %x Code: %x\n", wiiMotes[controllerID]->btns_h, code); usleep(10000);							
		//printf("\x1b[2;0H"); printf("\n\n\nAccelDiff: %d", myAccelDifference.x);
		// Check the regular wiimote button codes (which should be less than horizontal swing)
		// C and Z are nunchuck codes, which are stored in the 2nd 16 bits of the int
		if((wiiMotes[controllerID]->btns_h & 0xFFFF0000) & code)
		{
			return true;
		}
		// The other buttons come from the wiimote, which we get from the 1st 16 bits
		else if ((wiiMotes[controllerID]->btns_h & 0x0000FFFF) & code)
		{							
			return true;
		}
		else if((code == WII_HORIZONTAL_SWING_LEFT) && (myAccelDifference.x > 250))
		{
			return true;
		}
		else if((code == WII_HORIZONTAL_SWING_RIGHT) && (myAccelDifference.x < -250))
		{
				return true;
		}
		else if((code == WII_VERTICAL_SWING_UP) && (myAccelDifference.y < -250))
		{
			return true;
		}
		else if((code == WII_VERTICAL_SWING_DOWN) && (myAccelDifference.y > 250))
		{
			return true;
		}
		else
		
		{
			return false;
		}	
	}
	else
	{
		return false;
	}*/
	return false;
 }

 ///<summary>
 /// Returns true if button code for controller ID has been released, else false
 ///</summary>		
 bool ControllerWin::checkButtonRelease(int controllerID, CONTROLLER_BUTTONS code)
 {
	ASSERT(controllerID <= MAXIMUM_CONTROLLERS);	
	// If the controller specified is in a READY state, then do a bitwise and
	// to see if the button code is set ...
	/*if(wiiMoteStatus[controllerID] == CONTROLLER_READY)
	{		
		//debugPrint("WiiMoteCode: %x Code: %x\n", wiiMotes[controllerID]->btns_h, code); usleep(10000);							
				
		// Check the regular wiimote button codes (which should be less than horizontal swing)
		// C and Z are nunchuck codes, which are stored in the 2nd 16 bits of the int
		
		if((wiiMotes[controllerID]->btns_u & 0xFFFF0000) & code)
		{
			return true;
		}
		// The other buttons come from the wiimote, which we get from the 1st 16 bits
		else if ((wiiMotes[controllerID]->btns_u & 0x0000FFFF) & code)
		{							
			return true;
		}		
		else
		{
			return false;
		}
	}
	else
	*/
	{
		return false;
	}
 }
 
 /// <summary>
 /// Tells us the angle of the joystick if applicable (0 to 360 degrees, 0 being up)
 /// </summary>
 float ControllerWin::checkJoystickAngle(int controllerID)
 {
	ASSERT(controllerID <= MAXIMUM_CONTROLLERS);
	/*
	// If the controller specified is in a READY state, then return the joystick angle...
	if(wiiMoteStatus[controllerID] == CONTROLLER_READY)
	{
		return wiiMotes[controllerID]->exp.nunchuk.js.ang;
	}
	else
	*/
	{
		return 0.0f;
	}
 }

 /// <summary>
 /// Returns a float between 0.0 and 1.0 defining how much pressure is being placed on the joystick...
 /// </summary>
 float ControllerWin::checkJoystickMagnitude(int controllerID)
 {
	ASSERT(controllerID <= MAXIMUM_CONTROLLERS);
	/*
	// If the controller specified is in a READY state, then return the joystick angle...
	if(wiiMoteStatus[controllerID] == CONTROLLER_READY)
	{		
		return wiiMotes[controllerID]->exp.nunchuk.js.mag;
	}
	else
	*/
	{
		return 0.0f;
	}
 }
	
 ///<summary>
 /// Returns an unsigned int with or'd values of all active buttons
 ///</summary>
 unsigned int ControllerWin::getStatusOfAllButtons(int controllerID)
 {
	ASSERT(controllerID <= MAXIMUM_CONTROLLERS);
	
    /*if(wiiMoteStatus[controllerID] == CONTROLLER_READY)
	{
		return wiiMotes[controllerID]->btns_h;		
	}
	else
	{
	*/
		return 0;
	//}
 }
	
 ///<summary>
 /// Returns status of a device by ID ...
 ///</summary> 
 CONTROLLER_STATUS ControllerWin::checkControllerStatus(int controllerID)
 {
	ASSERT(controllerID <= MAXIMUM_CONTROLLERS);

	// Get the accelerometer details, and calculate the difference in motion from the last time we checked status to this one...
	myLastMotion = myCurrentMotion;
	myCurrentMotion = checkMotion(controllerID);
	myAccelDifference.x = (short)myLastMotion.x - (short)myCurrentMotion.x;
	myAccelDifference.y = (short)myLastMotion.x - (short)myCurrentMotion.y;
    myAccelDifference.z = (short)myLastMotion.x - (short)myCurrentMotion.z;

	return wiiMoteStatus[controllerID];
 }
	
 ///<summary>
 /// Returns an integer value specifying the number of devices properly connected and identified
 ///</summary>
 int ControllerWin::numberOfConnectedDevices()
 {
	int numberConnected = 0;
	for(int index = 0; index < MAXIMUM_CONTROLLERS; index++)
	{
		if(wiiMoteStatus[index] == CONTROLLER_READY)
		{
			numberConnected++;
		}
	}
	
	return numberConnected;
 }
		
 ///<summary>
 /// Can be used to check X,Y pointer information from controller
 ///</summary>
 float ControllerWin::checkPointer(int controllerID, CONTROLLER_POINTER pointerData)
 {    
	ASSERT(controllerID <= MAXIMUM_CONTROLLERS);
	float pointerValue = 0;
	
	/*if(wiiMoteStatus[controllerID] == CONTROLLER_READY)
	{
		if(wiiMotes[controllerID]->ir.valid)
		{
			switch(pointerData)
			{
				case POINTER_X:
					pointerValue = (int)wiiMotes[controllerID]->ir.x;
				break;
				case POINTER_Y:
					pointerValue = (int)wiiMotes[controllerID]->ir.y;
				break;
			}
		}		
	}*/		
	return pointerValue;
 }
	
 ///<summary>
 /// Can be used to check X,Y,Z Accelerometer motion from controller
 ///</summary>
 AccelerometerData ControllerWin::checkMotion(int controllerID)
 {	
	AccelerometerData returnMotion = {0, 0, 0};

	// Save the motion values in a circular buffer
	/*myMotionIndex++;
	if(myMotionIndex >= MOTION_SAMPLES) myMotionIndex = 0;	
	if(wiiMoteStatus[controllerID] == CONTROLLER_READY)
	{
		ASSERT(wiiMoteStatus[controllerID] == CONTROLLER_READY);
		myMotionValues[myMotionIndex].x = wiiMotes[controllerID]->accel.x;
		myMotionValues[myMotionIndex].y = wiiMotes[controllerID]->accel.y;
		myMotionValues[myMotionIndex].z = wiiMotes[controllerID]->accel.z;

		// AVERAGE the values of the motion samples and return the averaged amount...
		for(int index = 0; index < MOTION_SAMPLES; index++)
		{
			returnMotion.x += myMotionValues[myMotionIndex].x;
			returnMotion.y += myMotionValues[myMotionIndex].y;
			returnMotion.z += myMotionValues[myMotionIndex].z;
		}

		returnMotion.x /= MOTION_SAMPLES;
		returnMotion.y /= MOTION_SAMPLES;
		returnMotion.z /= MOTION_SAMPLES;
	}*/

	return returnMotion;	
 }
 
 /// <summary>
 /// Can be used to check Pitch, Roll, and Yaw orientation data from controller
 /// </summary>
 float ControllerWin::checkOrientation(int controllerID, CONTROLLER_ORIENTATION orientData)
 {
	float orientValue = 0;
	
	/*if(wiiMoteStatus[controllerID] == CONTROLLER_READY)
	{		
		switch(orientData)
		{
			case ORIENT_PITCH:
				orientValue = wiiMotes[controllerID]->orient.pitch;
			break;
			case ORIENT_YAW:
				orientValue = wiiMotes[controllerID]->orient.yaw;
			break;
			case ORIENT_ROLL:
				orientValue = wiiMotes[controllerID]->orient.roll;
			break;			
		}		
	}*/
		
	return orientValue;	
 }

 
 ///<summary>
 /// [Controller is rumbling] stops the rumbling bit ...
 ///</summary>
 void ControllerWin::stopRumblePack(int controllerID)
 {
	ASSERT(controllerID <= MAXIMUM_CONTROLLERS);
	if(wiiMoteStatus[controllerID] == CONTROLLER_READY)
	{
		//WPAD_Rumble(controllerID, 0);
	}
 }

 ///<summary>
 /// [Controller is not rumbling] starts the rumbling bit ...
 ///</summary>
 void ControllerWin::startRumblePack(int controllerID)
 {
	ASSERT(controllerID <= MAXIMUM_CONTROLLERS);
	if(wiiMoteStatus[controllerID] == CONTROLLER_READY)
	{
		//WPAD_Rumble(controllerID, 1);
	}
 }

 /// <summary>
 /// This is the test subject object used to test the observer pattern
 /// </summary>	
 void ControllerWin::registerObserver (IObserver *observer)         
 {
	ASSERT(observer != NULL);
 	mySubject->registerObserver(observer);
 }
	
 /// <summary>
 /// This is the test subject object used to test the observer pattern
 /// </summary>	
 void ControllerWin::removeObserver (IObserver *observer)
 {
	ASSERT(observer != NULL);
	mySubject->removeObserver(observer);
 } 

 /// <summary>
 /// This is the test subject object used to test the observer pattern
 /// </summary>	
 void ControllerWin::notifyObservers ()
 {
	mySubject->notifyObservers(); 
 }

#endif
 
 

