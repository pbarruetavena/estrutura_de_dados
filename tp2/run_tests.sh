#!/bin/bash

EXEC="./bin/tp2.out"
PASTA_TESTE="teste"

TOTAL=0
PASSOU=0

# Ajustado para ler os arquivos case_1 até case_5
for i in {1..5}
do
    IN="$PASTA_TESTE/case_$i.in"
    EXPECTED="$PASTA_TESTE/case_$i.out"
    OUTPUT="$PASTA_TESTE/my_out_$i.txt"

    # Executa o programa
    $EXEC < "$IN" > "$OUTPUT"

    # Compara saída
    if diff -q -w "$OUTPUT" "$EXPECTED" > /dev/null
    then
        echo "Teste $i: PASSOU"
        PASSOU=$((PASSOU+1))
    else
        echo "Teste $i: FALHOU"
        echo "Diferença:"
        # Adicione o -w aqui também para ver apenas erros reais de texto
        diff -w "$OUTPUT" "$EXPECTED" 
    fi

    TOTAL=$((TOTAL+1))
done

echo "-------------------------"
echo "Resultado: $PASSOU / $TOTAL passaram"