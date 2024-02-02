#!/bin/bash 

clear


echo "	░█████╗░██╗░░░██╗░░░░░░████████╗██████╗░██╗░░░██╗░█████╗░██╗░░██╗░██████╗
	██╔══██╗╚██╗░██╔╝░░░░░░╚══██╔══╝██╔══██╗██║░░░██║██╔══██╗██║░██╔╝██╔════╝
	██║░░╚═╝░╚████╔╝░█████╗░░░██║░░░██████╔╝██║░░░██║██║░░╚═╝█████═╝░╚█████╗░
	██║░░██╗░░╚██╔╝░░╚════╝░░░██║░░░██╔══██╗██║░░░██║██║░░██╗██╔═██╗░░╚═══██╗
	╚█████╔╝░░░██║░░░░░░░░░░░░██║░░░██║░░██║╚██████╔╝╚█████╔╝██║░╚██╗██████╔╝
	░╚════╝░░░░╚═╝░░░░░░░░░░░░╚═╝░░░╚═╝░░╚═╝░╚═════╝░░╚════╝░╚═╝░░╚═╝╚═════╝░
		"

EXEC="progc/exec"
images="images"
temp="temps"
dossier="data"
fichier="data.csv"
dossier2="demo"
resultat="resultatcsv"
v1=0
v2=0

#fonction effet visuel durant l'execution des traitements 

chargement(){
	echo -n "Traitement $i en cours"
        while :
        do
		for i in {1..3}; do
                echo -n "."
                sleep 1
            done
            echo -n -e "\b\b\b   \b\b\b"
            sleep 1
        done 
}

#fonction qui affiche toutt les présent dans le dossier Images

affichageimage(){
	echo "Fermer l'images ou les images pour pouvoir executer une nouvelle commande" 
	for image in $images/*.png
	do
		display "$image"
	done 
}
	
# verification qu'il a des arguments

if [ $(($#-1)) -le 0 ]
then 
	if [ $(($#-1)) -eq -1 ]
	then	
		echo "Rentrer: bash pro1.sh data.csv + une ou plusieur option parmi (-h ; -d1 ; -d2 ; -l ; -t ; -s)"
	else
		echo "Vous avez oublié de choisir des options parmi (-h ; -d1 ; -d2 ; -l ; -t ; -s)" 
	fi
	exit 1
fi


# verification du dossier images: 
#	- si le dossier contient des fichers alors il les déplace
#	- si le dossier n'existe pas il le crée 
  
if [ -e $dossier2 ]
then 
	if [ ! -e $dossier2/$temp ]
	then
		mkdir $dossier2/$temp
	fi
	
	if [ ! -e $dossier2/$resultat ]
	then
		mkdir $dossier2/$resultat
	fi
else
	mkdir $dossier2
	mkdir $dossier2/$temp
	mkdir $dossier2/$resultat	
fi

if [ -e $images ]
then 
	nombre_fichier=$((`ls -l $images | wc -l`-1))
	if [ $nombre_fichier -ne 0 ]
	then
		mv $images/* $dossier2
	fi
else 
	mkdir $images 
fi

#verification de la saisie du premier champs 

if [ $1 != "data.csv" ]
then
    v1=1
fi

# verification du fichier data.csv 

if [ -e $fichier ]; then
    mv $fichier $dossier
else
    if [ ! -e $dossier/$fichier ]
    then
        v2=1
    fi
fi

# verification du dossier:
# 	-si le ficher existe pas le crée 
#	-sinon efface ce qui y a dedans 

if [ -e $temp ]
then 
	nombre_fichier=$((`ls -l $temp | wc -l`-1))
	if [ $nombre_fichier -ne 0 ]
	then
		mv $temp/* $dossier2/$temp
	fi
else
	mkdir $temp
fi


# Execution des options 

if [ $v1 -eq 1 ] || [ $v2 -eq 1 ]
then
	if [ $v1 -eq 1 ]
	then
 		echo "Veuillez renomé le premier argument par data.csv ."
	fi

	if [ $v2 -eq 1 ]
	then
 		echo "Le fichier $fichier n'existe pas dans le dossier $dossier."
	fi
 	exit 1
fi

# verification du fichier executable c :
#	- si oui il accorde les permissions d'execution
#	- si non se crée 

if [ ! -e $EXEC ]
then
	cd progc
	make
	cd ..
else
	chmod +x $EXEC
fi

# afin de prendre que les arguments juste après le premier argument 
shift
 
# verfication que l'option -h est dans nos arguments 

for i in $@
do
	# affiche un message de tt les options disponible avec le temps d'execution
	if [ $i = "-h" ]
	then
			debut=$(date +%s)
			echo "Voici les options existantes:
			
	-> -d1: récupere les 10 conducteurs ayant fait le plus de trajets
			
	-> -d2: récupere les 10 conducteurs ayant parcouru les plus grandes distances
			
	-> -l:  récupere les 10 trajet les plus longs
			
	-> -s:  récupere les 10 villes les plus traverser avec leur nombre de fois où elles ont été ville de depart
	
	-> -t:  récupere les 50 trajets ayant une différence entre leur distance maximum et leur distance minimun les plus élevées avec leur moyennes des étapes
	"
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
    
    '-d1'|'-D1')
    
    	echo "Traitement $i en cours..."
        awk -F";" '/;1;/ {compte[$6] += 1} END {for (ligne in compte) print compte[ligne] ";" ligne}' data/data.csv | sort -k1nr | head -10 > demo/resultatcsv/resultatd1.csv
        
        gnuplot Gnuplots/traitement1.gn
        convert -rotate 90 figured1.png figured1.png
        mv figured1.png images;;
        
    '-d2'|'-D2')
    
    	echo "traitement $i en cours..."
        awk -F";" '{compte[$6] += $5} END {for (ligne in compte) print compte[ligne] ";" ligne}' data/data.csv | sort -k1nr | head -10 > demo/resultatcsv/resultatd2.csv
        
        gnuplot Gnuplots/traitement2.gn
	convert -rotate 90 figured2.png figured2.png
	mv figured2.png images;;
        
    '-l'|'-L')
    
    	chargement &
        awk -F";" '{compte[$1] += $5} END {for (ligne in compte) print compte[ligne] ";" ligne}' data/data.csv | sort -k1nr | head -10 | sort -t";" -k2n > demo/resultatcsv/resultatL.csv
        
        gnuplot Gnuplots/traitementL.gnu
        mv figureL.png images
        
	kill $!
        echo;;
        
    '-t'|'-T')
    
    	chargement &
        awk -F";" 'NR > 1 {compte[$1";"$4] +=1; if ($2==1) {compte[$1";"$3]+=1; deb[$1";"$3]=1}} END {for (ville in compte) print ville ";" compte[ville] ";" deb[ville] }' data/data.csv | awk -F";" '{compte[$2]+=1; deb[$2]+=$4} END {for (ville in compte) print ville ";" compte[ville] ";" deb[ville]}' > temps/temps_final.csv
        
        ./progc/exec -t > demo/resultatcsv/resultatt.csv
        gnuplot Gnuplots/traitementT.gn
        mv figureT.png images
        
        kill $!
        echo;;
        
    '-s'|'-S')
    	chargement &
        ./progc/exec -s > demo/resultatcsv/resultats.csv
        
        gnuplot Gnuplots/traitementS.gn
        mv figureS.png images
       	kill $!
        echo;;
    *)
        echo "Erreur : 
Option $i n'existe pas      
Veuillez choisir une option parmi (-h ; -d1 ; -d2 ; -l ; -t ; -s).
";;
    esac

    fin=$(date +%s)
    duree=$(($fin - $debut))
    echo -e "Execution : $duree secondes
    "
done

nmbimages=$((`ls -l $images| wc -l`-1))
if [ $nmbimages -eq 0 ]
then
	exit 1
else 
	read -p "Voulez-vous afficher les graphiques ? (O/N)" reponse
	case $reponse in 
		'O'|'o')
			affichageimage;;
		'n'|'N')
			exit 1;;
		*)
			exit 1;;
	esac
fi



# BONUS


#						option d1.bis même temps d'execution

#	grep ";1;" data.csv | cut -d";" -f6 | sort -k1 > datatestd1.csv
#	awk -F';' '{ line = $0; gsub(/\r/,"",line); if (line == prev_line) count++; else {print count ";" prev_line ; count = 1}; prev_line = line;}' datatestd1.csv | sort -k1nr | head -10 > resultatd1.csv


#						option d2.bis environ 34s d'execution

#	awk -F";" '{ print $5 "; " $6 }' data.csv | sort -t";" -k2 > datatestd2.csv
#	awk -F";" '{ line = $2; gsub(/\r/,"",line); if (line == prev_line) count += $1 ; else {print count ";" prev_line ; count = $1 }; prev_line = line;}' datatestd2.csv | sort -k1nr | head -10 > resultatd2.csv


#						option l.bis environ 46s d'execution

#	awk -F";" '{ print $1 ";" $5 }' data.csv | sort -t";" -k1 -n > datatestd3.csv
#	awk -F";" '{ line = $1; gsub(/\r/,"",line); if (line == prev_line) count += $2 ; else {print count ";" prev_line ; count = $2 }; prev_line = line;}' datatestd3.csv | sort -k1nr | head -10 > resultatd3.csv


#						option s environ 14s d'execution 
#LC_NUMERIC=C awk -F";" '{count[$1]+= $5; nm[$1]+=1; if(min[$1]=="" || min[$1]>$5) min[$1]=$5; if(max[$1]=="" || max[$1]<$5) max[$1]=$5;} END {for (line in count) print line ";" count[line]/nm[line] ";" min[line] ";" max[line] ";" max[line]-min[line]}' data/data.csv > temps/tempss.csv

 






 


