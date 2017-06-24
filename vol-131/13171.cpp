#include <stdio.h>
#include <string.h>

static const int MAX_NUM = 1 << 17;

int C[256];
int T, hM, hY, hC;
int N, nM, nY, nC;
char S[MAX_NUM];

int main() {
  C['M'] = 1 << 0;
  C['Y'] = 1 << 1;
  C['C'] = 1 << 2;
  C['R'] = C['M'] | C['Y'];
  C['B'] = C['M'] | C['Y'] | C['C'];
  C['G'] = C['Y'] | C['C'];
  C['V'] = C['M'] | C['C'];
  C['W'] = 0;
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d%s", &hM, &hY, &hC, S);
    N = strlen(S);
    int cnt[3] = {0, 0, 0};
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < 3; ++j) {
        if ((C[S[i]] >> j) & 1) {
          cnt[j]++;
        }
      }
    }
    nM = cnt[0];
    nY = cnt[1];
    nC = cnt[2];
    if (nM <= hM && nY <= hY && nC <= hC) {
      printf("YES %d %d %d\n", hM - nM, hY - nY, hC - nC);
    } else {
      puts("NO");
    }
  }
  return 0;
}
