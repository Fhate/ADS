// User.h : header file
//
// Das Benutzer interface.
/////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Parser.h"
#include "march.h"
#include <string>
#include <vector>
class MarchElement;
int NumLine;
vector<int> NumPerLine;
void Next_Line(int &NumLine);
void Zeichne_Dubletten(vector<bool> &doubles, vector<int> &NumPerLine);
void Zeichne_Rechteck(vector<MarchElement> &TestArea, string direction, string operation, vector<int> &NumPerLine, int &NumLine);
void user_main();		// Funktion in der der Benutzer seinen eigenen
					// Code programmieren kann.