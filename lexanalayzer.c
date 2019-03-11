#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define MAX 50



int isNumeric(const char *str)
{
    if (str == NULL || *str == '\0' || isspace(*str))
      return 0;
    
	char *ptr;
    strtod(str, &ptr);
    
    return *ptr == '\0';
}


int isKeyword(char charStream[])
{
	char keywords[32][10] = {"auto","break","case","char","const","continue","default",
							"do","double","else","enum","extern","float","for","goto",
							"if","int","long","register","return","short","signed",
							"sizeof","static","struct","switch","typedef","union",
							"unsigned","void","volatile","while"};
	int i, flag = 0;
	
	for(i = 0; i < 32; ++i)
	{
		if(strcmp(keywords[i], charStream) == 0)
		{
			flag = 1;
			break;
		}
	}
	
	return flag;
}

int main()
{
	char ch, charStream[15], arith[] = "+-*/%=()", other[] = "{};,[]<>";
	char oprtr[MAX];
	char* digit[5];
	char *operand;
	int o = 0, num = 0;
	int i,j=0;
	
	

	
	FILE *fp;
	
	fp = fopen("input.txt","r");
	
	if(fp == NULL){
		printf("(???) where's ur file i cant read it owo'\n");
		exit(0);
	}
	
	while((ch = fgetc(fp)) != EOF)
	{
   		for(i = 0; i < 6; ++i)
		{
   			if(ch == arith[i])
			{
   				//printf(" %c is OPERATOR\n", ch);
   				oprtr[o] = ch;
   				o++;
   				
   			}
   			else if (ch == other[i])
   			{
   				printf(" %c is an invalid input (SPECIAL SYMBOL). The program will terminate now. \n", ch);
   				exit(1);
   			}
   		}
   		
   		if(isalnum(ch))
		{
   			charStream[j++] = ch;
   		}
   		else if((ch == ' ' || ch == '\n') && (j != 0))
		{
   				charStream[j] = '\0';
   				j = 0;
   				
   				   				
   				if(isKeyword(charStream) == 1)
   				{
   					printf(" %s is an invalid input (KEYWORD). The program will terminate now. \n", charStream);
   					exit(1);
   					
   				}
   				else if(isNumeric(charStream) == 1)
   				{
   					printf(" %s is a NUMBER\n", charStream);
   					
   					for(i = 0; i < 5; i++)
					{
						digit[i] = (char*) malloc(5);
						strcpy(digit[i], charStream);
						num += strlen(digit[i]);
					}
					operand = (char*) malloc(num+1);
					strcpy(operand, digit[0]);
					
					printf(" Current digit in array: %s \n", operand);
					
					for(i = 0; i < 5; i++)
					{
						strcat(operand, ",");
						strcat(operand, digit[i]);
					}
   				}
   				else
   				{
   					printf(" %s is an invalid input (IDENTIFIER). The program will terminate now. \n", charStream);
   					exit(1);
   				}
   		}   		
	}
	
	
	oprtr[o] = '\0';
	printf("\n OPERATORS :: %s \n", oprtr);
	printf(" NUMBERS ::");
	printf(" %s", operand);
	
	
	
	
	fclose(fp);
	
	return 0;
}
