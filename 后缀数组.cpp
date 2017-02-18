//https://vjudge.net/problem/SPOJ-DISUBSTR
#include <cstdio>
#include <algorithm>
#include <cstring>
int delta, n;
int sa[10010], rank[10010], tmp[10010], height[10010];
char st[10010];
bool comp(int x, int y) {
	if (rank[x] != rank[y]) return rank[x] < rank[y];
	int a1 = (x + delta <= n)  ?  rank[x + delta]  :  -1,
		a2 = (y + delta <= n)  ?  rank[y + delta]  :  -1;
	return a1 < a2;
}
void Main() {
	scanf("%s", st+1);
	n = strlen(st+1);
	n++;st[n] = 0;
	for (int i = 1;i <= n;i++) {
		sa[i] = i;
		rank[i] = st[i];
	}
	for (delta = 1;delta <= n;delta <<= 1) {
		std::sort(sa+1, sa+1+n, comp);
		tmp[sa[1]] = 1;
		for (int i = 2;i <= n;i++)
			tmp[sa[i]] = tmp[sa[i-1]] + (comp(sa[i-1], sa[i])  ?  1  :  0);
		memcpy(rank, tmp, sizeof(tmp));
	}
//	for (int i = 1;i < n;i++) rank[i]--;
//	for (int i = 1;i < n;i++) sa[i] = sa[i+1];
//	n--;
	height[0] = 0;
	for (int i = 1;i <= n;i++) {
		int h = height[i - 1];
		if (h > 0) h--;
		if (rank[i] == 1) h = 0;else {
			while (st[sa[rank[i]-1] + h] == st[i + h]) h++;
		}
		height[i] = h;
	}
	int ans = (n-1) * n / 2;
	for (int i = 1;i <= n;i++) ans -= height[i];
	printf("%d\n", ans);
}
int main() {
	int T;scanf("%d\n", &T);
	while (T--) Main();
	return 0;
}
