-Il est censé y avoir 6 dossiers dans le fichier courant et 1 fichier :

Liste des dossiers : Gnuplots/progc/images/demo/data/temps
(les fichiers: demo,images,temps se crée s'il existe pas)

Le dossier data doit être créé (Pas possible de mettre un dossier vide sur Github) 

Liste des fichiers : pro1.sh

-Les fichiers .c, le ficher .h et le makefile doivent être dans le dossier progc sinon un message d'erreur sera affiché

-Les fichier .gn doivent être dans le dossier Gnuplots

-Le fichier data.csv doit être dans le dossier data (S'il n'y est pas un message d'erreur est envoyé)

-Pour éxécuter le script :

bash pro1.sh data.csv option

-Le premier argument doit être data.csv (fichier de donnée), si ce n'est pas le cas un message d'erreur sera envoyé demandant de renommer le fichier de donnée en "data.csv"

-Il existe 6 options -d1 -d2 -l -s -t -h (peut etre ecrit en majuscule), Il est possible de mettre toutes les options en même temps

-L'option -h ignorera toutes les autre options et indiquera les options possibles

-a la fin des executions il demande a l'utilisateur s'il veut afficher les graphique avec soit 'o' ou 'n' (peut etre ecrit en majuscule) et si oui il faudra fermer toutes les images qui se sont ouvertes afin d'executer une nouvelle commande


