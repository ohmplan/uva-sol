#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>

using namespace std;

static const int MAX_NUM = 1 << 5;

int NA, NB, NC;
char A[MAX_NUM];
char B[MAX_NUM];
char C[MAX_NUM];
char O[MAX_NUM];

int V[1 << 8];
int F[10];
int Carry[MAX_NUM];

bool setv(char c, int v) {
  if (V[c] == -1 && F[v] == -1) {
    V[c] = v, F[v] = c;
    return true;
  }
  return V[c] == v && F[v] == c;
}

bool setv(char c, int v, bool& flag) {
  if (V[c] == -1 && F[v] == -1) {
    V[c] = v, F[v] = c;
    flag = true;
    return true;
  }
  flag = false;
  return V[c] == v && F[v] == c;
}

void delv(char c, int v) {
  V[c] = F[v] = -1;
}

// S[i] = A[i] + B[i]
// S[i] + Carry[i - 1] = C[i] + Carry[i] * 10
bool dfs(int i) {
  if (i == NC) {
    return Carry[i - 1] == 0
           && (NA == 1 || (NA != 1 && V[A[NA - 1]] != 0))
           && (NB == 1 || (NB != 1 && V[B[NB - 1]] != 0))
           && (NC == 1 || (NC != 1 && V[C[NC - 1]] != 0));
  }
  vector<pair<int, bool> > VA;
  if (i < NA) {
    if (V[A[i]] != -1) {
      VA.push_back(make_pair(V[A[i]], false));
    } else {
      for (int d = 0; d < 10; ++d) {
        if (F[d] == -1) {
          VA.push_back(make_pair(d, true));
        }
      }
    }
  } else {
    VA.push_back(make_pair(0, false));
  }
  vector<pair<int, bool> > VB;
  if (i < NB) {
    if (V[B[i]] != -1) {
      VB.push_back(make_pair(V[B[i]], false));
    } else {
      for (int d = 0; d < 10; ++d) {
        if (F[d] == -1) {
          VB.push_back(make_pair(d, true));
        }
      }
    }
  } else {
    VB.push_back(make_pair(0, false));
  }
  for (int p = 0; p < (int)VA.size(); ++p) {
    for (int q = 0; q < (int)VB.size(); ++q) {
      if (VA[p].second) {
        setv(A[i], VA[p].first);
      }
      bool setbsuccess = true;
      if (VB[q].second) {
        if (!setv(B[i], VB[q].first)) {
          setbsuccess = false;
        }
      }
      if (!setbsuccess) {
        delv(A[i], VA[p].first);
        continue;
      }
      int S;
      if (O[0] == '+') {
        // S[i] = A[i] + B[i]
        S = VA[p].first + VB[q].first;
      } else {
        // S[i] = A[x] * B[y] (x + y = i)
        S = 0;
        for (int x = 0; x <= i; ++x) {
          int y = i - x;
          int curA = x < NA ? V[A[x]] : 0;
          int curB = y < NB ? V[B[y]] : 0;
          S += curA * curB;
        }
      }
      // S[i] + Carry[i - 1] = C[i] + Carry[i] * 10
      if (i - 1 >= 0) {
        S += Carry[i - 1];
      }
      bool setcflag = false;
      if (setv(C[i], S % 10, setcflag)) {
        Carry[i] = S / 10;
        if (dfs(i + 1)) {
          return true;
        }
      }
      if (setcflag) {
        delv(C[i], S % 10);
      }
      if (VA[p].second) {
        delv(A[i], VA[p].first);
      }
      if (VB[q].second) {
        delv(B[i], VB[q].first);
      }
    }
  }
  return false;
}

int main() {
  while (scanf("%s%s%s%*s%s", A, O, B, C) != EOF) {
    NA = strlen(A);
    reverse(A, A + NA);
    NB = strlen(B);
    reverse(B, B + NB);
    NC = strlen(C);
    reverse(C, C + NC);
    memset(V, 0xFF, sizeof(V));
    memset(F, 0xFF, sizeof(F));
    dfs(0);
    for (int i = NA - 1; i >= 0; --i) {
      printf("%d", V[A[i]]);
    }
    printf(" %s ", O);
    for (int i = NB - 1; i >= 0; --i) {
      printf("%d", V[B[i]]);
    }
    printf(" = ");
    for (int i = NC - 1; i >= 0; --i) {
      printf("%d", V[C[i]]);
    }
    puts("");
  }
  return 0;
}
