int gauss(int x) {
  return (x*(x+1))/2;
}

int gauss(int l, int r) {
  return gauss(r) - gauss(l-1);
}

int divisor_sum(int x) {
  int sum = 0;
  for (int i = 1; i <= x; i++) {
    int k = x/i;
    int j = x/k;
    sum += (gauss(i, j) * k);
    i = j;
  }
  return sum;
}

int divisor_sum(int l, int r) {
  return divisor_sum(r) - divisor_sum(l-1);
}
