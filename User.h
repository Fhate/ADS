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

void Next_Line();
void Zeichne_Rechteck(vector<MarchElement>TestArea, string direction, string operation);
void user_main();		// Funktion in der der Benutzer seinen eigenen
					// Code programmieren kann.