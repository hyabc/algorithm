//bzoj 1588
#include <cstdio>
#include <algorithm>
#define INF 1000000000
struct node {
	int left, right, v, p, count;
} d[1000000];
int mem;
int left_rot(int x) {
	int y = d[x].right;
	/*****/
	d[y].p = d[x].p;
	d[x].right = d[y].left;
	d[y].left = x;
	d[x].p = y;
	d[d[x].right].p = x;
	return y;
}
int right_rot(int x) {
	int y = d[x].left;
	/*****/
	d[y].p = d[x].p;
	d[x].left = d[y].right;
	d[y].right = x;
	d[x].p = y;
	d[d[x].left].p = x;
	return y;
}
int access(int x) {
	while (d[x].p != 0) {
		if (d[d[x].p].p == 0) {
			int fa = d[x].p;
			if (x == d[fa].left)
				return right_rot(fa);
			else
				return left_rot(fa);
		}
		int y = d[x].p, z = d[y].p;int su = d[z].p;
		if (d[z].left == y && d[y].left == x) {
			right_rot(z);
			right_rot(y);
			if (su) {
				if (d[su].left == z) {d[su].left = x;d[x].p = su;}
				else {d[su].right = x;d[x].p = su;}
			}
			continue;
		}
		if (d[z].right == y && d[y].right == x) {
			left_rot(z);
			left_rot(y);
			if (su) {
				if (d[su].left == z) {d[su].left = x;d[x].p = su;}
				else {d[su].right = x;d[x].p = su;}
			}
			continue;
		}
		if (d[z].left == y && d[y].right == x) {
			d[z].left = left_rot(y);
			right_rot(z);
			if (su) {
				if (d[su].left == z) {d[su].left = x;d[x].p = su;}
				else {d[su].right = x;d[x].p = su;}
			}
		}
		if (d[z].right == y && d[y].left == x) {
			d[z].right = right_rot(y);
			left_rot(z);
			if (su) {
				if (d[su].left == z) {d[su].left = x;d[x].p = su;}
				else {d[su].right = x;d[x].p = su;}
			}
		}
		x = z;
	}
	return x;
}
int insert(int x, int value) {
	if (d[x].v == value) {
		d[x].count++;
		return access(x);
	}
	if (value < d[x].v) {
		if (d[x].left == 0) {
			mem++;int c = mem;
			d[c].count = 1;d[c].p = x;d[c].v = value;
			d[x].left = c;
			return access(c);
		} else return insert(d[x].left, value);
	}
	if (value > d[x].v) {
		if (d[x].right == 0) {
			mem++;int c = mem;
			d[c].count = 1;d[c].p = x;d[c].v = value;
			d[x].right = c;
			return access(c);
		} else return insert(d[x].right, value);
	}
}
int res;
int lower_find(int x, int value) {
	if (d[x].v == value) {
		res = d[x].v;
		return access(x);
	}
	if (value > d[x].v) {
		res = std::max(d[x].v, res);
		if (d[x].right == 0) return access(x);
		else return lower_find(d[x].right, value);
	}
	if (value < d[x].v) {
		if (d[x].left == 0) return access(x);
		else return lower_find(d[x].left, value);
	}
}
int upper_find(int x, int value) {
		if (d[x].v == value) {
		res = d[x].v;
		return access(x);
	}
	if (value < d[x].v) {
		res = std::min(d[x].v, res);
		if (d[x].left == 0) return access(x);
		else return upper_find(d[x].left, value);
	}
	if (value > d[x].v) {
		if (d[x].right == 0) return access(x);
		else return upper_find(d[x].right, value);
	}
}
int main() {
	int n;scanf("%d", &n);
	int a;
	scanf("%d", &a);
	int ans = a;
	mem = 1;
	d[1].v = a;d[1].count = 1;
	int root = 1;
	for (int i = 2;i <= n;i++) {
		scanf("%d", &a);
		res = -INF;
		root = lower_find(root, a);
		int lower = res;
		res = INF;
		root = upper_find(root, a);
		int upper = res;
		int result = INF;
		if (lower > -INF && lower <= a && a - lower < result) result = a - lower;
		if (upper < INF && a <= upper && upper - a < result) result = upper - a;
	//	printf("%d\n", result);
		ans += result;
		root = insert(root, a);
	}
	printf("%d\n", ans);
	return 0;
}
