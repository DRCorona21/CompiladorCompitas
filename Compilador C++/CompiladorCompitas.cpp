
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include "Compilador.h"
int main(void)
{

	const char *archivo = "archivofuente.txt";	// Archivo de entrada
	const char *archivoCPP = "archivofuente.cpp";	// Archivo que guarda la traduccion de asm compliada
	const char *programa = "programafinal.asm"; // Estructura archivo de salida

	// En lugar de ingresar una cadena, se leen del archivo
	cout << endl
		 << "\t\tComprobando Lexemas";
	if (!LeeArchivo(archivo))
	{
		cout
			<< endl
			<< "Lexemas correctos"
			<< endl;
		cout
			<< "\t\tAnalisis de sintaxis" << endl
			<< "Impresion de arbol de lexemas y sintaxis" << endl;
		if (!AnalizadorSintactico(PTabla, 0))
		{
			ImprimeTabla(); //Funcion que nos ayuda a depurara errores en la primera fase
			cout
				<< "Sintaxis adecuada" << endl
				<< endl;
			cout
				<< "\t\tComprobacion de semantica" << endl
				<< "Impresion de arbol de Semantica" << endl
				<< "Semantica token por token" << endl;
			if (!AnalizadorSemantico(PTabla, 0))
			{
				cout
					<< "\t\tSemantica adecuada"
					<< endl;
				cout
					<< "\t\tTraduccion a ensamblador x86 M32" << endl;
				EscribeEnsamblador(programa);
			}
		}
	}
	fileFuente(archivoCPP);
	cout << endl
		 << "Presione una tecla para continuar..." << endl;
	getchar();
	// Compilacion de archivo final y depurador
	
	system("g++ -m32 -o compilacionExitosa.exe archivofuente.cpp");

	cout << "Archivo depuracion y ejecutable creado" << endl;
	cout << endl
		 << "Presione una tecla para finalizar..." << endl;
		 system("start compilacionExitosa.exe");
	getchar();
	return 0;
}
