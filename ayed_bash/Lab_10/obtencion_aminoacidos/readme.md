#Conteo de residuos cargados en proteínas
Sistema automatizado que permite contar aminoácidos cargados en diferentes proteínas usando archivos .pdb

Descripción general:
El script residuos_cargados.sh analiza una lista de proteínas y una lista de residuos cargados.
Para cada combinación, se busca en el archivo .pdb correspondiente cuántas veces aparece ese residuo considerando CA (carbono alfa).
El resultado final es un archivo csv que resume el número de residuos cargados por proteína.

#Arquitectura del proyecto
residuos_cargados.sh // Ejecutable para linux encargado del procesamiento y generación de resultados.
residuos_cargados.csv // Archivo geenrado con el conteo de residuos.

Archivos requeridos:
HEM_A.pdb
GFP_A.pdb
ACE2_A.pdb

#Consideraciones al ejecutar 
forma de ejecución: ./residuos_cargados.sh

#Requisitos:
Tener los archivos .pdb en la misma carpeta del script.
Se debe otorgar permisos de ejecución si es necesario.

#Formato del csv generado:
aas;HEM;GFP;ACE2
LYS;#;#;#
ARG;#;#;#
HIS;#;#;#
GLU;#;#;#
ASP;#;#;#

#Módulos del script
-Definición de proteínas y residuos (proteínas=HEM,GFP,ACE2; residuos cargados=LYS, ARG, HIS, GLU, ASP)
-Conteo de residuos: para cada residuo se realiza "grep "$res" ${p}_A.pdb | grep "CA" | wc -l", así se busca el residuo en el archivo .pdb y se filtran las líneas con CA, además cuenta el total.
-Generación del CSV: genera la cabecera y una línea por cada residuo con los valores correspondientes a cada proteína. Muestra "archivo generado: residuos_cargados.csv"

#Instalación
Requisitos mínimos: 
-Bash linux
-comandos estándar: grep, wc, echo

#Resultado esperado
-Se crea un archivo residuos_cargados.csv
-Se genera un resumen con el conteo de residuos por proteína
-Se confirma el archivo generado.

#Autoría
Catalina Rojas Sepúlveda
Estudiante de Ingeniería Civil en Bioinformática
Universidad de Talca - Facultad de Ingeniería
