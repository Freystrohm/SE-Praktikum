/*
 * plugin.cpp
 *
 *  Created on: 26.06.2017
 *      Author: Johannes
 */


#include "hightMeasure.h"


#define MEASURE0 3770
#define MEASURE1 3360
#define MEASURE2 3710
#define MEASURE3 3410
#define MEASURE4 3050
#define DEVIATION 100

HightMeasure::HightMeasure(FestoProcessAccess* process)
{
	this->process = process;
	res=true;
	hightState = HightMeasure0;
}

 void HightMeasure::evalCycle()
 {
	res = checkHight();
 }


 bool HightMeasure::result()
 {
	 return res;
 }

 bool HightMeasure::checkHight()
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

