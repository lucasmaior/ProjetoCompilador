#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct TokenS{
	int clas;
	char lex[30];
	int linha;
	int coluna;
}token; //ESTRUTURA RESPONS�VEL POR ARMAZENAR AS INFORMA��ES DO TOKEN

//INT = 1
//MAIN = 2
//IF = 3
//ELSE = 4
//WHILE = 5
//DO = 6
//FOR = 7
//FLOAT = 8
//CHAR = 9
//IDENTIFICADOR = 10
//VINT = 11
//VFLOAT = 12
//VCHAR = 13
//ABRE PARENTESES = 14
//FECHA PARENTESES = 15
//ABRE CHAVES = 16
//FECHA CHAVES = 17
//PONTO E VIRGULA = 18
//VIRGULA = 19
//MAIS = 20
//MENOS = 21
//MULTIPLICACAO = 22
//DIVISAO = 23
//IGUAL = 24
//IGUAL IGUAL = 25
//MENOR QUE = 26
//MENOR OU IGUAL = 27
//MAIOR QUE = 28
//MAIOR OU IGUAL = 29
//DIFERENTE = 30
//EOF = 31

/*=======================================================================================*/
/*FUN��O QUE RECEBE O ARQUIVO J� ABERTO, IDENTIFICA O TOKEN E RETORNA AS INFORMA��ES DELE*/
/*=======================================================================================*/

token scan(FILE *head){
	static token b;
	static char q[] = " ";
	char x[50];
	static int lin = 1;
	static int col = 1;
inicio:
	if(isspace(q[0])||q[0]=='\n'||q[0]=='	'){
		if(q[0]=='\n'){
			lin++;
			col = 1;
		}
		if(q[0]=='	')
			col=col+3;
		q[0]=getc(head);
		col++;
		goto inicio;
	}
	if(q[0]==EOF){
		b.clas = 31;
		b.linha = lin;
		b.coluna = col-1;
		return b;
	}
	/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	/*******************************************SE O TOKEN COME�AR COM LETRA*******************************************/
	/*-------------------------------------------------------------------------------------------------------------*/
	if(isalpha(q[0])||q[0]=='_'){
		strcpy(x,q);
		while(1){
			q[0]=getc(head);
			col++;
			if(isalpha(q[0])||isdigit(q[0])||q[0]=='_'){
				strcat(x,q);
			}
			else
				break;
		}/*ESSE LOOP ACUMULA OS CARACTERES V�LIDOS(NUMERO E LETRA) E QUANDO FINALIZA, O TOKEN VAI PARA O PASSO SEGUINTE 		 PARA SER CLASSIFICADO OU MOSTRA O ERRO DE CARACTER INVALIDO E RETORNA PARA O PROGRAMA PRINCIPAL*/

		/******************************************CLASSIFICA��O DO TOKEN********************************************/
		if(!strcmp(x,"int")){
			strcpy(b.lex,x);
			b.clas = 1;
			b.linha = lin;
			b.coluna = col-1;
			return b;
		}
		else if(!strcmp(x,"main")){
			strcpy(b.lex,x);
			b.clas = 2;
			b.linha = lin;
			b.coluna = col-1;
			return b;
		}
		else if(!strcmp(x,"if")){
			strcpy(b.lex,x);
			b.clas = 3;
			b.linha = lin;
			b.coluna = col-1;
			return b;
		}
		else if(!strcmp(x,"else")){
			strcpy(b.lex,x);
			b.clas = 4;
			b.linha = lin;
			b.coluna = col-1;
			return b;
		}
		else if(!strcmp(x,"while")){
			strcpy(b.lex,x);
			b.clas = 5;
			b.linha = lin;
			b.coluna = col-1;
			return b;
		}
		else if(!strcmp(x,"do")){
			strcpy(b.lex,x);
			b.clas = 6;
			b.linha = lin;
			b.coluna = col-1;
			return b;
		}
		else if(!strcmp(x,"for")){
			strcpy(b.lex,x);
			b.clas = 7;
			b.linha = lin;
			b.coluna = col-1;
			return b;
		}
		else if(!strcmp(x,"float")){
			strcpy(b.lex,x);
			b.clas = 8;
			b.linha = lin;
			b.coluna = col-1;
			return b;
		}
		else if(!strcmp(x,"char")){
			strcpy(b.lex,x);
			b.clas = 9;
			b.linha = lin;
			b.coluna = col-1;
			return b;
		}
		else{//IDENTIFICADOR
			strcpy(b.lex,x);
			b.clas=10;
			b.linha = lin;
			b.coluna = col-1;
			return b;
		}
	}
	/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	/*******************************SE O TOKEN COME�AR COM DIGITO*****************************/
	/*---------------------------------------------------------------------------------------*/
	if(isdigit(q[0])){
		strcpy(x,q);
		while(1){
			q[0]=getc(head);
			col++;
			if(isdigit(q[0])){
				strcat(x,q);
			}
			else if(q[0]=='.'){
				strcat(x,q);
				break;
			}
			else {
				strcpy(b.lex,x);
				b.clas = 11;
				b.linha = lin;
				b.coluna = col-1;
				return b;
			}//**************************VALOR INTEIRO (VINT)**************************
		}/*ESSE LOOP ACUMULA OS DIGITOS E SE DER ALGUM ERRO DE FORMA��O ELE AVISA E RETORNA PRA O PROGRAMA PRINCIPAL,
                 E SE N�O OCORRER SIGNIFICA QUE � UM VALOR INTEIRO. NESSE ACUMULO SE APARECER UM PONTO ESSE LOOP ACABA E VAI     	          PARA O PROXIMO*/
		q[0]=getc(head);
		col++;
		if(isdigit(q[0])){
			strcat(x,q);
			while(1){
				q[0]=getc(head);
				col++;
				if(isdigit(q[0])){
					strcat(x,q);
				}
				else {
					strcpy(b.lex,x);
					b.clas = 12;
					b.linha = lin;
					b.coluna = col-1;
					return b;
				}//**************************VALOR FLOAT (VFLOAT)**************************
			}/*ESSE LOOP ACUMULA OS DIGITOS E SE DER ALGUM ERRO DE FORMA��O ELE AVISA E RETORNA PRA O PROGRAMA 				 PRINCIPAL, E SE N�O OCORRER SIGNIFICA QUE � UM VALOR FLOAT*/
		}
		else{
			printf("Erro %s era esperado um digito. Na linha %i,coluna %i\n  ",x,lin,col);
			exit(0);
		}//ESSE ERRO EH PARA SE DEPOIS DO PONTO TENHA VINDO QUALQUER COISA MENOS UM DIGITO
	}


	/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	/****************************SE O TOKEN COME�AR COM ASPAS SIMPLES*************************/
	/*-------------------------------------------------------------------------------------*/


	if(!strcmp(q,"'")){
		strcpy(x,q);
		q[0]=getc(head);
		col++;
		if(isalpha(q[0])||isdigit(q[0])){
			strcat(x,q);
			q[0]=getc(head);
			col++;
			strcat(x,q);
			if(!strcmp(q,"'")){
				strcpy(b.lex,x);
				b.clas = 13;
				b.linha = lin;
				b.coluna = col;
				q[0]=getc(head);
				col++;
				return b;
			}
			else{
				printf("Erro %s era esperado uma aspas simples '\n Na linha %i,coluna %i\n ",x,lin,col);
				exit(0);
			}
		}
		else{
			strcat(x,q);
			printf("Erro %s era esperado uma letra ou digito Na linha %i,coluna %i\n ",x,lin,col);
			exit(0);
		}
	}

	/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	/***************************SE O TOKEN COME�AR COM ABRE PARENTESES************************/
	/*-------------------------------------------------------------------------------------*/

	if(q[0]=='('){
		strcpy(b.lex,q);
		b.clas = 14;
		b.linha = lin;
		b.coluna = col;
		q[0]=getc(head);
		col++;
		return b;
	}


	/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	/***************************SE O TOKEN COME�AR COM FECHA PARENTESES***********************/
	/*-------------------------------------------------------------------------------------*/

	if(q[0]==')'){
		strcpy(b.lex,q);
		b.clas = 15;
		b.linha = lin;
		b.coluna = col;
		q[0]=getc(head);
		col++;
		return b;
	}


	/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	/******************************SE O TOKEN COME�AR COM ABRE CHAVE**************************/
	/*-------------------------------------------------------------------------------------*/

	if(q[0]=='{'){
		strcpy(b.lex,q);
		b.clas = 16;
		b.linha = lin;
		b.coluna = col;
		q[0]=getc(head);
		col++;
		return b;
	}

	/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	/*****************************SE O TOKEN COME�AR COM FECHA CHAVE**************************/
	/*-------------------------------------------------------------------------------------*/

	if(q[0]=='}'){
		strcpy(b.lex,q);
		b.clas = 17;
		b.linha = lin;
		b.coluna = col;
		q[0]=getc(head);
		col++;
		return b;
	}

	/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	/***************************SE O TOKEN COME�AR COM PONTO E VIRGULA************************/
	/*-------------------------------------------------------------------------------------*/

	if(q[0]==';'){
		strcpy(b.lex,q);
		b.clas = 18;
		b.linha = lin;
		b.coluna = col;
		q[0]=getc(head);
		col++;
		return b;
	}

	/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	/********************************SE O TOKEN COME�AR COM VIRGULA***************************/
	/*-------------------------------------------------------------------------------------*/

	if(q[0]==','){
		strcpy(b.lex,q);
		b.clas = 19;
		b.linha = lin;
		b.coluna = col;
		q[0]=getc(head);
		col++;
		return b;
	}

	/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	/***************************SE O TOKEN COME�AR COM OPERADOR SOMA**************************/
	/*-------------------------------------------------------------------------------------*/

	if(q[0]=='+'){
		strcpy(b.lex,q);
		b.clas = 20;
		b.linha = lin;
		b.coluna = col;
		q[0]=getc(head);
		col++;
		return b;
	}

	/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	/*************************SE O TOKEN COME�AR COM OPERADOR SUBTRA��O***********************/
	/*-------------------------------------------------------------------------------------*/

	if(q[0]=='-'){
		strcpy(b.lex,q);
		b.clas = 21;
		b.linha = lin;
		b.coluna = col;
		q[0]=getc(head);
		col++;
		return b;
	}

	/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	/***********************SE O TOKEN COME�AR COM OPERADOR MULTIPLICA��O*********************/
	/*-------------------------------------------------------------------------------------*/

	if(q[0]=='*'){
		strcpy(b.lex,q);
		b.clas = 22;
		b.linha = lin;
		b.coluna = col;
		q[0]=getc(head);
		col++;
		return b;
	}

	/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	/*******************************SE O TOKEN COME�AR COM BARRA******************************/
	/*-------------------------------------------------------------------------------------*/

	if(q[0]=='/'){
		strcpy(x,q);
		q[0]=getc(head);
		col++;
		if(q[0]=='/'){
			while(1){
				q[0]=getc(head);
				col++;
				if(q[0]=='\n')
					break;
				if(q[0]==EOF){
					b.clas=-1;
					return b;
				}
			}
			goto inicio;
		}
		if(q[0]=='*'){
			q[0]=getc(head);
			col++;
			while(1){
				if(q[0]=='\n'){
					lin++;
					col=1;
					q[0]=getc(head);
					col++;
				}

				else if(q[0]=='*'){
					q[0]=getc(head);
					col++;
					if(q[0]=='/'){
						q[0]=getc(head);
						col++;
						break;
					}
				}
				else if(q[0]==EOF){
					printf("Erro fim de arquivo no comentario Na linha %i,coluna %i\n ",lin-2,col);
					exit(0);
				}
				else{
					q[0]=getc(head);
					col++;
				}
			}
			goto inicio;
		}
		else{
			strcpy(b.lex,x);
			b.clas = 23;
			b.linha = lin;
			b.coluna = col-1;
			return b;
		}
	}

	/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	/*****************************SE O TOKEN COME�AR COM O IGUAL******************************/
	/*-------------------------------------------------------------------------------------*/

	if(q[0]=='='){
		strcpy(x,q);
		q[0]=getc(head);
		col++;
		if(q[0]=='='){
			strcat(x,q);
			strcpy(b.lex,x);
			b.clas = 25;
			b.linha = lin;
			b.coluna = col;
			q[0]=getc(head);
			col++;
			return b;
		}
		else{
			strcpy(b.lex,x);
			b.clas = 24;
			b.linha = lin;
			b.coluna = col-1;
			return b;
		}
	}

	/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	/****************************SE O TOKEN COME�AR COM MENOR QUE*****************************/
	/*-------------------------------------------------------------------------------------*/

	if(q[0]=='<'){
		strcpy(x,q);
		q[0]=getc(head);
		col++;
		if(q[0]=='='){
			strcat(x,q);
			strcpy(b.lex,x);
			b.clas = 27;
			b.linha = lin;
			b.coluna = col;
			q[0]=getc(head);
			col++;
			return b;
		}
		else{
			strcpy(b.lex,x);
			b.clas = 26;
			b.linha = lin;
			b.coluna = col-1;
			return b;
		}
	}

	/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	/***************************SE O TOKEN COME�AR COM MAIOR QUE******************************/
	/*-------------------------------------------------------------------------------------*/

	if(q[0]=='>'){
		strcpy(x,q);
		q[0]=getc(head);
		col++;
		if(q[0]=='='){
			strcat(x,q);
			strcpy(b.lex,x);
			b.clas = 29;
			b.linha = lin;
			b.coluna = col;
			q[0]=getc(head);
			col++;
			return b;
		}
		else{
			strcpy(b.lex,x);
			b.clas = 28;
			b.linha = lin;
			b.coluna = col-1;
			return b;
		}
	}

	/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	/***************************SE O TOKEN COME�AR COM EXCLAMA��O*****************************/
	/*-------------------------------------------------------------------------------------*/

	if(q[0]=='!'){
		strcpy(x,q);
		q[0]=getc(head);
		col++;
		if(q[0]=='='){
			strcat(x,q);
			strcpy(b.lex,x);
			b.clas = 30;
			b.linha = lin;
			b.coluna = col;
			q[0]=getc(head);
			col++;
			return b;
		}
		else{
			printf("Erro %s era esperado um = \n Na linha %i,coluna %i\n ",x,lin,col-1);
			exit(0);
		}
	}

	/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	/*****************************SE O TOKEN COME�AR COM PONTO********************************/
	/*-------------------------------------------------------------------------------------*/

	if(q[0]=='.'){
		strcpy(x,q);
		q[0]=getc(head);
		col++;
		if(isdigit(q[0])){
			strcat(x,q);
			q[0]=getc(head);
			col++;
			while(1){
				if(!(isdigit(q[0]))){
					strcpy(b.lex,"0");
					strcat(b.lex,x);
					b.clas = 12;
					b.linha = lin;
					b.coluna = col-1;
					return b;
				}
				else{
				    strcat(x,q);
			 	    q[0]=getc(head);
				    col++;
				}
			}
		}
		else{
			printf("Erro %s era esperado um digito \n Na linha %i,coluna %i\n ",x,lin,col-1);
			exit(0);
		}
	}
	else{
		strcpy(x,q);
		printf("Erro %s character invalido \n Na linha %i,coluna %i\n ",x,lin,col);
		exit(0);
	}
}

int main(int argc, char *argv[]){
	FILE *file;
	//FILE *file2;
	char nome[30];
	token a;
	file = fopen(argv[1],"r+t");
	//file2 = fopen("banco","wb");
	while(1){
		a = scan(file);
		if(a.clas==31)
			break;
		}
			printf("Compilado com Sucesso!!!\n");
			fclose(file);
			//fclose(file2);
			return 0;
		//fwrite(&a,sizeof(token),1,file2);
		//printf(" %s  ID %i, linha %i, coluna %i\n",a.lex,a.clas,a.linha,a.coluna);
	
}
