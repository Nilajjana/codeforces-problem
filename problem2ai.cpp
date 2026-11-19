#include <bits/stdc++.h>
using namespace std;

int operation(int st, int end, vector<int> &arr, int X, int ln) {
  if (st < 0 || end >= ln || st > end)
    return -1;
  int def = 0;
  int maxim = 0;
  vector<int> arr2 = arr;
  int l = st, r = end;
  while (l < r) {
    swap(arr2[l], arr2[r]);
    l++;
    r--;
  }
  for (int k = st; k <= end; k++) {
    arr2[k] *= 2;
  }
  for (int i = 0; i < ln - 1; i++) {
    def = abs(arr2[i] - arr2[i + 1]);
    maxim = max(def, maxim);
  }
  return maxim;
}

bool check(int X, int sz, vector<int> &arr) {
  int start = -1;
  int end = -1;
  for (int i = 0; i < sz - 1; i++) {
    int def = abs(arr[i] - arr[i + 1]);
    if (def > X) {
      if (start == -1) start = i;
      end = i; // Track the exact violation index
    }
  }
  if (start == -1)
    return true;

  // Test candidate ranges anchored tightly around start and end
  for (int st : {start, max(0, start - 1)}) {
    for (int en : {end, min(sz - 1, end + 1)}) {
      if (st <= en) {
        int chk = operation(st, en, arr, X, sz);
        if (chk != -1 && chk <= X) {
          return true;
        }
      }
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
    int s;
    cin >> s;
    vector<int> arr(s);
    for (int i = 0; i < s; i++) {
      cin >> arr[i];
    }

    int low = 0;
    int high = 1e9; // Safe upper bound covering max possible values/differences
    int ans = high;

    while (low <= high) {
      int X = low + (high - low) / 2;
      if (check(X, s, arr)) {
        ans = X;
        high = X - 1; // Try to find a tighter answer
      } else {
        low = X + 1;
      }
    }
    cout << ans << "\n";
  }
  return 0;
}
