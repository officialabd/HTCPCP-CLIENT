rm ../out/c
make
clear 
for i in 1 2 3 4 5 6 7 8 9 10
do
    echo "Looping ... number $i"
    gnome-terminal -- sh -c "../out/c; bash"
done
