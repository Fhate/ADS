
#include "stdafx.h"
#include "Parser.h"


using namespace std;

void CParser::RunTest(vector<string> orderList, int length,int laengeorderlist){
/*bool Toggle_Next_Line = false;				//Kontrollvariable, die das Springen in eine neue Zeile steuert.
nMarch = laengeorderlist;
AnzahlTests = 0;
j = 0;	//Nummer der Einzeloperationen pro Testwiederholung
vector<MarchElement> TestArea(length);		//Speicherbereich den der Test durchläuft
vector<vector<MarchElement>> Testspeicher;	//Hier werden die einzelnen Testumgebungen abgespeichert um sie auf Dubletten pruefen zu koennen.


for (i = 0; i < length; ) {
	int n = 0;					//Anzahl der Operationen(R/W) im aktuellen Marchtest, die bereits durchgelaufen sind.
	while (j<nMarch) {
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
						checkForDoubles(Testspeicher, TestArea, k - 1);
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
		else if ((atoi(orderList[i].c_str()) != 0)) {
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
		else {	// Eignerblock für Lese und Schreibzugriffe, da sonst immer gezeichnet wird
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
}*/
}




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
			if (l == Speicherzaehler + 1)continue;		//durch l==Speicherzaehler+1 wird sichergestellt, dass der aktuell getestete Eintrag keinen Einfluss auf die Kennzeichnung als Dubletten nimmt.
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
2.Ob der erste Test R0 oder R1 ist, wenn ja ob in der letzten Anweisung des selben Test ein komplementaeres schreiben ist.
3.Bei dem March davor ob W0 oder W1 die letzte Anweisung und ob die erste Anweisung ein komplementaeres lesen dazu ist.

*/
string CParser::decodertest(string direction, vector<string> &orderList, vector<string> &orderListalt,int j) {

	if (orderListalt.empty())
	{
		return orderList[j];
	}
	else if (orderList[j] == orderListalt[j]) {
		return orderList[j];
	}
	else {
		if (orderList[j+1] == "R0")
		{
			if (orderListalt[orderListalt.size()-1]=="W0")
			{
				if (orderListalt[j] != "Ud") {
					cout << " Decodertest " << endl;
					for (int i = 0; i < orderListalt.size(); i++)
					{
						cout << orderListalt[i] << " ";
					}
					cout << endl;
					for (int i = 0; i < orderList.size(); i++)
					{
						cout << orderList[i] << " ";
					}
					cout << endl;

					return orderList[j];
				}
				else {
					return orderList[j];
				}
			}
			else
			{
				return orderList[j];
			}		
		}
		else if (orderList[j+1] == "R1")	// Das gleiche wie oben nur für R1 und W1!!!!!
		{
			if (orderListalt[orderListalt.size()-1] == "W1")
			{
				if (orderListalt[j]!="Ud")
				{
					cout << " Decodertest " << endl;
					for (int i = 0; i < orderListalt.size(); i++)
					{
						cout << orderListalt[i] << " ";
					}
					cout << endl;
					for (int i = 0; i < orderList.size(); i++)
					{
						cout << orderList[i] << " ";
					}
					cout << endl;

					return orderList[j];
				}
				else
				{
					return orderList[j];
				}				
			}
			else
			{
				return orderList[j];
			}

		}
		else
		{
			printf("Fehler bei Decodertest");
			return "Up";// deafault
		}

	}

}




//-------------------------------------------------------------------------------------------------------------------------------------------
// Adds a character to the string value
void CParser::PushString(char c)
{
	yylval.s += c;
}
//------------------------------------------------------------------------
void CParser::Load_tokenentry(string str, int index)
{
	IP_Token_table[str] = index;
	IP_revToken_table[index] = str;
}
void CParser::IP_init_token_table()
{
	Load_tokenentry("STRING1", 3);
	Load_tokenentry("IDENTIFIER", 4);
	Load_tokenentry("INTEGER1", 5);

	int ii = TOKENSTART;
	Load_tokenentry("AND", ii++);
	Load_tokenentry("OR", ii++);
	Load_tokenentry("Begin", ii++);
	Load_tokenentry("End", ii++);
}
//------------------------------------------------------------------------

void CParser::pr_tokentable()
{

	typedef map<string, int>::const_iterator CI;
	const char* buf;

	printf("Symbol Table ---------------------------------------------\n");

	for (CI p = IP_Token_table.begin(); p != IP_Token_table.end(); ++p) {
		buf = p->first.c_str();
		printf(" key:%s", buf);
		printf(" val:%d\n", p->second);;
	}
}
//------------------------------------------------------------------------

int	CParser::yyparse(int length)
{	
	//--------------------------------------------------------------------------------------------
	bool Toggle_Next_Line = false;				//Kontrollvariable, die das Springen in eine neue Zeile steuert
	AnzahlTests = 0;
	j = 0;	//Nummer der Einzeloperationen pro Testwiederholung
	vector<MarchElement> TestArea(length);		//Speicherbereich den der Test durchläuft
	vector<vector<MarchElement>> Testspeicher;
	vector<string> orderList;
	vector<string> orderListalt;
	int alt = 0;
	//---------------------------------------------------------------------------------------------------
	int tok;
	if (prflag)fprintf(IP_List, "%5d ", (int)IP_LineNumber);
	/*
	*	Go parse things!
	*/
	while ((tok = yylex()) != 0) {
		//printf("%d ", tok);
		;
		if (tok == STRING1)
			//printf("%s %s ", IP_revToken_table[tok].c_str(), yylval.s.c_str())
			;
		else
			if (tok == INTEGER1) {
				//printf("%s %d ", IP_revToken_table[tok].c_str(), yylval.i);
				orderList.push_back(to_string(yylval.i));
			}
			else
				if (tok == IDENTIFIER) {
					//printf("%s %s ", IP_revToken_table[tok].c_str(), yylval.s.c_str());
						if (yylval.s=="March")
						{
							if (orderList.empty())
							{
								orderList.push_back(yylval.s);
							}
							else
							{
								orderListalt = orderList;
								orderList.clear();
								orderList.push_back(yylval.s);
							}
						}
						else
						{
							orderList.push_back(yylval.s);
						}
				}
				else
					if (tok >= TOKENSTART)
						//printf("%s ", IP_revToken_table[tok].c_str())
						;
						
					else {
						//printf("%c ", tok);
						if (tok == ';')
						{
							nMarch = orderList.size();
							j = 0;
							for (i = 0; i < length; ) {
								int n = 0;					//Anzahl der Operationen(R/W) im aktuellen Marchtest, die bereits durchgelaufen sind.
								while (j<nMarch) {
									if (direction == "Up") {
										k = i;					//Zugriffsvariable, die aus der Laufvariable i in Abhaengigkeit von direction berechnet wird.
									}
									else if (direction == "Dn") {
										k = (length - 1) - i;
									}

									if (orderList[j] == "March") {
										/*if (n > 0) {
											if (i < length - 1) {			//Aktueller Marchtest auf den Anfang zurueck, Reset von n
												if (k == 15) {
													//Neuer March Test wird in neuer Zeile dargestellt, wir laufen den Speicherbereich von Anfang an durch  
													checkForDoubles(Testspeicher, TestArea, k - 1);
													AnzahlTests++;
													Toggle_Next_Line = true;
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
										else {*/
										if (orderList.size()>4)
										{
											AnzahlTests++;
											Toggle_Next_Line = true;
										}

											j++;//Zugriff auf nächste Operation
										continue;
									}
									else if ((atoi(orderList[j].c_str()) != 0)) {
										j++;
										continue;
									}
									else if (orderList[j] == "Up") {
										direction = decodertest(direction, orderList, orderListalt,j);
									}
									else if (orderList[j] == "Dn") {
										direction = decodertest(direction, orderList, orderListalt,j);
									}
									else if (orderList[j] == "Ud") {
										direction = "Up";
									}
									else {	// Eignerblock für Lese und Schreibzugriffe, da sonst immer gezeichnet wird
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
					}						
		if (!prflag);
	}
	return 0;

}
//------------------------------------------------------------------------

/*
*	Parse Initfile:
*
*	  This builds the context tree and then calls the real parser.
*	It is passed two file streams, the first is where the input comes
*	from; the second is where error messages get printed.
*/
void CParser::InitParse(FILE *inp, FILE *err, FILE *lst)

{

	/*
	*	Set up the file state to something useful.
	*/
	IP_Input = inp;
	IP_Error = err;
	IP_List = lst;

	IP_LineNumber = 1;
	ugetflag = 0;
	/*
	*	Define both the enabled token and keyword strings.
	*/
	IP_init_token_table();
}
//------------------------------------------------------------------------

/*
*	yyerror:
*
*	  Standard error reporter, it prints out the passed string
*	preceeded by the current filename and line number.
*/
void CParser::yyerror(char *ers)

{
	fprintf(IP_Error, "line %d: %s\n", IP_LineNumber, ers);
}
//------------------------------------------------------------------------

int CParser::IP_MatchToken(string &tok)
{
	int retval;
	if (IP_Token_table.find(tok) != IP_Token_table.end()) {
		retval = (IP_Token_table[tok]);
	}
	else {
		retval = (0);
	}
	return retval;
}

//------------------------------------------------------------------------

/*
*	yylex:
*
*/
int CParser::yylex()
{
	//Locals
	int c;
	lexstate s;
	/*
	*	Keep on sucking up characters until we find something which
	*	explicitly forces us out of this function.
	*/
	for (s = L_START, yytext = ""; 1;) {
		c = Getc(IP_Input);
		yytext = yytext + (char)c;
		if (!ugetflag) {
			if (c != EOF)if (prflag)fprintf(IP_List, "%c", c);
		}
		else ugetflag = 0;
		switch (s) {
			//Starting state, look for something resembling a token.
		case L_START:
			if (isdigit(c)) {
				s = L_INT;
			}
			else if (isalpha(c) || c == '\\') {
				s = L_IDENT;
			}
			else if (isspace(c)) {
				if (c == '\n') {
					IP_LineNumber += 1;
					if (prflag)
						fprintf(IP_List, "%5d ", (int)IP_LineNumber);
				}
				yytext = "";
			}
			else if (c == '/') {
				yytext = "";
				s = L_COMMENT;
			}
			else if (c == '"') {
				s = L_STRING;
				yylval.s = "";
			}
			else if (c == EOF) {
				return ('\0');
			}
			else {
				return (c);
			}
			break;

		case L_COMMENT:
			if (c == '/')
				s = L_LINE_COMMENT;
			else	if (c == '*')
				s = L_TEXT_COMMENT;
			else {
				Ungetc(c);
				return('/');	/* its the division operator not a comment */
			}
			break;
		case L_LINE_COMMENT:
			if (c == '\n') {
				s = L_START;
				Ungetc(c);
			}
			yytext = "";
			break;
		case L_TEXT_COMMENT:
			if (c == '\n') {
				IP_LineNumber += 1;
			}
			else if (c == '*')
				s = L_END_TEXT_COMMENT;
			yytext = "";
			break;
		case L_END_TEXT_COMMENT:
			if (c == '/') {
				s = L_START;
			}
			else {
				s = L_TEXT_COMMENT;
			}
			yytext = "";
			break;

			/*
			*	Suck up the integer digits.
			*/
		case L_INT:
			if (isdigit(c)) {
				break;
			}
			else {
				Ungetc(c);
				yylval.s = yytext.substr(0, yytext.size() - 1);
				yylval.i = atoi(yylval.s.c_str());
				return (INTEGER1);
			}
			break;

			/*
			*	Grab an identifier, see if the current context enables
			*	it with a specific token value.
			*/

		case L_IDENT:
			if (isalpha(c) || isdigit(c) || c == '_')
				break;
			Ungetc(c);
			yytext = yytext.substr(0, yytext.size() - 1);
			yylval.s = yytext;
			if (c = IP_MatchToken(yytext)) {
				return (c);
			}
			else {
				return (IDENTIFIER);
			}

			/*
			*	Suck up string characters but once resolved they should
			*	be deposited in the string bucket because they can be
			*	arbitrarily long.
			*/
		case L_STRING2:
			s = L_STRING;
			if (c == '"') {// >\"< found
				PushString((char)c);
			}
			else {
				if (c == '\\') {// >\\< found
					PushString((char)c);
				}
				else {
					PushString((char)'\\');// >\x< found
					PushString((char)c);
				}
			}
			break;
		case L_STRING:
			if (c == '\n')
				IP_LineNumber += 1;
			else if (c == '\r')
				;
			else	if (c == '"' || c == EOF) {
				return (STRING1);
			}
			else	if (c == '\\') {
				s = L_STRING2;
				//PushString((char)c);
			}
			else
				PushString((char)c);
			break;
		default: printf("***Fatal Error*** Wrong case label in yylex\n");
		}
	}
}
//------------------------------------------------------------------------

/*int main(int argc, char* argv[])
{
FILE *inf;
char fistr[100];
printf("Enter filename:\n");
cin >> fistr;
inf = fopen(fistr,"r");
if(inf==NULL){
printf("Cannot open input file %s\n",fistr);
return 0;
}
CParser obj;
obj.InitParse(inf,stderr,stdout);
//obj.pr_tokentable();
obj.yyparse();

return 0;
}*/

