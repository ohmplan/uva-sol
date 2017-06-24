#include <stdio.h>
#include <algorithm>

using namespace std;

static const int MAX_NUM = 1 << 5;

char G[MAX_NUM][MAX_NUM];
int N, M;
int S[MAX_NUM][MAX_NUM][MAX_NUM][MAX_NUM];
int F[MAX_NUM][MAX_NUM][MAX_NUM][MAX_NUM];

int dfs(int x0, int y0, int x1, int y1) {
  int &v = F[x0][y0][x1][y1];
  if (v != -1) {
    return v;
  }
  if (S[x0][y0][x1][y1] == 0 || S[x0][y0][x1][y1] == (x1 - x0 + 1) * (y1 - y0 + 1)) {
    return v = 0;
  }
  v = N * M;
  for (int x = x0; x + 1 <= x1; ++x) {
    v = min(v, 1 + dfs(x0, y0, x, y1) + dfs(x + 1, y0, x1, y1));
  }
  for (int y = y0; y + 1 <= y1; ++y) {
    v = min(v, 1 + dfs(x0, y0, x1, y) + dfs(x0, y + 1, x1, y1));
  }
  return v;
}

int main() {
  while (scanf("%d%d", &N, &M) != EOF) {
    for (int i = 0; i < N; ++i) {
      scanf("%s", G[i]);
    }
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < M; ++j) {
        for (int k = i; k < N; ++k) {
          for (int l = j; l < M; ++l) {
            S[i][j][k][l] = (G[k][l] == '#' ? 1 : 0);
            if (k - 1 >= i) {
              S[i][j][k][l] += S[i][j][k - 1][l];
            }
            if (l - 1 >= j) {
              S[i][j][k][l] += S[i][j][k][l - 1];
            }
            if (k - 1 >= i && l - 1 >= j) {
              S[i][j][k][l] -= S[i][j][k - 1][l - 1];
            }
            F[i][j][k][l] = -1;
          }
        }
      }
    }
    printf("%d\n", dfs(0, 0, N - 1, M - 1));
  }
  return 0;
}
