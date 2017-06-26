/** 
 * File:   fsm.cpp
 *
 * Class contains the controlling FSM for sorting out metal contaminated parts.
 * 
 * \author  Prof. Dr. Thomas Lehmann
 * \version 1
 * \date    2013-11-01
 */

#include "fsm.h"

#define MEASURE0 3770
#define MEASURE1 3360
#define MEASURE2 3710
#define MEASURE3 3410
#define MEASURE4 3050
#define DEVIATION 100

FSM::FSM(FestoProcessAccess *process, Plugin* plugin = 0)
{
	this->process = process;
	currentState = Start;
	this->plugin = plugin;
	hightState = HightMeasure0;
}

FSM::~FSM()
{
	delete plugin;
	delete process;
}

void FSM::eval()
{
	process->updateInputs();
	if (plugin != NULL)
	{
		plugin->evalCycle();
	}
	evalEvents();
	evalState();
	process->applyOutput();
}

void FSM::evalEvents()
{
	switch (currentState) {
	case Start:
		currentState = Standby;
		break;
	case Standby:
		if (process->isButtonStartNegativeEdge())
		{
			currentState = Ready;
		}
		break;
	case Ready:
		if (process->isButtonStartNegativeEdge())
		{
			currentState = Standby;
		}
		if (process->isItemAtBeginning() && !process->isItemAtEnd())
		{
			currentState = Transport;
		}
		if (process->isItemAtHightSensor() || process->isItemAtMetalDetector())
		{
			currentState = Error;
		}
		break;
	case Transport:
		//Tue Höhenmessung!!!-------------------------------------------------------------------------------------------------------
		if (!plugin->result())
		{
			currentState = WrongBlock;
		}
		if (process->isItemAtMetalDetector())
		{
			currentState = MetalDetection;
		}
		if (process->isItemAtEnd())
		{
			currentState = Error;
		}
		break;
	case WrongBlock:
		if (process->isItemAtBeginning())
		{
			currentState = BeginningReached;
		}
		break;
	case BeginningReached:
		if (!process->isItemAtBeginning())
		{
			currentState = Standby;
		}
		break;
	case MetalDetection:
		if (process->isMetalDetected())
		{
			currentState = Metalic;
		} else
		{
			currentState = NonMetalic;
		}
		break;
	case NonMetalic:
		if (process->isItemAtEnd())
		{
			currentState = EndReached;
		}
		if (process->isItemAtBeginning() || process->isItemAtHightSensor())
		{
			currentState = Error;
		}
		break;
	case EndReached:
		if (process->isButtonStartNegativeEdge())
		{
			currentState = Standby;
		}
		if (!(process->isItemAtEnd()))
		{
			currentState = Ready;
		}
		if (process->isItemAtMetalDetector() || process->isItemAtHightSensor())
		{
			currentState = Error;
		}
		break;
	case Metalic:
		if (process->hasItemPassedSlide())
		{
			currentState = SlideReached;
		}
		if (process->isItemAtBeginning() || process->isItemAtHightSensor())
		{
			currentState = Error;
		}
		break;
	case SlideReached:
		if (process->isButtonStartNegativeEdge())
		{
			currentState = Standby;
		}
		if (process->isItemAtBeginning())
		{
			currentState = Transport;
		}
		if (process->isItemAtEnd() || process->isItemAtHightSensor())
		{
			currentState = Error;
		}
		break;
	case Error:
		if (process->isButtonStartNegativeEdge())
		{
			currentState = Standby;
		}
		break;
	default:
		currentState = Start;
	}
}

void FSM::evalState()
{
	switch (currentState) {
	case Start:
	case Standby:
		process->driveStop();
		process->lightGreenOff();
		process->lightRedOff();
		process->lightYellowOff();
		process->turnLEDQ1Off();
		process->turnLEDQ2Off();
		process->turnLEDResetOff();
		process->turnLEDStartOn();
		break;
	case Ready:
		process->driveStop();
		process->lightGreenOn();
		process->lightRedOff();
		process->lightYellowOff();
		process->turnLEDStartOn();
		break;
	case Transport:
		process->driveRight();
		process->lightGreenOn();
		process->lightRedOff();
		process->lightYellowOff();
		process->turnLEDStartOff();
		break;
	case WrongBlock:
		process->driveLeft();
		process->lightGreenOff();
		blinkRed();
		process->lightYellowOff();
		break;
	case BeginningReached:
		process->driveStop();
		process->lightGreenOff();
		blinkRed();
		process->lightYellowOff();
		break;
	case MetalDetection:
		process->driveStop();
		process->lightGreenOn();
		process->lightRedOff();
		process->lightYellowOff();
		break;
	case NonMetalic:
		process->driveRight();
		process->lightGreenOn();
		process->lightRedOff();
		process->lightYellowOff();
		process->turnLEDStartOff();
		process->openJunction();
		break;
	case EndReached:
		process->driveStop();
		process->lightRedOff();
		process->lightYellowOff();
		process->turnLEDStartOff();
		process->closeJunction();
		process->turnLEDStartOn();
		blinkGreen();
		break;
	case Metalic:
		process->driveRight();
		process->lightGreenOff();
		process->lightRedOff();
		process->lightYellowOn();
		break;
	case SlideReached:
		process->driveStop();
		process->lightGreenOn();
		process->lightRedOff();
		process->lightYellowOff();
		process->turnLEDStartOn();
		break;
	case Error:
		process->driveStop();
		process->lightGreenOff();
		process->lightYellowOff();
		process->turnLEDStartOn();
		process->closeJunction();
		blinkRed();
		break;

	}
}

void FSM::blinkRed()
{
	if (process->timeCounter1s() & 0x01)
	{
		process->lightRedOn();
	} else
	{
		process->lightRedOff();
	}
}

void FSM::blinkGreen()
{
	if (process->timeCounter1s() & 0x01)
	{
		process->lightGreenOn();
	} else
	{
		process->lightGreenOff();
	}
}

bool FSM::checkHight()
{
	switch (hightState) {
	case HightMeasure0:
		if (!(process->getHight() < MEASURE1 - DEVIATION
				|| process->getHight() > MEASURE1 + DEVIATION))
		{
			hightState = HightMeasure1;
		} else if (process->getHight() < MEASURE0 - DEVIATION
				|| process->getHight() > MEASURE0 + DEVIATION)
		{
			return false;
		}
		break;
	case HightMeasure1:
		if (!(process->getHight() < MEASURE2 - DEVIATION
				|| process->getHight() > MEASURE2 + DEVIATION))
		{
			hightState = HightMeasure2;
		} else if (process->getHight() < MEASURE1 - DEVIATION
				|| process->getHight() > MEASURE1 + DEVIATION)
		{
			return false;
		}
		break;
	case HightMeasure2:
		if (!(process->getHight() < MEASURE3 - DEVIATION
				|| process->getHight() > MEASURE3 + DEVIATION))
		{
			hightState = HightMeasure3;
		} else if (process->getHight() < MEASURE2 - DEVIATION
				|| process->getHight() > MEASURE2 + DEVIATION)
		{
			return false;
		}
		break;
	case HightMeasure3:
		if (!(process->getHight() < MEASURE4 - DEVIATION
				|| process->getHight() > MEASURE4 + DEVIATION))
		{
			hightState = HightMeasure4;
		} else if (process->getHight() < MEASURE3 - DEVIATION
				|| process->getHight() > MEASURE3 + DEVIATION)
		{
			return false;
		}
		break;
	case HightMeasure4:
		if (!(process->getHight() < MEASURE0 - DEVIATION
				|| process->getHight() > MEASURE0 + DEVIATION))
		{
			hightState = HightMeasure0;
		} else if (process->getHight() < MEASURE4 - DEVIATION
				|| process->getHight() > MEASURE4 + DEVIATION)
		{
			return false;
		}
		break;
		break;
	}
	return true;
}
