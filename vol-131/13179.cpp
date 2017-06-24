#include <stdio.h>
#include <algorithm>

using namespace std;

static const int MAX_NUM = 100 + 2;

int N, M, K;
int X[MAX_NUM], Y[MAX_NUM], S[MAX_NUM], F[MAX_NUM][MAX_NUM * MAX_NUM];

int dis(int i, int j) {
  return abs(X[i] - X[j]) + abs(Y[i] - Y[j]);
}

int sum(int i, int j) {
  return S[j] - S[i];
}

int sol() {
  for (int i = 0; i <= K + 1; ++i) {
    S[i] = (i == 0 ? 0 : S[i - 1] + dis(i - 1, i));
  }
  int INF = sum(0, K + 1) + 1;
  int ans = sum(0, K + 1);
  for (int i = 1; i <= K + 1; ++i) {
    for (int j = 0; j < INF; ++j) {
      F[i][j] = INF;
    }
    F[i][sum(0, i - 1)] = max(sum(0, i - 1), dis(0, i));
    for (int j = 1; j <= i - 1; ++j) {
      for (int k = 0; k < INF; ++k) {
        int t0 = F[j][k] + sum(j, i - 1);
        int t1 = max(t0, k + dis(j - 1, i));
        if (t0 < INF) {
          F[i][t0] = min(F[i][t0], t1);
        }
      }
    }
    for (int j = 0; j < INF; ++j) {
      int t0 = F[i][j] + sum(i, K + 1);
      int t1 = j + dis(i - 1, K + 1);
      ans = min(ans, max(t0, t1));
    }
  }
  return ans + 1;
}

int main() {
  while (scanf("%d%d%d", &N, &M, &K) == 3) {
    X[0] = 1;
    Y[0] = 1;
    for (int i = 1; i <= K; ++i) {
      scanf("%d%d", &X[i], &Y[i]);
    }
    X[K + 1] = N;
    Y[K + 1] = M;
    printf("%d\n", sol());
  }
  return 0;
}
