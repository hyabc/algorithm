//bzoj 1588
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#define INF 1000000000
struct node {
	int l, r, v, count, h;
} d[1000000];
int mem;
int rightrot(int x) {
	int y = d[x].l;
	d[x].l = d[y].r;
	d[y].r = x;
	return y;
}
int leftrot(int x) {
	int y = d[x].r;
	d[x].r = d[y].l;
	d[y].l = x;
	return y;
}
int insert(int x, int val) {
	if (x == 0) {
		mem++;
		d[mem].l = d[mem].r= 0;d[mem].count = 1;d[mem].v = val;d[mem].h = rand();
		return mem;
	}
	if (d[x].v == val) {
		d[x].count++;
		return x;
	}
	if (val < d[x].v) {
		d[x].l = insert(d[x].l, val);
		if (d[d[x].l].h > d[x].h) x = rightrot(x);
		return x;
	}
	if (val > d[x].v) {
		d[x].r = insert(d[x].r, val);
		if (d[d[x].r].h > d[x].h) x = leftrot(x);
		return x;
	}
}
int lower_find(int x, int val) {
	if (x == 0) return -INF;
	if (val == d[x].v) return d[x].v;
	if (val < d[x].v) return lower_find(d[x].l, val);
	if (val > d[x].v) {
		int ret = lower_find(d[x].r, val);
		return std::max(d[x].v, ret);
	}
}
int upper_find(int x, int val) {
	if (x == 0) return INF;
	if (val == d[x].v) return d[x].v;
	if (val > d[x].v) return upper_find(d[x].r, val);
	if (val < d[x].v) {
		int ret = upper_find(d[x].l, val);
		return std::min(d[x].v, ret);
	}
}
int main() {
	int n;scanf("%d", &n);
	int a;scanf("%d", &a);
	int ans = a;
	mem = 1;
	int root = 1;d[1].l = d[1].r = 0;d[1].count = 1;d[1].v = a;d[1].h = rand();
	for (int i = 1;i < n;i++) {
		scanf("%d", &a);
		int lower = lower_find(root, a), upper = upper_find(root, a);
		if (lower <= -INF || a - lower > upper - a) ans += upper - a;
		else ans += a - lower;
		root = insert(root, a);
	}
	printf("%d\n", ans);
	return 0;
}