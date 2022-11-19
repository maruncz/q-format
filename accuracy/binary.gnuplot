#set terminal svg size 1000,1500 dynamic background rgb 'white'
set terminal pngcairo size 1000,1500
set output outplot
set key outside right center
set grid
set multiplot layout 2,1
set size ratio 1
set cbrange [-10<*:*<10]
set xzeroaxis linetype -1
plot filename u 1:2:5 w image title 'relative precision'
set cbrange [-10<*:*<10]
plot filename u 1:2:6 w image title 'absolute precision in LSB'
unset multiplot
