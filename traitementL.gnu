set title 'Les 10 trajets les plus longs'
set terminal png size 800,800
set output 'figureL.png'
set style data histograms
set style fill solid border -1
set boxwidth 2 relative
set ylabel 'Kilomètres' tc rgb 'red'
set xlabel 'ID trajet' tc rgb 'red'
set datafile separator ';'
plot 'temps/resultatL.csv' using 1:xticlabels(2) notitle lc rgbcolor "#99FFCC"
