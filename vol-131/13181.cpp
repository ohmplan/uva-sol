#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

static const int MAX_NUM = 1 << 19;

int N;
char S[MAX_NUM];

int main() {
  while (scanf("%s", S) != EOF) {
    N = strlen(S);
    int P = -1;
    int M = 0;
    for (int i = 0; i < N; ++i) {
      if (S[i] == '.') {
        if (P == -1 || i == N - 1) {
          M = max(M, i - P - 1);
        } else {
          M = max(M, (i - P - 1) / 2);
        }
      } else {
        P = i;
      }
    }
    printf("%d\n", M);
  }
  return 0;
}
