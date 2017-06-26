/*
 * FestoProcessAccessSim.h
 *
 *  Created on: 26.06.2017
 *      Author: Luis Nickel
 */

#ifndef SOURCES_ORIG_FESTOPROCESSACCESSSIM_H_
#define SOURCES_ORIG_FESTOPROCESSACCESSSIM_H_

#include "FestoProcessAccess.h"

#include <fstream>
#include <iostream>
#include <sstream>

class FestoProcessAccessSim:public FestoProcessAccess {

private:
	bool directionRight;
	bool directionLeft;
	bool directionSlowRight;
	bool directionSlowLeft;
	bool directionStop;
	bool junction;
	bool lightGreen;
	bool lightRed;
	bool lightYellow;
	bool startLED;
	bool resetLED;
	bool q1LED;
	bool q2LED;

	bool beginningSensor;
	bool hightSensor;
	bool metalDetector;
	bool metalDetected;
	bool slide;
	bool slidePassed;
	bool end;
	bool buttonStartPressed;
	bool buttonStartPositiveEdge;
	bool buttonStartNegativeEdge;
	bool buttonStopPressed;
	bool buttonResetPressed;
	bool buttonEmergencyActive;
	unsigned short hight;

	std::ifstream file, logFile;



public:
	FestoProcessAccessSim();
	~FestoProcessAccessSim();
    void updateInputs(void);
    void applyOutput(void);
public:
    virtual void driveRight(void);
    virtual void driveLeft(void);
    virtual void driveSlowRight(void);
    virtual void driveSlowLeft(void);
    virtual void driveStop(void);
    virtual void openJunction(void);
    virtual void closeJunction(void);
    virtual void lightGreenOn(void);
    virtual void lightGreenOff(void);
    virtual void lightYellowOn(void);
    virtual void lightYellowOff(void);
    virtual void lightRedOn(void);
    virtual void lightRedOff(void);
    virtual void turnLEDStartOn(void);
    virtual void turnLEDStartOff(void);
    virtual void turnLEDResetOn(void);
    virtual void turnLEDResetOff(void);
    virtual void turnLEDQ1On(void);
    virtual void turnLEDQ1Off(void);
    virtual void turnLEDQ2On(void);
    virtual void turnLEDQ2Off(void);
    virtual void turnAllOff(void);

    virtual bool isItemAtBeginning(void);
    virtual bool isItemAtHightSensor(void);
    virtual bool isItemAtMetalDetector(void);
    virtual bool isMetalDetected(void);
    virtual bool isJunctionOpen(void);
    virtual bool isItemAtSlide(void);
    virtual bool hasItemPassedSlide(void);
    virtual bool isItemAtEnd(void);
    virtual bool isButtonStartPressed(void);
    virtual bool isButtonStartPositiveEdge(void);
    virtual bool isButtonStartNegativeEdge(void);
    virtual bool isButtonStopPressed(void);
    virtual bool isButtonResetPressed(void);
    virtual bool isButtonEmergencyActive(void);
    virtual unsigned short getHight();

    virtual time_t timeCounter1s();
private:
    void logProcessData();
};


#endif /* SOURCES_ORIG_FESTOPROCESSACCESSSIM_H_ */
