#pragma once

#ifndef _Parser_H
#define _Parser_H
// Parser.h : Zureinbundung von Lexan in GDE
//
// In diesem Header-File sind alle Lexan funktionen, die der Benutzer
// zur Programmierung verwenden kann deklariert.
//
/////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#pragma warning(disable:4786)
//#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <cstdlib>
#include <iostream>
#include "User.h"

using namespace std;

#define	Getc(s)			getc(s)
#define	Ungetc(c)		{ungetc(c,IP_Input); ugetflag=1;}

enum lexstate {
	L_START, L_INT, L_IDENT, L_STRING, L_STRING2,
	L_COMMENT, L_TEXT_COMMENT, L_LINE_COMMENT, L_END_TEXT_COMMENT
};

const int STRING1 = 3;
const int IDENTIFIER = 4;
const int INTEGER1 = 5;
const int TOKENSTART = 300;



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


class CParser
{
public:
	//---------------------------------------------------------------
	int AnzahlTests;
	int nMarch;		//Anzahl der Operationen
	string direction = " ";
	int i, j, k;	//Laufvariablen für Schleifen

	string decodertest(string direction, vector<string> &orderList, vector<string> &orderListalt,int j);
	
	//---------------------------------------------------------------

	string yytext;								//input buffer
	struct tyylval {								//value return
		string s;								//structure
		int i;
	}yylval;
	FILE *IP_Input;								//Input File
	FILE *IP_Error;								//Error Output
	FILE *IP_List;								//List Output
	int  IP_LineNumber;							//Line counter
	int ugetflag;								//checks ungets
	int prflag;									//controls printing
	map<string, int> IP_Token_table;				//Tokendefinitions
	map<int, string> IP_revToken_table;			//reverse Tokendefinitions


	int CParser::yylex();						//lexial analyser
	void CParser::yyerror(char *ers);			//error reporter
	int CParser::IP_MatchToken(string &tok);	//checks the token
	void CParser::InitParse(FILE *inp, FILE *err, FILE *lst);
	int	CParser::yyparse(int length);						//parser
	void CParser::pr_tokentable();				//test output for tokens
	void CParser::IP_init_token_table();		//loads the tokens
	void CParser::Load_tokenentry(string str, int index);//load one token
	void CParser::PushString(char c);			//Used for dtring assembly
	CParser() { IP_LineNumber = 1;ugetflag = 0;prflag = 0; };	//Constructor

};


void checkForDoubles(vector<vector<MarchElement>> &Testspeicher);
void Next_Line();
void Zeichne_Dubletten(vector<vector<bool>> &doubles);
void Zeichne_Rechteck(vector<MarchElement> &TestArea, string direction, string operation);

#endif