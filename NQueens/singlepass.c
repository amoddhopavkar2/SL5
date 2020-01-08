#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
bool LTORG = false;
int symIndex = 0, lc = 0, litIndex = 0, lastLTORG = 0;

struct symTable {
	char sym[10];
	int address;
	int length;
}SYM[20];

struct mneTable {
	char mneName[10];
	int opcode;
	char type[3];
	int opcodeCount;
}MNE[20];

struct litTable {
	char lit[10];
	int address;
}LIT[20];

int length(char *s1) {
	int i = 0;
	while (s1[i] != '\0')
		i++;
	return i;
}

bool compare(char *s1, char *s2) {
	int i = 0;
	int l1 = length(s1);
	int l2 = length(s2);
	if (l1 == l2) {
		for (i=0; i<l1; i++) {
			if (s1[i] != s2[i])
				return false;
		}
	}
	else 
		return false;
	
	return true;
}

bool checkSym(char sym[10]) {
	int i = 0;
	bool check = compare(sym,'AREG') || compare(sym,'BREG') || compare(sym,'CREG') || compare(sym,'DREG');
	if (sym[0] == '=')
		return true;
	for (i=0; i<symIndex; i++) {
		if (compare(sym,SYM[i].sym) || check)
			return true;
	}
	return false;
}

void insertSymTable(char sym[10], int add, int len) {
	strcpy(SYM[symIndex].sym,sym);
	SYM[symIndex].address = add;
	SYM.[symIndex].length = len;
	symIndex++;
}

void main() {
	FILE *fp;
	int i = 0, count = 0;
	CreateMneTable();
}