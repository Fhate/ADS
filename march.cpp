#include "stdafx.h"
#include "march.h"
using namespace std;


vector<bool> checkForDoubles(vector<vector<MarchElement>> &Testspeicher, vector<MarchElement> &TestArea, int &Speicherzaehler) {
//Funktion pr�ft die aktuell zu zeichnende Umgebung auf Dubletten unter bereits gespeicherten Umgebungen, aktuell wird dabei jede Umgebung einzeln verglichen. 
	vector<bool> doubles(Testspeicher.size());			
	for (int k = 0; k < Testspeicher.size(); k++) {			//k l�uft die bisher abgespeicherten Elemente ab
		doubles[k] = true;									//standardm��ig wird jeder Wert auf TRUE gesetzt
		for (int l = 0; l < TestArea.size(); l++) {			//l�uft die Werte des aktuellen Speicherabbilds ab
			if (l == Speicherzaehler || TestArea[l].getValue() == Testspeicher[k][l].getValue()) {	//durch l==Speicherzaehler wird sichergestellt, dass der aktuell getestete Eintrag keinen Einfluss auf die Kennzeichnung als Dubletten nimmt.
				continue;				
			}
			else if (TestArea[l].getValue() != Testspeicher[k][l].getValue()) {
				doubles[k] = false;						//FALSE-setzen wenn die Werte nicht �bereinstimmen
			}
			
		}
	}
	return doubles;
}

bool MarchElement::checkOne() {
	return (value == 1);
}

bool MarchElement::checkZero() {
	return (value == 0);
}

void MarchElement::writeOne() {
	value = 1;
}

void MarchElement::writeZero() {
	value = 0;
}

int MarchElement::getValue() {
	return value;
}



void MarchTest::RunTest(vector<string> orderList, int length) {
	
	bool Toggle_Next_Line = false;				//KOntrollvariable, die das Springen in eine neue Zeile steuert.
	nMarch = orderList.size();
	j = 0;	//Nummer der Einzeloperationen pro Testwiederholung
	vector<MarchElement> TestArea(length);		//Speicherbereich den der Test durchl�uft
	vector<vector<MarchElement>> Testspeicher;	//Hier werden die einzelnen Testumgebungen abgespeichert um sie auf Dubletten pruefen zu koennen.
	

		for (i = 0; i < length; ) {
			int n = 0;					//Anzahl der Operationen(R/W) im aktuellen Marchtest, die bereits durchgelaufen sind.
			while(j<nMarch) {
			if (direction == "Up") {
				k = i;					//Zugriffsvariable, die aus der Laufvariable i in Abhaengigkeit von direction berechnet wird.
			}
			else if (direction == "Dn") {
				k = (length - 1) - i;
			}

			if (orderList[j] == "March") {
				if (n > 0) {
					if (i < length - 1) {			//Aktueller Marchtest auf den Anfang zurueck, Reset von n
						j = j - n;
						n = 0;
						i++;
					}
					else {							//Neuer March Test wird in neuer Zeile dargestellt, wir laufen den Speicherbereich von Anfang an durch  
						Toggle_Next_Line = true;
						n = 0;
						j++;
						i = 0;
						break;
					}
				}
				else {
					j++;				//Zugriff auf n�chste Operation
				}

				continue;	
			}
			else if (orderList[j] == "Up") {		// Decodertest
				direction = orderList[j];			//Einstellen der Richtung
				/*if (direction == "" || direction == " ") {
					direction = orderList[j];
				}
				else if (direction == orderList[j]) {
					direction = orderList[j];
				}
				else
					if ((j - 4) != 0) {
						if (orderList[j - 2] == "W0") {
							if (orderList[j + 1] == "R0")
								cout << "Decodertest" << endl;
							direction = orderList[j];
						}
						else if (orderList[j - 2] == "W1") {
							if (orderList[j + 1] == "R1")
								cout << "Decodertest" << endl;
							direction = orderList[j];
						}
					}
						else
							direction = orderList[j];
					*/
			}
			else if (orderList[j] == "Dn") {	
				direction = orderList[j];	//Richtungs�nderung
			/*	if (direction == "" || direction == " ") {			//Dekodertest
					direction = orderList[j];
				}
				else if (direction == orderList[j]) {
					direction = orderList[j];
				}
				else
					if ((j - 4) != 0) {
						if (orderList[j - 2] == "W0") {
							if (orderList[j + 1] == "R0") {
								cout << "Decodertest" << endl;
								direction = orderList[j];
							}
						}
						else if (orderList[j - 2] == "W1") {
							if (orderList[j + 1] == "R1") {
								cout << "Decodertest" << endl;
								direction = orderList[j];
							}
						}
					}
					else
						direction = orderList[j];
*/
					
			}
			else {
				if (orderList[j] == "W0") {
					TestArea[k].writeZero();
					n++;				//n hochzaehlen, um die Laenge des Testdurchlaufs zu z�hlen
				}
				else if (orderList[j] == "W1") {
					TestArea[k].writeOne();
					n++;
				}
				else if (orderList[j] == "R0") {
					n++;
					if (!TestArea[k].checkZero()) {
						cout << "An der Stelle " << k << " befindet sich ein Fehler(0)." << endl;
					}
				}
				else if (orderList[j] == "R1") {
					n++;
					if (!TestArea[k].checkOne()) {
						cout << "An der Stelle " << k << " befindet sich ein Fehler(1)." << endl;
					}
				}
				if (k == 14) {			//an der 14. Stelle wird der Speicherbereich gezeichnet. 
					if (Toggle_Next_Line) {
						Next_Line();				//Zeilenumbruch in GDE
						Toggle_Next_Line = false;

					}

					
					vector<bool> doubles = checkForDoubles(Testspeicher, TestArea, k);		//TRUE-FALSE Kennzeichnung der Dubletten, dabei wird der aktuelle Speicher mit allen vorherigen verglichen.
					Testspeicher.push_back(TestArea);		//Abspeichern des aktuell getesteten Bereichs
					Zeichne_Rechteck(TestArea, direction, orderList[j]);					//Zeichnen der Rechtecke in der GDE
					if (Testspeicher.size()>1)Zeichne_Dubletten(doubles);					//beim ersten Diagramm m�ssen keine Dubletten gezeichnet werden.
				}
			}
			j++;
		}

		if (j >= nMarch) {		//faengt Fehler ab 
			j = j - n;
			n = 0;
			i++;
		}
	}

}

void main() {
	return;
}