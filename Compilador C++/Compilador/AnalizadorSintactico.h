
#include <iostream>
using namespace std;
int contadorLlaves = 0, contadorParentesis = 0;

int AnalizadorSintactico(TSimbolos *Ini, int numCopia)
{
	auxTabla = Ini;
	push("G");
	// Mientras haya simbolos por analizar
	while (auxTabla != NULL)
	{
		imprimeDerivacion();
		// Si hay un simbolo no terminal al frente de la pila, y es G
		if (!strcmp(QPila->derivacion, "G"))
		{
			// Se elimina de la pila
			pop();
			// Si el primer token es una palabra reservada
			if (!(strcmp(auxTabla->tipoToken, "PR")))
			{
				strcpy(auxTabla->derivacion, "PR");
				// Si el token es un int o float, se trata de una declaracion
				if (!(strcmp(auxTabla->lexema, "int")) || !(strcmp(auxTabla->lexema, "float")))
				{
					// Se declara una variable que guarda el tipo de dato declarado
					char tipoDato[5];
					strcpy(tipoDato, auxTabla->lexema);
					// Se ingresa la palabra reservada a la pila
					push(auxTabla->lexema);
					push(" ");
					push("V");
					imprimeDerivacion();
					// Se avanza al siguiente caracter
					auxTabla = auxTabla->liga; 
					// Mientras los siguientes sean no terminales V
					if (auxTabla != NULL && !strcmp(QPila->derivacion, "V")) // Se asegura de que exista al menos un ID
					{
						while (auxTabla != NULL && !strcmp(QPila->derivacion, "V"))
						{
							pop();
							if (auxTabla != NULL && !strcmp(auxTabla->tipoToken, "ID"))
							{
								strcpy(auxTabla->derivacion, "ID");
								push("ID");
								// Localiza alguna declaracion anterior de esta variable
								// Si la encuentra, se muestra un error sintactico
								TSimbolos *Aux2 = PTabla;
								while (Aux2 != auxTabla && (strcmp(Aux2->tipoToken, "ID") || strcmp(Aux2->lexema, auxTabla->lexema)))
									Aux2 = Aux2->liga;
								if (Aux2 != auxTabla)
								{
									cout<<"Error encontrado en la sintactica. La variable "<<auxTabla->lexema<<" ya ha sido declarada anteriormente."<<endl;
									return -1;
								}
								strcpy(auxTabla->tipDat, tipoDato);
								auxTabla = auxTabla->liga;
								if (auxTabla != NULL && !strcmp(auxTabla->lexema, ","))
								{
									strcpy(auxTabla->derivacion, "SEP");
									push(",");
									push(" ");
									push("V");
									imprimeDerivacion();
									auxTabla = auxTabla->liga;
								}
								else if (auxTabla != NULL && !strcmp(auxTabla->lexema, ";"))
								{ // Sino, si es un ; se termina la instrucción
									strcpy(auxTabla->derivacion, "SEP");
									push(";");
									imprimeDerivacion();
									auxTabla = auxTabla->liga;
									if (auxTabla != NULL && !strcmp(auxTabla->lexema, "}"))
									{
										contadorLlaves--;
										if (contadorLlaves < 0)
										{
											cout<<"Error encontrado en la sintactica: El numero de llaves de cierre excede el de llaves de apertura"<<endl;
											return -1;
										}
										push("}");
										imprimeDerivacion();
										auxTabla = auxTabla->liga;
										return 0;
									}
								}
								else
								{ // Si el siguiente no es , o ; , es un error sintactico
									cout<<"Error en la sintactica: Se estaba esperando una ',' o un ';'"<<endl;
									return -1;
								}
							}
							else
							{
								cout<<"Error encontrado en la sintactica: Se estaba esperando un identificador"<<endl;
								return -1;
							}
						}
					}
					else
					{
						cout<<"Error encontrado en la sintactica: Se estaba esperando un identificador"<<endl;
					}
				}
			}
			else if (auxTabla != NULL && !strcmp(auxTabla->tipoToken, "ID"))
			{ // Si empieza con ID
				strcpy(auxTabla->derivacion, "ID");
				push("ID");
				// Localiza la declaracion de la variable e identifica su tipo
				// Si no la encuentra, se muestra un error sintactico
				TSimbolos *Aux2 = PTabla;
				while (Aux2 != auxTabla && (strcmp(Aux2->tipoToken, "ID") || strcmp(Aux2->lexema, auxTabla->lexema)))
					Aux2 = Aux2->liga;
				if (Aux2 == auxTabla)
				{
					cout<<"Error encontrado en la sintactica. La variable "<< auxTabla->lexema <<" no ha sido declarada."<<endl;
					return -1;
				}
				else
				{
					strcpy(auxTabla->tipDat, Aux2->tipDat);
				}
				auxTabla = auxTabla->liga;
				// Si el siguiente es un =, ocurre una asignacion
				if (auxTabla != NULL && !strcmp(auxTabla->tipoToken, "AS"))
				{
					strcpy(auxTabla->derivacion, "AS");
					push(" = ");
					push("S");
					imprimeDerivacion();
					auxTabla = auxTabla->liga;
					// mientras los siguientes sean no terminales S
					while (auxTabla != NULL && !strcmp(QPila->derivacion, "S"))
					{
						pop();
						if (auxTabla != NULL && (!strcmp(auxTabla->tipoToken, "NE") || !strcmp(auxTabla->tipoToken, "ND") || !strcmp(auxTabla->tipoToken, "NX") || !strcmp(auxTabla->tipoToken, "ID")))
						{
							if (!strcmp(auxTabla->tipoToken, "ID"))
							{
								strcpy(auxTabla->derivacion, "ID");
								push("ID");
								// Localiza la declaracion de la variable e identifica su tipo
								// Si no la encuentra, se muestra un error sintactico
								TSimbolos *Aux2 = PTabla;
								while (Aux2 != auxTabla && (strcmp(Aux2->tipoToken, "ID") || strcmp(Aux2->lexema, auxTabla->lexema)))
									Aux2 = Aux2->liga;
								if (Aux2 == auxTabla)
								{
									cout<<"Error encontrado en la sintactica. La variable "<< auxTabla->lexema <<" no ha sido declarada."<<endl;
									return -1;
								}
								else
								{
									strcpy(auxTabla->tipDat, Aux2->tipDat);
								}
							}
							else
							{
								strcpy(auxTabla->derivacion, "NUM");
								push(auxTabla->tipoToken);
							}
							auxTabla = auxTabla->liga;
							if (auxTabla != NULL && !strcmp(auxTabla->lexema, ";"))
							{
								strcpy(auxTabla->derivacion, "SEP");
								auxTabla = auxTabla->liga;
								push(";");
								imprimeDerivacion();
								if (auxTabla != NULL && !strcmp(auxTabla->lexema, "}"))
								{
									contadorLlaves--;
									if (contadorLlaves < 0)
									{
										cout<<"Error encontrado en la sintactica: El numero de llaves de cierre excede el de llaves de apertura"<<endl;
										return -1;
									}
									push("}");
									imprimeDerivacion();
									auxTabla = auxTabla->liga;
									return 0;
								}
								break;
							}
							else if (auxTabla != NULL && !strcmp(auxTabla->tipoToken, "OA"))
							{
								strcpy(auxTabla->derivacion, "OA");
								push(" ");
								push(auxTabla->lexema);
								auxTabla = auxTabla->liga;
								push(" ");
								push("S");
								imprimeDerivacion();
							}
							else if (auxTabla->lexema, ")")
							{
								push(")");
								contadorParentesis--;
								imprimeDerivacion();
								auxTabla = auxTabla->liga;
								if (auxTabla != NULL && (strcmp(auxTabla->tipoToken, "OA") || strcmp(auxTabla->lexema, ";")))
								{
									if (auxTabla != NULL && !strcmp(auxTabla->tipoToken, "OA"))
									{
										strcpy(auxTabla->derivacion, "OA");
										push(" ");
										push(auxTabla->lexema);
										auxTabla = auxTabla->liga;
										push(" ");
										push("S");
										imprimeDerivacion();
									}
									else
									{
										strcpy(auxTabla->derivacion, "SEP");
										auxTabla = auxTabla->liga;
										push(";");
										imprimeDerivacion();
										if (auxTabla != NULL && !strcmp(auxTabla->lexema, "}"))
										{
											contadorLlaves--;
											if (contadorLlaves < 0)
											{
												cout<<"Error encontrado en la sintactica: El numero de llaves de cierre excede el de llaves de apertura"<<endl;
												return -1;
											}
											push("}");
											imprimeDerivacion();
											auxTabla = auxTabla->liga;
											return 0;
										}
										break;
									}
								}
							}
							else
							{
								cout<<"Error encontrado en la sintactica: Se estaba esperando un operador aritmetico o un ';'"<<endl;

								return -1;
							}
						}
						else if (auxTabla != NULL && !strcmp(auxTabla->lexema, "("))
						{
							push("(");
							contadorParentesis++;
							imprimeDerivacion();
							auxTabla = auxTabla->liga;
							push("S");
							imprimeDerivacion();
						}
					}
				}
				else
				{
					cout<<"Error en la sintactica: Se estaba esperando una asignacion."<<endl;;
				}
			}
			else
			{
				cout<<"Error en la sintactica: La sintaxis es irreconocible."<<endl;
				return -1;
			}
		}

		if (auxTabla != NULL && !strcmp(auxTabla->lexema, "}"))
		{
			push("}");
			imprimeDerivacion();
			auxTabla = auxTabla->liga;
			return 0;
		}

		if (QPila != NULL && strcmp(QPila->derivacion, ";") && strcmp(QPila->derivacion, "}") && strcmp(QPila->derivacion, ")"))
		{ // Si el ultimo caracter no fue ; es error sintactico
			cout<<"Error en la sintactica: Se estaba esperando un ';' o una llave de cierre."<<endl;
			return -1;
		}
		if (numCopia == 0)
		{
			vaciaPila();
			cout<<endl;
		}
		if (auxTabla != NULL)
			push("G");
	}
	if (numCopia == 0 && contadorLlaves != 0)
	{
		cout<<"Error sintactico encontrado: La cantidad de llaves de apertura no es la misma que las de cierre"<<endl;
	}
	if (numCopia == 0 && contadorParentesis != 0)
	{
		cout<<"Error sintactico encontrado: La cantidad de parentsis de apertura no es la misma que las de cierre"<<endl;
		return -1;
	}
	return 0;
}
