# Compilador Compitas

README para uso del Compliador.

## Instrucciones de uso
Es necesario tener instalado algun compilador basico de C++ como gcc o g++
Todas las pruebas correspondientes fueron hecas desde Visual Studio Code.
## 1
Crear el archivo fuente con extension .txt y de nombre 'archivofuente' 
con las gramaticas aceptadas por el compilador, veanse mas adelante.
## 2
Ejecutar en el compilador de su gusto (recomendamos Visual Studio Code) CompiladorCompitas.cpp
## 3
Se crearan distintos archivos en la carpeta
Uno con extension .ASM que es la traduccion a Assembly
Y uno con extension .exe que es la prueba de ejecucion.
## Nota
El archivo exe generado como prueba final es un print que nostros agregamos en la fase final de la compilacion
Ya que de momento todavia no acepta el lexico, sintaxis y semantica de un printf, cout o cin
Es por eso que no se puede mostrar algo tangible en pantalla mas que un mensaje comprobando que la compilacion fue exitosa
Para comprobar que todas las fases fueron exitosas se puede revisar minuciosamente el .asm que contiene la traduccion a 
assemby.
## Gramáticas del compilador

Las siguientes son las gramáticas definidas en el compilador.

Gramática de asignación:
```txt
S -> int V | float V ;
V -> ID, V | ID
```

Gramática de operaciones aritméticas:
```txt
S -> ID = V;
V -> ID + V | num + V | ID - V | num - V | num - V | ID * V | num * V |
     ID / V | num / v | ID | num
```

Gramática de while:
```txt
S -> while ( C ) { sentencia } | while ( C ) { S } |
     while ( C ) { S sentencias } | while ( C ) { sentencias S sentencias }
    
C  -> CR OL C | CR
CR -> id OR id | id OR num | num OR id
OL -> && | || 
OR -> < | > | <= | >= | == | !=
```
Gramaticas especificas aceptadas por el compilador

Inicio
|
V
Definir nombres de archivo
|
V
Verificar lexemas leyendo un archivo
|
V
Si los lexemas son correctos:
|
|----> Realizar análisis de sintaxis
|      |
|      V
|      Si la sintaxis es adecuada:
|      |
|      |----> Realizar comprobación semántica
|      |      |
|      |      V
|      |      Si la semántica es adecuada:
|      |      |
|      |      |----> Realizar traducción a ensamblador x86 M32
|      |
|      |
|      Fin
|
Escribir archivo de código fuente en C++
|
Compilar archivo generado
|
Imprimir mensajes y esperar interacción del usuario
|
Fin
