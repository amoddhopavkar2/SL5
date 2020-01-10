// Name        : 2 SL-V Assembler
// Author      : Amod Dhopavkar

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct symTable
{
	char symbol[10];
	char length[5];
	int address;
}symTable;	

typedef struct literalTable
{
	char literal[10];
	int address;
}literalTable;

int pooltab[5];

typedef struct MOT
{
	char mneCode[10];
	char class[4];
	int code;
	int length;
	int chain;
}MOT;

void initMot(MOT mot[21]);
int checkSymTab(char token[], int *stp, symTable symtab[], int lc);
int allocateSymbol(char token[], int stp, symTable symtab[], int lc);
int checkLitTable(char token[], int *ltp, int ptp, literalTable symtab[], int lc);
int checkMot(char token[], MOT mot[]);

int main()
{
	symTable symtab[10];
	literalTable littab[10];
	MOT mot[21];
	
	int lc=0, ptp=0, ltp=0, stp=0, rc=0, temp, temp2, temp3;
	pooltab[0]=1;
	
	char line[50], ch;
	char areg[5], breg[5], creg[5], dreg[5];
	FILE *fp1, *fp2;
	char buffer[32];
	char *b = buffer;
	size_t bufsize = 30;
	size_t characters;
	
	initMot(mot);

	char delimeter[] = " ";
	char *token;
	char temp_token[20];
	char temp_label[20];
	int i;
	strcpy(areg, "R 1 ");
	strcpy(breg, "R 2 ");
	strcpy(creg, "R 3 ");
	strcpy(dreg, "R 4 ");
	if((fp1=fopen("input.txt","r+"))==NULL)
		printf("\nERROR!\nInput file cannot be opened...");
	else
	{
		if((fp2=fopen("interCode.txt","w+"))==NULL)
			printf("\nERROR!\nOutput file cannot be opened...");
		else
		{
			printf("\n\nInput file being interpreted...\n");	
			while(!feof(fp1))
			{
				characters = getline(&b,&bufsize,fp1);
				//b = replace_multi_space_with_single_space(b);
				//printf("%s \n",buffer);
				
				token = strtok(buffer, delimeter);	//get the first token
				i = checkMot(token, mot);
				if(i != -1) 						//first token is mnemonic
				{
					fprintf(fp2, "%d ", lc);
					fprintf(fp2, "%s ", mot[i].class);
					fprintf(fp2, "%d ", mot[i].code);
					if(strcmp(mot[i].class, "AD") == 0)
					{
						if(strcmp(mot[i].mneCode, "START") == 0) 
						{
							token = strtok(NULL, delimeter);
							lc = atoi(token);
							fprintf(fp2, "C %d ", lc);
						}
						else if(strcmp(mot[i].mneCode, "ORIGIN") == 0)
						{
							token = strtok(NULL, delimeter);
							if((int)token[0] < 58) 		// if op1 is only a number i.e 200
								lc = atoi(token);
							else 						// if op1 is alphanumeric i.e A+1
							{
								temp = checkSymTab(token, &stp, symtab, lc);
								lc = symtab[temp].address;
								/*temp = 0;
								while((token[temp] != '+') || (token[temp] != '-') || (token[temp] != '\0'))
								{
									temp_token[temp] = token[temp];
									temp++;
								}
								temp_token[temp] = '\0';
								for(temp2 = 0; temp2 < stp; temp2++)
								{
									if(strcmp(temp_token,symtab[temp2].symbol) == 0)
									{
										temp3 = symtab[temp2].address;
									}
									if(token[temp] == '+')
									{
										temp3 += (int)token[temp+1];
									}
									else if(token[temp] == '-')
									{
										temp3 -= (int)token[temp+1];
									}
								}	
								lc = temp3;*/
							}		
						}
						else if(strcmp(mot[i].mneCode, "END") == 0)
						{
							for(temp = pooltab[ptp]-1; temp < ltp; temp++)
							{
								littab[temp].address = lc;
								lc++;
							}
							ptp++;
							pooltab[ptp] = ltp+1;
							printf("\n\n--SYMBOL TABLE--\n\n");
							for(i = 0; i < stp; i++)
							{
								printf("%s\t%d\n",symtab[i].symbol, symtab[i].address);
							}
							printf("\n\n--LITERAL TABLE--\n\n");
							for(i = 0; i < ltp; i++)
							{
								printf("%s\t%d\n",littab[i].literal, littab[i].address);
							}
							printf("\n\n");
							return 0;
						} 
						else if(strcmp(mot[i].mneCode, "LTORG") == 0)
						{
							for(temp = pooltab[ptp]-1; temp < ltp; temp++)
							{
								littab[temp].address = lc;
								lc++;
							}
							ptp++;
							pooltab[ptp] = ltp+1;
						}
					}
					

					else if(strcmp(mot[i].class, "IS") == 0)
					{
						token = strtok(NULL, delimeter);
						if(strcmp(token, "AREG") == 0)
							fprintf(fp2, "%s", areg);
						else if(strcmp(token, "BREG") == 0)
							fprintf(fp2, "%s", breg);
						else if(strcmp(token, "CREG") == 0)
							fprintf(fp2, "%s", creg);	
						else if(strcmp(token, "DREG") == 0)
							fprintf(fp2, "%s", dreg);
						else
						{
							temp = checkSymTab(token, &stp, symtab, lc);
							fprintf(fp2, "S %d", temp+1);
						}	
						token = strtok(NULL, delimeter);
						if(token[0] == '=')
						{
							temp = checkLitTable(token, &ltp, ptp, littab, lc);
							fprintf(fp2, "L %d", temp+1);
						}
						else
						{
							temp = checkSymTab(token, &stp, symtab, lc);
							fprintf(fp2, "S %d", temp+1);
						}
						lc++;
					}
					fprintf(fp2, "\n");
				}
				else										 // first token is label
				{
					if(allocateSymbol(token, stp, symtab, lc) == 0)
					{
						strcpy(symtab[stp].symbol, token);
						symtab[stp].address = lc;
						stp++;
					}	
					strcpy(temp_label, token);
					token = strtok(NULL, delimeter);
					i = checkMot(token, mot);
					if(i == -1)
					{
						printf("Error in input\n");
					}
					fprintf(fp2, "%d ", lc);
					fprintf(fp2, "%s ", mot[i].class);
					fprintf(fp2, "%d ", mot[i].code);
					if(strcmp(mot[i].class, "AD") == 0)
					{
						if(strcmp(mot[i].mneCode, "START") == 0) 
						{
							token = strtok(NULL, delimeter);
							lc = atoi(token);
							fprintf(fp2, "C %d ", lc);
							fprintf(fp2, "\n");
						}
						else if(strcmp(mot[i].mneCode, "ORIGIN") == 0)
						{
							token = strtok(NULL, delimeter);
							if((int)token[0] < 58) // if op1 is only a number i.e 200
								lc = atoi(token);
							else // if op1 is alphanumeric i.e A+1
							{
								temp = checkSymTab(token, &stp, symtab, lc);
								lc = symtab[temp].address;
								/*temp = 0;
								while((token[temp] != '+') || (token[temp] != '-') || (token[temp] != '\0'))
								{
									temp_token[temp] = token[temp];
									temp++;
								}
								temp_token[temp] = '\0';
								for(temp2 = 0; temp2 < stp; temp2++)
								{
									if(strcmp(temp_token,symtab[temp2].symbol) == 0)
									{
										temp3 = symtab[temp2].address;
									}
									if(token[temp] == '+')
									{
										temp3 += (int)token[temp+1];
									}
									else if(token[temp] == '-')
									{
										temp3 -= (int)token[temp+1];
									}
								}	
								lc = temp3;*/
							}	
							fprintf(fp2, "\n");	
						}
						else if(strcmp(mot[i].mneCode, "END") == 0)
						{
							for(temp = pooltab[ptp]-1; temp < ltp; temp++)
							{
								littab[temp].address = lc;
								lc++;
							}
							ptp++;
							pooltab[ptp] = ltp+1;
							fprintf(fp2, "\n");
							return 0;
						} 
						else if(strcmp(mot[i].mneCode, "LTORG") == 0)
						{
							for(temp = pooltab[ptp]-1; temp < ltp; temp++)
							{
								littab[temp].address = lc;
								lc++;
							}
							ptp++;
							pooltab[ptp] = ltp+1;
							fprintf(fp2, "\n");
						}
						else if(strcmp(mot[i].mneCode, "EQU") == 0)
						{
							token = strtok(NULL, delimeter);
							if((int)token[0] < 58) // if op1 is only a number i.e 200
								temp3 = atoi(token);
							else // if op1 is alphanumeric i.e A+1
							{
								temp = checkSymTab(token, &stp, symtab, lc);
								temp2 = symtab[temp].address;
								temp3 = checkSymTab(temp_token, &stp, symtab, lc);
								symtab[temp3].address = temp2;
								/*temp = 0;
								while((token[temp] != '+') || (token[temp] != '-') || (token[temp] != '\0'))
								{
									temp_token[temp] = token[temp];
									temp++;
								}
								temp_token[temp] = '\0';
								for(temp2 = 0; temp2 < stp; temp2++)
								{
									if(strcmp(temp_token,symtab[temp2].symbol) == 0)
									{
										temp3 = symtab[temp2].address;
									}
									if(token[temp] == '+')
									{
										temp3 += (int)token[temp+1];
									}
									else if(token[temp] == '-')
									{
										temp3 -= (int)token[temp+1];
									}
								}	
								temp2 = checkSymTab(token, &stp, symtab, lc);
								symtab[temp2].address = temp3;*/
							}
							fprintf(fp2, "\n");		
						}
					}
					else if(strcmp(mot[i].class, "IS") == 0)
					{
						token = strtok(NULL, delimeter);
						if(token != NULL)
						{
							if(strcmp(token, "AREG") == 0)
								fprintf(fp2, "%s", areg);
							else if(strcmp(token, "BREG") == 0)
								fprintf(fp2, "%s", breg);
							else if(strcmp(token, "CREG") == 0)
								fprintf(fp2, "%s", creg);	
							else if(strcmp(token, "DREG") == 0)
								fprintf(fp2, "%s", dreg);
							else
							{
								temp = checkSymTab(token, &stp, symtab, lc);
								fprintf(fp2, "S %d", temp+1);
							}
						}	
						token = strtok(NULL, delimeter);
						if(token != NULL)
						{
							if(token[0] == '=')
							{
								temp = checkLitTable(token, &ltp, ptp, littab, lc);
								fprintf(fp2, "L %d", temp+1);
							}
							else
							{
								temp = checkSymTab(token, &stp, symtab, lc);
								fprintf(fp2, "S %d", temp+1);
							}	
						}
						lc++;
						fprintf(fp2, "\n");
					}
					else if(strcmp(mot[i].class, "DL") == 0)
					{
						if(strcmp(mot[i].mneCode, "DS") == 0) 
						{
							token = strtok(NULL, delimeter);
							temp2 = checkSymTab(temp_label, &stp, symtab, lc);
							strcpy(symtab[temp2].length, token);
							temp = atoi(token);
							lc += temp;
							fprintf(fp2, "C %d\n", temp);
						}
						else if(strcmp(mot[i].mneCode, "DC") == 0) 
						{
							token = strtok(NULL, delimeter);
							temp2 = checkSymTab(temp_label, &stp, symtab, lc);
							strcpy(symtab[temp2].length, token);
							lc++;
							fprintf(fp2, "C %s\n", token);
						}
					}	
				}	
			}
		}
		fclose(fp2);
	}
	fclose(fp1);
}

/*
char* replace_multi_space_with_single_space(char *str)
{
    char *dest = str;  
    while (*str != '\0')
    {
        while (*str == ' ' && *(str + 1) == ' ')
            str++;
       *dest++ = *str++;
    }
    *dest = '\0';
    return *dest;
}
*/

void initMot(MOT mot[21])
{
	int i;
	for(i=0;i<21;i++)
	{
		mot[i].length=2;
		strcpy(mot[i].class,"IS");
		mot[i].chain=-1;
	}
	
	strcpy(mot[0].mneCode,"ADD");
	mot[0].code=1;
	
	strcpy(mot[1].mneCode,"BC");
	mot[1].code=7;
	
	strcpy(mot[2].mneCode,"COMP");
	mot[2].code=6;
	
	strcpy(mot[3].mneCode,"DIV");
	mot[3].code=8;
	mot[3].chain=5;
	
	strcpy(mot[4].mneCode,"END");
	mot[4].code=2;
	strcpy(mot[4].class,"AD");
	mot[4].chain=7;
	
	strcpy(mot[5].mneCode,"DC");
	mot[5].code=1;
	strcpy(mot[5].class,"DL");
	mot[5].chain=6;
	
	strcpy(mot[6].mneCode,"DS");
	mot[6].code=2;
	strcpy(mot[6].class,"DL");
	
	strcpy(mot[7].mneCode,"EQU");
	mot[7].code=5;
	strcpy(mot[7].class,"AD");
	
	strcpy(mot[11].mneCode,"LTORG");
	mot[11].code=3;
	strcpy(mot[11].class,"AD");
	
	strcpy(mot[12].mneCode,"MULT");
	mot[12].code=3;
	mot[12].chain=13;
	
	strcpy(mot[13].mneCode,"MOVER");
	mot[13].code=4;
	mot[13].chain=16;
	
	strcpy(mot[14].mneCode,"ORIGIN");
	mot[14].code=4;
	strcpy(mot[14].class,"AD");
	
	strcpy(mot[15].mneCode,"PRINT");
	mot[15].code=10;
	
	strcpy(mot[16].mneCode,"MOVEM");
	mot[16].code=5;
	
	strcpy(mot[17].mneCode,"READ");
	mot[17].code=9;
	
	strcpy(mot[18].mneCode,"STOP");
	mot[18].code=0;
	mot[18].chain=19;
	
	strcpy(mot[19].mneCode,"SUB");
	mot[19].code=2;
	mot[19].chain=20;
	
	strcpy(mot[20].mneCode,"START");
	mot[20].code=1;
	strcpy(mot[20].class,"AD");
}

int allocateSymbol(char token[], int stp, symTable symtab[], int lc)
{
	int i;
	for(i = 0; i < stp; i++)
	{
		if(strcmp(symtab[i].symbol, token) == 0)
		{
			symtab[i].address = lc;
			return 1;
		}
	}
	return 0;
}

int checkSymTab(char token[], int *stp, symTable symtab[], int lc)
{
	int i;
	for(i = 0; i < *stp; i++)
	{
		if(strcmp(symtab[i].symbol, token) == 0)
		{
			return i;
		}
	}
	strcpy(symtab[i].symbol, token);
	(*stp)++;
	return i;
}

int checkLitTable(char token[], int *ltp, int ptp,literalTable littab[], int lc)
{
	int i;
	for(i = pooltab[ptp]-1; i < *ltp; i++)
	{
		if(strcmp(littab[i].literal, token) == 0)
		{
			return i;
		}
	}
	strcpy(littab[i].literal, token);
	(*ltp)++;
	return i;
}

int checkMot(char token[], MOT mot[])
{
	int i;
	char firstChar;
	firstChar = token[0];
	i = (int)firstChar;
	i = i - 65;
	while(i != -1)
	{
		if(strcmp(mot[i].mneCode,token)==0)
			return i;
		else
		{
			i = mot[i].chain;
		}
	}
	return -1;
}
