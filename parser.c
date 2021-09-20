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

#define INT  1
#define MAIN  2
#define IF  3
#define ELSE  4
#define WHILE  5
#define DO  6
#define FOR  7
#define FLOAT  8
#define CHAR  9
#define ID  10
#define VINT  11
#define VFLOAT  12
#define VCHAR  13
#define ABRE_PARENTESES  14
#define FECHA_PARENTESES  15
#define ABRE_CHAVES  16
#define FECHA_CHAVES  17
#define PONTO_VIRGULA  18
#define VIRGULA  19
#define MAIS  20
#define MENOS  21
#define MULTIPLICACAO  22
#define DIVISAO 23
#define IGUAL 24
#define IGUAL_IGUAL 25
#define MENOR_QUE 26
#define MENOR_IGUAL 27
#define MAIOR_QUE 28
#define MAIOR_IGUAL 29
#define DIFERENTE 30
#define FIM 31

/*=======================================================================================*/
/*FUN��O QUE RECEBE O ARQUIVO J� ABERTO, IDENTIFICA O TOKEN E RETORNA AS INFORMA��ES DELE*/
/*=======================================================================================*/

token scan(FILE *head);
token comando2(FILE * file18, token q);
token fator(FILE * file17, token p);
token termo(FILE * file16, token o);
token iteracao(FILE * file15, token n);
token op_relacional(FILE * file14, token m);
token expr_relacional(FILE * file13, token l);
token expr_arit2(FILE * file12,token k);
token termo2(FILE * file11, token j);
token expr_arit(FILE * file10, token i);
token atribuicao(FILE * file8, token g);
token cmd_basico(FILE * file7, token f);
token comando(FILE * file5, token d);
token declara_var(FILE * file4, token c);
token bloco(FILE * file3,token b);
int programa(FILE * file2);


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
					b.clas=31;
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

token comando2(FILE * file18, token q){
	if(q.clas == ID || q.clas == ABRE_CHAVES){
	 q = cmd_basico(file18,q);
	 return q;
	}

	else if(q.clas == WHILE || q.clas == DO){
	 q = iteracao(file18,q);
	 return q;
	}

    else if(q.clas == IF ){
         q = scan(file18);
         if(q.clas == ABRE_PARENTESES){
           q = scan(file18);
           q = expr_relacional(file18, q);
           if(q.clas == FECHA_PARENTESES){
                 q = scan(file18);
                 q = comando2(file18,q);
               if(q.clas == ELSE){
                   q = scan(file18);
                   q = comando2(file18,q);
                   return q;
               }
               else
               	return q;
           }
           else{
               printf("Erro linha %i coluna %i ultimo token lido %s era esperado um ) \n",q.linha,q.coluna,q.lex);
               exit(0);
           }
        }
        else {
           printf("Erro linha %i coluna %i ultimo token lido %s era esperado um ( \n",q.linha,q.coluna,q.lex);
           exit(0);
        }
    }
    else{
    	printf("Erro linha %i coluna %i ultimo token lido %s era esperado um comando \n",q.linha,q.coluna,q.lex);
        exit(0);
    }
}

token fator(FILE * file17, token p){
    if(p.clas == ID || p.clas == VINT || p.clas == VFLOAT|| p.clas == VCHAR || p.clas == ABRE_PARENTESES){
        if(p.clas == ABRE_PARENTESES){
            p = scan(file17);
            p = expr_arit(file17,p);
            if(p.clas == FECHA_PARENTESES){
                p = scan(file17);
                return p;
            }
            else{
                printf("Erro linha %i coluna %i ultimo token lido %s era esperado um ) \n",p.linha,p.coluna,p.lex);
                exit(0);
            }
        }
        else{
            p = scan(file17);
            return p;
        }
    }
    else{
        printf("Erro linha %i coluna %i ultimo token lido %s era esperado um fator \n",p.linha,p.coluna,p.lex);
        exit(0);
    }

}

token termo(FILE * file16, token o){
    o = fator(file16,o);
    o = termo2(file16,o);
    return o;

}

token iteracao(FILE * file15, token n){
	if(n.clas == WHILE ){
        n = scan(file15);
        if(n.clas == ABRE_PARENTESES){
            n = scan(file15);
   	        n = expr_relacional(file15,n);
    	    if(n.clas == FECHA_PARENTESES){
    	        n = scan(file15);
        	    n = comando2(file15,n);
        	    return n;
        	}
        	else{
        	    printf("Erro linha %i coluna %i ultimo token lido %s era esperado um ) \n",n.linha,n.coluna,n.lex);
        	    exit(0);
        	}
   		}
    	else {
    	    printf("Erro linha %i coluna %i ultimo token lido %s era esperado um ( \n",n.linha,n.coluna,n.lex);
    	    exit(0);
    	}
    }

    else if(n.clas == DO ){
        n = scan(file15);
        n = comando2(file15,n);
        if(n.clas == WHILE ){
        n = scan(file15);
        if(n.clas == ABRE_PARENTESES){
            n = scan(file15);
   	        n = expr_relacional(file15,n);
    	    if(n.clas == FECHA_PARENTESES){
    	        n = scan(file15);
        	    if(n.clas == PONTO_VIRGULA){
                  n = scan(file15);
                  return n;
                }
                else{
               		 printf("Erro linha %i coluna %i ultimo token lido %s era esperado um ; \n",n.linha,n.coluna,n.lex);
              		  exit(0);
           		 }
        	}
        	else{
        	    printf("Erro linha %i coluna %i ultimo token lido %s era esperado um ) \n",n.linha,n.coluna,n.lex);
        	    exit(0);
        	}
   		}
    	else {
    	    printf("Erro linha %i coluna %i ultimo token lido %s era esperado um ( \n",n.linha,n.coluna,n.lex);
    	    exit(0);
    	}
    }
  }
}

token op_relacional(FILE * file14, token m){
    if (m.clas == IGUAL_IGUAL || m.clas == DIFERENTE || m.clas ==MENOR_QUE || m.clas ==MAIOR_QUE
       || m.clas ==MENOR_IGUAL || m.clas == MAIOR_IGUAL){
       m = scan(file14);
       return m;
    }
    else{
        printf("Erro linha %i coluna %i ultimo token lido %s era esperado um operador relacional \n",m.linha,m.coluna,m.lex);
        exit(0);
    }

}

token expr_relacional(FILE * file13, token l){
    l = expr_arit(file13,l);
    l = op_relacional(file13,l);
    l = expr_arit(file13,l);
    return l;

}

token expr_arit2(FILE * file12,token k){
    if(k.clas == MAIS){
        k = scan(file12);
        k = termo(file12,k);
        k = expr_arit2(file12,k);
        return k;
    }
    else if(k.clas == MENOS){
        k = scan(file12);
        k = termo(file12,k);
        k = expr_arit2(file12,k);
        return k;
    }
    else
        return k;

}

token termo2(FILE * file11, token j){
    if(j.clas == MULTIPLICACAO){
        j = scan(file11);
        j = fator(file11,j);
        j = termo2(file11,j);
        return j;
    }
    else if(j.clas == DIVISAO){
        j = scan(file11);
        j = fator(file11,j);
        j = termo2(file11,j);
        return j;
    }
    else
        return j;

}

token expr_arit(FILE * file10, token i){
    i = termo(file10,i);
    i = expr_arit2(file10,i);
    return i;
}

token atribuicao(FILE * file8, token g){
	if (g.clas == ID){
        g = scan(file8);
        if(g.clas == IGUAL){
            g = scan(file8);
            g = expr_arit(file8,g);
            //g = scan(file8);//OBSERVAR SE REALMENTE VAI PRECISAR PEGAR O PROXIMO TOKEN OU O LAÇO INTERNO VAI TER FEITO ISSO
            if(g.clas == PONTO_VIRGULA){
                g = scan(file8);
                return g;
            }
            else{
                printf("Erro linha %i coluna %i ultimo token lido %s era esperado um ; \n",g.linha,g.coluna,g.lex);
                exit(0);
            }
        }
        else{
            printf("Erro linha %i coluna %i ultimo token lido %s era esperado um '=' \n",g.linha,g.coluna,g.lex);
            exit(0);
        }

    }
}

token cmd_basico(FILE * file7, token f){
	if(f.clas == ID){
		f = atribuicao(file7, f);
		return f;
	}
	else{
		f = bloco(file7,f);
		return f;
	}

}

token comando(FILE * file5, token d){
	if(d.clas == ID || d.clas == ABRE_CHAVES){
	 d = cmd_basico(file5,d);
	 return d;
	}

	else if(d.clas == WHILE || d.clas == DO){
	 d = iteracao(file5,d);
	 return d;
	}

    else if(d.clas == IF ){
         d = scan(file5);
         if(d.clas == ABRE_PARENTESES){
           d = scan(file5);
           d = expr_relacional(file5, d);
           if(d.clas == FECHA_PARENTESES){
                 d = scan(file5);
                 d = comando2(file5,d);
               if(d.clas == ELSE){
                   d = scan(file5);
                   d = comando2(file5,d);
                   return d;
               }
               else
               	return d;
           }
           else{
               printf("Erro linha %i coluna %i ultimo token lido %s era esperado um ) \n",d.linha,d.coluna,d.lex);
               exit(0);
           }
        }
        else {
           printf("Erro linha %i coluna %i ultimo token lido %s era esperado um ( \n",d.linha,d.coluna,d.lex);
           exit(0);
        }
    }
    else if(d.clas != FECHA_CHAVES && d.clas != FIM){
       printf("Erro linha %i coluna %i ultimo token lido %s era esperado um comando \n",d.linha,d.coluna,d.lex);
       exit(0);
    }
    else
        return d;
}

token declara_var(FILE * file4, token c){
	inicio2:
	if(c.clas == INT || c.clas == FLOAT || c.clas == CHAR){
		c = scan(file4);
		if(c.clas == ID){
			c = scan(file4);
			while(1){
				if(c.clas == VIRGULA){
					c = scan(file4);
					if(c.clas == ID){
						c = scan(file4);
					}
					else {
						printf("Erro linha %i coluna %i ultimo token lido %s era esperado um id \n",c.linha,c.coluna,c.lex);
						exit(0);
					}
				}
				else
					break;
			}
			if (c.clas == PONTO_VIRGULA){
				c = scan(file4);
				goto inicio2;
			}
			else {
				printf("Erro linha %i coluna %i ultimo token lido %s era esperado um ; \n",c.linha,c.coluna,c.lex);
				exit(0);
			}
		}
		else {
			printf("Erro linha %i coluna %i ultimo token lido %s era esperado um id \n",c.linha,c.coluna,c.lex);
			exit(0);
		}
	}
	else
		return c;
}

token bloco(FILE * file3,token b){
	if(b.clas == ABRE_CHAVES){
		b = scan(file3);
		b = declara_var(file3,b);
        while(b.clas != FECHA_CHAVES && b.clas != FIM)
        	b = comando(file3,b);
		if(b.clas == FECHA_CHAVES){
			b = scan(file3);
			return b;
		}
		else{
			printf("Erro linha %i coluna %i ultimo token lido %s era esperado um } \n",b.linha,b.coluna,b.lex);
			exit(0);
		}
	}
	else{
		printf("Erro linha %i coluna %i ultimo token lido %s era esperado {  \n",b.linha,b.coluna,b.lex);
		exit(0);
	}
}

int programa(FILE * file2){
	token a;
	a = scan(file2);
	if(a.clas==INT){
		a = scan(file2);
		if(a.clas == MAIN){
			a = scan(file2);
			if(a.clas == ABRE_PARENTESES){
				a = scan(file2);
				if(a.clas == FECHA_PARENTESES){
						a = scan(file2);
						a = bloco(file2,a);
						if(a.clas == FIM)
							printf("Compilado com sucesso\n");
						else {
							 printf("Erro linha %i coluna %i ultimo token lido %s era esperado fim de arquivo \n",a.linha,a.coluna,a.lex);
                             exit(0);
						}
				}
				else {
                     printf("Erro linha %i coluna %i ultimo token lido %s era esperado um ) \n",a.linha,a.coluna,a.lex);
                     exit(0);
				}
			}
			else{
                printf("Erro linha %i coluna %i ultimo token lido %s era esperado um ( \n",a.linha,a.coluna,a.lex);
                exit(0);
            }
		}
		else{
            printf("Erro linha %i coluna %i ultimo token lido %s era esperado a palavra main \n",a.linha,a.coluna,a.lex);
            exit(0);
        }
	}
	else{
        printf("Erro linha %i coluna %i ultimo token lido %s era esperado a palavra int \n",a.linha,a.coluna,a.lex);
        exit(0);
	}
}

int main(int argc, char *argv[]){
	FILE *file;
	file = fopen(argv[1],"r+t");
	programa(file);
	fclose(file);
	return 0;
}
