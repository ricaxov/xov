solve="a"
expected="b"
cases="c"

g++ -o "$solve" "$solve.cpp" -Wall -Wextra -pedantic -std=c++20 -O3 -Wshift-overflow=2 -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC
if [ $? -ne 0 ]; then
  echo "Error compiling the '$solve' program."
  exit 1
fi

g++ -o "$expected" "$expected.cpp" -Wall -Wextra -pedantic -std=c++20 -O3 -Wshift-overflow=2 -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC
if [ $? -ne 0 ]; then
  echo "Error compiling the '$expected' program."
  exit 1
fi

g++ -o "$cases" "$cases.cpp" -Wall -Wextra -pedantic -std=c++20 -O3 -Wshift-overflow=2 -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC
if [ $? -ne 0 ]; then
  echo "Error compiling the '$cases' program."
  exit 1
fi

while true; do
  "./$cases" > "input.txt"
  echo "Test case:"
  cat "input.txt"
  "./$solve" < "input.txt" > "output_${solve}.txt"
  echo "Output of the '$solve' program:"
  cat "output_${solve}.txt"
  "./$expected" < "input.txt" > "output_${expected}.txt"
  echo "Output of the '$expected' program:"
  cat "output_${expected}.txt"
  if diff "output_${solve}.txt" "output_${expected}.txt" >/dev/null; then
    echo "Outputs of the '$solve' and '$expected' programs are equal. Generating a new input..."
  else
    echo "Outputs of the '$solve' and '$expected' programs are different."
    break
  fi
  echo
done

mkdir -p output

mv "output_${solve}.txt" "output/"
mv "output_${expected}.txt" "output/"
mv "input.txt" "output/"
mv "$solve" "output/"
mv "$expected" "output/"
mv "$cases" "output/"