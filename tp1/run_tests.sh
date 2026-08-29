#!/bin/bash

EXEC="bin/tp1.out"
PASTA_TESTE="teste"

TOTAL=0
PASSOU=0

for i in {0..14}
do
    IN="$PASTA_TESTE/in_$i.txt"
    EXPECTED="$PASTA_TESTE/out_$i.txt"
    OUTPUT="$PASTA_TESTE/my_out_$i.txt"

    # Executa o programa
    "$EXEC" < "$IN" > "$OUTPUT"

    # Compara saída
    if diff -q "$OUTPUT" "$EXPECTED" > /dev/null
    then
        echo "Teste $i: PASSOU"
        PASSOU=$((PASSOU+1))
    else
        echo "Teste $i: FALHOU"
        echo "Diferença:"
        diff "$OUTPUT" "$EXPECTED"
    fi

    TOTAL=$((TOTAL+1))
done

echo "-------------------------"
echo "Resultado: $PASSOU / $TOTAL passaram"