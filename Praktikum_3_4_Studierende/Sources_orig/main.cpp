/* 
 * File:   main.cpp
 * Author: Lehmann
 *
 * Created on 8. November 2013, 16:24
 */

#include <cstdlib>
#include <cstdio>

#include "factory.h"
#include "hightMeasure.h"
#include "FestoProcessAccess.h"
#include "FestoProcessAccessSim.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    bool run = true; // set this variable to false whilst debugging to end program.
//    FSMFactory factory;
//
//    FSM* fsm = factory.createFSM();

    FestoProcessAccess* processAcc = new FestoProcessAccessSim();

    FSM* fsm = new FSM(processAcc, new HightMeasure(processAcc));
    // Start Processing
    while (fsm != NULL && run) {
        fsm->eval();
    }

    delete fsm;

    puts("!!!Hello World!Test!!"); /* prints !!!Hello World!!! */
    return 0;
}

