// User.cpp : header file
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Parser.h"
#include "User.h"
#include "graphics\graphicfunctions.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>


#ifndef _USE_OLD_OSTREAMS
using namespace std;
#endif 
//DOUBLESIGNS wird benutzt um Dubletten zu kennzeichnen
const char DOUBLESIGNS[26] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y', };
COLORREF Colref[]={BLACK,RED,GREEN,BLUE,YELLOW,BROWN};
vector<int> AnzahlProZeile;
int ZeilenZahl;

/*
Struct für die anfang Dimensionen der Rechecken 
*/
struct _Anfang_Dim {
	int x1;
	int y1;
	int x2;
	int y2;
	int cframe=BLACK;
	int cfill = -1;
}anfang_dim;

void Zeichne_Dubletten(vector<vector<bool>> &doubles) {
	int dx = 150;	//Zurück auf die Anfangsposition
	int dy = 170;
	int Dublettenzaehler = 0; //Anzahl der Dubletten, die gezeichnet werden sollen.

	for (int i = 0; i < doubles.size(); i++) {		//i läuft die Zeilen entlang
		for (int j = 0; j < doubles[i].size(); j++) {
			if (doubles[i][j]) {		//für i=0 muss 0 eingetragen werden, damit die Reihen korrekt berechnet werden.
				//Dublette kennzeichnen, Farbiges X oder ähnliches, dabei verschieben um dx*j und dy*i
				//50 ist der Startwert, mit dem Durchlaufen der beiden Schleifen werden somit alle Darstellungen abgearbeitet.

				text(50 + 10 , 50 + dy*i - 10, 15, BLUE, 0, CENTER_ALIGN, "%c", DOUBLESIGNS[i], 11);
				text(50 + 10 , 50 + dy*j - 10, 15, BLUE, 0, CENTER_ALIGN, "%c", DOUBLESIGNS[i], 11);
			}
		}
	
	}


}

void Next_Line() {
//Funktion um die Startkoordinaten anzupassen beim Zeilenumbruch
	anfang_dim.y1 += 170;	//Versetzen um eine Zeile nach unten
	anfang_dim.x1 = 50;	//Zuruecksetzen auf Startpos
	AnzahlProZeile.push_back(0);	//Anlegen eines neuen Elements
	ZeilenZahl++;		//Mitzaehlen der Zeilen
}

/*
Funktion: Zeichne_Rechteck um die Umgebungmuster in der GDE graphisch zu darstellen
Input: Die Daten des Tests, Richtung des Tests, die ausgeführte Operation
Output: Keine Rückgabewert
1- Zeichnet die Umgebungsmuster und die Pfeilrichtung von den einzelnen Operationen von jedem Test
*/

void Zeichne_Rechteck(vector<MarchElement> &TestArea, string direction, string operation)
//Zeichnen des aktuell festgehaltenen Speicherbereichs, benötigt die Richtung, die aktuelle Operation sowie einen Zeiger auf den Speicherbereich als Eingangsparameter, ohne Rückgabewert
{
	int ii, jj, zz;


	if (anfang_dim.x1 > 1470) {
		Next_Line();
	}

	//Länge und Breite vom Rechteck anpassen
	anfang_dim.x2 = anfang_dim.x1 + 130;
	anfang_dim.y2 = anfang_dim.y1 + 130;
			
	text(anfang_dim.x1 + 50, anfang_dim.y1 - 20, 15, BLACK, 0, CENTER_ALIGN, "%s",operation.c_str(), 11);
			
	//Ausgabe der Umgebungsmuster 
	for (zz = 0;zz < 4;zz++) {
		for (jj = 0;jj < 5;jj++) {
				text(anfang_dim.x1 + 20 * jj + 25, anfang_dim.y1 + 10 + 25 * zz, 30, BLACK, 0, CENTER_ALIGN, "%d", TestArea[19-(jj + 4 * zz)], 11);
		}
	}


	if (direction=="Up") {
		//Pfeilrichtung up
			line(anfang_dim.x1 - 10, anfang_dim.y1 + 5, anfang_dim.x1 - 10, anfang_dim.y2 - 40, BLACK);
			line(anfang_dim.x1 - 15, anfang_dim.y1 + 5, anfang_dim.x1 - 5, anfang_dim.y1 + 5, BLACK);
			line(anfang_dim.x1 - 5, anfang_dim.y1 + 5, anfang_dim.x1 - 10, anfang_dim.y1, BLACK);
			line(anfang_dim.x1 - 10, anfang_dim.y1, anfang_dim.x1 - 15, anfang_dim.y1 + 5, BLACK);
			//Position während des Testdurchlaufs
			text(anfang_dim.x1 + 44, anfang_dim.y1 + 30, 35, RED, 0, CENTER_ALIGN, "_", 11);
				
	}
	else
	{
		//Pfeilrichtung down
			line(anfang_dim.x1 - 10, anfang_dim.y1, anfang_dim.x1 - 10, anfang_dim.y2 - 40, BLACK);
			line(anfang_dim.x1 - 15, anfang_dim.y2 - 40, anfang_dim.x1 - 5, anfang_dim.y2 - 40, BLACK);
			line(anfang_dim.x1 - 5, anfang_dim.y2 - 40, anfang_dim.x1 - 10, anfang_dim.y2 - 35, BLACK);
			line(anfang_dim.x1 - 10, anfang_dim.y2 - 35, anfang_dim.x1 - 15, anfang_dim.y2 - 40, BLACK);
			//Position während des Testdurchlaufs
			text(anfang_dim.x1 + 44, anfang_dim.y1 + 30, 35, RED, 0, CENTER_ALIGN, "_", 11);
	}
	
	//Zeichnen des Rahmens
	rectangle(anfang_dim.x1, anfang_dim.y1, anfang_dim.x2, anfang_dim.y2, anfang_dim.cframe, anfang_dim.cfill = -1);
			
	//Koordinaten erweitern
	anfang_dim.x1 = anfang_dim.x1 + 150;
	anfang_dim.x2 = anfang_dim.x2 + 150;
	AnzahlProZeile[ZeilenZahl]++;			//Tabellenanzahl pro Zeile um eins erhoehen
}


void Restart()
{
	int b, h, x, y;

	get_drawarea(&b, &h);

	textbox(b - 120, h - 40, b - 5, h - 5, 18, BLUE, GREY, GREY, SINGLE_LINE | VCENTER_ALIGN | CENTER_ALIGN, ("Restart"));
	updatescr();

	while ( 
		!((mouseclick(&x,&y) == 1) &&
		  ((x > b-120) && (x < b-5)) &&
		  ((y > h-40)  &&	(y < h-5))
		 )) {
		printf(".");
		if(StopProcess())break;
	};

	printf("######################################\n\n");
	clrscr();
	printf("######################################\n\n");
}


void user_main()
{

	//-----------------------------------------------------------------------------------
	vector <string> helpary;
	AnzahlProZeile = {0};
	ZeilenZahl = 0;
	//----------------------------------------------------------------------------------


	FILE *inf;
	char fistr[100];
	while(1) {
		printf("Enter filename:\n");
		cin >> fistr;
		inf = fopen(fistr, "r");
		if (inf == NULL) {
			printf("Cannot open input file %s\n", fistr);
			continue;
		}
		break;
	}
	
	
	

	int ww, hh;
	set_windowpos(0, 0, 1600, 1000);

	while (1) {								// Endlosschleife
		get_windowsize(&ww, &hh);
		set_drawarea(ww, hh);				// Setzen des Zeichenbereiches
		clrscr();
		
			anfang_dim.x1 = 50;
			anfang_dim.y1 = 50;
			//MarchTest MT;
			//MT.RunTest(helpary, 20);
			CParser obj;
			obj.InitParse(inf, stderr, stdout);
			obj.yyparse(20);
			cout << "Rechtecke gezeichnet !\n";
		
	

		Restart();						// Den "Restart"-Button malen und auf eine Aktivierung warten.
		if(StopProcess())break;
		
	}
}