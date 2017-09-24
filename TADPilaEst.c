#include "TADPilaEst.h"

void Initialize(pila *s)
{
	(*s).tope=-1; //s->tope=-1;
	return;
}

void Push(pila *s, elemento e)
{
  (*s).tope++;
  (*s).arreglo[(*s).tope]=e;
  return;
}

elemento Pop(pila *s)
{
  elemento e;
  e=(*s).arreglo[(*s).tope];
  (*s).tope--;
  return e;
}

boolean Empty(pila *s)
{
	boolean b;
  if((*s).tope==-1)
    b=TRUE;
  else
    b=FALSE;
  return b;
}

elemento Top(pila *s)
{
  elemento e;
  e=(*s).arreglo[(*s).tope];
  return e;
}

int Size(pila *s)
{
  int size;
  size=(*s).tope+1;
  return size;
}

void Destroy(pila *s)
{
	Initialize(s);
	return;
}
