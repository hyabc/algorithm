//https://oi.men.ci/fft-notes/
#include <cstdio>
#include <cmath>
double pi = acos(-1.0);
#define MAXN 800010
bool reverse;
struct complex {
	double real, imag;
	complex(double r, double im):real(r), imag(im) {}
	complex(double r):real(r), imag(0) {}
	complex():real(0), imag(0) {}
};
complex operator * (complex a, complex b) {
	return complex(a.real * b.real - a.imag * b.imag, a.real * b.imag + a.imag * b.real);
}
complex operator - (complex a, complex b) {
	return complex(a.real - b.real, a.imag - b.imag);
}
complex operator + (complex a, complex b) {
	return complex(a.real + b.real, a.imag + b.imag);
}
complex conj(complex a) {
	a.imag = -a.imag;
	return a;
}
complex tmp[MAXN];
complex omega(int x, int k) {
	double real = cos( 2.0 * pi * k / x );
	double imag = sin( 2.0 * pi * k / x );
	complex ret(real, imag);
	if (reverse) return conj(ret);else return ret;
}	
complex a[MAXN], b[MAXN], c[MAXN], Omega[MAXN];
void fft(complex* a, int level) {
	int size = 1 << level;
	for (int i = 0;i < size;i++) {
		int ni = 0;
		for (int j = 0;j < level;j++) if (i & (1 << j)) ni |= (1 << (level - 1 - j));
		if (i < ni) {complex t = a[i];a[i] = a[ni];a[ni] = t;}
	}
	//preprocess omega
	for (int i = 0;i < size;i++) Omega[i] = omega(size, i);
	for (int i = 1;i <= level;i++) {
		int all = 1 << i;
		int half = all / 2;
		for (complex *start = a;start != a + size;start += all) {
			for (int j = 0;j < half;j++) {
				complex t = Omega[size / all * j] * start[half + j];
				start[j + half] = start[j] - t;
				start[j] = start[j] + t;
			}
		}
	}
}
int main() {
	int n, m;scanf("%d%d", &n, &m);
	for (int i = 0;i <= n;i++) scanf("%lf", &a[i].real);
	for (int i = 0;i <= m;i++) scanf("%lf", &b[i].real);
	int len = n + m;
	int level, size;
	for (level = 1, size = 2;size <= n + m + 3;level++, size <<= 1) ;
	reverse = false;
	fft(a, level);
	fft(b, level);
	for (int i = 0;i < size;i++) c[i] = a[i] * b[i];
	reverse = true;
	fft(c, level);
	for (int i = 0;i < size;i++) c[i].real /= size;
	printf("%d", (int)(c[0].real + 0.5));
	for (int i = 1;i <= len;i++) printf(" %d", (int)(c[i].real + 0.5));
	printf("\n");
	return 0;
}
