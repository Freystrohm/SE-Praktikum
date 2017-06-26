/** 
 * File:   fsm.h
 *
 * Class contains the controlling FSM for sorting out metal contaminated parts.
 * 
 * \author  Prof. Dr. Thomas Lehmann
 * \version 1
 * \date    2013-11-01
 */

#ifndef FSM_H
#define	FSM_H
#include "FestoProcessAccess.h"
#include "plugin.h"

enum fsm_states
{
	Start,
	Standby,
	Ready,
	Transport,
	MetalDetection,
	NonMetalic,
	Metalic,
	SlideReached,
	Error,
	EndReached,
	HightMeasure0,
	HightMeasure1,
	HightMeasure2,
	HightMeasure3,
	HightMeasure4,
	HightMeasure5,
	WrongBlock,
	BeginningReached
};

class FSM
{
private:
	fsm_states currentState, hightState;
	FestoProcessAccess *process;
	Plugin* plugin;
public:
	FSM(FestoProcessAccess *process, Plugin* plugin);
	~FSM();
	void eval();
private:
	void evalEvents();
	void evalState();
private:
	void blinkGreen();
	void blinkRed();
	bool checkHight();
};

#endif	/* FSM_H */

