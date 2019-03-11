#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>


int main(){
	char *a;
	a = "a";
	char b = 'b';
	char c = 'c';
	char d = 'd';
	char e = 'e';
	char f = 'f';
	char *s;
	s = (char *) malloc(0);
	strcpy(s, "g");
	printf("String = %s,  Address = %u\n", s, s);
	printf("%s\n", s);
	strcat(s, a);
	printf("String = %s,  Address = %u\n", s, s);
	printf("%s\n", s);
}

