#include <iostream>
#include <string>
#include <string.h>

using namespace std;

static const int MAX_NUM = 1 << 8;
static const int DX[8] = {+0, +0, +1, +1, +1, -1, -1, -1};
static const int DY[8] = {+1, -1, +1, -1, +0, +1, -1, +0};

int N, M, Q;
string G[MAX_NUM], T;

bool fit(int x, int y) {
  return 0 <= x && x < N && 0 <= y && y < M;
}

template<int N, int M>
struct Trie {
  int n, child[N][M];
  int cnt[N], flag[N];
  int add() {
    n++;
    memset(child[n], 0xff, sizeof(child[n]));
    cnt[n] = flag[n] = 0;
    return n;
  }
  void init() {
    n = -1;
    add();
  }
  void ins(string& s) {
    int at = 0;
    for (int i = 0; i < (int)s.size(); ++i) {
      if (child[at][s[i] - '0'] == -1) {
        child[at][s[i] - '0'] = add();
      }
      at = child[at][s[i] - '0'];
    }
    flag[at]++;
  }
  void upd(string& s) {
    int at = 0;
    for (int i = 0; i < (int)s.size(); ++i) {
      if (child[at][s[i] - '0'] == -1) {
        return;
      }
      at = child[at][s[i] - '0'];
      cnt[at]++;
    }
  }
  void dfs(int u, char* s, int l) {
    if (flag[u] && cnt[u]) {
      for (int i = 0; i < flag[u]; ++i) {
        s[l] = '\0';
        cout << s << " " << (l == 1 ? cnt[u] / 8 : cnt[u]) << endl;
      }
    }
    for (int i = 0; i < M; ++i) {
      if (child[u][i] != -1) {
        s[l] = '0' + i;
        dfs(child[u][i], s, l + 1);
      }
    }
  }
  void out() {
    char buf[MAX_NUM];
    dfs(0, buf, 0);
  }
};

Trie<1 << 22, 2> trie;

int main() {
  ios_base::sync_with_stdio(false);
  while (cin >> M >> N) {
    for (int i = 0; i < N; ++i) {
      cin >> G[i];
    }
    cin >> Q;
    trie.init();
    for (int i = 0; i < Q; ++i) {
      cin >> T;
      trie.ins(T);
    }
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < M; ++j) {
        for (int k = 0; k < 8; ++k) {
          T = "";
          for (int x = i, y = j; fit(x, y); x += DX[k], y += DY[k]) {
            T += G[x][y];
          }
          trie.upd(T);
        }
      }
    }
    trie.out();
    cout << "---" << endl;
  }
  return 0;
}
