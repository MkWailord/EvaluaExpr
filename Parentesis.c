#include "TADPilaEst.o"
#include<stdio.h>
#include<stdlib.h>
#define MAXCADENA 100


main()
{
	char expresion[MAXCADENA];
	pila pila1;
	elemento e1;
	Initialize(pila1);
	tamCadena=strlen(expresion);

	scanf("%s", expresion);
	for(i=0;i<=tamCadena;i++)
	{
		if(expresion[i]=='(')
		{
			e1.c='(';
			push(&pila1, e1);
		}
		else if(expresion[i]==')')
		{

			if(Empty(&pila1)==1)
				{
					printf("ERROR");
					exit(1);
				}
			e1=pop(&pila1)
		}
	}
}

InAPos(char infija[], char postfija[])
{
	int posicion, vacia;
	int posicion2=0;
	char simboloMayor= '+';
	char simbolo;
	pila pilaAux;
	Initialize(pila);
	elemento aux;

	for(posicion=0;(simbolo=infija[posicion])!='\0';posicion++)
		if(isOperand(simbolo))
			postfija[posicion2]=simbolo;
			posicion2++;
		else
		{
			if(!vacia)
				simboloMayor=pop(&pilaAux);
			while(prcd(simboloMayor, simbolo))
			{
				postfija[posicion2++]=simboloMayor;
				if(!vacia)
					simboloMayor=pop(&pilaAux);
			}
			if(!vacia)
				{
					aux.c=simboloMayor;
					push(&pilaAux, aux);
				}
			if(vacia||symb!=')')
				{
					aux.c=simbolo
					push(&pilaAux, aux);
				}
			else
				simboloMayor=pop(&pilaAux);
	}
		while(!empty(&pilaAux))
			postfija[posicion2++]=pop(&pilaAux);
}


int isOperand(char x)
{
	if((x!='+')&&(x!='-')&&(x!='*')&&(x!='/')&&(x!='$'))
		return TRUE;
	else
		return FALSE;
}

int prcd(char a, char b)
{
	int ValorA,ValorB;
	if(a=='+'||(a=='-')
		valorA=1;
	if(a=='*'||(a=='/')
		valorA=2;
	if(a==''||(a=='-')
		valorA=3;

	if(b=='+'||(b=='-')
		valorB=1;
	if(b=='*'||(b=='/')
		valorB=2;
	if(b==''||(b=='-')
		valorB=3;

	if((ValorA==ValorB)||(ValorA>ValorB))
		return TRUE;
	return FALSE;
}

double oper(int symb, double op1, double op2)
{
	switch(symb){
		case '+': return(op1+op2);
		case '-': return(op1-op2);
		case '*': return(op1*op2);
		case '/': return(op1/op2);
		case '$': return(pow(op1,op2));
		default: printf("Error en la operacion");
			exit(1);
	}
}

double eval(char expr[])
{
	int c, posicion;
	double opnd1, opnd2, valor;
	pila pilaAux;
	elemento aux;
	Initialize(&pilaAux);
	for(position=0;(c=expr[position])!='\0';position++){
		if(isdigit(c)){
			aux.d=c-'0';
			push(&pilaAux,aux);
		}
		else{
			aux=Pop(&pilaAux);
			opnd2=aux.d;
			aux=Pop(&pilaAux);
			opnd1=aux.d;
			aux.d=oper(opnd1,opnd2);
			push(&pilaAux, aux);
		}
	}
}
