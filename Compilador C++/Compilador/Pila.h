TSimbolos *PPila, *QPila, *auxPila, *nuevoPila;
TSimbolos *PPosfija, *QPosfija, *auxPosfija, *nuevoPosfija;
TSimbolos *POperadores, *QOperadores, *auxOperadores, *auxOperadores2, *NuevoOperadores;
TSimbolos *PPilaJerarquia, *QPilaJerarquia, *auxPilaJerarquia, *nuevoPilaJerarquia;
#include <iostream>
using namespace std;

void push(const char* a)
{
	nuevoPila = (TSimbolos*)(malloc(sizeof(TSimbolos)));
	nuevoPila->liga = NULL;
	strcpy(nuevoPila->derivacion, a);
	if(PPila == NULL)
	{
		PPila = nuevoPila;
		QPila = PPila;
	}
	else
	{
		QPila->liga = nuevoPila;
		QPila = QPila->liga;	
	}
}

void pop()
{
	auxPila = PPila;
	if(auxPila != NULL)
	{
		if( PPila->liga != NULL )
		{	
			while(auxPila->liga->liga != NULL)
				auxPila = auxPila->liga;
			QPila = auxPila;
			auxPila = QPila->liga;
			QPila->liga = NULL;
			free(auxPila);
		}
		else
		{
			free(auxPila);
			PPila = NULL;
			QPila = NULL;
		}	
	}
}

void top()
{
	cout<<QPila->derivacion<<endl;
}

void imprimeDerivacion()
{
	cout<<"=> ";
	auxPila = PPila;
	while(auxPila != NULL)
	{
		cout<<auxPila->derivacion;
		auxPila = auxPila->liga;
	}
	cout<<endl;
}

void vaciaPila()
{
	while( PPila != NULL )
		pop();
}


void push_pos(TSimbolos *a)
{
	nuevoPosfija = (TSimbolos*)(malloc(sizeof(TSimbolos)));
	nuevoPosfija->liga = NULL;
	strcpy(nuevoPosfija->lexema, a->lexema);
	strcpy(nuevoPosfija->tipoToken, a->tipoToken);
	if(PPosfija == NULL)
	{
		PPosfija = nuevoPosfija;
		QPosfija = PPosfija;
	}
	else
	{
		QPosfija->liga = nuevoPosfija;
		QPosfija = QPosfija->liga;	
	}
}

void push_op(TSimbolos *a)
{
	NuevoOperadores = (TSimbolos*)(malloc(sizeof(TSimbolos)));
	NuevoOperadores->liga = NULL;
	strcpy(NuevoOperadores->lexema, a->lexema);
	strcpy(NuevoOperadores->tipoToken, a->tipoToken);
	if(POperadores == NULL)
	{
		POperadores = NuevoOperadores;
		QOperadores = POperadores;
	}
	else
	{
		QOperadores->liga = NuevoOperadores;
		QOperadores = QOperadores->liga;	
	}
}

void pop_op()
{
	auxOperadores = POperadores;
	if(auxOperadores != NULL)
	{
		if( POperadores->liga != NULL )
		{	
			while(auxOperadores->liga->liga != NULL)
				auxOperadores = auxOperadores->liga;
			QOperadores = auxOperadores;
			auxOperadores = QOperadores->liga;
			QOperadores->liga = NULL;
			free(auxOperadores);
		}
		else
		{
			free(auxOperadores);
			POperadores = NULL;
			QOperadores = NULL;
			
		}	
	}
}

void push_jerarquia(const char *a)
{
	nuevoPilaJerarquia = (TSimbolos*)(malloc(sizeof(TSimbolos)));
	nuevoPilaJerarquia->liga = NULL;
	strcpy(nuevoPilaJerarquia->lexema, a);
	if(PPilaJerarquia == NULL)
	{
		PPilaJerarquia = nuevoPilaJerarquia;
		QPilaJerarquia = PPilaJerarquia;
	}
	else
	{
		QPilaJerarquia->liga = nuevoPilaJerarquia;
		QPilaJerarquia = QPilaJerarquia->liga;	
	}
}

void pop_jerarquia()
{
	auxPilaJerarquia = PPilaJerarquia;
	if(auxPilaJerarquia != NULL)
	{
		if( PPilaJerarquia->liga != NULL )
		{	
			while(auxPilaJerarquia->liga->liga != NULL)
				auxPilaJerarquia = auxPilaJerarquia->liga;
			QPilaJerarquia = auxPilaJerarquia;
			auxPilaJerarquia = QPilaJerarquia->liga;
			QPilaJerarquia->liga = NULL;
			free(auxPilaJerarquia);
		}
		else
		{
			free(auxPilaJerarquia);
			PPilaJerarquia = NULL;
			QPilaJerarquia = NULL;
		}	
	}
}

void vaciaPosfija(void)
{
	auxPosfija = PPosfija;
	while( auxPosfija != NULL )
	{
		PPosfija = PPosfija->liga;
		free(auxPosfija);
		auxPosfija = PPosfija;
	}
	QPosfija = NULL;
}

void vaciaOperadores(void)
{
	auxOperadores = POperadores;
	while( auxOperadores != NULL )
	{
		POperadores = POperadores->liga;
		free(auxOperadores);
		auxOperadores = POperadores;
	}
	QOperadores = NULL;
}