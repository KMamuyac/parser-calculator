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

char * equation;
char token [150] = {NULL};

int parseEquation(){
	int result = parseDiff();
	if(*equation == '\0'){
		return result;
	}
	printf("\nError : unexpected input found %c\n", *equation);
	return 0;
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
			printf("Error : cannot divide by 0\n");
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
	equation = "-98*-1+-34--18/-5%(3--1)";
	printf("%s\n", equation);
	int result = parseEquation();
	printf("%d\n", result);
	return 0;
}
