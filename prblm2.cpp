
#include <bits/stdc++.h>
using namespace std;
bool edgesOK(int l, int r, int X, vector<int> &arr, int sz) {
  if (l > 0 && abs(arr[l - 1] - 2 * arr[r]) > X)
    return false;
  if (r < sz - 1 && abs(2 * arr[l] - arr[r + 1]) > X)
    return false;
  return true;
}
bool check(int X, int sz, vector<int> &arr) {
  int maxim = 0;
  int defs = 0, defe = 0;
  int start = -1;
  int bad = 0;
  int end = -1;
  for (int i = 0; i < sz - 1; i++) {
    defs = abs(arr[i] - arr[i + 1]);
    if (defs > X && start == -1) {
      start = i + 1;
      for (int j = start; j < sz - 1; j++) {
        defe = abs(arr[j] - arr[j + 1]);
        if (defe > X) {
          end = j;
        }
      }
    }
    if (defs > X)
      bad++;
  }
  if (start == -1)
    return true;
  if (bad == 2 && end + 1 < sz && start - 1 >= 0) {
    int opsval = arr[end] * 2;
    int defl = 0, defr = 0, defc = 0, def = 0;
    defl = abs(arr[start - 1] - opsval);
    defr = abs(arr[end + 1] - (arr[start] * 2));
    int maxdef = 0;
    for (int i = end; i > start; i--) {
      def = abs((2 * arr[i]) - (2 * arr[i - 1]));
      maxdef = (def > maxdef) ? def : maxdef;
    }
    if (maxdef <= X && defr <= X && defl <= X)
      return true;
  }
  int def = 0;
  if (bad == 1) {
    int p = start - 1;                 // the bad pair is (p, start)
    for (int r = start; r < sz; r++) { // bad pair is the LEFT edge, grow right
      if (r > start && 2 * abs(arr[r - 1] - arr[r]) > X)
        break;
      if (edgesOK(start, r, X, arr, sz))
        return true;
    }
    for (int l = p; l >= 0; l--) { // bad pair is the RIGHT edge, grow left
      if (l < p && 2 * abs(arr[l] - arr[l + 1]) > X)
        break;
      if (edgesOK(l, p, X, arr, sz))
        return true;
    }
  }
  return false;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;
  while (t--) {
    vector<int> arr;
    int s;
    cin >> s;
    int b;
    int maxim;
    int ans;
    for (int i = 0; i < s; i++) {
      cin >> b;
      arr.push_back(b);
    }
    maxim = *max_element(arr.begin(), arr.end());
    maxim = 2 * maxim;
    int min = 0;
    int X = 0;
    int chk = false;
    int ln = arr.size();
    while (maxim >= min) {
      X = min + (maxim - min) / 2;
      if (check(X, ln, arr)) {
        ans = X;
        maxim = X - 1;
      } else
        min = X + 1;
    }
    cout << ans << "\n";
  }
  return 0;
}
