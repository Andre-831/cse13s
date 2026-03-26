if [ "$1" = "" ]
then
    printf 'Usage:  cd tests   (if not already in the tests directory)\n'
    printf '        sh delayinput.sh \033[3mtestfile\033[0m.txt | ../xd > got.txt\n'
    printf '        sh delayinput.sh \033[3mtestfile\033[0m.txt | xxd > expected.txt\n'
    printf '        diff -s expected.txt got.txt\n'
    exit 1
fi

while read input
do echo "$input"
   sleep 1
done < $1

