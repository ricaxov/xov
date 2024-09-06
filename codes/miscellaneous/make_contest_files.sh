# Make Contest Files (v0.5.0 - 06/09/2024) {{{
echo "Digite quem serão os participantes:"
read contestants

echo "Digite o ID do contest que será feito:"
read contest_id

response=$(curl -s "https://codeforces.com/api/contest.standings?contestId=$contest_id")
contest_name=$(echo "$response" | jq -r '.result.contest.name')

if [ "$contest_name" = "null" ]; then
  echo "Não foi possível obter o nome do contest. Verifique o contest_id e tente novamente."
  exit 1
fi

echo "Nome do contest: $contest_name"
dir_name=$(echo "$contest_name" | sed 's/ /_/g')
mkdir -p "$dir_name"

cd "$dir_name" || exit
xdg-open "https://codeforces.com/gym/$contest_id"

IFS=' '
contestants_array=($contestants)

touch stress.sh
touch makefile
code makefile

for contestant in "${contestants_array[@]}"; do
  touch "$contestant.cpp"
  code "$contestant.cpp"
done
#}}}
