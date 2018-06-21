#pragma once

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include "User.h"
using namespace std;
class MarchElement
{
private:
	int value;
public:
	bool checkZero();
	bool checkOne();
	void writeOne();
	void writeZero();
	int getValue();
	};

void checkForDoubles(vector<vector<MarchElement>> &Testspeicher, vector<MarchElement> &TestArea, int Speicherzaehler);

class MarchTest {
public:
	int AnzahlTests;
	int nMarch;		//Anzahl der Operationen
	string direction = " ";
	int i, j, k;	//Laufvariablen für Schleifen

	MarchTest() {};
	void RunTest(vector<string> orderList, int length);		//orderList = array mit OPerationsbefehlen, length = Laenge des Bereichs
	string decodertest(string direction, vector<string> &orderList, int j);
};