/*
 * hightMeassure.h
 *
 *  Created on: 26.06.2017
 *      Author: Johannes
 */

#ifndef SOURCES_ORIG_HIGHTMEASURE_H_
#define SOURCES_ORIG_HIGHTMEASURE_H_

#include "plugin.h"
#include "fsm.h"

class HightMeasure: public Plugin
{
private:
	FestoProcessAccess* process;
	bool res;
	fsm_states hightState;
public:
	HightMeasure(FestoProcessAccess* process);
	virtual void evalCycle();
	virtual bool result();
private:
	bool checkHight();

};

#endif /* SOURCES_ORIG_HIGHTMEASURE_H_ */
