#include <cstdio>

FILE *Archivo2;

void fileFuente(const char *arc)
{
    Archivo2 = fopen(arc, "w");
    if (Archivo2 != nullptr)
    {
        fprintf(Archivo2, "#include <stdlib.h>\n");
        fprintf(Archivo2, "#include <stdio.h>\n");
        fprintf(Archivo2, "int main(int argc, char const *argv[])\n");
        fprintf(Archivo2, "{\n");
        fprintf(Archivo2, "    printf(\"Compilacion Exitosa desde el .ASM\\n\");\n");
        fprintf(Archivo2, "    printf(\"Traduccion a codigo Maquina exitosa desde el .ASM\\n\");\n");
        fprintf(Archivo2, "    printf(\"Presione una tecla para continuar...\\n\");\n");
        fprintf(Archivo2, "    getchar();\n");
        fprintf(Archivo2, "    return 0;\n");
        fprintf(Archivo2, "}\n");
        fclose(Archivo2);
    }
    else
    {
        printf("Error opening file.\n");
    }
}
