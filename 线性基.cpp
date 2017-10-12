//luogu 3812
#include <cstdio>
long long a[1000];
long long power[100];
bool discard[1000];
int main() {
    int n;scanf("%d", &n);
    for (int i = 1;i <= n;i++) scanf("%lld", &a[i]);
    power[0] = 1;
    for (int i = 1;i <= 60;i++) power[i] = power[i - 1] * 2;
    
    long long ans = 0;
    for (int i = 60;i >= 0;i--) {
        bool tf = false;int rec;
        for (int j = 1;j <= n;j++) if (!discard[j]) 
            if (a[j] & power[i]) {
                tf = true;
                rec = j;
                break;
            }

        if (tf) {
            discard[rec] = true;
            if ((ans & power[i]) == 0) ans ^= a[rec];
            for (int j = 1;j <= n;j++) if (!discard[j])
                if ((a[j] & power[i]))
                    a[j] = a[j] ^ a[rec];
        }
    }
    printf("%lld\n", ans);
    return 0;
}
