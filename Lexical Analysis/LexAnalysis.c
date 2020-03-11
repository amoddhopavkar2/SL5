#include <stdio.h>
#include <stdlib.h>
#define SIZE 25

typedef struct TT {
	int index;
	char terminal[SIZE];
}TT;

typedef struct IT {
	int index;
	char identifier[SIZE];
}IT;

typedef struct LT {
	int index;
	char literal[SIZE];
}LT;

void initTT(TT terminalTable[SIZE]);

int main() {
	TT terminalTable[SIZE];
	char fileName[SIZE];
	FILE *f1;

	initTT(terminalTable);
	printf("\n---LEXICAL ANALYSIS OF A C PROGRAM---\n");
	printf("\nEnter the name of program:");
	scanf("%s",fileName);
	f1 = fopen(fileName,"r");
	fclose();
}

void fillUST(string &a) {
	FILE *op;
	string b, c, d;
	int lexIndex = 0;
	op = fopen("UST.txt","w");
	
	for (int i=0; i<a.size();i++) {
		if (isalpha(a[i]) > 0) {
			b += a[i];
		}

		else if (a[i] >= 48 && a[i] <= 57) {
			if (b.size() != 0) {
				fprintf(op,"%d\t\t%s\t\t""\n",lexIndex,b);
				lexIndex++;
				b.clear();
			}
		}

		else {
			d += a[i];
			if (a[i] == '' || a[i] == '\t') {
				//d.clear();
			}

			if (a[i] == '<' && (a[i+1] == '<' || a[i+1] == '=')) {
				d = a[i+1];
				lexIndex = retIndexTrm(d);
				fprintf("%d\t\t%s\t\tTERMINAL\n",lexIndex,d);
				//d.clear();
				i++;
			}

			else if (a[i] == '>' && (a[i+1] == '>' || a[i+1] == '=')) {
				d = a[i+1];
				lexIndex = retIndexTrm(d);
				fprintf("%d\t\t%s\t\tTERMINAL\n",lexIndex,d);
				//d.clear();
				i++;
			}

			else if (a[i] == '+' && (a[i+1] == '+' || a[i+1] == '=')) {
				d = a[i];
				lexIndex = retIndexTrm(d);
				fprintf("%d\t\t%s\t\tTERMINAL\n",lexIndex,d);
				//d.clear();
				i++;
			}

			else if(a[i] == '-' && (a[i+1] == '-' || a[i+1] == '=')) {
				d = a[i];
				lexIndex = retIndexTrm(d);
				fprintf("%d\t\t%s\t\tTERMINAL\n",lexIndex,d);
				//d.clear();
				i++;
			}

			if (b.size() != 0) {
				if (isKeyword(b)) {
					lexIndex = retIndexTrm(b);
					fprintf("%d\t\t%s\t\tTERMINAL\n",lexIndex,b);
				}
				else {
					putIdentifier(b);
					lexIndex = retIndexIdn(b);
					fprintf("%d\t\t%s\t\tSYMBOL\n",lexIndex,b);
				}
			}

			if(a[i] == ',' || a[i] == ';') {
				//d = a[i];
				lexIndex = retIndexTrm(d);
				fprintf("%d\t\t%s\t\tTERMINAL\n",lexIndex,d);
			}

			if (a[i] = '(' && a[i+1] = '"') {
				lexIndex = retIndexTrm(d);
				size_t found = a.find('"',i+2);
				fprintf("%d\t\t%s\t\tTERMINAL\n",lexIndex,d);

				if (found != string::npos) {
					
				}

			}
		}
	}
}

void initTT(TT terminalTable[SIZE]) {
	terminalTable[0].index = 1;
	strcpy(terminalTable[0].terminal,"#");

	terminalTable[1].index = 2;
	strcpy(terminalTable[1].terminal,"include");

	terminalTable[2].index = 3;
	strcpy(terminalTable[2].terminal,"<");

	terminalTable[3].index = 4;
	strcpy(terminalTable[3].terminal,"stdio.h");

	terminalTable[4].index = 5;
	strcpy(terminalTable[4].terminal,">");

	terminalTable[5].index = 6;
	strcpy(terminalTable[5].terminal,"stdlib.h");

	terminalTable[6].index = 7;
	strcpy(terminalTable[6].terminal,"void");

	terminalTable[7].index = 8;
	strcpy(terminalTable[7].terminal,"(");

	terminalTable[8].index = 9;
	strcpy(terminalTable[8].terminal,")");

	terminalTable[9].index = 10;
	strcpy(terminalTable[9].terminal,"{");

	terminalTable[10].index = 11;
	strcpy(terminalTable[10].terminal,"int");

	terminalTable[11].index = 12;
	strcpy(terminalTable[11].terminal,",");

	terminalTable[12].index = 13;
	strcpy(terminalTable[12].terminal,"=");

	terminalTable[13].index = 14;
	strcpy(terminalTable[13].terminal,";");

	terminalTable[14].index = 15;
	strcpy(terminalTable[14].terminal,"for");

	terminalTable[15].index = 16;
	strcpy(terminalTable[15].terminal,"<=");

	terminalTable[16].index = 17;
	strcpy(terminalTable[16].terminal,"++");

	terminalTable[17].index = 18;
	strcpy(terminalTable[17].terminal,"+");

	terminalTable[18].index = 19;
	strcpy(terminalTable[18].terminal,"*");

	terminalTable[19].index = 20;
	strcpy(terminalTable[19].terminal,"}");

	terminalTable[20].index = 21;
	strcpy(terminalTable[20].terminal,"if");

	terminalTable[21].index = 22;
	strcpy(terminalTable[21].terminal,"==");

	terminalTable[22].index = 23;
	strcpy(terminalTable[22].terminal,"printf");
}
