#ª/bin/bash

VOCALES=( 'A                     I                    U')

cat palabras_todas.txt | grep -v '.*-$' | grep -v ^- | sort | uniq > palabras_todas.txt
cat palabras_todas.txt | grep '.*-$' | sort | uniq > prefijos.txt
cat palabras_todas.txt | grep ^- | sort | uniq > sufijos.txt
rm palabras_todas.txt

for l in "${LETRAS[@]}"; do
  cat palabras_todas.txt | grep ^$l > palabras_$l.txt
done
