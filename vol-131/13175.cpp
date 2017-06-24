#include <stdio.h>
#include <algorithm>

using namespace std;

static const int MAX_NUM = 5000;

int T;
int N;
int R;

int dfs(int c) {
  if (c == 0) {
    return 0;
  } else if (c == 1) {
    int left;
    scanf("%d", &left);
    dfs(left);
    return 0;
  } else if (c == 2) {
    int left, right;
    scanf("%d", &left);
    int d0 = dfs(left);
    scanf("%d", &right);
    int d1 = dfs(right);
    R = max(R, min(d0, d1) + 1);
    return min(d0, d1) + 1;
  }
}

int main() {
  scanf("%d", &T);
  while (T--) {
    N = 0;
    R = 0;
    int left;
    scanf("%d", &left);
    R = max(R, dfs(left));
    printf("%d\n", R);
  }
  return 0;
}
