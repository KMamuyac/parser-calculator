#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
 
int parseDiff();
int parseSum();
int parseMod();
int parseQuotient();
int parseProduct();
int parseFactor();
int parseEquation();
int parseDigits();

char * equation = NULL;
int result = 0;

int parseEquation(){
	int results = parseDiff();
	if(*equation == '\0'){
		return results;
	}
//	printf("\nError : unexpected input found %c\n", *equation);
	return results;
}

int parseDiff(){
	int diff1 = parseSum();
	while(*equation == '-'){
		++equation;
		if(*equation == '-'){
			++equation;
			int diff3 = parseSum();
			diff1 = diff1+diff3;
			return diff1;
		}
		int diff2 = parseSum();
		diff1 = diff1-diff2;
	}
	return diff1;
}

int parseSum(){
	int product1 = parseMod();
	while(*equation == '+'){
		++equation;
		if(*equation == '-'){
			++equation;
			int product3 = parseMod();
			product1 = product1-product3;
			return product1;
		}
		int product2 = parseMod();
		product1 = product1+product2;
	}
	return product1;
}

int parseMod(){
	int mod1 = parseQuotient();
	while(*equation == '%'){
		++equation;
		int mod2 = parseQuotient();
		if(mod2 == 0){
			printf("Error : undefined\n");
			return 0;
		}
		mod1 = mod1%mod2;
	}

	return mod1;
}

int parseQuotient(){
	int quo1 = parseProduct();
	while(*equation == '/'){
		++equation;
		if(*equation == '-'){
			++equation;
			int quo3 = parseProduct();
			quo3 = quo3 * -1;
			if(quo3 == 0){
				printf("Error : cannot divide by 0\n");
				return 0;
			}
			quo1 = quo1/quo3;
			return quo1;
		}
		int quo2 = parseProduct();
		if(quo2 == 0){
			printf("Error : cannot divide by 0\n");
			return 0;
		}
		quo1 = quo1/quo2;
	}

	return quo1;
}

int parseProduct(){
	int factor1 = parseFactor();
	while(*equation == '*'){
		++equation;
		if(*equation == '-'){
			++equation;
			int factor3 = parseFactor();
			factor1 = factor1*-factor3;
			return factor1;
		}
		int factor2 = parseFactor();
		factor1 = factor1*factor2;
	}
	return factor1;
}

int parseFactor(){
	if(*equation >= '0' && *equation <= '9'){
		return parseDigits();
	}
	else if(*equation == '('){
		while(*equation != ')'){
			++equation;
			int diff = parseDiff();
			++equation;
			return diff;
		}
	}
	else if(*equation == '-'){
		return -parseDigits();
	}
}

int parseDigits(){
	int number = 0;
	while(*equation >= '0' && *equation <= '9'){
		number = number * 10;
		number = number + *equation - '0';
		++equation;
	}
	return number;
}



 
int main(){
	char ch;
	FILE *fp;
	int i,j=0;
	
	int n = 0;
	char token[150] = {NULL};
	
	fp = fopen("input.txt","r");
	
	if(fp == NULL){
		printf("error while opening the file\n");
		exit(0);
	}
	
	while((ch = fgetc(fp)) != EOF){
   		if(ch != ' '){
   			token[n] = ch;
   			n++;
		}
		if(ch == '\n' ){
			equation = token;
//			printf("%s\n", equation);
			result = parseEquation();
			printf("%s = %d\n\n", token, result);
			memset(token, NULL, n);
			memset(equation, NULL, n);
			n = 0;
		}
		if(ch == EOF){
			equation = token;
			result = parseEquation();
			printf("%s = %d\n\n", token, result);
			memset(token, NULL, n);
			memset(equation, NULL, n);
			n = 0;
		}
	}

	
	fclose(fp);
	
	return 0;
}
