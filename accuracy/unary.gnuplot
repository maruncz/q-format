set terminal pngcairo size 1000, 1000
set output outplot
set key left top
set grid
set multiplot layout 3,1
plot filename u 1:2 w lines title 'double', filename u 1:3 w lines title 'fixpoint'
set yrange [-10<*:*<10]
set xzeroaxis linetype -1
plot filename u 1:4 w lines title 'relative precision'
set yrange [-10<*:*<10]
plot filename u 1:5 w lines title 'absolute precision in LSB'
unset multiplot
