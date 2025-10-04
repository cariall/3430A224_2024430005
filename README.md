Los comandos utilizados para pasar de pdb a txt fueron:

awk 'BEGIN{OFS=";"} /^ATOM/ {print substr($0,18,3), substr($0,22,1), substr($0,23,4)}' 1UHM.pdb > 1UHM_Resids.pdb
grep ';A;' 1UHM_Resids.pdb > 1UHM_Resids_ChainA.pdb
awk 'BEGIN{FS=";";OFS=""}{print $1, $3}' 1UHM_Resids_ChainA.pdb > 1UHM_Resids_ChainA_Format.pdb
uniq 1UHM_Resids_ChainA_Format.pdb > 1UHM_Resids_ChainA_Format_Uniq.txt 
awk '!seen[$0]++' 1UHM_Resids_ChainA_Format_Uniq.txt > 1UHM_RESIDS_final.txt

Se utilizó '!seen[$0]++' para eliminar todos aquellos resn y resid iguales que no fuesen consecutivos para facilitar
la ejecución del programa.

Ejecución del programa:
g++ Rojas_Catalina_Actividad_2.cpp -o programa
./programa

Generación de png y dot se guardan en la carpeta destino donde se ejecuta el programa.
