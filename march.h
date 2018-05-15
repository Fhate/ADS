#pragma once

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include "User.h"
using namespace std;
class MarchElement
{
public:
	int value;

	bool checkZero();
	bool checkOne();
	void writeOne();
	void writeZero();
	int getValue();
	};

vector<bool> checkForDoubles(vector<vector<MarchElement>> &Testspeicher, vector<MarchElement> &TestArea, int &Speicherzaehler);

class MarchTest {
public:
	int nMarch;		//Anzahl der Operationen
	string direction = " ";
	int i, j, k;	//Laufvariablen für Schleifen

	MarchTest() {};
	void RunTest(vector<string> orderList, int length);		//orderList = array mit OPerationsbefehlen, length = Laenge des Bereichs

};