/*
Assignment 3 : Pass II assembler
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
}SYMTAB;	

typedef struct LITTAB
{
	char literal[10];
	int address;
}LITTAB;

int pooltab[5];

int fill_symtab(SYMTAB symtab[]);
int fill_littab(LITTAB littab[]);
int fill_pooltab(int pooltab[]);

int main()
{
	SYMTAB symtab[10];
	LITTAB littab[10];
	
	FILE *fp1,*fp2;
	int stp=0,ltp=0,ptp=0,ptp_final=0,lc=0,temp=0,temp1=0,temp2=0,i=0,j=0;
	
	char buffer[32];
	char *b = buffer;
	char *token;
	char delimiter[]=" ";
	size_t bufsize = 32;
	size_t characters;

	stp = fill_symtab(symtab);
	ltp = fill_littab(littab);
	ptp_final = fill_pooltab(pooltab);
	if((fp1=fopen("inter_code.txt","r+"))==NULL) //opening input file
		printf("\nERROR : Input file cannot be opened");
	else
	{
		if((fp2=fopen("end_code.txt","w+"))==NULL) //opening output file
			printf("\nERROR : Output file cannot be opened");
		else
		{
			printf("\n\nInterpretation of intermediate code in process ...\n\n");

			while(!feof(fp1))
			{	
				characters = getline(&b,&bufsize,fp1);
				
				token=strtok(buffer,delimiter);

				lc=atoi(token);
				token=strtok(NULL,delimiter);

				if(strcmp(token,"IS")==0)
				{
					token=strtok(NULL,delimiter);
					fprintf(fp2,"%d + %s  ",lc,token);
					token=strtok(NULL,delimiter);
					if(token!=NULL)
					{
						if(token[0]=='R')
						{
							token=strtok(NULL,delimiter);
							fprintf(fp2,"%s  ",token);
						}
						token=strtok(NULL,delimiter);
						if(token!=NULL)
						{
							if(token[0]=='L')
							{
								token=strtok(NULL,delimiter);
								temp=atoi(token);
								temp1=littab[temp-1].address;
								fprintf(fp2,"%d \n",temp1);
							}
							else if(token[0]=='S')
							{
								token=strtok(NULL,delimiter);
								temp=atoi(token);
								temp1=symtab[temp-1].address;
								fprintf(fp2,"%d \n",temp1);
							}
						}
						else
							fprintf(fp2,"\n");
					}
					else
						fprintf(fp2,"\n");
					
				}
				else if(strcmp(token,"DL")==0)
				{
					token=strtok(NULL,delimiter);
					temp=atoi(token);
					fprintf(fp2,"%d  ",lc);
					if(temp==1)
					{
						token=strtok(NULL,delimiter);
						token=strtok(NULL,delimiter);
						fprintf(fp2,"%s \n",token);
					}
					else
						fprintf(fp2,"\n");
				}
				else if(strcmp(token,"AD")==0)
				{
					j=0;
					token=strtok(NULL,delimiter);
					temp=atoi(token);
					if(temp==3)
					{
						temp1=pooltab[ptp]-1;
						if(pooltab[ptp+1]!=-1)
						{
							temp2=pooltab[ptp+1]-1;
						}
						else
							temp2=ltp;

						for(i=temp1;i<temp2;i++)
						{
							fprintf(fp2,"%d  %s \n",lc+j,littab[i].literal);
							j++;
						}
						ptp++;
					}
					else if(temp==2)
					{
						temp1=pooltab[ptp]-1;
						if(pooltab[ptp+1]!=-1)
						{
							temp2=pooltab[ptp+1]-1;
						}
						else
							temp2=ltp;

						for(i=temp1;i<temp2;i++)
						{
							fprintf(fp2,"%d  %s \n",lc,littab[i].literal);
						}
						ptp++;
						
						printf("Machine code generated\n\n");
						fclose(fp1);
						fclose(fp2);
						return 0;
					}
				}
			}
		}
	}

	/*for(i = 0; i < stp; i++)
	{
		printf("%d\t%s\t%d\t%s\n",i+1, symtab[i].symbol, symtab[i].address, symtab[i].length);
	}
	printf("\n\n");
	for(i = 0; i < ltp; i++)
	{
		printf("%d\t%s\t%d\n",i+1, littab[i].literal, littab[i].address);
	}
	printf("\n\n");
	for(i = 0; i < ptp; i++)
	{
		printf("%d\t#%d\n", i+1,pooltab[i]);
	}
	printf("\n\n");	*/		
}

int fill_symtab(SYMTAB symtab[])
{
	FILE *f_sym;
	int stp = 0;
	if((f_sym = fopen("symtab.txt", "r+"))==NULL)
			printf("\nERROR : Output file cannot be opened");
	else
	{
		while(fscanf(f_sym, "%s %d %s", symtab[stp].symbol, &symtab[stp].address, symtab[stp].length) != EOF)
		{
			stp++;
		}
	}
	return stp;		
}

int fill_littab(LITTAB littab[])
{
	FILE *f_lit;
	int ltp = 0;
	if((f_lit = fopen("littab.txt", "r+"))==NULL)
			printf("\nERROR : Output file cannot be opened");
	else
	{
		while(fscanf(f_lit, "%s %d", littab[ltp].literal, &littab[ltp].address) != EOF)
		{
			ltp++;
		}
	}
	return ltp;		
}

int fill_pooltab(int pooltab[])
{
	FILE *f_pool;
	int ptp = 0;
	if((f_pool = fopen("pooltab.txt", "r+"))==NULL)
			printf("\nERROR : Output file cannot be opened");
	else
	{
		while(fscanf(f_pool, "%d", &pooltab[ptp]) != EOF)
		{
			ptp++;
		}
	}
	return ptp;		
}
