/**
 * File:   FestoProcessAccess.cpp
 *
 * Class providing high level access to sensors and actuators of the FESTO
 * system.
 *
 * \author  Prof. Dr. Thomas Lehmann
 * \version 1
 * \date    2013-11-01
 */

#include "iomasks.h"
#include "FestoProcessAccessSim.h"
#include <time.h>

FestoProcessAccessSim::FestoProcessAccessSim(): FestoProcessAccess(NULL)
{
	timeCounter = 0;

#ifdef LOG_PROCESS
	logFile = fopen("c:\\tmp\\processlog.txt", "w");
#else
	logFile = NULL;
#endif

	directionRight = false;
	directionLeft = false;
	directionSlowRight = false;
	directionSlowLeft = false;
	directionStop = false;
	junction = false;
	lightGreen = false;
	lightRed = false;
	lightYellow = false;
	startLED = false;
	resetLED = false;
	q1LED = false;
	q2LED = false;
	beginningSensor = false;
	hightSensor = false;
	metalDetector = false;
	metalDetected = false;
	slide = false;
	slidePassed = false;
	end = false;
	buttonStartPressed = false;
	buttonStartPositiveEdge = false;
	buttonStartNegativeEdge = false;
	buttonStopPressed = false;
	buttonResetPressed = false;
	buttonEmergencyActive = false;
	hight = 0;

}

FestoProcessAccessSim::~FestoProcessAccessSim()
{
	//delete process;
	if (logFile != NULL)
	{
		fclose(logFile);
	}
}

void FestoProcessAccessSim::updateInputs(void)
{
	printf("UpdateInputs");
}
void FestoProcessAccessSim::logProcessData()
{

}

void FestoProcessAccessSim::applyOutput(void)
{
}

void FestoProcessAccessSim::driveRight(void)
{
	directionRight = true;
	directionLeft = false;
	directionSlowLeft = false;
	directionSlowRight = false;
	directionStop = false;
	printf("Drive Right");
}

void FestoProcessAccessSim::driveLeft(void)
{
	directionRight = false;
	directionLeft = true;
	directionSlowLeft = false;
	directionSlowRight = false;
	directionStop = false;
	printf("Drive Left");
}

void FestoProcessAccessSim::driveSlowRight(void)
{
	directionRight = false;
	directionLeft = false;
	directionSlowLeft = false;
	directionSlowRight = true;
	directionStop = false;
	printf("Drives slow Right");
}

void FestoProcessAccessSim::driveSlowLeft(void)
{
	directionRight = true;
	directionLeft = false;
	directionSlowLeft = true;
	directionSlowRight = false;
	directionStop = false;
	printf("Drives slow Left");
}

void FestoProcessAccessSim::driveStop(void)
{
	directionRight = false;
	directionLeft = false;
	directionSlowLeft = false;
	directionSlowRight = false;
	directionStop = true;
	printf("Drive Stop");
}

void FestoProcessAccessSim::openJunction(void)
{
	junction = true;
	printf("Open Junction");
}

void FestoProcessAccessSim::closeJunction(void)
{
	junction = false;
	printf("Close Junction");
}

void FestoProcessAccessSim::lightGreenOn(void)
{
	lightGreen = true;
	printf("lightGreenON");
}

void FestoProcessAccessSim::lightGreenOff(void)
{
	lightGreen = false;
	printf("lightGreenOff");
}

void FestoProcessAccessSim::lightYellowOn(void)
{
	lightYellow = true;
	printf("lightYellowOn");
}

void FestoProcessAccessSim::lightYellowOff(void)
{
	lightYellow = false;
	printf("lightYellowOff");
}

void FestoProcessAccessSim::lightRedOn(void)
{
	lightRed = true;
	printf("lightRedOn");
}

void FestoProcessAccessSim::lightRedOff(void)
{
	lightRed = false;
	printf("lightRedOff");
}

void FestoProcessAccessSim::turnLEDStartOn(void)
{
	startLED = true;
	printf("turnLEDStartOn");
}

void FestoProcessAccessSim::turnLEDStartOff(void)
{
	startLED = false;
	printf("turnLEDStartOff");
}

void FestoProcessAccessSim::turnLEDResetOn(void)
{
	resetLED = true;
	printf("turnLEDResetOn");
}
;

void FestoProcessAccessSim::turnLEDResetOff(void)
{
	resetLED = false;
	printf("turnLEDResetOff");
}

void FestoProcessAccessSim::turnLEDQ1On(void)
{
	q1LED = true;
	printf("turnLEDQ10nOn");
}

void FestoProcessAccessSim::turnLEDQ1Off(void)
{
	q1LED = false;
	printf("turnLEDQ10nOff");
}

void FestoProcessAccessSim::turnLEDQ2On(void)
{
	q2LED = true;
	printf("turnLEDQ20nOn");
}

void FestoProcessAccessSim::turnLEDQ2Off(void)
{
	q2LED = false;
	printf("turnLEDQ20nOff");
}

void FestoProcessAccessSim::turnAllOff(void)
{
	lightGreen = false;
	lightRed = false;
	lightYellow = false;
	q1LED = false;
	q2LED = false;
	printf("turnAllOff");
}

bool FestoProcessAccessSim::isItemAtBeginning(void)
{
	return beginningSensor; // active low
}

bool FestoProcessAccessSim::isItemAtHightSensor(void)
{
	return hightSensor; // active low
}
;

bool FestoProcessAccessSim::isItemAtMetalDetector(void)
{
	return metalDetector; // active low
}

bool FestoProcessAccessSim::isMetalDetected(void)
{
	return metalDetected;
}

bool FestoProcessAccessSim::isJunctionOpen(void)
{
	return junction;
}

bool FestoProcessAccessSim::isItemAtSlide(void)
{
	return slide; // active low
}
bool FestoProcessAccessSim::hasItemPassedSlide(void)
{
	return slidePassed; // active low, so pos edge
}

bool FestoProcessAccessSim::isItemAtEnd(void)
{
	return end; // active low
}

bool FestoProcessAccessSim::isButtonStartPressed(void)
{
	return buttonStartPressed;
}

bool FestoProcessAccessSim::isButtonStartPositiveEdge(void)
{
	return buttonStartPositiveEdge;
}

bool FestoProcessAccessSim::isButtonStartNegativeEdge(void)
{
	return buttonStartNegativeEdge;
}

bool FestoProcessAccessSim::isButtonStopPressed(void)
{
	return buttonStopPressed; // active low
}

bool FestoProcessAccessSim::isButtonResetPressed(void)
{
	return buttonResetPressed;
}

bool FestoProcessAccessSim::isButtonEmergencyActive(void)
{
	return buttonEmergencyActive; // active low
}
unsigned short FestoProcessAccessSim::getHight()
{
	return hight;
}

time_t FestoProcessAccessSim::timeCounter1s()
{
	return time(NULL);
}
