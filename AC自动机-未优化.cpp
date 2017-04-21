//https://oi.men.ci/acam-notes/的优化
//hdu 2896
#include <cstring>
#include <algorithm>
#include <cstdio>
int mem;
char st[10010];
int g[100010][128];
int list[10000];
int tag[100010][10];
int fail[100010];
void dfs(int u, int dep) {
    for (int i = 0;i < 128;i++) {
        int v = g[u][i];
        if (v == 0) continue;
        if (dep == 0) fail[v] = 0; else {
            fail[v] = fail[u];
            while (fail[v] != 0 && g[fail[v]][i] == 0) fail[v] = fail[fail[v]];
            fail[v] = g[fail[v]][i];
        }
        for (int i = 1;i <= tag[fail[v]][0];i++) {
            tag[v][0]++;
            tag[v][tag[v][0]] = tag[fail[v]][0];
        }
        dfs(v, dep + 1);
    }
}
int main() {
    int n;scanf("%d\n", &n);
    mem = 0;
    for (int i = 1;i <= n;i++) {
        gets(st);
        int cur = 0;
        for (int j = 0;j < strlen(st);j++) {
            char x = st[j];
            if (g[cur][x] == 0) {
                mem++;g[cur][x] = mem;
            }
            cur = g[cur][x];
        }
        tag[cur][0] = 1;tag[cur][1] = i;
    }
    dfs(0, 0);
    int ans = 0;
    int m;scanf("%d\n", &n);
    for (int i = 1;i <= n;i++) {
        bool tf = true;
        gets(st);
        int cur = 0;
        list[0] = 0;
        for (int j = 0;j < strlen(st);j++) {
            char x = st[j];
            while (cur != 0 && g[cur][x] == 0) cur = fail[cur];
            cur = g[cur][x];
            if (tag[cur][0]) {
                tf = false;
                for (int k = 1;k <= tag[cur][0];k++) {
                    bool disappear = true;
                    for (int qaq = 1;qaq <= list[0];qaq++)
                        if (list[qaq] == tag[cur][k]) disappear = false;
                    if (disappear) {
                        list[0]++;
                        list[list[0]] = tag[cur][k];
                    }
                }
            }
        }
        if (!tf) {
            ans++;
            printf("web %d:", i);
            std::sort(list+1, list+list[0]+1);
            for (int j = 1;j <= list[0];j++) printf(" %d", list[j]);
            printf("\n");
        }
    }
    printf("total: %d\n", ans);
    return 0;
}
