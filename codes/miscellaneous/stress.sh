# Brute Force Script {{{
# chmod +x stress.sh && ./stress.sh

solve="a"
expected="b"
cases="c"

make "$solve"
if [ $? -ne 0 ]; then
  echo "Erro ao compilar '$solve'."
  exit 1
fi

make "$expected"
if [ $? -ne 0 ]; then
  echo "Erro ao compilar '$expected'."
  exit 1
fi

make "$cases"
if [ $? -ne 0 ]; then
  echo "Erro ao compilar '$cases'."
  exit 1
fi

for ((i = 1; ; i)); do
  "./$cases" >"cases.in"
  "./$solve" <"cases.in" >"solve.out"
  "./$expected" <"cases.in" >"expected.out"

  if (! cmp -s "solve.out" "expected.out"); then
    echo "-> Entrada:"
    cat cases.in
    echo "-> Resultado:"
    cat solve.out
    echo "-> Esperado:"
    cat expected.out
    break
  fi
  echo Passou do caso $i
done

rm "cases.in"
rm "solve.out"
rm "expected.out"
#}}}
