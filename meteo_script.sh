#!/bin/bash

function loc {
	local loc=$1
	local opt=$2
	local csv_file=$3
	if [ "$loc" = "-F" -o "$loc" = "-f" ]; then 
		echo "La localisation choisie est : $loc"
		echo "L'option choisie est : $opt"
		awk -F ";" '{split($3,coord,",");
		if (coord[1]+0 >= 41 && coord[1]+0 <= 51 && coord[2]+0 >= -4 && coord[2]+0 <= 8) print $1 ";" $2 ";" $4}' "$csv_file" > temp && mv temp "$csv_file"
	elif [ "$loc" = "-G" -o "$loc" = "-g" ]; then 
		awk -F ";" '{split($3,coord,",");
		if (coord[1]+0 >= 2 && coord[1]+0 <= 6 && coord[2]+0 >= -54 && coord[2]+0 <= -51) print $1 ";" $2 ";" $4}' "$csv_file" > temp && mv temp "$csv_file"
	elif [ "$loc" = "-S" -o "$loc" = "-s" ]; then 
		awk -F ";" '{split($3,coord,",");
		if (coord[1]+0 >= 46 && coord[1]+0 <= 47 && coord[2]+0 >= -57 && coord[2]+0 <= -56) print $1 ";" $2 ";" $4}' "$csv_file" > temp && mv temp "$csv_file"
	elif [ "$loc" = "-A" -o "$loc" = "-a" ]; then 
		awk -F ";" '{split($3,coord,",");
		if (coord[1]+0 >= 12 && coord[1]+0 <= 16 && coord[2]+0 >= -63 && coord[2]+0 <= -59) print $1 ";" $2 ";" $4}' "$csv_file" > temp && mv temp "$csv_file"
	elif [ "$loc" = "-O" -o "$loc" = "-o" ]; then 
		awk -F ";" '{split($3,coord,",");
		if (coord[1]+0 >= -34 && coord[1]+0 <= -11 && coord[2]+0 >= 33 && coord[2]+0 <= 178) print $1 ";" $2 ";" $4}' "$csv_file" > temp && mv temp "$csv_file"
	elif [ "$loc" = "-Q" -o "$loc" = "-q" ]; then 
		awk -F ";" '{split($3,coord,",");
		if (coord[1]+0 >= -75 && coord[1]+0 <= -45 && coord[2]+0 >= 52 && coord[2] <= 93) print $1 ";" $2 ";" $4}' "$csv_file" > temp && mv temp "$csv_file"
	fi
}

function colonne {
	local csv_file=$1
	awk -F ";" '{print $1 ";" $2 ";" $4}' "$csv_file" > temp && mv temp "$csv_file"
}

function compil {
	local arg1=$1
	local arg2=$2
	local arg3=$3
	local arg4=$4
	
	make 
	
	./main "$arg1" "$arg2" "$arg3" > "$arg4"
	
	if [ $? -eq 1 ]; then
		echo "Erreur sur les options, si problème entrez --help"
	elif [ $? -eq 2 ]; then
		echo "Erreur sur le fichier d'entrée"
	elif [ $? -eq 3 ]; then
		echo "Erreur sur le fichier de sortie"
	elif [ $? -eq 4 ]; then
		echo "Erreur d'exécution interne"
	elif [ $? -eq 0 ]; then
		echo "Exécution réussie"
	fi
	
	make clean
}

i=0
while [ True ]; do
	if [ "$1" = "-t1" ]; then 
		awk -F ";" 'NR>1 && $1 != "" && $2 != "" && $11 != "" {print $1 ";" substr($2, 1, 19) ";" $10 ";" $11}' data.csv > Temp1.csv
		tab[i]="Temp1.csv"
		opt[i]="$1"
		i=$((i+1))
		shift 1
	elif [ "$1" = "-t2" ]; then
		awk -F";" 'NR>1 && $1 != "" && $2 != "" && $11 != "" {print $1 ";" substr($2, 1, 19) ";" $10 ";" $11}' data.csv >> Temp2.csv
		tab[i]="Temp2.csv"
		opt[i]="$1"
		i=$((i+1))
		shift 1
	elif [ "$1" = "-t3" ]; then
		awk -F ";" 'NR>1  && $1 != "" && $2 != "" && $11 != "" {print $1 ";" substr($2, 1, 19) ";" $10 ";" $11}' data.csv >> Temp3.csv
		tab[i]="Temp3.csv"
		opt[i]="$1"
		i=$((i+1))
		shift 1	
	elif [ "$1" = "-p1" ]; then 
		awk -F ";" 'NR>1  && $1 != "" && $2 != "" && $7 != "" {print $1 ";" substr($2, 1, 19) ";" $10 ";" $7}' data.csv >> Press1.csv
		tab[i]="Press1.csv"
		opt[i]="$1"
		i=$((i+1))
		shift 1
	elif [ "$1" = "-p2" ]; then
		awk -F";" 'NR>1  && $1 != "" && $2 != "" && $7 != "" {print $1 ";" substr($2, 1, 19) ";" $10 ";" $7}' data.csv >> Press2.csv
		tab[i]="Press2.csv"
		opt[i]="$1"
		i=$((i+1))
		shift 1
	elif [ "$1" = "-p3" ]; then
		awk -F ";" 'NR>1  && $1 != "" && $2 != "" && $7 != "" {print $1 ";" substr($2, 1, 19) ";" $10 ";" $7}' data.csv >> Press3.csv
		tab[i]="Press3.csv"
		opt[i]="$1"
		i=$((i+1))
		shift 1	
	elif [ "$1" = "-w" ]; then
		awk -F ";" 'NR>1  && $1 != "" && $2 != "" && $5 != "" {print $1 ";" $4 ";" $10 ";" $5}' data.csv >> Wind.csv
		tab[i]="Wind.csv"
		opt[i]="$1"
		i=$((i+1))
		shift 1
	elif [ "$1" = "-m" ]; then
		awk -F ";" 'NR>1  && $1 != "" && $2 != "" && $6 != "" {print $1 ";" $6 ";" $10}' data.csv >> Moisture.csv
		tab[i]="Moisture.csv"
		opt[i]="$1"
		i=$((i+1))
		shift 1
	elif [ "$1" = "-h" ]; then
		awk -F ";" 'NR>1  && $1 != "" && $2 != "" && $14 != "" {print $1 ";" substr($2, 1, 19) ";" $10 ";" $14}' data.csv >> Height.csv
		tab[i]="Height.csv"
		opt[i]="$1"
		i=$((i+1))
		shift 1
	elif [ "$1" = "--help" ]; then
		echo "bash [Options] [File]
		Affiche un graphique météorologique selon l'option choisie :
		OPTIONS METEO: (non exclusives)
		-t1: température moyenne, min et max par station, format:barre d'erreur
		-t2: température moyenne par date, format: ligne simple
		-p1: pression moyenne, min et max par station, format:barre d'erreur
		-p2: pression moyenne par date, format: ligne simple
		-h: altitude par station, format: carte interpolée et colorée
		-m: altitude par station, format: carte interpolée et colorée
		OPTIONS LOCALISATION: (exclusives)
		-F: France métropolitaine et Corse
		-G: Guyane française
		-S: Saint-Pierre et Miquelon
		-A: Antilles
		-O: Océan Indien
		-Q: Antartique
		FORMAT DE TRI:(exclusives)
		--avl
		--abr
		--tab
		FICHIER:
		data.csv
		exemple de commande: bash meteo_script.sh -t1 -h --abr data.csv"
		shift 1
	elif [ "$1" = "--abr" -o "$1" = "--ABR" -o "$1" = "--avl" -o "$1" = "--AVL" -o "$1" = "--tab" -o "$1" = "--TAB" ]; then
		if [ -z "$format" ]; then
			format=$1
			shift 1
		else
			echo "Too much arguments of structures"
			exit
		fi
	elif [ "$1" = "-F" -o "$1" = "-f" -o "$1" = "-G" -o "$1" = "-g" -o "$1" = "-S" -o "$1" = "-s" -o "$1" = "-A" -o "$1" = "-a" -o "$1" = "-O" -o "$1" = "-o" -o "$1" = "-q" -o "$1" = "-Q" ]; then
		if [ -z "$LOC" ]; then
			LOC=$1
			shift 1
		else
			echo "Too much arguments of localisation"
			exit
		fi
	elif [ "$1" = "*.csv" ]; then
		doc="$1"
		if [ "$1" != "data.csv" ]; then
			echo "Erreur: $1 n'est pas autorisé."
			exit 2
		elif [ ! -f "$1" ]; then
			echo "Erreur: $1 n'existe pas dans le dossier courant."	
		else
			echo "Erreur: $1 n'est pas un fichier csv."
		fi
		shift 1
	else	
		break		
	fi

done

j=0
if [ ! -z "$LOC" ]; then
	for i in "${tab[@]}"; do 
		loc "$LOC" "${opt[j]}" "$i" 
		j=$((j+1))
	done
else
	for i in "${tab[@]}"; do
		colonne "$i"
	done
fi

j=0
if [ ! -z "$format" ]; then
	for i in "${tab[@]}"; do 
		cat "$i" > texte.txt
		compil "texte.txt" "${opt[j]}" "$format" "$i"
		j=$((j+1))
	done
else
	for i in "${tab[@]}"; do 
		cat "$i" > texte.txt
		compil "texte.txt" "${opt[j]}" "--abr" "$i"
		j=$((j+1))
	done
fi
rm -f texte.txt

k=0
for i in "${opt[@]}"; do 
	if [ "$i" = "-t1" ]; then 
		gnuplot -persist <<-EOFMarker
  		set datafile separator ";"
  		set xlabel "ID de station"
  		set ylabel "Température"
  		set title "Températures par station"
  		plot "${tab[k]}" using 1:4 with lines title "minimum", \
       		"${tab[k]}" using 1:5 with lines title "maximum", \
       		"${tab[k]}" using 1:4:5 with filledcurves title "espace entre minimum et maximum" fillstyle transparent solid 0.25 noborder, \
       		"${tab[k]}" using 1:3 with lines title "moyenne"
		EOFMarker
	elif [ "$i" = "-p1" ]; then 
		gnuplot -persist <<-EOFMarker
  		set datafile separator ";"
  		set xlabel "ID de station"
  		set ylabel "Pression"
  		set title "Pressions par station"
  		plot "${tab[k]}" using 1:4 with lines title "minimum", \
       		"${tab[k]}" using 1:5 with lines title "maximum", \
       		"${tab[k]}" using 1:4:5 with filledcurves title "espace entre minimum et maximum" fillstyle transparent solid 0.25 noborder, \
       		"${tab[k]}" using 1:3 with lines title "moyenne"
		EOFMarker
	elif [ "$i" = "-t2" ]; then 
		gnuplot -persist <<-EOFMarker
  		set datafile separator ";"
  		set xdata time
  		set timefmt "%Y-%m-%dT%H:%M"
  		set xlabel "Date"
  		set ylabel "Température"
  		set title "Températures moyennes au cours du temps"
  		plot "${tab[k]}" using 2:3 with lines title "Température"
		EOFMarker
	elif [ "$i" = "-p2" ]; then 
		gnuplot -persist <<-EOFMarker
  		set datafile separator ";"
  		set xdata time
  		set timefmt "%Y-%m-%dT%H:%M"
  		set xlabel "Date"
  		set ylabel "Pression"
  		set title "Pressions moyennes au cours du temps"
  		plot "${tab[k]}" using 2:3 with lines title "Pression"
		EOFMarker
	elif [ "$i" = "-h" ]; then 
		while read line; do
			id=$(echo $line | awk -F";" '{print $1}')
			coord=$(grep -m 1 $id data.csv | awk -F";" '{print $10}')
			echo "$line;$coord" 
		done < "${tab[k]}" > nv.csv

		awk -F ";" '{split($4,coords,","); print $1 ";" $2 ";" $3 ";" coords[1] ";" coords[2]}' nv.csv > coords.csv
		gnuplot -persist <<-EOFMarker
  		set datafile separator ";"
  		set xlabel "Longitude"
  		set ylabel "Latitude"
  		set title "Diagramme carte interpolée"
  		set pm3d map
  		splot "coords.csv" using 4:5 with pm3d
		EOFMarker
	fi
	k=$((k+1))
done

for i in "${tab[@]}"; do 
		rm -f "$i"
	done





