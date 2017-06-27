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

using namespace std;

FestoProcessAccessSim::FestoProcessAccessSim() :
		FestoProcessAccess(NULL)
{
	timeCounter = 0;

#ifdef LOG_PROCESS
	logFile = fopen("processlog.txt", "w");
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

	file.open("TestFiles\\TestdurchlaufBisTransport.txt");
	filenr = 1;
	run = true;

}

FestoProcessAccessSim::~FestoProcessAccessSim()
{
	//delete process;
	if (logFile != NULL)
	{
		fclose(logFile);
	}
	file.close();
}

void FestoProcessAccessSim::updateInputs(void)
{
	printf("UpdateInputs");
	string str, temp;
	getline(file, str);
	stringstream stream(str);
	switch (filenr) {
	case 1:
		stream >> beginningSensor >> hightSensor >> metalDetector
				>> metalDetected >> slide >> slidePassed >> end
				>> buttonStartPressed >> buttonStartPositiveEdge
				>> buttonStartNegativeEdge >> buttonStopPressed
				>> buttonResetPressed >> buttonEmergencyActive >> hight;
		if (file.eof())
		{
			filenr = 2;
			file.close();
			file.open("Logs\\processlog2.txt");
		}
		break;
	case 2:
		getline(file, str);
		for (int i = 0; i < str.size(); i++)
		{
			if (str[i] == ';')
			{
				str[i] = ' ';
			}
		}
		stream >> temp >> temp >> hight;
		if (file.eof())
		{
			filenr = 3;
			file.close();
			//file.open("TestFiles\\TestdurchlaufKorrekterBaustein.txt");
			file.open("TestFiles\\TestdurchlaufFehlerhafterBaustein.txt");
		}
		break;
	case 3:
		stream >> beginningSensor >> hightSensor >> metalDetector
				>> metalDetected >> slide >> slidePassed >> end
				>> buttonStartPressed >> buttonStartPositiveEdge
				>> buttonStartNegativeEdge >> buttonStopPressed
				>> buttonResetPressed >> buttonEmergencyActive >> hight;
		if (file.eof())
		{
			run = false;

		}
	}

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
	printf("Drive Right\n");
}

void FestoProcessAccessSim::driveLeft(void)
{
	directionRight = false;
	directionLeft = true;
	directionSlowLeft = false;
	directionSlowRight = false;
	directionStop = false;
	printf("Drive Left\n");
}

void FestoProcessAccessSim::driveSlowRight(void)
{
	directionRight = false;
	directionLeft = false;
	directionSlowLeft = false;
	directionSlowRight = true;
	directionStop = false;
	printf("Drives slow Right\n");
}

void FestoProcessAccessSim::driveSlowLeft(void)
{
	directionRight = true;
	directionLeft = false;
	directionSlowLeft = true;
	directionSlowRight = false;
	directionStop = false;
	printf("Drives slow Left\n");
}

void FestoProcessAccessSim::driveStop(void)
{
	directionRight = false;
	directionLeft = false;
	directionSlowLeft = false;
	directionSlowRight = false;
	directionStop = true;
	printf("Drive Stop\n");
}

void FestoProcessAccessSim::openJunction(void)
{
	junction = true;
	printf("Open Junction\n");
}

void FestoProcessAccessSim::closeJunction(void)
{
	junction = false;
	printf("Close Junction\n");
}

void FestoProcessAccessSim::lightGreenOn(void)
{
	lightGreen = true;
	printf("lightGreenON\n");
}

void FestoProcessAccessSim::lightGreenOff(void)
{
	lightGreen = false;
	printf("lightGreenOff\n");
}

void FestoProcessAccessSim::lightYellowOn(void)
{
	lightYellow = true;
	printf("lightYellowOn\n");
}

void FestoProcessAccessSim::lightYellowOff(void)
{
	lightYellow = false;
	printf("lightYellowOff\n");
}

void FestoProcessAccessSim::lightRedOn(void)
{
	lightRed = true;
	printf("lightRedOn\n");
}

void FestoProcessAccessSim::lightRedOff(void)
{
	lightRed = false;
	printf("lightRedOff\n");
}

void FestoProcessAccessSim::turnLEDStartOn(void)
{
	startLED = true;
	printf("turnLEDStartOn\n");
}

void FestoProcessAccessSim::turnLEDStartOff(void)
{
	startLED = false;
	printf("turnLEDStartOff\n");
}

void FestoProcessAccessSim::turnLEDResetOn(void)
{
	resetLED = true;
	printf("turnLEDResetOn\n");
}
;

void FestoProcessAccessSim::turnLEDResetOff(void)
{
	resetLED = false;
	printf("turnLEDResetOff\n");
}

void FestoProcessAccessSim::turnLEDQ1On(void)
{
	q1LED = true;
	printf("turnLEDQ10nOn\n");
}

void FestoProcessAccessSim::turnLEDQ1Off(void)
{
	q1LED = false;
	printf("turnLEDQ10nOff\n");
}

void FestoProcessAccessSim::turnLEDQ2On(void)
{
	q2LED = true;
	printf("turnLEDQ20nOn\n");
}

void FestoProcessAccessSim::turnLEDQ2Off(void)
{
	q2LED = false;
	printf("turnLEDQ20nOff\n");
}

void FestoProcessAccessSim::turnAllOff(void)
{
	lightGreen = false;
	lightRed = false;
	lightYellow = false;
	q1LED = false;
	q2LED = false;
	printf("turnAllOff\n");
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
