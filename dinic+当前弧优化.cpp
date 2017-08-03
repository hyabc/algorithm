//bzoj3280
//HASHTAG: minimum-cut graph-building
#include <cstdio>
#include <cstring>
#define INF 100000000
int edge;
int a[1000], l[1000], p[1000], d[1000], q[1000];
bool inq[100];
int first[10010], next[20010], tail[20010], f[20010], c[20010], cost[20010], prev[20010];
int queue[1000010];
int S, T;
void addedge(int u, int v, int cap, int co) {
	edge++;
	next[edge] = first[u];
	first[u] = edge;
	tail[edge] = v;
	c[edge] = cap;
	f[edge] = 0;
	cost[edge] = co;

	edge++;
	next[edge] = first[v];
	first[v] = edge;
	tail[edge] = u;
	c[edge] = 0;
	f[edge] = 0;
	cost[edge] = -co;
}
bool spfa() {
	memset(d, 8, sizeof(d));
	memset(inq, false, sizeof(inq));
	int l = 1, r = 1;queue[1] = S;d[S] = 0;inq[S] = true;
	while (l <= r) {
		int u = queue[l++];
		inq[u] = false;
		//BUG
		for (int e = first[u];e;e = next[e]) if (f[e] < c[e] && d[u] + cost[e] < d[tail[e]]) {
			int v = tail[e];
			d[v] = d[u] + cost[e];
			prev[v] = e;
			if (!inq[v]) {
				inq[v] = true;
				queue[++r] = v;
			}
		}
	}
	return d[T] < 10000000;
}
int total;
int augment() {
	int v = T;
	int flow = INF;
	while (v != S) {
		int e = prev[v];
		int u = tail[e ^ 1];
		if (c[e] - f[e] < flow) flow = c[e] - f[e];
		v = u;
	}
	v = T;
	while (v != S) {
		int e = prev[v];
		int u = tail[e ^ 1];
		f[e] += flow;f[e ^ 1] -= flow;
		total += cost[e] * flow;
		v = u;
	}
	return flow;
}
void solve() {
	memset(first, 0, sizeof(first));
	int n, m, k;scanf("%d%d%d", &n, &m, &k);
	int sum = 0;
	for (int i = 1;i <= n;i++) {scanf("%d", &a[i]);sum += a[i];}
	for (int i = 1;i <= m;i++) scanf("%d%d", &l[i], &p[i]);
	for (int i = 1;i <= k;i++) scanf("%d%d", &d[i], &q[i]);
	S = 2 * n + 1, T = 2 * n + 2;
	edge = 1;
	for (int i = 1;i <= m;i++) addedge(S, 1, l[i], p[i]);
	for (int i = 1;i < n;i++) addedge(i, i + 1, INF, 0);
	for (int i = 1;i <= n;i++) {
		addedge(S, i + n, a[i], 0);
		addedge(i, T, a[i], 0);
	}
// 	for (int i = 1;i <= n;i++) addedge(i + n, T, INF, 0);//BUG
	for (int type = 1;type <= k;type++)
		for (int i = 1;i <= n - d[type] - 1;i++) 
			addedge(i + n, i + d[type] + 1, INF, q[type]);
	int ans = 0;
	total = 0;
	while (spfa()) ans += augment();
	if (ans == sum) printf("%d\n", total);else printf("impossible\n");
}
int main() {
	int T;scanf("%d", &T);
	for (int i = 1;i <= T;i++) {
		printf("Case %d: ", i);
		solve();
	}
	return 0;
}
