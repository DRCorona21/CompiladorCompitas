int indID = 0, indNE = 201, indND = 301, indNX = 401;

void AgregaTablaSimbolos(const char *lex, int tiptok)
{
	nuevoTabla = (TSimbolos *)malloc(sizeof(TSimbolos));
	strcpy(nuevoTabla->lexema, lex);
	nuevoTabla->liga = NULL;
	switch (tiptok)
	{
	case 1:
		strcpy(nuevoTabla->tipoToken, "ID");
		if (QTabla != NULL)
			strcpy(nuevoTabla->tipDat, QTabla->lexema);
		strcpy(nuevoTabla->regla, "D(D|A)*");
		nuevoTabla->ind = indID;
		indID++;
		break;
	case 2:
		strcpy(nuevoTabla->tipoToken, "PR");
		if (!strcmp(lex, "int"))
		{
			nuevoTabla->ind = 517;
			strcpy(nuevoTabla->tipDat, "int");
			strcpy(nuevoTabla->regla, "int ID");
		}
		else if (!strcmp(lex, "float"))
		{
			nuevoTabla->ind = 518;
			strcpy(nuevoTabla->tipDat, "float");
			strcpy(nuevoTabla->regla, "float ID");
		}
		else if (!strcmp(lex, "while"))
		{
			nuevoTabla->ind = 519;
			strcpy(nuevoTabla->tipDat, "NULL");
			strcpy(nuevoTabla->regla, "while(C){S}");
		}
		break;
	case 3:
		strcpy(nuevoTabla->tipoToken, "OR");
		if (!strcmp(lex, ">"))
		{
			nuevoTabla->ind = 503;
		}
		else if (!strcmp(lex, "<"))
		{
			nuevoTabla->ind = 504;
		}
		else if (!strcmp(lex, ">="))
		{
			nuevoTabla->ind = 505;
		}
		else if (!strcmp(lex, "<="))
		{
			nuevoTabla->ind = 506;
		}
		else if (!strcmp(lex, "!="))
		{
			nuevoTabla->ind = 507;
		}
		else if (!strcmp(lex, "=="))
		{
			nuevoTabla->ind = 508;
		}

		break;
	case 4:
		strcpy(nuevoTabla->tipoToken, "AS");
		nuevoTabla->ind = 800; // Indice de la asignacion
		strcpy(nuevoTabla->tipDat, "NULL");
		strcpy(nuevoTabla->regla, "ID = ID|num");
		break;
	case 5:
		strcpy(nuevoTabla->tipoToken, "OL");
		if (!strcmp(lex, "&&"))
		{
			nuevoTabla->ind = 501;
		}
		else if (!strcmp(lex, "||"))
		{
			nuevoTabla->ind = 502;
		}
		break;
	case 6:
		strcpy(nuevoTabla->tipoToken, "OA");
		strcpy(nuevoTabla->regla, "Aritm.");
		switch (lex[0])
		{
		case '*':
			nuevoTabla->ind = 510;
			break;
		case '/':
			nuevoTabla->ind = 511;
			break;
		case '+':
			nuevoTabla->ind = 512;
			break;
		case '-':
			nuevoTabla->ind = 513;
			break;
		case '=':
			nuevoTabla->ind = 514;
			break;
		}
		break;
	case 7:
		strcpy(nuevoTabla->tipoToken, "NE");
		strcpy(nuevoTabla->tipDat, "int");
		strcpy(nuevoTabla->regla, "Aritm.");
		nuevoTabla->ind = indNE;
		indNE++;
		break;
	case 8:
		strcpy(nuevoTabla->tipoToken, "ND");
		strcpy(nuevoTabla->regla, "Aritm.");
		nuevoTabla->ind = indND;
		indND++;
		break;
	case 9:
		strcpy(nuevoTabla->tipoToken, "NX");
		strcpy(nuevoTabla->regla, "Aritm.");
		nuevoTabla->ind = indNX;
		indNX++;
		break;

	case 10:
		strcpy(nuevoTabla->tipoToken, "SEP");
		switch (lex[0])
		{
		case ',':
			nuevoTabla->ind = 515;
			break;
		case ';':
			nuevoTabla->ind = 516;
			strcpy(nuevoTabla->tipDat, "NULL");
			strcpy(nuevoTabla->regla, "S;");
			break;
		}
		break;
	case 11:
		strcpy(nuevoTabla->tipoToken, "PAR");
		switch (lex[0])
		{
		case '(':
			nuevoTabla->ind = 701;
			strcpy(nuevoTabla->tipDat, "NULL");
			strcpy(nuevoTabla->regla, "(S)");
			break;
		case ')':
			nuevoTabla->ind = 702;
			strcpy(nuevoTabla->tipDat, "NULL");
			strcpy(nuevoTabla->regla, "(S)");
			break;
		}
		break;
	case 12:
		strcpy(nuevoTabla->tipoToken, "LLA");
		switch (lex[0])
		{
		case '{':
			nuevoTabla->ind = 801;
			strcpy(nuevoTabla->tipDat, "NULL");
			strcpy(nuevoTabla->regla, "{S}");
			break;
		case '}':
			nuevoTabla->ind = 802;
			strcpy(nuevoTabla->tipDat, "NULL");
			strcpy(nuevoTabla->regla, "{S}");
			break;
		}
		break;
	}

	if (PTabla == NULL)
	{
		PTabla = nuevoTabla;
		QTabla = PTabla;
	}
	else
	{
		QTabla->liga = nuevoTabla;
		QTabla = nuevoTabla;
	}
}