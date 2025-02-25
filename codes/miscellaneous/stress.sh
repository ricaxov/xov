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

[ -f "input.in" ] || touch "input.in"

for ((i = 1; i <= 200; i++)); do
  "./$cases" > "cases.in"
  "./$solve" < "cases.in" > "solve.out"
  "./$expected" < "cases.in" > "expected.out"

  if (! cmp -s "solve.out" "expected.out"); then
    [ -s input.in ] && tail -c1 input.in | read -r _ || echo "" >> input.in

    echo "-> Entrada:"    
    cat cases.in
    echo "-> Resultado:"
    cat solve.out
    echo "-> Esperado:"
    cat expected.out
    
    echo "--------------------" >> input.in
    cat cases.in >> input.in
    
    break
  fi
  echo "Passou do caso $i"
done

rm "cases.in"
rm "solve.out"
rm "expected.out"
#}}}
