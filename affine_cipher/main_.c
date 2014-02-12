#include <stdio.h>
#include <stdlib.h>
#define ASC 97
#define asc 65
#define alen 26

int cypher(char khar, int a, int b){
	int ihar,r ;
	ihar = (int)khar - ASC;
	if(ihar < 0) // ASCII no valido
		exit(1);
	r = (a * ihar) +  b;
	while(r > alen)
		r = r % alen;
	return r + asc;
}

int mod(int a, int b) { int r = a % b; return r < 0 ? r + b : r; }

int decoder(char khar, int a, int b){
	int ihar;
	int r;
	ihar = (int)khar - asc;
	if(ihar < 0) // ASCII no valido
		exit(1);
	r = (alen-a) * (ihar - b);
	while(r > alen || r < 0){
		r = mod(r, alen);
	}
	return (int)r + ASC;
}

int gcd(int a,int b){
	if(b==0)
		return a;
	else
		return gcd(b,a%b);
}

int strln(char *s){
	int i;
	i = 0;
	while(s[i] != '\0'){
		i++;
	}
	return i;
}

void encrypt(char *to, int a, int b){
	char khar;
	int len, x;
	len = strln(to);
	char output[len];
	x = 0;
	for(x; x<len; x++){
		khar = to[x];
		if( khar == '\0' || khar == '\r' )
			continue;
		if(khar == ' '){
			output[x] = '~';
			continue;
		}
		output[x] = (char)cypher(khar, a, b);
	}

	printf("Encrypted string: %s \n", output);
}

void decrypt(char *to, int a, int b){
	char khar;
	int len, x;
	len = strln(to);
	char output[len];
	x = 0;
	for(x; x<len; x++){
		khar = to[x];
		if( khar == '\0' || khar == '\r' )
			continue;
		if(khar == '~'){
			output[x] = ' ';
			continue;
		}
		output[x] = (char)decoder(khar, a, b);
	}
	printf("Decrypted string: %s \n", output);
}

int menu(){
	char input[256];
	int a,b, pos;
	int menu;
	char exiit[10];

	system("clear");
	printf("1) Encrypt\n2) Decrypt \n3) Exit \n\t Select an option: ");
	scanf("%d", &menu);
	system("clear");

	if(menu == 3) return 0;

	//
	printf("Set alpha: ");
	scanf("%d", &a);
	printf("Set beta: ");
	scanf("%d", &b);

	if(menu == 1)
		while(gcd(a,b) != 1){
			system("clear");
			printf("Los numeros %d y %d  no son COPRIMOS.\n", a, b);
			printf("Set alpha: ");
			scanf("%d", &a);
			printf("Set beta: ");
			scanf("%d", &b);
		}
	else
		while(gcd(a,alen) != 1){
			system("clear");
			printf("Los numeros %d y %d  no son COPRIMOS.\n", a, alen);
			printf("Set alpha: ");
			scanf("%d", &a);
			printf("Set beta: ");
			scanf("%d", &b);
		}

	switch(menu){
		case 1:
			printf("Ingresa la cadena a cifrar: ");
			scanf("%s",input);
			encrypt(input,a,b);
			break;
		case 2:
			printf("Ingresa la cadena a descifrar: ");
			scanf("%s",input);
			decrypt(input,a,b);
			break;
		default:
			return 	1;
	}
	
	printf("\nPresiona una tecla y enter para continuar...");
	scanf("%s",exiit);
	return 1;
}

int main(void){
	
	while(menu() != 0);
	
	return 0;
}