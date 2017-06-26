/* 
 * File:   main.cpp
 * Author: Lehmann
 *
 * Created on 8. November 2013, 16:24
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>
//#include <cstdio>

#include <windows.h>

#include "factory.h"
#include "hightMeasure.h"
#include "FestoProcessAccess.h"
#include "FestoProcessAccessSim.h"
using namespace std;

/*
 * 
 */
int main(int argc, char** argv)
{
	bool run = true; // set this variable to false whilst debugging to end program.
//    FSMFactory factory;
//
//    FSM* fsm = factory.createFSM();
	std::cout << "test";
	puts("Putest");
	printf("printf");

	//fflush(stdout);
	FestoProcessAccessSim* processAcc = new FestoProcessAccessSim();

	FSM* fsm = new FSM(processAcc, new HightMeasure(processAcc));
	// Start Processing
//	while (fsm != NULL && run)
//	{
//		fsm->eval();
//		fflush(stdout);
//		Sleep(1000);
//	}

	delete fsm;

	puts("!!!Hello World!Test!!"); /* prints !!!Hello World!!! */

	ifstream file("Test.txt");
	ifstream
	if(file == NULL)
	{
		std::cout<<"file leer";
	}
	string str;
	getline(file, str);
	std::cout<< str << "\n";
	getline(file, str);
	std::cout<< str << "\n";

	string s;
	int a;
	stringstream sstream(str);

	sstream >> s >> a;
	std::cout << s << " " << a << "\n";


	return 0;
}

