struct TSimbolos
{
	//datos
	char lexema[100];
	char tipoToken[100];
	char tipDat[100];
	char regla[100];
	int ind;
	char derivacion[100];
	//liga
	TSimbolos *liga;
} *PTabla, *QTabla, *auxTabla, *nuevoTabla;