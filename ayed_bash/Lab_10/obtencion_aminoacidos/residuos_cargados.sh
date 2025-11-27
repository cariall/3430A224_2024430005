#Proteínas a analizar
proteinas=("HEM" "GFP" "ACE2")
residuos=("LYS" "ARG" "HIS" "GLU" "ASP")

output="residuos_cargados.csv"

#la cabecera
echo "aas;HEM;GFP;ACE2" > $output 

for res in "${residuos[@]}"; do
linea="$res"

	#recorre las proteínas
	for p in "${proteinas[@]}"; do
		count=$(grep "$res" ${p}_A.pdb | grep " CA " | wc -l)
		linea="$linea;$count"
	done

	echo "$linea" >> $output
done

echo "Archivo generado: $output"
