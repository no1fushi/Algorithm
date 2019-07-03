#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF 256

typedef struct{
	char* state;
	char* symbol;
	int** stf;
	char first;
	char* fin;
} fa;

int input_int(){

	char str[32];
	int n;

	while(1){
		printf(">");
		fgets(str, sizeof(str), stdin);
		n = atoi(str);
		if(n == 0 && strcmp(str,"0") == 0){
			puts("Error: Please enter a correct value");
		}else{
			break;
		}
	}

	return(n);
}

size_t input_char(size_t buf, char* str){

	if(buf > BUF) buf = BUF;
	size_t len;

	while(1){
		printf(">");
		if (fgets(str, buf, stdin) == NULL || str[0] == '\n') {
			puts("Error: Please enter the correct character string");
		}else{
			break;
		}
	}

	len = strlen(str);
  if (str[len - 1] == '\n') str[--len] = '\0';

  return(len);
}

char* def_set(char* set){

	size_t stnum, len;
	int i, j, ext;
	int size = 0;
	int* stlen;
	char str[BUF],swap[BUF];

	while(1){

		puts("Please enter the number of elements of the set");

		stnum = input_int();
		if(stnum == 0){
			puts("Error: Please enter the correct number of elements of the set");
			continue;
		}

		stlen = malloc(sizeof(int) * stnum);
		set = (char *)malloc(sizeof(char *) * stnum * BUF);

		for(i = 0; i < stnum; i++){
			printf("Please enter the %dth elements\n",i);
			stlen[i] = input_char(BUF,str);
			if(i != 0 && strcmp(str,swap) == 0){
				i--;
				puts("Error: It is an already defined element");
			}else{
				strcat(set, str);
				strcpy(swap, str);
				size = (size + stlen[i]) * sizeof(char);
			}
		}

		set = (char *)realloc(set, size);

		puts("");
		puts("The defined set is");
		printf("{");
		for(i = 0; i < stnum; i++){
			for (j = 0; j < stlen[i]; j++){
				printf("%c", set[i * stlen[i] + j]);
			}
			if(i != stnum - 1) printf(",");
		}
		puts("}");

		puts("Do you want to redefine it? (yes=1,no=Enter)");
		ext = input_int();
		if(ext != 1) break;
	}
	return (set);
}

void print_set(char* set ) {
	int i = 0;

	while(set[i]) {
		if(i != 0) printf(",");
		printf("%c", set[i]);
		i++;
	}
}

fa def_fa(fa am){

	int i = 0;

	puts("**Define a finite automaton**");
	puts("fa = (Q{}, S{}, δ, q0, F)");
	puts("\n*Define a finite state*\n");
	am.state = def_set(am.state);

	printf("fa = (Q{");
	print_set(am.state);
	puts("}, S{\n");

	puts("\n*Define a finite symbol*\n");
	am.symbol = def_set(am.symbol);

	print_set(am.state);

	printf("}, δ, q0, F)");

	return (am);
}

int main(void){
	fa am;
	def_fa(am);
	return(0);
}
