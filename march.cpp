#include "stdafx.h"
#include "march.h"



/* Funktion void checkForDoubles(vector<vector<MarchElement>> &Testspeicher, vector<MarchElement> &TestArea, int Speicherzaehler)
	Argumente: 
		Testspeicher
		TestArea
		Speicherzaehler
	
	R�ckgabetyp 
		-
	Die bereits gespeicherten Tests werden nacheinander mit dem letzten durchgef�hrten Test verglichen. 
	Wenn die Testumgebungen �bereinstimmen, wird in einem internen Zwischenspeicher (vector<bool> doubles) der entsprechende Wert auf True gesetzt.
	Nachdem die bereits gespeicherten Tests verglichen wurden, wird der zuletzt durchgef�hrte Test ebenfalls in Testspeicher abgespeichert.
	Wenn der Testspeicher mehr als einen Eintrag enth�lt, also nach dem Durchf�hren und Pr�fen des zweiten Tests wird die Funktion zum Kennzeichnen der Dubletten aufgerufen.
				
*/ 
void checkForDoubles(vector<vector<MarchElement>> &Testspeicher, vector<MarchElement> &TestArea, int Speicherzaehler) {
	vector<bool> doubles(Testspeicher.size());			
	for (int k = 0; k < Testspeicher.size(); k++) {			//k l�uft die bisher abgespeicherten Elemente ab
		doubles[k] = false;									//standardm��ig wird jeder Wert auf false gesetzt
		for (int l = 0; l < TestArea.size(); l++) {	//l�uft die Werte des aktuellen Speicherabbilds ab
			if (l == Speicherzaehler+1)continue;		//durch l==Speicherzaehler+1 wird sichergestellt, dass der aktuell getestete Eintrag keinen Einfluss auf die Kennzeichnung als Dubletten nimmt.
			if (TestArea[l].getValue() == Testspeicher[k][l].getValue()) {
				doubles[k] = true;
			}	//true-setzen wenn die Werte �bereinstimmen 
			if (TestArea[l].getValue() != Testspeicher[k][l].getValue()) {	
				doubles[k] = false;
				break;						//sobald ein Wert nicht �bereinstimmt, kann die aktuell zu vergleichende Testumgebung �bersprungen und die n�chste gepr�ft werden.
			}			
		}
	}		
	Testspeicher.push_back(TestArea);//Abspeichern des aktuell getesteten Bereichs
	if (Testspeicher.size() > 1)Zeichne_Dubletten(doubles);	//beim ersten Diagramm m�ssen keine Dubletten gezeichnet werden.

	return;
}
/*
Funktion bool MarchElement::checkOne()
	Argumente:
		keine
	Ausgabe:
		bool
	Diese Funktion pr�ft den Wert des MarchElements auf den Wert Eins.
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
Diese Funktion pr�ft den Wert des MarchElements auf den Wert Null.
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
Diese Funktion gibt den Wert des MarchElements zur�ck.
*/
int MarchElement::getValue() {
	return value;
}
/*
Funktion: Dekodertest zur �perpr�fung der richtigen Adressierung.
Input: (string direction, vector<string> &orderList, int j)
Output: string direction
1.Es wird geschaut ob ein Richtungswechsel statt gefunden hat.
2.Ob der erste Test R0 oder R1 ist, wenn ja ob in der letzten Anweisung des selben Test ein komplementaeres schreiben ist.
3.Bei dem March davor ob W0 oder W1 die letzte Anweisung und ob die erste Anweisung ein komplementaeres lesen dazu ist.

*/
string MarchTest::decodertest(string direction, vector<string> &orderList, int j) {
	bool found = false;
	bool err = false;
	string help1, help2; // baut die March strings f�r ausgabe
	if (direction == "" || direction == " ") {	
		return orderList[j];
	}
	else if (direction == orderList[j]) {
		return orderList[j];
	}
	else {
		if (orderList[j+1]== "R0")
		{
			for (int iii = j; iii != orderList.size() ; iii++)//L�uft den March von dem momentanen Punkt j aus hoch.
			{
				if ((orderList[iii] == "March"))	// gegenn n�chsten March laufen
				{
					if (orderList[iii-1] == "W1")		// Bedingung f�r Decodertest beim hoch laufend
					{
						for (int ii = j;ii != 1;ii--)//vom Momentanwert R�ckw�rtslaufen und nach W0 und R1 suchen
						{
							if ((orderList[ii] == "W1"))
							{
								help2 = " " + orderList[ii - 2] + help2;
								err = true;
								
							}
							else if ((err == false) && (orderList[ii] == "W0"))//erstes gefunde W0 
							{
								help2 = " " + orderList[ii - 2] + help2;
								found = true;
							}
							else if ((found == true) && (orderList[ii - 1] == "March"))//l�uft runter bis zum Anfang eines March
							{
								if ((orderList[ii] == "Ud") || orderList[ii + 1] != "R1")// zweite Bedingung f�r decodertest, dass komplement�re Einlesen des vorherigen Marchsuchen
								{
									help2 = " " + orderList[ii - 2] + help2;
									continue;
								}
								else if (orderList[ii]== orderList[j])	// beim runterlaufen auf die gleiche richtung gesto�en
								{
									return orderList[j];
								}
								else
								{
									std::cout << "\n\nDekodertest:\n" << endl;
									std::cout << help2 << endl;
									std::cout << help1 << "\n\n" << endl;
									return orderList[j];
								}
							}
							else
								if ((ii >= 0) && (orderList[ii-2] != "March"))
								{
									help2 = " " + orderList[ii - 2] + help2;
								}

						}
					}
					break;
				}
				// eigentlich das selbe wie oben nur das der zu testen March kein Nachfolger hat
				else if(iii == (orderList.size()-1)) { 
					if (orderList[iii] == "W1")			// Bedingung f�r Decodertest nach vorne laufend
					{
						help1 = help1 + " " + orderList[iii];
						//die selbe for schleife wie oben!!
							for (int ii = j;ii != 1;ii--)//vom Momentanwert R�ckw�rtslaufen und nach W0 suchen
							{
								if ((orderList[ii] == "W1"))
								{
									help2 = " " + orderList[ii - 2] + help2;
									err = true;
									
								}
								else if ((err == false) && (orderList[ii] == "W0"))
								{
									help2 = " " + orderList[ii-2]+help2;
									found = true;
								}
								else if ((found == true) && (orderList[ii - 1] == "March"))//l�uft runter bis zum Anfang eines March
								{
									if ((orderList[ii] == "Ud") || orderList[ii + 1] != "R1")
									{
										help2 = " " + orderList[ii - 2] + help2;
										continue;
									}
									else if (orderList[ii] == orderList[j])	// beim runterlaufen auf die gleiche richtung gesto�en
									{
										return orderList[j];
									}
									else
									{
										std::cout << "\n\nDekodertest:\n" << endl;
										std::cout << help2 << endl;
										std::cout << help1 << "\n\n" << endl;
										return orderList[j];
									}
								}
								else
									if ((ii >= 0) && (orderList[ii-2]!= "March"))
									{
										help2 = " " + orderList[ii - 2] + help2;
									}
								
							}
					}
					break;
				}
				else
					help1 = help1 + " " + orderList[iii];
			}
			return orderList[j];// f�r fehler die nicht agbefangen wurden
		}
		else if (orderList[j + 1] == "R1")	// Das gleiche wie oben nur f�r R1 und W1!!!!!
		{
			for (int iii = j; iii != orderList.size(); iii++)
			{
				if ((orderList[iii] == "March"))
				{
					if (orderList[iii-1] == "W0")		
					{
						for (int ii = j;ii != 1;ii--)//vom Momentanwert R�ckw�rtslaufen und nach W0 suchen
						{
							if ((orderList[ii] == "W0"))
							{
								help2 = " " + orderList[ii - 2] + help2;
								err = true;
								
							}
							else if ((err == false) && (orderList[ii] == "W1"))
							{
								help2 = " " + orderList[ii - 2] + help2;
								found = true;
							}
							else if ((found == true) && (orderList[ii - 1] == "March"))//l�uft runter bis zum Anfang eines March
							{
								if ((orderList[ii] == "Ud") || orderList[ii + 1] != "R0")
								{
									help2 = " " + orderList[ii - 2] + help2;
									continue;
								}
								else if (orderList[ii] == orderList[j])	// beim runterlaufen auf die gleiche richtung gesto�en
								{
									return orderList[j];
								}
								else
								{
									std::cout << "\n\nDekodertest:\n" << endl;
									std::cout << help2 << endl;
									std::cout << help1 << "\n\n" << endl;
									return orderList[j];
								}
							}
							else
								if ((ii >= 0) && (orderList[ii-2] != "March"))
								{
									help2 = " " + orderList[ii - 2] + help2;
								}

						}
					}
					break;
				}
				else if (iii == (orderList.size() - 1)) { 
					if (orderList[iii] == "W0")			
					{
						help1 = help1 + " " + orderList[iii];
						for (int ii = j;ii != 1;ii--)//vom Momentanwert R�ckw�rtslaufen und nach W0 suchen
						{
							if ((orderList[ii] == "W0"))
							{
								help2 = " " + orderList[ii - 2] + help2;
								err = true;
								
							}
							else if ((err == false) && (orderList[ii] == "W1"))
							{
								help2 = " " + orderList[ii - 2] + help2;
								found = true;
							}
							else if ((found == true) && (orderList[ii - 1] == "March"))//l�uft runter bis zum Anfang eines March
							{
								if ((orderList[ii] == "Ud") || orderList[ii + 1] != "R0")
								{
									help2 = " " + orderList[ii - 2] + help2;
									continue;
								}
								else if (orderList[ii] == orderList[j])	// beim runterlaufen auf die gleiche richtung gesto�en
								{
									return orderList[j];
								}
								else
								{
									std::cout << "\n\nDekodertest:\n" << endl;
									std::cout << help2 << endl;
									std::cout << help1 << "\n\n" << endl;
									return orderList[j];
								}
							}
							else
								if ((ii >= 0) && (orderList[ii-2] != "March"))
								{
									help2 = " " + orderList[ii - 2] + help2;
								}

						}
					}
					break;
				}
				else
					help1 = help1 + " " + orderList[iii];
			}
		
			return orderList[j];
		}
		else
		{
			return "Up";// deafault
		}

	}

}
/*
Funktion void MarchTest::RunTest(vector<string> orderList, int length)
	Argumente:
		orderList,
		length
	R�ckgabe
		void

	Diese Funktion f�hrt die im Argument orderList dargestellten March Tests durch. Hierbei wird ein Testbereich in der entsprechenden L�nge erzeugt und Element f�r Element durchlaufen.
	Bei jedem Element wird die orderList durchlaufen, allerdings wird der n�chste March Test erst durchgef�hrt(ein auszuwertendes "March" nur �berspr�ngen), wenn der gesamte Speicherbereich bereits getestet wurde.
	Ist dies nicht der Fall, wird der Befehlszaehler auf den ersten Befehl des aktuellen Tests zur�ckgesetzt. 
	Die Richtung wird zu Beginn jeder Operation bestimmt, je nachdem ob der aktuelle Test "UP" oder "DOWN" als Eintrag hat.
	Bei Beginn eines neuen March Tests wird in der GDE ein Zeilenumbruch erzeugt. 
	Bei Erreichen der 14. Stelle des Speichers wird die Testumgebung gezeichnet. 
*/

void MarchTest::RunTest(vector<string> orderList, int length) {
	
	bool Toggle_Next_Line = false;				//Kontrollvariable, die das Springen in eine neue Zeile steuert.
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
			else {	// Eignerblock f�r Lese und Schreibzugriffe, da sonst immer gezeichnet wird
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
						std::cout << "An der Stelle " << k << " befindet sich ein Fehler. Der aktuelle Befehl ist " << orderList[j] << " Hier wurde faelschlicherweise eine Null erwartet." << endl;
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