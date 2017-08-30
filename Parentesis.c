#include "TADPilaEst.o"
#include<stdio.h>
#include<stdlib.h>
#define MAXCADENA 100


main()
{
	char expresion[MAXCADENA]	
	pila pila1;	
	elemento e1;	
	Initialize(pila1);	
	tamCadena=strlen(expresion);
	
	scanf("%s", expresion)
	
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
