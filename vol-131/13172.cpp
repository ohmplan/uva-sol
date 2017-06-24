#include <stdio.h>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

static const int MAX_NUM = 1000;

int N, M;
vector<pair<int, int> > E[MAX_NUM];
int D[MAX_NUM][MAX_NUM];
priority_queue<pair<int, int> > Q;
int T, K, A[6], P[6];
vector<pair<int, pair<int, int> > > V;

void dij(int u, int* d) {
  fill(d, d + N, (int)1e9);
  d[u] = 0;
  Q.push(make_pair(-d[u], u));
  while (!Q.empty()) {
    int p = Q.top().second;
    int c = -Q.top().first;
    Q.pop();
    for (int i = 0; i < E[p].size(); ++i) {
      int q = E[p][i].first;
      if (c + E[p][i].second < d[q]) {
        d[q] = c + E[p][i].second;
        Q.push(make_pair(-d[q], q));
      }
    }
  }
}

int main() {
  while (scanf("%d%d", &N, &M) != EOF) {
    for (int i = 0; i < N; ++i) {
      E[i].clear();
    }
    for (int i = 0, u, v, w; i < M; ++i) {
      scanf("%d%d%d", &u, &v, &w);
      --u;
      --v;
      E[u].push_back(make_pair(v, w));
      E[v].push_back(make_pair(u, w));
    }
    for (int i = 0; i < N; ++i) {
      dij(i, D[i]);
    }
    scanf("%d", &T);
    while (T--) {
      scanf("%d", &K);
      for (int i = 0; i < K; ++i) {
        scanf("%d", &A[i]);
        --A[i];
        P[i] = i;
      }
      V.clear();
      do {
        int sum = 0;
        for (int i = 1; i < K; ++i) {
          sum += D[A[P[i - 1]]][A[P[i]]];
        }
        int st = A[P[0]];
        int ed = A[P[K - 1]];
        V.push_back(make_pair(sum, make_pair(st, ed)));
      } while(next_permutation(P, P + K));
      int X;
      int Y = (int)(1e9);
      for (int i = 0; i < N; ++i) {
        bool flag = false;
        for (int j = 0; j < K; ++j) {
          if (i == A[j]) {
            flag = true;
            break;
          }
        }
        if (flag) {
          continue;
        }
        for (int j = 0; j < (int)V.size(); ++j) {
          int st = V[j].second.first;
          int ed = V[j].second.second;
          int cost = V[j].first + D[i][st] + D[ed][i];
          if (cost < Y) {
            X = i;
            Y = cost;
          }
        }
      }
      printf("%d %d\n", X + 1, Y);
    }
    puts("---");
  }
  return 0;
}
