#include <stdio.h>

static const int MAX_NUM = 50;
int N, M;
int D[MAX_NUM];

int main() {
  while (scanf("%d%d", &N, &M) != EOF && N) {
    for (int i = 0; i < N; ++i) {
      D[i] = 0;
    }
    for (int i = 0, u, v; i < M; ++i) {
      scanf("%d%d", &u, &v);
      --u;
      --v;
      D[u]++;
      D[v]++;
    }
    int C0 = 0, C1 = 0;
    for (int i = 0; i < N; ++i) {
      C0 += (D[i] == 0 ? 1 : 0);
      C1 += (D[i] == 1 ? 1 : 0);
    }
    if ((C1 / 2 == 0 && C0 <= 2) || (C1 / 2 == 1 && C0 <= 1))  {
      puts("YES");
    } else {
      puts("NO");
    }
  }
  return 0;
}
