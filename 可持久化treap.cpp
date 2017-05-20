//uva12538
#include <cstdio>
#include <utility>
#include <cstring>
#include <cstdlib>
#define MAXN 5000010
int mem;
int left[MAXN], right[MAXN], size[MAXN], h[MAXN];
char ch[MAXN];
int root[50010];
int newnode(char x) {
	mem++;
	left[mem] = right[mem] = 0;
	ch[mem] = x;
	h[mem] = rand() % 9999;
	size[mem] = 1;
	return mem;
}
int fork(int x) {
	mem++;
	left[mem] = left[x];
	right[mem] = right[x];
	ch[mem] = ch[x];
	h[mem] = h[x];
	size[mem] = size[x];
	return mem;//bug
}
void maintain(int x) {
	size[x] = size[left[x]] + size[right[x]] + 1;
}
int merge(int x, int y) {
	if (x == 0) return y;
	if (y == 0) return x;
	if (h[x] > h[y]) {
		int z = fork(x);
		right[z] = merge(right[z], y);
		maintain(z);
		return z;
	} else {
		int z = fork(y);
		left[z] = merge(x, left[z]);
		maintain(z);
		return z;
	}
}
typedef std::pair<int, int> droot;
droot split(int x, int k) {
	droot ret(0, 0);
	if (x == 0) return ret;
	if (k <= size[left[x]]) {
		ret = split(left[x], k);
		int y = fork(x);
		left[y] = ret.second;
		maintain(y);
		ret.second = y;
		return ret;
	} else {
		ret = split(right[x], k - 1 - size[left[x]]);
		int y = fork(x);
		right[y] = ret.first;
		maintain(y);
		ret.first = y;
		return ret;
	}
}
int cnt;
void print(int x) {
	if (x == 0) return;
	print(left[x]);
	putchar(ch[x]);
	if (ch[x] == 'c') cnt++;
	print(right[x]);
}
char st[1000];
int q[1000];
int build() {
	int n = strlen(st + 1);
	int top = 1;q[1] = newnode(' ');
	h[q[1]] = 1000000;
	for (int i = 1;i <= n;i++) {
		int cur = newnode(st[i]);
		while (h[cur] > h[q[top]]) {
			maintain(q[top]);
			top--;
		}
		int p = q[top];
		left[cur] = right[p];
		right[p] = cur;
		maintain(cur);
		maintain(p);
		top++;q[top] = cur;
	}
	while (top) {
		maintain(q[top]);
		top--;
	}
	return right[q[1]];
}
int main() {
	cnt = 0;
	mem = 0;	
	int m;scanf("%d", &m);
	root[0] = 0;
	int version = 0;
	while (m--) {
		int op;scanf("%d", &op);
		if (op == 1) {
			int pos;
			scanf("%d%s", &pos, st + 1);
			pos -= cnt;
			int is = build();
			droot ret = split(root[version], pos);
			root[++version] = merge(merge(ret.first, is), ret.second);
		}
		if (op == 2) {
			int p, c;scanf("%d%d", &p, &c);
			p -= cnt;c -= cnt;
			droot t1 = split(root[version], p - 1);
			droot t2 = split(t1.second, c);
			root[++version] = merge(t1.first, t2.second);
		}
		if (op == 3) {
			int	v, p, c;scanf("%d%d%d", &v, &p, &c);
			v -= cnt;p -= cnt;c -= cnt;
			droot t1 = split(root[v], p - 1);
			droot t2 = split(t1.second, c);
			print(t2.first);putchar('\n');
		}
	}
	return 0;
}
