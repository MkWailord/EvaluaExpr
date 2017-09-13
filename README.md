# TADPila
Tema 02 Estructura de Datos: TAD Pila, Evaluación de paréntesis y expresiones.
En la primer branch se realizo la implementacion de la pila, es decir,
se creo la libreria de TADPilaEst.c en base a las especificaciones dadas
en TADPilaEst.h

Branch Implementacion
Se agregan las siguientes funciones con su respectivo codigo:
void Initialize(pila *s);
void Push(pila *s, elemento e);		
elemento Pop (pila *s);				
boolean Empty(pila *s);				
elemento Top(pila *s);				
int Size(pila *s);					
void Destroy(pila *s);

TADPilaEst.c es parte de la implementacion, por lo que puede ser
vista por el implementador.

Branch VersionPrevia.
Se agregan las siguientes funciones:
boolean isOperand(char x);
boolean prcd(char a, char b);
void InfAPos(char infija[], char postfija[]);
float oper(char symb, float op1, float op2);
float eval(char expr[]);
float pvalores(char posfijav[]);
boolean compParentesis(char expresion[]);


