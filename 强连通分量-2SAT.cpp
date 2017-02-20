//hdu 3062
#include <cstring>
#include <cstdio>
#include <stack>
int cnt, clock;
int first[2010], next[2000010], tail[2000010], dfn[2010], low[2010], scc[2010];
void addedge(int u, int v) {
	cnt++;
	next[cnt] = first[u];
	first[u] = cnt;
	tail[cnt] = v;
}
std::stack<int> q;
void dfs(int u) {
	clock++;
	dfn[u] = clock;
	low[u] = dfn[u];
	q.push(u);
	for (int e = first[u];e != 0;e = next[e]) {
		int v = tail[e];
		if (dfn[v] == 0) {
			dfs(v);
			low[u] = std::min(low[u], low[v]);
		} else if (scc[v] == 0) low[u] = std::min(low[u], dfn[v]);
	}
	int v;
	if (low[u] == dfn[u]) {
		do {
			v = q.top();q.pop();
			scc[v] = u;
		} while (v != u);
	}
}
bool Main() {
	cnt = 0;
	int n, m;
	if (scanf("%d%d", &n, &m) != 2) return false;
	memset(first, 0, sizeof(first));memset(next, 0, sizeof(next));memset(tail, 0, sizeof(tail));memset(dfn, 0, sizeof(dfn));memset(low, 0, sizeof(low));memset(scc, 0, sizeof(scc));
	for (int i = 1;i <= m;i++) {
		int a1, a2, c1, c2;
		scanf("%d%d%d%d", &a1, &a2, &c1, &c2);
		a1++;a2++;
		int x = a1 + n * c1, y = a2 + n * c2;
		int Nx = a1 + n * (1 - c1), Ny = a2 + n * (1 - c2);
		addedge(x, Ny);addedge(y, Nx);
	}
	clock = 0;
	for (int i = 1;i <= 2 * n;i++) if (dfn[i] == 0) dfs(i);
	bool tf = true;
	for (int i = 1;i <= n;i++) if (scc[i] == scc[i + n]) {tf = false;break;}
	if (tf) printf("YES\n");else printf("NO\n");
	/*2-SAT:
	 * "x所在的强连通分量拓扑序在not x所在的强连通分量以后 ， x为true
	 */
	return true;
}
int main() {
	while (Main()) ;
	return 0;
}
