/* Contiene AnalizadorLexico() e identificaTipo() */
const char *palRes[] = {"int", "float", "while"};
int i;
// Tabla de valores de tokens
// 1: ID
// 3: Operador Relacional
// 4: Asignacion
// 5: Operador Logico
// 6: Operador Aritmetico
// 7: Entero
// 8: Decimal
// 9: Exponencial
int AnalizadorLexico(const char *lex)
{
	int t = strlen(lex), tipTok = 0;
	i = 0;
	// Todos los tipos de caso para cada token
	switch (lex[i])
	{
	case 'a' ... 'z':
	case 'A' ... 'Z':
		tipTok = 1;
		i++;
		while (i < t && isalnum(lex[i]))
			i++;
		break;
	case '<':
	case '>':
	case '=':
	case '!':
		if (lex[i] == '!')
			tipTok = 5;
		else if (lex[i] == '=')
			tipTok = 4;
		else
			tipTok = 3;
		i++;
		if (i < t && lex[i] == '=')
		{
			tipTok = 3;
			i++;
		}
		break;
	case '*':
	case '/':
		tipTok = 6;
		i++;
		break;
	case '&':
		i++;
		if (i < t && lex[i] == '&')
		{
			tipTok = 5;
			i++;
		}
		else
			tipTok = 0;
		break;
	case '|':
		i++;
		if (i < t && lex[i] == '|')
		{
			tipTok = 5;
			i++;
		}
		else
			tipTok = 0;
		break;
	case '0' ... '9':
	case '+':
	case '-':
		if (lex[i] == '+' || lex[i] == '-')
		{
			tipTok = 6;
			i++;
		}
		if (i < t && lex[i] >= '0' && lex[i] <= '9')
		{
			i++;
			tipTok = 7;
			while (i < t && lex[i] >= '0' && lex[i] <= '9')
				i++;
			if (i < t && lex[i] == '.')
			{
				i++;
				if (i < t && lex[i] >= '0' && lex[i] <= '9')
				{
					tipTok = 8;
					while (i < t && lex[i] >= '0' && lex[i] <= '9')
						i++;
				}
				else
					return 0;
			}
			if (i < t && lex[i] == 'e' || lex[i] == 'E')
			{
				i++;
				if (i < t && lex[i] == '+' || lex[i] == '-')
					i++;
				if (i < t && lex[i] >= '0' && lex[i] <= '9')
				{
					tipTok = 9;
					while (i < t && lex[i] >= '0' && lex[i] <= '9')
						i++;
				}
				else
					return 0;
			}
		}
		break;
	case ';':
	case ',':
		tipTok = 10;
		i++;
		break;
	case '(':
	case ')':
		tipTok = 11;
		i++;
		break;
	case '{':
	case '}':
		tipTok = 12;
		i++;
		break;
	default:
		break;
	}
	return tipTok;
}

int identificaTipo(const char *cad)
{
	int tipo = AnalizadorLexico(cad);
	char seAgrega[1000];
	memset(seAgrega, 0, sizeof(seAgrega));
	strncpy(seAgrega, cad, i);

	// 2: Palabra Reservada
	int c = 0;
	if (tipo == 1)
		while (c < 3)
		{
			if (!strcmp(seAgrega, palRes[c]))
			{
				tipo = 2;
				break;
			}
			c++;
		}

	switch (tipo)
	{
	case 1:
		return 1;
	case 2:
		return 2;
	case 3:
		return 3;
	case 4:
		return 4;
	case 5:
		return 5;
	case 6:
		return 6;
	case 7:
		return 7;
	case 8:
		return 8;
	case 9:
		return 9;
	case 10:
		return 10;
	case 11:
		return 11;
	case 12:
		return 12;
	default:
		return -1;
	}
}