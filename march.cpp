#include "stdafx.h"
#include "march.h"
using namespace std;


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
	bool Toggle_Next_Line = false;
	nMarch = orderList.size();
	j = 0;	//Nummer der Einzeloperationen pro Testwiederholung
	vector<MarchElement> TestArea(length);


	for (i = 0; i < length; ) {
		int n = 0;
		while (j<nMarch) {
			if (direction == "Up") {
				k = i;
			}
			else if (direction == "Dn") {
				k = (length - 1) - i;
			}

			if (orderList[j] == "March") {
				if (n > 0) {
					if (i < length - 1) {
						j = j - n;
						n = 0;
						i++;
					}
					else {
						Toggle_Next_Line = true;
						n = 0;
						j++;
						i = 0;
						break;
					}
				}
				else {
					j++;
				}

				continue;
			}
			else if (orderList[j] == "Up") {		// Decodertest

				if (direction == "") {
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
					
			}
			else if (orderList[j] == "Dn") {		// Decodertest
				if (direction == "") {
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

					
			}
			else {
				if (orderList[j] == "W0") {
					TestArea[k].writeZero();
					n++;
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
				if (k == 14) {
					if (Toggle_Next_Line) {
						Next_Line();
						Toggle_Next_Line = false;

					}

					Zeichne_Rechteck(TestArea, direction, orderList[j]);

				}
			}
			j++;
		}

		if (j >= nMarch) {
			j = j - n;
			n = 0;
			i++;
		}
	}

}

void main() {
	return;
}