#include <stdio.h>

int T;
int N;

int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &N);
    int X = 0;
    while (N % 3 != 0) {
      X += N % 3;
      --N;
    }
    puts(X % 3 == 0 ? "YES" : "NO");
  }
  return 0;
}
