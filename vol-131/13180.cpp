#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_NUM = 1 << 10;
int N, A[MAX_NUM];

int main() {
  N = 0;
  while (scanf("%d", &A[0]) != EOF && A[0]) {
    N = 1;
    while (scanf("%d", &A[N]) != EOF && A[N] != 0) {
      ++N;
    }
    sort(A, A + N);
    if (N & 1) {
      bool flag = true;
      for (int i = 2; i < N; i += 2) {
        if (A[i] == A[i - 2]) {
          flag = false;
          break;
        }
      }
      for (int i = 1; i < N - 1; i += 2) {
        if (A[i] != A[i - 1]) {
          flag = false;
          break;
        }
      }
      if (!flag) {
        puts("NO");
      } else {
        vector<int> V;
        for (int i = 0; i < N; i += 2) {
          V.push_back(A[i]);
        }
        for (int i = N - 2; i >= 0; i -= 2) {
          V.push_back(A[i]);
        }
        for (int i = 0; i < (int)V.size(); ++i) {
          printf("%d%s", V[i], (i == (int)V.size() - 1 ? "\n" : " "));
        }
      }
    } else {
      puts("NO");
    }
  }
  return 0;
}
