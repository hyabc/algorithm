//poj3469
#include <cstdio>
#include <cstring>
#include <algorithm>
int s, t;
int cnt;
int INF;
int first[40010],  next[500010], tail[500010], rev[500010], iter[40010], c[500010], f[500010], q[40010], dep[40010];
void addedge(int x, int y, int cap, int isdouble) {
	cnt++;
	next[cnt] = first[x];
	first[x] = cnt;
	tail[cnt] = y;
	c[cnt] = cap;
	f[cnt] = 0;
	rev[cnt] = cnt + 1;
	cnt++;
	next[cnt] = first[y];
	first[y] = cnt;
	tail[cnt] = x;
	c[cnt] = cap * isdouble;
	f[cnt] = 0;
	rev[cnt] = cnt - 1;
}
bool bfs()  {
	int l = 1, r = 1;q[1] = t;
	memset(dep, 8, sizeof(dep));
	dep[t] = 1;
	INF = dep[0];
	while (l <= r) {
		int cur = q[l++];
		for (int e = first[cur];e != 0;e = next[e]) {
			int v = tail[e];
			if (c[rev[e]] > f[rev[e]] && dep[v] >= INF) {
				dep[v] = dep[cur] + 1;
				q[++r] = v;
			}
		}
	}
	if (dep[s] >= INF) return false;else return true;
}
int dfs(int u, int cap) {
	if (u == t) return cap;
	int flowtotal = 0;
	for (int e = first[u];e != 0;e = next[e]) {
		int v = tail[e];
		if (dep[v] == dep[u] - 1) {
			int flow = dfs(v, std::min(c[e] - f[e], cap));
			flowtotal += flow;
			f[e] += flow;f[rev[e]] -= flow;
			cap -= flow;
			if (cap == 0) {
				return flowtotal;
			}
		}
	}
	return flowtotal;
}
int main() {
	int n, m;scanf("%d%d", &n, &m);
	cnt = 0;
	s = n + 1, t = n + 2;
	for (int i = 1;i <= n;i++) {
		int a, b;scanf("%d%d", &a, &b);
		addedge(s, i, a, 0);
		addedge(i, t, b, 0);
	}
	for (int i = 1;i <= m;i++) {
		int a, b, w;scanf("%d%d%d", &a, &b, &w);
		addedge(a, b, w, 1);
	};
	long long flow = 0;
	for (int i = 1;i <= n + 2;i++) iter[i] = first[i];
	while (bfs()) flow += dfs(s, INF);
	printf("%lld\n", flow);
	return 0;
}
