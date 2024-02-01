#!/bin/bash 

EXEC="progc/exec"
images="images"
nombre_fichier=$((`ls -l $images | wc -l` -1))
temp="temps"
dossier="data/data.csv"

# va verifer s'il y a un argument au minimum

if [ $# -eq 0 ]
then 
    echo "Choisis une option entre -h, -d1, -d2, -l"
    exit 1
fi

#Vérification de l'executable C

if [ ! -e $EXEC ]
then
	cd progc
	make
	cd ..
else
	echo "L'executable C existe bien"
fi

# verification si le dossier images existe et si non le crée

if [ -e $images ]
then 
	if [ $nombre_fichier -ne 0 ]
	then
		mv images/* demo
	fi
else
	mkdir images
fi

# verifie si notre premier champ est un fichier 

if [ ! -f $0 ] 
then 
	echo "ce n'est pas un fichier"
fi 

# verification que le dossier des fichiers temporelles est présent ou bien le vide avant l'execution 

if [ -e $temp ]
then 
	rm -r temps
fi
mkdir temps

#Vérification du fichier data

if [ ! -e $dossier ]
then
	echo "Le fichier data.csv n'existe pas dans le dossier data"
	exit 1
fi

#Vérification de la saisie du premier champs

if [ $1 != "data.csv" ]
then 
	echo "Veuillez renommer data.csv pour le premier champs"
	exit 1
fi	

# Execution des options 

shift
 
# verfication que l'option -h est dans nos arguments 

for i in $@
do
	# affiche un message de tt les options disponible avec le temps d'execution
	if [ "$i" = "-h" ]
	then
			debut=$(date +%s)
			echo "Voici les options existantes -d1 -d2 -l -s -t"
			fin=$(date +%s)
			duree=$(($fin - $debut ))
			echo "Execution : $duree secondes" 
			exit 3
	fi
done

# identifie les options afin de les executer et donne le temps d'execution 

for i in "$@"; do
    debut=$(date +%s)

    case $i in
    
    '-d1')
        awk -F";" '/;1;/ {count[$6] += 1} END {for (line in count) print count[line] ";" line}' data/data.csv | sort -k1nr | head -10 > temps/resultatd1.csv
        gnuplot Gnuplots/traitement1.gn
        convert -rotate 90 resultatd1.png figureD1.png
        rm resultatd1.png
	   mv figureD1.png images
        ;;
        
    '-d2')
        awk -F";" '{count[$6] += $5} END {for (line in count) print count[line] ";" line}' data/data.csv | sort -k1nr | head -10 > temps/resultatd2.csv
        gnuplot Gnuplots/traitement2.gn
	   convert -rotate 90 resultatd2.png figureD2.png
	   rm resultatd2.png
	   mv figureD2.png images
        ;;
        
    '-l')
        awk -F";" '{count[$1] += $5} END {for (line in count) print count[line] ";" line}' data/data.csv | sort -k1nr | head -10 | sort -t";" -k2n > temps/resultatL.csv
        gnuplot Gnuplots/traitementL.gnu
	   mv figureL.png images
        ;;
        
    '-t')
        awk -F";" 'NR > 1 {count[$1";"$4] +=1; if ($2==1) {count[$1";"$3]+=1; deb[$1";"$3]=1}} END {for (ville in count) print ville ";" count[ville] ";" deb[ville] }' data/data.csv > temps/tempst.csv
        awk -F";" '{count[$2]+=1; deb[$2]+=$4} END {for (ville in count) print ville ";" count[ville] ";" deb[ville]}' temps/tempst.csv > temps/temps_final.csv
        ./progc/exec -t > temps/resultatt.csv
        gnuplot Gnuplots/traitementT.gn
        mv figureT.png images
        ;;
        
    '-s')
        #LC_NUMERIC=C awk -F";" '{count[$1]+= $5; nm[$1]+=1; if(min[$1]=="" || min[$1]>$5) min[$1]=$5; if(max[$1]=="" || max[$1]<$5) max[$1]=$5;} END {for (line in count) print line ";" count[line]/nm[line] ";" min[line] ";" max[line] ";" max[line]-min[line]}' data/data.csv > temps/tempss.csv
        ./progc/exec -s > temps/resultats.csv
        gnuplot Gnuplots/traitementS.gn
        mv figureS.png images
        ;;
    *)
        echo "Erreur : Veuillez choisir une autre option."
        ;;
    esac

    fin=$(date +%s)
    duree=$(($fin - $debut))
    echo "Execution : $duree secondes"
done





# BONUS


#						option 1.bis même temps d'execution

#	grep ";1;" data.csv | cut -d";" -f6 | sort -k1 > datatestd1.csv
#	awk -F';' '{ line = $0; gsub(/\r/,"",line); if (line == prev_line) count++; else {print count ";" prev_line ; count = 1}; prev_line = line;}' datatestd1.csv | sort -k1nr | head -10 > resultatd1.csv


#						option 2.bis plus de 34s d'execution

#	awk -F";" '{ print $5 "; " $6 }' data.csv | sort -t";" -k2 > datatestd2.csv
#	awk -F";" '{ line = $2; gsub(/\r/,"",line); if (line == prev_line) count += $1 ; else {print count ";" prev_line ; count = $1 }; prev_line = line;}' datatestd2.csv | sort -k1nr | head -10 > resultatd2.csv


#						option 3.bis plus de 46s d'execution

#	awk -F";" '{ print $1 ";" $5 }' data.csv | sort -t";" -k1 -n > datatestd3.csv
#	awk -F";" '{ line = $1; gsub(/\r/,"",line); if (line == prev_line) count += $2 ; else {print count ";" prev_line ; count = $2 }; prev_line = line;}' datatestd3.csv | sort -k1nr | head -10 > resultatd3.csv








 


