# Test Case Runner Script {{{
# chmod +x runner.sh && ./runner.sh

custom_separator="--------------------"

solve="a"
expected="b"

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

GREEN='\033[0;32m'
NEUTRAL='\033[0m'
RED='\033[0;31m'

input_file="input.in"
temp_input="temp_input.in"

if [ -f "$input_file" ]; then
  case_number=1
  awk -v RS="$custom_separator" '{print > "case_" NR ".in"}' "$input_file"

  for case_input in case_*.in; do
    output_solve="output_solve.out"
    output_expected="output_expected.out"
    
    ./"$solve" < "$case_input" > "$output_solve"
    ./"$expected" < "$case_input" > "$output_expected"
    
    if diff -q "$output_solve" "$output_expected" > /dev/null; then
      echo -e "${GREEN}[Accepted]${NEUTRAL} Caso $case_number"
    else
      echo -e "${RED}[Wrong Answer]${NEUTRAL} Caso $case_number"
      echo "Esperado:" 
      cat "$output_expected"
      echo "Resultado:" 
      cat "$output_solve"
    fi
    
    rm -f "$output_solve" "$output_expected" "$case_input"
    case_number=$((case_number + 1))
  done
fi
#}}}
