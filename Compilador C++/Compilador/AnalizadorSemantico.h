#include <iostream>
using namespace std;

int AnalizadorSemantico(TSimbolos *Ini, int numCopia)
{
	auxTabla = Ini;
	push("G");
	// Mientras haya simbolos por analizar
	while (auxTabla != NULL)
	{
		// El analisis semantico asume que el codigo esta sintacticamente correcto
		// De modo que omite las comprobaciones de tokens consecutivos
		// Si hay un simbolo no terminal al frente de la pila, y es G
		if (!strcmp(QPila->derivacion, "G"))
		{
			// Si empieza con ID, y le sigue un =, ocurre una asignacion
			if (auxTabla != NULL && !strcmp(auxTabla->tipoToken, "ID") && auxTabla->liga != NULL && !strcmp(auxTabla->liga->tipoToken, "AS"))
			{
				imprimeDerivacion();
				// Se elimina G de la pila
				pop();
				char tipo[1000]; // Contiene el tipo de dato que se va a analizar en todos los tokens
				memset(tipo, 0, sizeof(tipo));
				strcpy(tipo, auxTabla->tipDat);
				push(tipo);
				push(" ");
				// Como el analisis sintactico se ejecuta antes se asume que esta sintacticamente correcto
				// De modo que se salta el token = sin comprobacion
				auxTabla = auxTabla->liga;
				// Si el siguiente es un =, ocurre una asignacion
				if (auxTabla != NULL && !strcmp(auxTabla->tipoToken, "AS"))
				{
					push(" = ");
					push(" ");
					push("S");
					imprimeDerivacion();
					auxTabla = auxTabla->liga;
					// mientras los siguientes sean no terminales S
					while (auxTabla != NULL && !strcmp(QPila->derivacion, "S"))
					{
						pop();
						// Si el tipo de la variable que guarda la asignacion es int
						if (!strcmp(tipo, "int"))
						{
							if (strcmp(auxTabla->tipDat, "int"))
							{
								if (auxTabla != NULL && !strcmp(auxTabla->lexema, "("))
								{
									push("(");
									auxTabla = auxTabla->liga;
									imprimeDerivacion();
									push("S");
									imprimeDerivacion();
								}
								else
								{
									cout << "Error encontrado en la semantica. Imposible asignar resultado de division a un entero" << endl;
							
									return -1;
								}
							}
							else if (!strcmp(auxTabla->liga->lexema, "/"))
							{
								cout << "Error encontrado en la semantica. Imposible asignar resultado de division a un entero" << endl;
						
								return -1;
							}
							else
							{
								push(auxTabla->tipDat);
								auxTabla = auxTabla->liga;
								if (auxTabla != NULL && !strcmp(auxTabla->lexema, ";"))
								{
									auxTabla = auxTabla->liga;
									push(";");
									imprimeDerivacion();
									break;
								}
								else if (auxTabla != NULL && !strcmp(auxTabla->tipoToken, "OA"))
								{
									push(" ");
									push(auxTabla->lexema);
									auxTabla = auxTabla->liga;
									push(" ");
									push("S");
									imprimeDerivacion();
								}
								else if (auxTabla != NULL && !strcmp(auxTabla->lexema, ")"))
								{
									push(")");
									imprimeDerivacion();
									auxTabla = auxTabla->liga;
									if (auxTabla != NULL && !(strcmp(auxTabla->tipoToken, "OA") || !strcmp(auxTabla->lexema, ";")))
									{
										if (auxTabla != NULL && !strcmp(auxTabla->lexema, ";"))
										{
											auxTabla = auxTabla->liga;
											push(";");
											imprimeDerivacion();
											break;
										}
										else if (auxTabla != NULL && !strcmp(auxTabla->tipoToken, "OA"))
										{
											push(" ");
											push(auxTabla->lexema);
											auxTabla = auxTabla->liga;
											push(" ");
											push("S");
											imprimeDerivacion();
										}
									}
								}
							}
						}
						else if (!strcmp(tipo, "float")) // Sino, si el tipo de la variable que guarda la asignacion es float
						{
							if (!strcmp(auxTabla->tipDat, "float") && !strcmp(auxTabla->tipDat, "int"))
							{
								cout << "Error encontrado en la semantica. No se reconoce el tipo de dato especificado." << endl;
				
								return -1;
							}
							else
							{
								if (auxTabla != NULL && !strcmp(auxTabla->lexema, "("))
								{
									push("(");
									auxTabla = auxTabla->liga;
									imprimeDerivacion();
									push("S");
									imprimeDerivacion();
									pop();
								}
								push(auxTabla->tipDat);
								auxTabla = auxTabla->liga;

								if (auxTabla != NULL && !strcmp(auxTabla->lexema, ";"))
								{
									auxTabla = auxTabla->liga;
									push(";");
									imprimeDerivacion();
									break;
								}
								else if (auxTabla != NULL && !strcmp(auxTabla->tipoToken, "OA"))
								{
									push(" ");
									push(auxTabla->lexema);
									auxTabla = auxTabla->liga;
									push(" ");
									push("S");
									imprimeDerivacion();
								}
								else if (auxTabla != NULL && !strcmp(auxTabla->lexema, ")"))
								{
									push(")");
									imprimeDerivacion();
									auxTabla = auxTabla->liga;
									if (auxTabla != NULL && (strcmp(auxTabla->tipoToken, "OA") || strcmp(auxTabla->tipoToken, "SEP")))
									{
										if (auxTabla != NULL && !strcmp(auxTabla->lexema, ";"))
										{
											auxTabla = auxTabla->liga;
											push(";");
											imprimeDerivacion();
											break;
										}
										else if (auxTabla != NULL && !strcmp(auxTabla->tipoToken, "OA"))
										{
											push(" ");
											push(auxTabla->lexema);
											auxTabla = auxTabla->liga;
											push(" ");
											push("S");
											imprimeDerivacion();
										}
									}
								}
							}
						}
						else
						{
							cout << "Error encontrado en la semantica. No se reconoce el tipo de dato especificado" << endl;
							return -1;
						}
					}
				}
			}
			else
			{
				auxTabla = auxTabla->liga;
			}
		}
		vaciaPila();

		if (auxTabla != NULL)
			push("G");
	}
	return 0;
}
