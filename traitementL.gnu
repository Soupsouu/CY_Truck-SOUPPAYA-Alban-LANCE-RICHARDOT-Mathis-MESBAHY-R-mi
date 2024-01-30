set title 'Les 10 trajets les plus longs'
set terminal png size 800,800
set output 'figureL.png'
set style data histograms
set style fill solid border -1
set ylabel 'Kilomètres'
set xlabel 'ID trajet'
set datafile separator ';'
plot 'demo/resultatL.csv' using 1:xticlabels(2) notitle
