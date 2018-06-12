#include "stdafx.h"
#include "march.h"



/* Funktion void checkForDoubles(vector<vector<MarchElement>> &Testspeicher, vector<MarchElement> &TestArea, int Speicherzaehler)
	Argumente: 
		Testspeicher
		TestArea
		Speicherzaehler
	
	Rückgabetyp 
		-
	Die bereits gespeicherten Tests werden nacheinander mit dem letzten durchgeführten Test verglichen. 
	Wenn die Testumgebungen übereinstimmen, wird in einem internen Zwischenspeicher (vector<bool> doubles) der entsprechende Wert auf True gesetzt.
	Nachdem die bereits gespeicherten Tests verglichen wurden, wird der zuletzt durchgeführte Test ebenfalls in Testspeicher abgespeichert.
	Wenn der Testspeicher mehr als einen Eintrag enthält, also nach dem Durchführen und Prüfen des zweiten Tests wird die Funktion zum Kennzeichnen der Dubletten aufgerufen.
				
*/ 
void checkForDoubles(vector<vector<MarchElement>> &Testspeicher, vector<MarchElement> &TestArea, int Speicherzaehler) {
	vector<bool> doubles(Testspeicher.size());			
	for (int k = 0; k < Testspeicher.size(); k++) {			//k läuft die bisher abgespeicherten Elemente ab
		doubles[k] = false;									//standardmäßig wird jeder Wert auf false gesetzt
		for (int l = 0; l < TestArea.size(); l++) {	//läuft die Werte des aktuellen Speicherabbilds ab
			if (l == Speicherzaehler+1)continue;		//durch l==Speicherzaehler^+1 wird sichergestellt, dass der aktuell getestete Eintrag keinen Einfluss auf die Kennzeichnung als Dubletten nimmt.
			if (TestArea[l].getValue() == Testspeicher[k][l].getValue()) {
				doubles[k] = true;
			}	//true-setzen wenn die Werte übereinstimmen 
			if (TestArea[l].getValue() != Testspeicher[k][l].getValue()) {	
				doubles[k] = false;
				break;						//sobald ein Wert nicht übereinstimmt, kann die aktuell zu vergleichende Testumgebung übersprungen und die nächste geprüft werden.
			}			
		}
	}		
	Testspeicher.push_back(TestArea);//Abspeichern des aktuell getesteten Bereichs
	if (Testspeicher.size() > 1)Zeichne_Dubletten(doubles);	//beim ersten Diagramm müssen keine Dubletten gezeichnet werden.

	return;
}
/*
Funktion bool MarchElement::checkOne()
	Argumente:
		keine
	Ausgabe:
		bool
	Diese Funktion prüft den Wert des MarchElements auf den Wert Eins.
*/
bool MarchElement::checkOne() {
	return (value == 1);
}

/*
Funktion bool MarchElement::checkZero()
Argumente:
keine
Ausgabe:
bool
Diese Funktion prüft den Wert des MarchElements auf den Wert Null.
*/
bool MarchElement::checkZero() {
	return (value == 0);
}

/*
Funktion void MarchElement::writeOne()
Argumente:
keine
Ausgabe:
void
Diese Funktion setzt den Wert des MarchElements auf den Wert Eins.
*/
void MarchElement::writeOne() {
	value = 1;
}

/*
Funktion void MarchElement::writeZero()
Argumente:
keine
Ausgabe:
void
Diese Funktion setzt den Wert des MarchElements auf den Wert Null.
*/
void MarchElement::writeZero() {
	value = 0;
}

/*
Funktion int MarchElement::getValue()
Argumente:
keine
Ausgabe:
int
Diese Funktion gibt den Wert des MarchElements zurück.
*/
int MarchElement::getValue() {
	return value;
}
/*
Funktion: Dekodertest zur Üperprüfung der richtigen Adressierung.
Input: (string direction, vector<string> &orderList, int j)
Output: string direction
1.Es wird geschaut ob ein Richtungswechsel statt gefunden hat.
2.Ob der erste Test R0 oder R1 ist, wenn ja ob bei dem Vorherigen die letzte SChreibanweisung ein W0 oder W1 war.

*/
string MarchTest::decodertest(string direction, vector<string> &orderList, int j) {
	bool found = false;
	bool err = false;
	if (direction == "" || direction == " ") {	
		return orderList[j];
	}
	else if (direction == orderList[j]) {
		return orderList[j];
	}
	else {
		if (orderList[j+1]== "R0")
		{
			for (int ii = j;ii!=0;ii--)//vom Momentanwert Rückwärtslaufen und nach W0 suchen
			{
				if ((orderList[ii]== "W1"))
				{
					err = true;
				}
				else if ((err==false) && (orderList[ii] == "W0")) 
				{
					found = true;
				}
				else if ((found==true)&&(orderList[ii-1]=="March"))//läuft runter bis zum Anfang eines March
				{
					if (orderList[ii+1]=="Ud")
					{
						continue;
					}
					else
					{
						std::cout << "Dekodertest" << endl;
						string help1, help2;
						for (int iii = j; orderList[iii] != "March" ; iii++)//Erzeugt den March von dem momentanen Punkt j aus.
						{

							help1 = help1 + " " + orderList[iii];
							if (iii==orderList.size()-1)//Abbruchbedingung für ende des Programms
							{
								break;
							}
						}
						for (int iii = ii; iii != j -1; iii++)//Erzeugt den March,der unterhalb momentanen Punkt j  ist.
						{
							help2 = help2 + " " + orderList[iii];
						}
						std::cout << help2 << endl;
						std::cout << help1 << endl;
						return orderList[j];
					}
				}
				
			}
			return orderList[j];
		}
		else if (orderList[j + 1] == "R1")	// Das gleiche wie oben nur für R1 und W1
		{
			for (int ii = j;ii != 0;ii--)
			{
				if ((orderList[ii] == "W0"))
				{
					err = true;
				}
				else if ((err == false) && (orderList[ii] == "W1"))
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
						std::cout << "Dekodertest" << endl;
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
						std::cout << help2 << endl;
						std::cout << help1 << endl;
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
/*
Funktion void MarchTest::RunTest(vector<string> orderList, int length)
	Argumente:
		orderList,
		length
	Rückgabe
		void

	Diese Funktion führt die im Argument orderList dargestellten March Tests durch. Hierbei wird ein Testbereich in der entsprechenden Länge erzeugt und Element für Element durchlaufen.
	Bei jedem Element wird die orderList durchlaufen, allerdings wird der nächste March Test erst durchgeführt(ein auszuwertendes "March" nur übersprüngen), wenn der gesamte Speicherbereich bereits getestet wurde.
	Ist dies nicht der Fall, wird der Befehlszaehler auf den ersten Befehl des aktuellen Tests zurückgesetzt. 
	Die Richtung wird zu Beginn jeder Operation bestimmt, je nachdem ob der aktuelle Test "UP" oder "DOWN" als Eintrag hat.
	Bei Beginn eines neuen March Tests wird in der GDE ein Zeilenumbruch erzeugt. 
	Bei Erreichen der 14. Stelle des Speichers wird die Testumgebung gezeichnet. 
*/

void MarchTest::RunTest(vector<string> orderList, int length) {
	
	bool Toggle_Next_Line = false;				//KOntrollvariable, die das Springen in eine neue Zeile steuert.
	nMarch = orderList.size();
	AnzahlTests = 0;
	j = 0;	//Nummer der Einzeloperationen pro Testwiederholung
	vector<MarchElement> TestArea(length);		//Speicherbereich den der Test durchläuft
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
						if (k == 15) {
							//Neuer March Test wird in neuer Zeile dargestellt, wir laufen den Speicherbereich von Anfang an durch  
							checkForDoubles(Testspeicher, TestArea, k-1);
						}
						j = j - n;
						n = 0;
						i++;
					}
					else {			
						AnzahlTests++;
						Toggle_Next_Line = true;
						n = 0;
						j++;
						i = 0;
						break;
					}
				}
				else {
					j++;				//Zugriff auf nächste Operation
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
					n++;				//n hochzaehlen, um die Laenge des Testdurchlaufs zu zählen
				}
				else if (orderList[j] == "W1") {
					TestArea[k].writeOne();
					n++;
				}
				else if (orderList[j] == "R0") {
					n++;
					if (!TestArea[k].checkZero()) {
						std::cout << "An der Stelle " << k << " befindet sich ein Fehler. Der aktuelle Befehl ist " << orderList[k] << " Hier wurde faelschlicherweise eine Null erwartet." << endl;
					}
				}
				else if (orderList[j] == "R1") {
					n++;
					if (!TestArea[k].checkOne()) {
						std::cout << "An der Stelle " << k << " befindet sich ein Fehler. Hier wurde faelschlicherweise eine Eins erwartet." << endl;
					}
				}
				else
				{	
					cout << "Der aktuelle Befehl " << orderList[j] << " kann nicht verarbeitet werden. ";
					continue;
				}
				if (k == 14) {			//an der 14. Stelle wird der Speicherbereich gezeichnet. 
					if (Toggle_Next_Line) {
						Next_Line();				//Zeilenumbruch in GDE
						Toggle_Next_Line = false;

					}

					
					
					Zeichne_Rechteck(TestArea, direction, orderList[j]);					//Zeichnen der Rechtecke in der GDE
					
				}
			}
			j++;
		}

		if (j >= nMarch) {		//faengt Fehler ab 
			if (k == 15) {
				checkForDoubles(Testspeicher, TestArea, k - 1);
			}
			j = j - n;
			n = 0;
			i++;
		}
	}

}

void main() {
	return;
}