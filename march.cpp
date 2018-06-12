#include "stdafx.h"
#include "march.h"




void checkForDoubles(vector<vector<MarchElement>> &Testspeicher, vector<MarchElement> &TestArea, int Speicherzaehler) {
//Funktion prüft die aktuell zu zeichnende Umgebung auf Dubletten unter bereits gespeicherten Umgebungen, aktuell wird dabei jede Umgebung einzeln verglichen. 
	vector<bool> doubles(Testspeicher.size());			
	for (int k = 0; k < Testspeicher.size(); k++) {			//k läuft die bisher abgespeicherten Elemente ab
		doubles[k] = false;									//standardmäßig wird jeder Wert auf false gesetzt
		for (int l = 0; l < TestArea.size(); l++) {	//läuft die Werte des aktuellen Speicherabbilds ab
			if (l == Speicherzaehler+1)continue;
			if (TestArea[l].getValue() == Testspeicher[k][l].getValue()) {
				doubles[k] = true;
			}	//FALSE-setzen wenn die Werte nicht übereinstimmen (wird im allgemeinen so sein)
			if (TestArea[l].getValue() != Testspeicher[k][l].getValue()) {	//durch l==Speicherzaehler wird sichergestellt, dass der aktuell getestete Eintrag keinen Einfluss auf die Kennzeichnung als Dubletten nimmt.
				doubles[k] = false;
				break;
			}			
		}
	}		
	Testspeicher.push_back(TestArea);//Abspeichern des aktuell getesteten Bereichs
	if (Testspeicher.size() > 1)Zeichne_Dubletten(doubles);	//beim ersten Diagramm müssen keine Dubletten gezeichnet werden.

	return;
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
				if ((orderList[ii] == "W0"))//(orderList[ii]== "W0")&&(orderList[ii+1]=="March")
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
						std::cout << "An der Stelle " << k << " befindet sich ein Fehler(0)." << endl;
					}
				}
				else if (orderList[j] == "R1") {
					n++;
					if (!TestArea[k].checkOne()) {
						std::cout << "An der Stelle " << k << " befindet sich ein Fehler(1)." << endl;
					}
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