
#include <iostream>
#include <map>
#define base1 48
#define base2 39
#define mod 1000000007
using namespace std;
typedef long long ll;
const int maxn = 210;
int n, m, L;
map <pair <ll, ll>, int> z;
ll ans;
pair <int, int> to[maxn][maxn][8][40];
ll f[maxn][maxn][8][40], g[maxn][maxn][8][40], pz[maxn], py[maxn], p2[maxn];
int p[8][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, -1}, {1, 1}, {-1, 1}, {-1, -1}};
int c[maxn][maxn];
int tx (int x, int v) {
  int tmp = x + p[v][0];
  if (tmp == n + 1) return 1;
  if (tmp == 0) return n;
  return tmp;
}
int ty (int y, int v) {
  int tmp = y + p[v][1];
  if (tmp == m + 1) return 1;
  if (tmp == 0) return m;
  return tmp;
}
ll Pow (ll x, ll y) {
  if (y == 0) return 1;
  if (y == 1) return x;
  if (y & 1) {
    ll t = Pow (x, y >> 1);
    return t * t % mod * x % mod;
  } else {
    ll t = Pow (x, y >> 1);
    return t * t % mod;
  }
}
ll gcd (ll x, ll y) {
  if (y == 0) return x;
  return gcd (y, x % y);
}
int main () {
  cin.tie (0) -> sync_with_stdio (false);
  cin >> n >> m >> L;
  for (int i = 1; i <= n; i++) {
    cin.get ();
    for (int j = 1; j <= m; j++) {
      c[i][j] = cin.get ();
      c[i][j] -= 'a';
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      for (int v = 0; v < 8; v++) {
        int x = tx (i, v), y = ty(j, v);
        f[i][j][v][0] = c[i][j] % mod;
        g[i][j][v][0] = c[i][j] % mod;
        to[i][j][v][0] = {x, y};
      }
    }
  }
  p2[0] = 1;
  for (int k = 1; k <= 30; k++) {  
    p2[k] = (p2[k - 1] << 1);
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        for (int v = 0; v < 8; v++) {
          int x = to[i][j][v][k - 1].first, y = to[i][j][v][k - 1].second;
          f[i][j][v][k] = (f[i][j][v][k - 1] * Pow (base1, p2[k  - 1]) + f[x][y][v][k - 1]) % mod;
          g[i][j][v][k] = (g[i][j][v][k - 1] * Pow (base2, p2[k  - 1]) + g[x][y][v][k - 1]) % mod;
          to[i][j][v][k] = to[x][y][v][k - 1];
        }
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      int u = i, v = j, len = 0;
      for (int v_ = 0; v_ < 8; v_++) {
        ll tmp = 0, res = 0;
        len = 0;
        for (int k = 30; k >= 0; k--) {
          if (p2[k] + len <= L) {
            len += p2[k];
            tmp = (tmp * Pow (base1, p2[k]) + f[u][v][v_][k]) % mod;
            res = (res * Pow (base2, p2[k]) + g[u][v][v_][k]) % mod;
            int x = to[u][v][v_][k].first, y = to[u][v][v_][k].second;
            u = x; v = y;
          }
        }
        // cout << i << ' ' <<  j << ' ' << v_ << ' ' << tmp << endl;
        z[{tmp, res}]++;
        ans += z[{tmp, res}];
      }
    }
  }
  ll gc = gcd (n * m * 8 * n * m * 8, ans);
  cout << ans / gc << '/' << n * m * 8 * n * m * 8 / gc;
  return 0;
}
