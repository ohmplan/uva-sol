#include <stdio.h>

using namespace std;

static const int MAX_NUM = 1 << 18;
int N, M;
int A[MAX_NUM];

int chk(int P) {
  int C = 0;
  for (int i = 0; i < N; ++i) {
    C += (A[i] + P - 1) / P;
    if (C > M) {
      return false;
    }
  }
  return true;
}

int sol(int l, int r) {
  while (r - l > 1) {
    int m = (l + r) / 2;
    if (chk(m)) {
      r = m;
    } else {
      l = m;
    }
  }
  return chk(l) ? l : r;
}

int main() {
  while (scanf("%d%d", &M, &N) != EOF) {
    for (int i = 0; i < N; ++i) {
      scanf("%d", &A[i]);
    }
    printf("%d\n", sol(1, 1000));
  }
  return 0;
}
