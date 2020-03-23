/*
Name - Amod Dhopavkar
Roll No - 33304
Batch - K11
Problem Statement - RDP

The grammar on which recursive descent parsing is performed is:
E -> E+T | T
T -> T*F | F
F -> (E) | id


*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define SIZE 10

char input[SIZE];
int error, i;
void EFunc();
void EDashFunc();
void TFunc();
void TDashFunc();
void FFunc();

int main() {
    error = 0;
    i = 0;
    printf("\n---Recursive Descent Parser---\n");
    printf("\nEnter an expression:");
    gets(input);
    EFunc();
    if (strlen(input) == i && error == 0) {
        printf("\nACCEPTED...");
    }
    else {
        printf("\nREJECTED...");
    }
}

void EFunc() {
    TFunc();
    EDashFunc();
}

void EDashFunc() {
    if (input[i] == '+') {
        i++;
        TFunc();
        EDashFunc();
    }
}

void TFunc() {
    FFunc();
    TDashFunc();
}

void TDashFunc() {
    if (input[i] == '*') {
        i++;
        FFunc();
        TDashFunc();
    }
}

void FFunc() {
    if (isalnum(input[i]))i++;

    else if (input[i] == '(') {
        i++;
        EFunc();

        if (input[i] == ')') {
            i++;
        }

        else error = 1;
    }
    else error = 1;
}
