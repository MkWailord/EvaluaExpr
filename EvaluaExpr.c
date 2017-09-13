/*
AUTOR: Equipo Lambda; Casas Carbajal Jose Mauricio y Jesus Salgado (C) Septiembre 2017
VERSIÃ“N: 1.0

DESCRIPCION: Aplicacion de la pila para comprobacion de parentesis en una expresion,
posteriormente se tranformara la expresion de infijo a postfijo para poder realizar
su evaluacion.

OBSERVACIONES: Se emplea la libreria TADPilaDin.h o TADPilaEst.h implementadas
en clase. Ambas estructuras elemento, ya sea la de la implementacion estatica o dinamica deberian tener campos char c; double d; y int i;

COMPILACION: 	gcc -o EvaluaExpr EvaluaExpr.c TADPila(Din|Est).o (Si se tiene el objeto de la implementacion)
				gcc -o EvaluaExpr EvaluaExpr.c TADPila(Din|Est).c (Si se tiene el fuente de la implementacion)

EJECUCION: EvaluaParentesis.exe (En Windows) - ./EvaluaParentesis (En Linux)
*/

#include "TADPilaEst.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>
#define MAXCADENA 100
#define TRUE 1
#define FALSE 0
#include<math.h>


/* ***PROTOTIPOS DE FUNCIONES*** */
boolean isOperand(char x);
boolean prcd(char a, char b);
void InfAPos(char infija[], char postfija[]);
float oper(char symb, float op1, float op2);
float eval(char expr[]);
float pvalores(char posfijav[]);
boolean compParentesis(char expresion[]);

void main()
{
	char expresion[MAXCADENA], posfija[MAXCADENA];
	char simb[MAXCADENA], simb2;
	float a,b, result;
	boolean aux;
	printf("\t\t//// BIENVENIDO ////\n\n");
	printf("Programa que recibe una expresion infija, la cual se transformara en\n");
	printf("infija para su posterior evaluacion.\n\n");
	printf("Ejemplo de expresion Infija	-	Ejemplo de expresion Postfija\n");
	printf("  (a+b)*c					ab+c*\n\n");
	printf("Escriba una expresion infija: ");
	scanf("%s", expresion);
	aux=compParentesis(expresion); //aux no es utilizable en este caso, pero la funcion debe retornar un boolean
																 //puede ser utilizable para casos de if, pero habria que modificar la parte
																 //falsa de la funcion, ya que al ser falso, cierra el programa
																 //es decir, actualmente la funcion no puede regresar false

	printf("\nLa expresion infija es: %s \n", &expresion);
	system("PAUSE");
	printf("\nLa expresion postfija es: ");
	InfAPos(expresion, posfija);
	system("PAUSE");
	result=eval(posfija);
	printf("\nEl resultado de la expresion Postfija es: %.2f \n", result);

	system("PAUSE");
	//printf("%s \n", &posfija);
	//printf("%s", posfija);
	/*printf("Escriba a: ");
	scanf("%f",&a);
	printf("Escriba b: ");
	scanf("%f",&b);
	printf("%.2f", oper(simb,a,b));


	printf("%s", posfija);
	pvalores(posfija);
	*/


}

boolean compParentesis(char expresion[])
{
	int i, tamCadena;
	tamCadena=strlen(expresion);
	elemento e1;
	pila pila1;
	Initialize(&pila1);

	for(i=0;i<=tamCadena;i++)
	{
		if(expresion[i]=='(')
		{
			e1.c='(';
			Push(&pila1, e1);
		}
		else if(expresion[i]==')')
			{

				if(Empty(&pila1))
				{
					printf("ERROR: Existen mas parentesis que cierran de los que abren");
					exit(1);
				}
				e1=Pop(&pila1);
			}
	}

	return TRUE;
}

boolean isOperand(char x) //Retorna TRUE o FALSE si el signo 'x' es un operando
{
	boolean a;
	if((x!='+')&&(x!='-')&&(x!='*')&&(x!='/')&&(x!='$')&&(x!='(')&&(x!=')'))
		a=TRUE;
	else
		a=FALSE;
	return a;
}
//
boolean prcd(char a, char b) //Retorna TRUE si el signo 'a' tiene mayor precedencia que el 'b'
{
	int valorA,valorB;
	if((a=='+')||(a=='-'))
		valorA=1;
	if((a=='*')||(a=='/'))
		valorA=2;
	if((a=='$'))
		valorA=3;
	if((a=='('))
		valorA=0;

	if((b=='+')||(b=='-'))
		valorB=1;
	if((b=='*')||(b=='/'))
		valorB=2;
	if((b=='$'))
		valorB=3;
	if((b=='('))
		valorB=0;

	if((valorA>=valorB))
		return TRUE;
	else
		return FALSE;
}

void InfAPos(char infija[], char postfija[]) //Transforma una funcion de infija a postfija
{
	int posicion;
	boolean vacia;
	int posicion2=0;
	char simboloMayor= '+';
	char simbolo,c;
	pila pilaAux;
	Initialize(&pilaAux);
	elemento aux;

	for(posicion=0;(simbolo=infija[posicion])!='\0';posicion++)
	{
		if(isOperand(simbolo)) //si el signo a evaluar es un operando, lo agrega a la cadena postfija
		{
			postfija[posicion2++]=simbolo;
		}
		else if(simbolo=='(') //si el signo a evaluar es un parentesis que abre lo agrega a la pila
		{
			aux.c=simbolo;
			Push(&pilaAux, aux);
		}
		else if(simbolo==')') //si el signo a evaluar es un parentesis que cierra, se hara pop hasta encontrar el parentesis que abre
		{											//NOTA: no se agrega el parentesis que cierra a la cadena postfija
			aux=Pop(&pilaAux);
			simboloMayor=aux.c;
			if(simboloMayor!='(')
				postfija[posicion2++]=simboloMayor;
		}
		else //El simbolo a evaluar es un operador
		{
			vacia=Empty(&pilaAux); //Comprobacion si la pila esta vacia
			if(!vacia) //No esta vacia, se hace pop y se asigna a simboloMayor
			{
				aux=Pop(&pilaAux);
				simboloMayor=aux.c;
			}
			while(!vacia&&(prcd(simboloMayor, simbolo))) //Mientras que no este vacia y el simboloMayor tenga mas precedencia
			{																						 // que el signo a evaluar
				postfija[posicion2++]=simboloMayor;
				vacia=Empty(&pilaAux);
				if(!vacia) //se cambia el simboloMayor si no esta vacia
				{
					aux=Pop(&pilaAux);
					simboloMayor=aux.c;
				}
			}
			if(!vacia)
				{
					aux.c=simboloMayor;
					Push(&pilaAux, aux);
				}
			if(vacia||(simbolo!=')')) //La pila esta vacia y el simbolo no es un parentesis que cierra
				{
					aux.c=simbolo;
					Push(&pilaAux, aux);
				}
			else
			{
				aux=Pop(&pilaAux);
				simboloMayor=aux.c;
			}
		}
	}

		while(!Empty(&pilaAux)) //Se vacia la pila una vez acabada de leer la expresion infija
		{
			aux=Pop(&pilaAux);
			if(aux.c!='(')
				postfija[posicion2++]=aux.c;
		}
		postfija[posicion2]='\0';
		printf("%s\n", postfija);
}


float oper(char symb, float op1, float op2) //Se realizara la operacion dependiendo del caso
{
	switch(symb){
		case '+': return(op1+op2);
		case '-': return(op1-op2);
		case '*': return(op1*op2);
		case '/': return(op1/op2);
		case '$': return(pow(op1,op2));
		default: printf("\nError en la operacion");
			exit(1);
	}
}

float eval(char expr[]) //Evalua una expresion postfija
{
	int c, position;
	double opnd1, opnd2, valor;
	pila pilaAux;
	elemento aux;
	Initialize(&pilaAux);
	for(position=0;(c=expr[position])!='\0';position++){
		if(isdigit(c)) //si el simbolo a evaluar es un digito
		{
			aux.d=c-'0'; //Transformacion de char (tomando en cuenta que el char es un numero) a int
			Push(&pilaAux,aux);
		}
		else{ //el simbolo a evaluar es un operador
			aux=Pop(&pilaAux);
			opnd2=aux.d; //Se saca el primer operando
			aux=Pop(&pilaAux);
			opnd1=aux.d; //Se saca el segundo operando
			aux.d=oper(c,opnd1,opnd2); //Se realiza la operacion de los operandos, dependiendo del signo, se asigna al elemento aux
			Push(&pilaAux, aux); //se guarda el resultado de la operacion en la pila
		}
	}
	return aux.d; //retorna el valor final
}

float pvalores(char posfijav[])
{
    char posfijan[strlen(posfijav)];
    char posfijan1[strlen(posfijav)];
    int i,j=0,h=0,k=0,z;
    unsigned long s;
    s=strlen(posfijav);
	double resul;
    for(i=0;i<s;i++)
    {
        posfijan[i]='\0';
        posfijan1[i]=0;
    }
    for(i=0;i<s;i++)
    {
        if ((posfijav[i]>=65 && posfijav[i]<=90)||(posfijav[i]>=97 && posfijav[i]<=122))
        {
            if(i>0)
            {
                for(h=0;h<s;h++)
                {
                    if(posfijav[i]==posfijan[h])
                    {
                        k=1;
                    }
                }
            }
            if(k==0)
            {
                posfijan[j]=posfijav[i];
                printf("Eligja el valor de %c: ",posfijav[i]);
                scanf(" %s",&posfijan1[j]);
                j++;
            }
            k=0;
        }
    }
    for(i=0;i<j;i++)
    {
        printf("%c es igual a %c",posfijan[i],posfijan1[i]);
    }
	for(i=0;i<j;i++)
	{
		for(z=0;z<j;z++)
		{
			if(posfijav[i]==posfijan[z])
			{
				posfijav[i]==posfijan1[z];
			}
		}
	resul=eval(posfijav);
	}
	return resul;
}
