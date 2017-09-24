/*
AUTOR: Equipo Lambda; Casas Carbajal Jose Mauricio y Jesus Salgado Gallegos (C) Septiembre 2017
VERSIÃ“N: 1.0

DESCRIPCION: Aplicacion de la pila para comprobacion de parentesis en una expresion,
posteriormente se tranformara la expresion de infijo a postfijo para poder realizar
su evaluacion.

OBSERVACIONES: Se emplea la libreria TADPilaDin.h o TADPilaEst.h implementadas
en clase. Ambas estructuras elemento, ya sea la de la implementacion estatica o dinamica deberian tener campos char c; double d; y int i;

COMPILACION: 	gcc -o EvaluaExpr EvaluaExpr.c TADPila(Din|Est).o (Si se tiene el objeto de la implementacion)
				gcc -o EvaluaExpr EvaluaExpr.c TADPila(Din|Est).c (Si se tiene el fuente de la implementacion)

EJECUCION: EvaluaExpr.exe (En Windows) - ./EvaluaExpr (En Linux)
*/

#include "TADPilaEst.h"
//#include "TADPilaDin.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>
#define MAXCADENA 100
#define TRUE 1
#define FALSE 0
#include<math.h>


/* ***PROTOTIPOS DE FUNCIONES*** */
boolean isOperand(char x); //Retorna TRUE o FALSE si el signo 'x' es un operando, recibe un caracter char.
boolean prcd(char a, char b); //Retorna TRUE si el signo 'a' tiene mayor precedencia que el 'b', recibe dos caracter char.
void InfAPos(char infija[], char postfija[]); //Transforma una funcion de infija a postfija, recibe dos arreglos de char.
boolean compParentesis(char expresion[]);	 //Retorna TRUE o FALSE si los parentesis estan correctamente escritos, recibe un arreglo de char
int  *pedirCoeficientes(char *cadena); //Pide los coeficientes de las variables, recibe un arreglo de char, el cual es la cadena postfija
int resolverPosfija(int *valores, char *cadena); //Retorna el resultado de una expresion postfija, recibe los valores de las variables y la expresion postfija

void main()
{
	char expresion[MAXCADENA], posfija[MAXCADENA];
	char simb[MAXCADENA], simb2;
	float a,b, result;
	int *valores;
	valores=(int*)malloc(65*sizeof(int));
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

	valores=pedirCoeficientes(posfija);

	printf("\nLa expresion postfija es %s: ", posfija);
	result=resolverPosfija(valores, posfija);
	printf("\nEl resultado de la expresion Postfija es: %.2f \n", result);

	system("PAUSE");

}

//DEFINICIÓN DE FUNCIONES

/*
boolean compParentesis(char expresion[])
Descripción: Comprueba que los parentesis de una expresion esten correctamente escritos.
Recibe: char expresion[] (Expresion infija)
Devuelve: boolean (TRUE o FALSE según sea el caso)
Observaciones: La expresion a comprobar debe ser una expresion postfija, no es posible que la funcion retorne FALSE, puesto que es considerado error.
*/
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

/*
boolean isOperand(char x)
Descripción: Funcion para saber si un signo es un operando o un operador.
Recibe: (char x) (x es el signo a comprobar)
Devuelve: boolean (TRUE o FALSE según sea el caso)
Observaciones: Si el signo x es un operando o parentesis devuelve TRUE, de lo contrario devuelve FALSE
							 en este caso, un operando puede ser una letra que va desde A hasta Z (debido a que mas adelante se pide el valor de esta variable)
*/
boolean isOperand(char x) //Retorna TRUE o FALSE si el signo 'x' es un operando
{
	boolean a;
	if((x!='+')&&(x!='-')&&(x!='*')&&(x!='/')&&(x!='$')&&(x!='(')&&(x!=')'))
		a=TRUE;
	else
		a=FALSE;
	return a;
}

/*
boolean prcd(char a, char b)
Descripción: Funcion para saber si un operador precede a otro operador.
Recibe: (char a, char b)
Devuelve: boolean (TRUE o FALSE según sea el caso).
Observaciones: Si el signo a tiene mayor prioridad que el signo b, retorna TRUE, de lo contrario retorna FALSE.
*/
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

/*
void InfAPos(char infija[], char postfija[])
Descripción: Funcion para transformar una expresion infija a postfija.
Recibe: (char infija[], char postfija[])  (Al ser cadenas, el paso es por referencia, por lo que la cadena postfija que recibe cambia tambien en el main)
Devuelve:
Observaciones: Esta funcion hace uso de la funcion "prcd" y de la funcion "isOperand", por lo que deben ser implementadas antes.
*/
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

/*
int  *pedirCoeficientes(char *cadena)
Descripción: Funcion que pide los coeficientes de una cadena postfija
Recibe: (char *cadena) (Cadena que guarda una expresion matematica)
Devuelve: int (Arreglo con los valores de las variables).
Observaciones: Esta funcion no ha sido probada en una expresion infija, sin embargo es posible que pueda guardar sus valores.
*/
int  *pedirCoeficientes(char *cadena) //Pide los coeficientes de las variables
{

	char *variables;
	variables = (char*)malloc(65*sizeof(char)); //Pide memoria para el arreglo variables

	int *valores;
	valores = (int*)malloc(65*sizeof(int)); //Pide memoria para el arreglo valores


	int j;
	for (j = 0; j < 65; j++)
	{
		variables[j] = 'N'; //Verificacion para saber si ya pidio el valor o no
	}

	int i = 0;

	while(i < strlen(cadena))
	{
		if((cadena[i] > 64 && cadena[i] < 91) || (cadena[i] > 96 && cadena[i] < 123) ) //Valida que solo ingresen numeros en ASCII
		{
			if(variables[cadena[i]%65] != 'Y' ) //Si aun no pide el valor
			{
				printf("Ingresa el valor para %c: ", cadena[i]);
				scanf("%d",&valores[cadena[i]%65]); //Transforma el el valor ascii de la letra
				variables[cadena[i]%65] = 'Y';  //Cambia la verificacion para saber que ya se pidio el valor
			}

		}


		i++;
	}

	free(variables);
	return valores;


}

/*
int resolverPosfija(int *valores, char *cadena)
Descripción: Funcion que resuelve una expresion postfija, recibe los valores de las variables y la expresion postfija
Recibe: (int *valores, char *cadena) (El primer int es el arreglo que contiene los valores, el segundo arreglo de char es la expresion postfija)
Devuelve: int (Resultado de la expresion postfija).
Observaciones: Para un correcto funcionamiento, se recomienda usar la funcion pedirCoeficientes, ya que es la que retorna el arreglo que contiene los valores
*/
int resolverPosfija(int *valores, char *cadena)
{

	//Se crea Pila y se limpia
	pila mi_pila;
	elemento e,aux;

    Initialize(&mi_pila);

	int i=0, j;
	elemento op1, op2;


	while((e.c=cadena[i]) != '\0'){

				//Valida que solo ingresen numeros en ASCII
		if((cadena[i] > 64 && cadena[i] < 91) || (cadena[i] > 96 && cadena[i] < 123) ){
			aux.c = valores[e.c%65];
			Push(&mi_pila, aux);
	}

		else{
			//En caso de percibir un + sacar 2 elementos y realizar el ultimo por el penultimo

			if (e.c == '+')
			{
				op2 = Pop(&mi_pila);
				op1 = Pop(&mi_pila);
				aux.c = op1.c+op2.c;
				Push(&mi_pila, aux);
			}
			//En caso de percibir un - sacar 2 elementos y realizarÃ¡ el ultimo menos el penultimo
			if (e.c == '-')
			{
				op2 = Pop(&mi_pila);
				op1 = Pop(&mi_pila);
				aux.c = op1.c-op2.c;
				Push(&mi_pila, aux);
			}
			//En caso de percibir un * sacar 2 elementos y realizar el ultimo por el penultimo

			if (e.c == '*')
			{
				op2=Pop(&mi_pila);
				op1=Pop(&mi_pila);
				aux.c = op1.c*op2.c;
				Push(&mi_pila, aux);
			}
			//En caso de percibir un / sacar¡ 2 elementos y realizar el ultimo entre el penultimo
			if (e.c == '/')
			{
				op2 = Pop(&mi_pila);
				op1 = Pop(&mi_pila);
				aux.c = op1.c/op2.c;
				Push(&mi_pila, aux);
			}
			//En caso de percibir un ^ sacar¡ 2 elementos y realizar¡ el ultimo elevado al penultimo
			if (e.c == '$')
			{
				op2 = Pop(&mi_pila);
				op1 = Pop(&mi_pila);
				aux.c = pow(op1.c,op2.c);
				Push(&mi_pila, aux);	//Posteriormente insertar¡ el resultado obtenido
			}
		}

		i++;
	}

	i = Pop(&mi_pila).c;

	return i;
}

