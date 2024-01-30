#!/bin/bash 

	
#awk -F";" '/46998;/ { print $1 ";" $3 ";" $4 }' data/data.csv > test1.csv


# va verifer s'il y a un argument au minimum
 

if [ $# -eq 0 ]
then 
    echo "Choisis une option entre -h, -d1, -d2, -l"
    exit 1
fi


#if [ -e   ]
#then
#else
#fi

# verification si le dossier images existe et si non le crée

images="images"

if [ -e $images ]
then 
	rm -r images
fi
mkdir images

# verifie si notre premier champ est un fichier 


if [ ! -f $0 ] 
then 
	echo "ce n'est pas un fichier"
fi 


# verification que le dossier des fichiers temporelles est présent ou bien le vide avant l'execution 

temp="temps"

if [ -e $temp ]
then 
	rm -r temps
fi
mkdir temps

# Execution des options 
 
 
# verfication que l'option -h est dans nos arguments 

for i in $@
do
	# affiche un message de tt les options disponible avec le temps d'execution
	if [ "$i" = "-h" ]
	then
			debut=$(date +%s)
			echo "voici les options"
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
        awk -F";" '/;1;/ {count[$6] += 1} END {for (line in count) print count[line] ";" line}' data/data.csv | sort -k1nr | head -10 > demo/resultatd1.csv
        ;;
    '-d2')
        awk -F";" '{count[$6] += $5} END {for (line in count) print count[line] ";" line}' data/data.csv | sort -k1nr | head -10 > demo/resultatd2.csv
        ;;
    '-l')
        awk -F";" '{count[$1] += $5} END {for (line in count) print count[line] ";" line}' data/data.csv | sort -k1nr | head -10 | sort -t";" -k2n > demo/resultatL.csv
        ;;
    '-t')
        #awk -F";" 'NR > 1 {tab[$1";"$4] +=1; if ($2==1) {tab[$1";"$3]+=1; deb[$1";"$3]=1}} END {for (ville in tab) print ville ";" tab[ville] ";" deb[ville] }' data/data.csv | awk -F";" '{tab[$2]+=1; deb[$2]+=$4} END {for (ville in tab) print ville ";" tab[ville] ";" deb[ville]}' > temps/temps_final.csv
        gcc -o t progc/t.c
        chmod +x progc/t.c
        ./t > demo/resultatt.csv;;
    '-s')
         #LC_NUMERIC=C awk -F";" '{count[$1]+= $5; nm[$1]+=1; if(min[$1]=="" || min[$1]>$5) min[$1]=$5; if(max[$1]=="" || max[$1]<$5) max[$1]=$5;} END {for (line in max) print line ";" count[line]/nm[line] ";" max[line] ";" min[line] ";" max[line]-min[line] }' data/data.csv > temps/tempss.csv
        gcc -o s progc/s.c
        chmod +x progc/s.c
        ./s > demo/resultats.csv
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








 


