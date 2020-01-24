/*
Assignment 2 : Pass I assembler
Author : 33304
Date : 24/12/19
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct SYMTAB
{
	char symbol[10];
	int address;
	char length[5];
	//int size;
}SYMTAB;

typedef struct LITTAB
{
	char literal[10];
	int address;
}LITTAB;

int pooltab[5];

typedef struct MOT
{
	char mn_code[10];
	int mac_code;
	char class[4];
	int length;
	int chain;
}MOT;

void init_mot(MOT mot[21]);
int check_symtab(char token[], int *stp, SYMTAB symtab[], int lc);
int allocate_symbol(char token[], int stp, SYMTAB symtab[], int lc);
int check_littab(char token[], int *ltp, int ptp, LITTAB symtab[], int lc);
int check_mot(char token[], MOT mot[]);

int main()
{
	SYMTAB symtab[10];
	LITTAB littab[10];
	MOT mot[21];

	int lc=0, ptp=0, ltp=0, stp=0, rc=0, temp, temp2, temp3;
	pooltab[0]=1;

	char line[50], ch;
	char areg[5];
	char breg[5];
	char creg[5];
	char dreg[5];
	FILE *fp1, *fp2, *f_sym, *f_lit, *f_pool;
	char buffer[32];
	char *b = buffer;
	size_t bufsize = 30;
	size_t characters;
	init_mot(mot);
	char delimeter[] = " ";
	char *token;
	char temp_token[20];
	char temp_label[20];
	int i;
	strcpy(areg, "R 1 ");
	strcpy(breg, "R 2 ");
	strcpy(creg, "R 3 ");
	strcpy(dreg, "R 4 ");

	for(i = 0; i < 10; i++)
	{
		strcpy(symtab[i].length,"-");
	}
	if((fp1=fopen("input.txt","r+"))==NULL)
		printf("\nERROR : Input file cannot be opened");
	else
	{
		if((fp2=fopen("inter_code.txt","w+"))==NULL)
			printf("\nERROR : Output file cannot be opened");
		else
		{
			printf("\n\nInterpretation of input file in process ...\n");
			while(!feof(fp1))
			{
				characters = getline(&b,&bufsize,fp1);
				//b = replace_multi_space_with_single_space(b);
				//printf("%s \n",buffer);

				/* get the first token */
				token = strtok(buffer, delimeter);
				i = check_mot(token, mot);
				if(i != -1) //first token is mnemonic
				{
					fprintf(fp2, "%d ", lc);
					fprintf(fp2, "%s ", mot[i].class);
					fprintf(fp2, "%d ", mot[i].mac_code);
					if(strcmp(mot[i].class, "AD") == 0)
					{
						if(strcmp(mot[i].mn_code, "START") == 0)
						{
							token = strtok(NULL, delimeter);
							lc = atoi(token);
							fprintf(fp2, "C %d ", lc);
						}
						else if(strcmp(mot[i].mn_code, "ORIGIN") == 0)
						{
							token = strtok(NULL, delimeter);
							if((int)token[0] < 58) // if op1 is only a number i.e 200
								lc = atoi(token);
							else // if op1 is alphanumeric i.e A+1
							{
								temp = check_symtab(token, &stp, symtab, lc);
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
						else if(strcmp(mot[i].mn_code, "END") == 0)
						{
							for(temp = pooltab[ptp]-1; temp < ltp; temp++)
							{
								littab[temp].address = lc;
								lc++;
							}
							ptp++;
							pooltab[ptp] = ltp+1;
							printf("\n\n");
							if((f_sym=fopen("symtab.txt","w+"))==NULL)
								printf("\nERROR : Output file cannot be opened");
							else
							{
								printf("==============SYMTAB============\n");
								for(i = 0; i < stp; i++)
								{
									fprintf(f_sym, "%s %d %s\n", symtab[i].symbol, symtab[i].address, symtab[i].length);
									printf("%d\t%s\t%d\t%s\n",i+1, symtab[i].symbol, symtab[i].address, symtab[i].length);
								}
								printf("\n\n");
							}
							if((f_lit=fopen("littab.txt","w+"))==NULL)
								printf("\nERROR : Output file cannot be opened");
							else
							{
								printf("==============LITTAB============\n");
								for(i = 0; i < ltp; i++)
								{
									fprintf(f_lit, "%s %d\n", littab[i].literal, littab[i].address);
									printf("%d\t%s\t%d\n",i+1, littab[i].literal, littab[i].address);
								}
								printf("\n\n");
							}

							if((f_pool=fopen("pooltab.txt","w+"))==NULL)
								printf("\nERROR : Output file cannot be opened");
							else
							{
								printf("=============POOLTAB============\n");
								for(i = 0; i < ptp; i++)
								{
									fprintf(f_pool ,"%d\n",pooltab[i]);
									printf("%d\t#%d\n", i+1,pooltab[i]);
								}
								printf("\n\n");
							}
							return 0;
						}
						else if(strcmp(mot[i].mn_code, "LTORG") == 0)
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
						if(strcmp(token,"STOP")!=0)
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
								temp = check_symtab(token, &stp, symtab, lc);
								fprintf(fp2, "S %d", temp+1);
							}
							token = strtok(NULL, delimeter);
							if(token[0] == '=')
							{
								temp = check_littab(token, &ltp, ptp, littab, lc);
								fprintf(fp2, "L %d", temp+1);
							}
							else
							{
								temp = check_symtab(token, &stp, symtab, lc);
								fprintf(fp2, "S %d", temp+1);
							}
						}
						lc++;
					}
					fprintf(fp2, "\n");
				}
				else // first token is label
				{
					if(allocate_symbol(token, stp, symtab, lc) == 0)
					{
						strcpy(symtab[stp].symbol, token);
						symtab[stp].address = lc;
						stp++;
					}
					strcpy(temp_label, token);
					token = strtok(NULL, delimeter);
					i = check_mot(token, mot);
					if(i == -1)
					{
						printf("Error in input\n");
					}
					fprintf(fp2, "%d ", lc);
					fprintf(fp2, "%s ", mot[i].class);
					fprintf(fp2, "%d ", mot[i].mac_code);
					if(strcmp(mot[i].class, "AD") == 0)
					{
						if(strcmp(mot[i].mn_code, "START") == 0)
						{
							token = strtok(NULL, delimeter);
							lc = atoi(token);
							fprintf(fp2, "C %d ", lc);
							fprintf(fp2, "\n");
						}
						else if(strcmp(mot[i].mn_code, "ORIGIN") == 0)
						{
							token = strtok(NULL, delimeter);
							if((int)token[0] < 58) // if op1 is only a number i.e 200
								lc = atoi(token);
							else // if op1 is alphanumeric i.e A+1
							{
								temp = check_symtab(token, &stp, symtab, lc);
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
						else if(strcmp(mot[i].mn_code, "END") == 0)
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
						else if(strcmp(mot[i].mn_code, "LTORG") == 0)
						{
							for(temp = pooltab[ptp]-1; temp < ltp; temp++)
							{
								littab[temp].address = lc;
								lc++;
							}
							ptp++;
							pooltab[ptp] = ltp+1;
							fprintf(fp2, "\n");

							fprintf(fp2, );
						}
						else if(strcmp(mot[i].mn_code, "EQU") == 0)
						{
							token = strtok(NULL, delimeter);
							if((int)token[0] < 58) // if op1 is only a number i.e 200
								temp3 = atoi(token);
							else // if op1 is alphanumeric i.e A+1
							{
								temp = check_symtab(token, &stp, symtab, lc);
								temp2 = symtab[temp].address;
								temp3 = check_symtab(temp_label, &stp, symtab, lc);
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
								temp2 = check_symtab(token, &stp, symtab, lc);
								symtab[temp2].address = temp3;*/
							}
							fprintf(fp2, "\n");
						}
					}
					else if(strcmp(mot[i].class, "IS") == 0)
					{
						if(strcmp(token,"STOP")!=0)
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
									temp = check_symtab(token, &stp, symtab, lc);
									fprintf(fp2, "S %d", temp+1);
								}
							}
							token = strtok(NULL, delimeter);
							if(token != NULL)
							{
								if(token[0] == '=')
								{
									temp = check_littab(token, &ltp, ptp, littab, lc);
									fprintf(fp2, "L %d", temp+1);
								}
								else
								{
									temp = check_symtab(token, &stp, symtab, lc);
									fprintf(fp2, "S %d", temp+1);
								}
							}
						}
						lc++;
						fprintf(fp2, "\n");
					}
					else if(strcmp(mot[i].class, "DL") == 0)
					{
						if(strcmp(mot[i].mn_code, "DS") == 0)
						{
							token = strtok(NULL, delimeter);
							temp2 = check_symtab(temp_label, &stp, symtab, lc);
							strcpy(symtab[temp2].length, token);
							temp = atoi(token);
							lc += temp;
							fprintf(fp2, "C %d\n", temp);
						}
						else if(strcmp(mot[i].mn_code, "DC") == 0)
						{
							token = strtok(NULL, delimeter);
							temp2 = check_symtab(temp_label, &stp, symtab, lc);
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

void init_mot(MOT mot[21])
{
	int i;
	for(i=0;i<21;i++)
	{
		mot[i].length=2;
		strcpy(mot[i].class,"IS");
		mot[i].chain=-1;
	}

	strcpy(mot[0].mn_code,"ADD");
	mot[0].mac_code=1;

	strcpy(mot[1].mn_code,"BC");
	mot[1].mac_code=7;

	strcpy(mot[2].mn_code,"COMP");
	mot[2].mac_code=6;

	strcpy(mot[3].mn_code,"DIV");
	mot[3].mac_code=8;
	mot[3].chain=5;

	strcpy(mot[4].mn_code,"END");
	mot[4].mac_code=2;
	strcpy(mot[4].class,"AD");
	mot[4].chain=7;

	strcpy(mot[5].mn_code,"DC");
	mot[5].mac_code=1;
	strcpy(mot[5].class,"DL");
	mot[5].chain=6;

	strcpy(mot[6].mn_code,"DS");
	mot[6].mac_code=2;
	strcpy(mot[6].class,"DL");

	strcpy(mot[7].mn_code,"EQU");
	mot[7].mac_code=5;
	strcpy(mot[7].class,"AD");

	strcpy(mot[11].mn_code,"LTORG");
	mot[11].mac_code=3;
	strcpy(mot[11].class,"AD");

	strcpy(mot[12].mn_code,"MULT");
	mot[12].mac_code=3;
	mot[12].chain=13;

	strcpy(mot[13].mn_code,"MOVER");
	mot[13].mac_code=4;
	mot[13].chain=16;

	strcpy(mot[14].mn_code,"ORIGIN");
	mot[14].mac_code=4;
	strcpy(mot[14].class,"AD");

	strcpy(mot[15].mn_code,"PRINT");
	mot[15].mac_code=10;

	strcpy(mot[16].mn_code,"MOVEM");
	mot[16].mac_code=5;

	strcpy(mot[17].mn_code,"READ");
	mot[17].mac_code=9;

	strcpy(mot[18].mn_code,"STOP");
	mot[18].mac_code=0;
	mot[18].chain=19;

	strcpy(mot[19].mn_code,"SUB");
	mot[19].mac_code=2;
	mot[19].chain=20;

	strcpy(mot[20].mn_code,"START");
	mot[20].mac_code=1;
	strcpy(mot[20].class,"AD");
}

int allocate_symbol(char token[], int stp, SYMTAB symtab[], int lc)
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

int check_symtab(char token[], int *stp, SYMTAB symtab[], int lc)
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

int check_littab(char token[], int *ltp, int ptp,LITTAB littab[], int lc)
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

int check_mot(char token[], MOT mot[])
{
	int i;
	char firstChar;
	firstChar = token[0];
	i = (int)firstChar;
	i = i - 65;
	while(i != -1)
	{
		if(strcmp(mot[i].mn_code,token)==0)
			return i;
		else
		{
			i = mot[i].chain;
		}
	}
	return -1;
}
