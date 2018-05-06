#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

/*char* march_test(string& OP1, string& OP2, string& OP3, string& OP4, string& direction = 'UD'){
	int *fieldtotest=NULL;
	
	if(*direction == 'Up'){
		do{
			if(*OP1 == 'W1'){
			}else if(*OP1 == 'W0')
			fieldtotest++;
		}while(fieldtotest!=NULL)
	}else if(*direction == 'Dn'){
		
	}else if(*direction == 'UD' || *direction != NULL){
		
	}
}
*/

class MarchElement
{
	public: 
	int value;
	
	bool checkZero();
	bool checkOne();
	void writeOne();
	void writeZero();
};

bool MarchElement::checkOne() {
return (this.value == 1);	
}

bool MarchElement::checkZero() {
return (this.value == 0);	
}

void MarchElement::writeOne() {
	this.value = 1;
}

void MarchElement::writeZero() {
	this.value = 0;
}


void main (){
	string direction;
	const int nOp;			//Nummer der Einzeloperationen pro Testwiederholung
	int length;				//legt Größe des Speicherbereichs fest.
	string orderList[nOp];	//Array, das die verschiedenen Operationen ('W1', 'W0', 'R0', 'R1') enthält.
	int i = 0;
	
	if(direction == 'Up'){
		int p = i;				//Indirekte Zugriffsvariable, die je nach Richtung bestimmt wird.
	}else if(direction == 'Dn'){
		int p = length - i;
	}else{
	}
				
	TestArea[length] = new MarchElement;
	
	for(i<length; i++;){
		for(int j=0; j<nOp; j++){
			switch (orderList[j]){
				case 'W1':
					TestArea[p].writeOne();
					break;
				case 'W0':
					TestArea[p].writeZero();
					break;
				case 'R0':
					TestArea[p].checkZero();
					break;
				case 'R1':
					TestArea[p].checkOne();
					break;
			}
		}
		j=0;
	}

}