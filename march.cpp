#include "stdafx.h"
#include "march.h"
using namespace std;


vector<bool> checkForDoubles(vector<vector<MarchElement>> &Testspeicher, vector<MarchElement> &TestArea, int &Speicherzaehler, int &Befehlszaehler) {
//Funktion pr�ft die aktuell zu zeichnende Umgebung auf Dubletten unter bereits gespeicherten Umgebungen, aktuell wird dabei jede Umgebung einzeln verglichen. 
	vector<bool> doubles(Testspeicher.size());			
	for (int k = 0; k < Testspeicher.size(); k++) {			//k l�uft die bisher abgespeicherten Elemente ab
		doubles[k] = true;									//standardm��ig wird jeder Wert auf TRUE gesetzt
		for (int l = 0; l < TestArea.size(); l++) {	//l�uft die Werte des aktuellen Speicherabbilds ab
			if (TestArea[l].getValue() != Testspeicher[k][l].getValue()||k<Befehlszaehler) {
				doubles[k] = false;						//FALSE-setzen wenn die Werte nicht �bereinstimmen (wird im allgemeinen so sein)
			}else if (l == Speicherzaehler || TestArea[l].getValue() == Testspeicher[k][l].getValue()) {	//durch l==Speicherzaehler wird sichergestellt, dass der aktuell getestete Eintrag keinen Einfluss auf die Kennzeichnung als Dubletten nimmt.
				doubles[k] = true;
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
/*
Dekodertest zur �perpr�fung der richtigen Adressierung:
1.Es wird geschaut ob ein Richtungswechsel statt gefunden hat.
2.Ob der erste Test R0 oder R1 ist, wenn ja ob bei dem Vorherigen die letzte Anweisung ein W0 oder W1 war.

*/
string MarchTest::decodertest(string direction, vector<string> &orderList, int j) {
	bool found = false;
	if (direction == "" || direction == " ") {	
		return orderList[j];
	}
	else if (direction == orderList[j]) {
		return orderList[j];
	}
	else {
		if (orderList[j+1]== "R0")
		{
			for (int ii = j;ii!=0;ii--)
			{
				if ((orderList[ii]== "W0")&&(orderList[ii+1]=="March"))
				{
					found = true;
				}
				else if ((found==true)&&(orderList[ii-1]=="March"))
				{
					if (orderList[ii+1]=="Ud")
					{
						continue;
					}
					else
					{
						cout << "Dekodertest" << endl;
						string help1, help2;
						for (int iii = j; orderList[iii] != "March" ; iii++)
						{

							help1 = help1 + " " + orderList[iii];
							if (iii==orderList.size()-1)
							{
								break;
							}
						}
						for (int iii = ii; iii != j -1; iii++)
						{
							help2 = help2 + " " + orderList[iii];
						}
						cout << help2 << endl;
						cout << help1 << endl;
						return orderList[j];
					}
				}
				
			}
			return orderList[j];
		}
		else if (orderList[j + 1] == "R1")
		{
			for (int ii = j;ii != 0;ii--)
			{
				if ((orderList[ii] == "W1") && (orderList[ii + 1] == "March"))
				{
					found = true;
				}
				else if ((found == true) && (orderList[ii - 1] == "March"))
				{
					if (orderList[ii + 1] == "Ud")
					{
						continue;
					}
					else
					{
						cout << "Dekodertest" << endl;
						string help1, help2;
						for (int iii = j; orderList[iii] != "March"; iii++)
						{
							help1 = help1 + " " + orderList[iii];
							if (iii == orderList.size()-1)
							{
								break;
							}
						}
						for (int iii = ii; iii != j - 1; iii++)
						{
							help2 = help2 + " " + orderList[iii];
						}
						cout << help2 << endl;
						cout << help1 << endl;
						return orderList[j];
					}
				}

			}
			return orderList[j];
		}
		else
		{
			return orderList[j];
		}

	}

}


void MarchTest::RunTest(vector<string> orderList, int length) {
	
	bool Toggle_Next_Line = false;				//KOntrollvariable, die das Springen in eine neue Zeile steuert.
	nMarch = orderList.size();
	AnzahlTests = 0;
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
						AnzahlTests++;
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
			else if (orderList[j] == "Up") {	
				direction = decodertest(direction, orderList, j);					
			}
			else if (orderList[j] == "Dn") {	
				direction = decodertest(direction, orderList, j);					
			}
			else if (orderList[j] == "Ud") {
				direction = "Up";			
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

					
					vector<bool> doubles = checkForDoubles(Testspeicher, TestArea, k, n);		//TRUE-FALSE Kennzeichnung der Dubletten, dabei wird der aktuelle Speicher mit allen vorherigen verglichen.
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