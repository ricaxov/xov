# Contest Files (v0.7.0 - 10/09/2024) {{{
# chmod +x contest.sh && ./contest.sh
echo "Digite o ID do contest que será feito:"
read contest_id

response=$(curl -s "https://codeforces.com/api/contest.standings?contestId=$contest_id")
contest_name=$(echo "$response" | jq -r '.result.contest.name')

if [ "$contest_name" = "null" ]; then
  echo "Não foi possível obter o nome do contest. Verifique o ID da competição e tente novamente."
  exit 1
fi

amount=$(echo "$response" | jq '.result.problems | length')

echo "Nome do contest: $contest_name"
echo "Quantidade de problemas: $amount"

dir_name=$(echo "$contest_name" | sed 's/ /_/g')
mkdir -p "$dir_name"

cd "$dir_name" || exit
xdg-open "https://codeforces.com/gym/$contest_id"

touch stress.sh
touch makefile
code makefile

for letter in {a..z}; do
  if [ "$amount" -eq 0 ]; then
    break
  else
    touch "$letter.cpp"
    code "$letter.cpp"
    ((amount--))
  fi
done
#}}}
