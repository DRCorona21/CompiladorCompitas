#include <map>
#include <string>

using namespace std;

FILE *Archivo;
char asig[1000];
map<string, int> precedencia;

void ConversionPosfija(TSimbolos *Ini){
	precedencia["*"] = 2;
	precedencia["/"] = 2;
	precedencia["-"] = 1;
	precedencia["+"] = 1;

	//Si es un ID, es una asignación
	if (!strcmp(auxTabla->tipoToken,"ID"))
	{
		/*
		//Se agrega la variable y el operador de asignacion "=" a la notación
		push_pos(auxTabla->lexema);
		auxTabla = auxTabla->liga;
		push_pos(auxTabla->lexema);
		auxTabla = auxTabla->liga;
		*/
		auxTabla = auxTabla->liga->liga;
		//AQUI COMIENZA LA CONVERSION
		//Comienza a evaluar desde el primer operando mientras no sea ;
		while (strcmp(auxTabla->lexema,";") != 0)
		{
			//Si es un número lo agrega a la notación
			if (!strcmp(auxTabla->tipoToken,"NE") || !strcmp(auxTabla->tipoToken,"ND"))
			{
				push_pos(auxTabla);
			//Si es una variable lo agrega a la notación
			}else if (!strcmp(auxTabla->tipoToken,"ID"))
			{
				push_pos(auxTabla);
			//Si es un operador
			}else if (!strcmp(auxTabla->tipoToken,"OA"))
			{
				//Si no hay operadores en la pila de operadores, hace push
				if (POperadores == NULL)
				{
					push_op(auxTabla);
				}else
				{
					//Mientras haya operadores en la pila, si el operador en el tope es de mayor precedencia,
					//se saca de la pila y se introduce en la notación.
					//Si no, rompe el ciclo
					while (QOperadores!=NULL)
					{
						if ( (strcmp(QOperadores->lexema,"(") != 0) && (precedencia[QOperadores->lexema] > precedencia[auxTabla->lexema]))
						{
							push_pos(QOperadores);
							pop_op();
						}else break;
					}
				
					push_op(auxTabla);
				}
			//Si es un paréntesis
			}else if (!strcmp(auxTabla->tipoToken,"PAR"))
			{
				if (!strcmp(auxTabla->lexema,"("))
				{
					push_op(auxTabla);
				}else if(!strcmp(auxTabla->lexema,")"))
				{
					while (strcmp(QOperadores->lexema,"(")!= 0)
					{
						push_pos(QOperadores);
						pop_op();
					}
					pop_op();
				}
			}
			auxTabla = auxTabla->liga;
		}
			
		while (QOperadores != NULL)
		{
			push_pos(QOperadores);
			pop_op();
		}

		//Imprime la notacion posfija por consola
		
		auxPosfija = PPosfija;
		while (auxPosfija!=NULL)
		{
			printf("%s ",auxPosfija->lexema);
			cout<<auxPosfija->lexema;
			auxPosfija = auxPosfija->liga;
		}
		cout<<";"<<endl;
	}			
}

void PosfijaAEnsamblador(void)
{
	char ultimoToken[1000];
	char Op1[1000];
	char Op2[1000];
	char OpArit[1000];
	bool especial = true;
	auxPosfija = PPosfija;
	int numtemp = -1;
	if( auxPosfija != NULL && auxPosfija->liga != NULL )
	{
		while( auxPosfija != NULL )
		{
			//if( auxPosfija->liga != NULL && auxPosfija->liga->liga != NULL )
			//printf("auxPosfija vale: %s %s %s\n", auxPosfija->tipoToken, auxPosfija->liga->tipoToken, auxPosfija->liga->liga->tipoToken);
			bool operacion = false;
			//Si la estructura es Operando-Operando-Operador
			if( strcmp(auxPosfija->tipoToken, "OA") && auxPosfija->liga != NULL && auxPosfija->liga->liga != NULL && strcmp(auxPosfija->liga->tipoToken, "OA") && !strcmp(auxPosfija->liga->liga->tipoToken, "OA") )
			{
				//Se guarda el ultimo token en la pila de jerarquias
				if( auxPosfija != PPosfija && !especial )
					push_jerarquia(ultimoToken);
				else
					especial = false;
				//Se anota una operacion que va a utilizar un nuevo temporal
				strcpy( Op1, auxPosfija->lexema );
				strcpy( Op2, auxPosfija->liga->lexema);
				strcpy( OpArit, auxPosfija->liga->liga->lexema);
				//Se indica el temporal que se va a utilizar
				numtemp++;
				char ult[1000];
				sprintf(ult, "T%d\0", numtemp);
				strcpy(ultimoToken, ult);
				operacion = true;
				auxPosfija = auxPosfija->liga->liga->liga;
		  	//Sino, si la estructura es Operando-Operador
			} else if( strcmp(auxPosfija->tipoToken, "OA") && auxPosfija->liga != NULL && !strcmp(auxPosfija->liga->tipoToken, "OA") )
			{
				char Temp[1000];
		  		sprintf(Temp, "T%d\0", numtemp);
		  		//Se anota una operacion que va a utilizar un nuevo temporal
		  		strcpy( Op1, Temp);
		  		strcpy( Op2, auxPosfija->lexema);
		  		strcpy( OpArit, auxPosfija->liga->lexema);
		 		numtemp++;
				char ult[1000];
				sprintf(ult, "T%d\0", numtemp);
				strcpy(ultimoToken, ult);
		  		operacion = true;
				auxPosfija = auxPosfija->liga->liga;
		 		//Sino, si la estructura es Operador
			} else if( !strcmp(auxPosfija->tipoToken, "OA") )
			{
				char Temp[1000];
				sprintf(Temp, "T%d\0", numtemp);
				//Se anota una operacion que va a utilizar un nuevo temporal
		  		strcpy( Op1, QPilaJerarquia->lexema);
				pop_jerarquia();
		  		strcpy( Op2, Temp);
		  		strcpy( OpArit, auxPosfija->lexema);
		 		numtemp++;
				char ult[1000];
				sprintf(ult, "T%d\0", numtemp);
				strcpy(ultimoToken, ult);
		  		operacion = true;
				auxPosfija = auxPosfija->liga;
		  	//Sino, ocurre un caso especial
			} else {
				push_jerarquia(auxPosfija->lexema);
				char ult[1000];
				sprintf(ult, "T%d\0", numtemp);
				strcpy(ultimoToken, ult);
				especial = true;
				operacion = false;
				auxPosfija = auxPosfija->liga;
			}

			//Si se va a realizar una operacion
			if( operacion )
			{
				if( !strcmp(OpArit, "+") )
				{
					fprintf(Archivo, "\tmov ax, %s\n", Op1);
					fprintf(Archivo, "\tmov bx, %s\n", Op2);
					fprintf(Archivo, "\tadd ax, bx\n");
					fprintf(Archivo, "\tmov T%d, ax\n\n", numtemp);
				} else if( !strcmp(OpArit, "-") )
				{
					fprintf(Archivo, "\tmov ax, %s\n", Op1);
					fprintf(Archivo, "\tmov bx, %s\n", Op2);
					fprintf(Archivo, "\tsub ax, bx\n");
					fprintf(Archivo, "\tmov T%d, ax\n\n", numtemp);
				} else if( !strcmp(OpArit, "*") )
				{
					fprintf(Archivo, "\tmov ax, %s\n", Op1);
					fprintf(Archivo, "\tmov bx, %s\n", Op2);
					fprintf(Archivo, "\tmul bx\n");
					fprintf(Archivo, "\tmov T%d, ax\n\n", numtemp);
				} else if( !strcmp(OpArit, "/") )
				{
					fprintf(Archivo, "\tmov ax, %s\n", Op1);
					fprintf(Archivo, "\tmov bx, %s\n", Op2);
					fprintf(Archivo, "\tdiv bx\n");
					fprintf(Archivo, "\t mov dx, 0\n");
					fprintf(Archivo, "\tmov T%d, ax\n", numtemp);
				}
			}
		}
		fprintf(Archivo, "\tmov ax, T%d\n", numtemp);
		fprintf(Archivo, "\tmov T%d, ax\n", ++numtemp);
		fprintf(Archivo, "\tmov ax, T%d\n", numtemp);
		fprintf(Archivo, "\tmov %s, ax\n\n", asig);
		numtemp++;
	} else {
		fprintf(Archivo, "\tmov ax, %s\n", auxPosfija->lexema);
		fprintf(Archivo, "\tmov T0, ax\n");
		fprintf(Archivo, "\tmov ax, T0\n");
		fprintf(Archivo, "\tmov %s, ax\n\n", asig);
	}
}

void EscribeEnsamblador(const char* arc)
{
	Archivo = fopen(arc, "w");
	int tottemp = 0;	//El total de temporales que se tienen que generar
	if( Archivo != NULL ) //Si el archivo se abre correctamente
	{
		fprintf(Archivo, ".model small\n\n");
		fprintf(Archivo, ".stack\n\n");
		fprintf(Archivo, ".data\n");
		//Nota: La generacion de codigo objeto asume que el archivo fuente esta lexica y sintacticamente correcto

		auxTabla = PTabla;
		//Primero, recorre todo el archivo fuente en busqueda de declaraciones
		//Para agregar las variables
		//O de asignaciones
		//Para agregar los temporales
		while( auxTabla != NULL )
		{
			//Si se encuentra una palabra reservada
			if( !strcmp( auxTabla->tipoToken, "PR" ) )
			{
				//Si la palabra reservada es un tipo de dato, procesa una declaracion
				if( !strcmp( auxTabla->lexema, "int" ) || !strcmp( auxTabla->lexema, "float" ) )
				{
					//Salta al primer identificador
					auxTabla = auxTabla->liga;
					while ( auxTabla != NULL && !strcmp(auxTabla->tipoToken, "ID") ) {
						fprintf(Archivo, "\t%s DW ?\n", auxTabla->lexema);
						if( auxTabla->liga != NULL && !strcmp(auxTabla->liga->lexema, ",") )
						{
							auxTabla = auxTabla->liga;
							auxTabla = auxTabla->liga;
						}
						else
							break;
					}
					auxTabla = auxTabla->liga;
				}
			} else if( !strcmp( auxTabla->tipoToken, "ID" ) ) {	//Si no, si se encuentra un identificador, es una asignacion
				int numtemp = 0; //Esta variable cuenta el numero total de temporales que se necesitan para esta asignacion
				//Salta a la asignacion
				auxTabla = auxTabla->liga;
				//Si el siguiente es una asignacion, cuenta un temporal
				if( !strcmp( auxTabla->tipoToken, "AS" ) )
					numtemp++;
				//Salta al primer ID o NUM
				auxTabla = auxTabla->liga;
				while( strcmp( auxTabla->derivacion, "SEP" ) )	//Mientras queden tokens por analizar
				{
					if( !strcmp(auxTabla->tipoToken, "OA") )
						numtemp++;
					//Salta al siguiente caracter
					auxTabla = auxTabla->liga;
				}
				//Actualiza los temporales necesarios totales
				if( numtemp > tottemp )
					tottemp = numtemp;
			}
			//Avanza a la siguiente instruccion
			auxTabla = auxTabla->liga;
		}
		//Genera el numero de temporales totales necesarios
		for( int c=0; c<tottemp; c++ )
			fprintf( Archivo, "\tT%d DW ?\n", c );
		fprintf( Archivo, "\n");
		fprintf( Archivo, ".code\n");
		fprintf( Archivo, "begin:\n");
		fprintf( Archivo, "\tmov ax, @data\n");
		fprintf( Archivo, "\tmov ds, ax\n\n");
		//Ahora, genera el codigo del programa
		auxTabla = PTabla;
		while( auxTabla != NULL )
		{
			if( !strcmp( auxTabla->tipoToken, "ID") && auxTabla->liga != NULL && !strcmp(auxTabla->liga->tipoToken, "AS") ) {	//Si se encuentra un identificador, es una asignacion
				strcpy(asig, auxTabla->lexema);
				ConversionPosfija(auxTabla);
				PosfijaAEnsamblador();
				vaciaPosfija();
				vaciaOperadores();
			}
			else
			{
				while( auxTabla != NULL && strcmp( auxTabla->lexema, ";" ) )
					auxTabla = auxTabla->liga;
			}
			//Avanza a la siguiente instruccion
			auxTabla = auxTabla->liga;
		}
		fprintf( Archivo, "\tEND begin\n");
		fclose(Archivo);
		cout<<"\t\tCompiacion exitosa -> ASM creado\n";		
	}
	else
		cout<<"Ocurrio un error al intentar abrir el archivo\n";
}