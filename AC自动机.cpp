//bzoj3172
//HASHTAG: ac-automaton
#include <cstdio>
#include <cstring>
struct node {
    node* ch[40];
    node *next, *fail;
    bool isword;
    int cnt;
 
    node():next(0), fail(0), isword(false), cnt(0) {
        memset(ch, 0, sizeof(ch));
    }
    void apply() {
        cnt++;
        if (next) next->apply();
    }
} *root, *ptr;
 
node* db[400];
node pool[1000010];
char st[210][100010];
node* q[2000010];
void init() {
    ptr = pool;
 
    root = pool;
    root->fail = root;
}
node* newnode() {
    ptr++;
    return ptr;
}
node* insert(node* x, char* begin, char* end) {
    for (char* i = begin;i != end;i++) {
        if (!x->ch[*i  - 'a']) x->ch[*i - 'a'] = newnode();
        x = x->ch[*i - 'a'];
    }
    x->isword = true;
    return x;
}
void build() {
    int l = 1, r = 1;q[1] = root;
    while (l <= r) {
        node* x = q[l++];
        for (int i = 0;i < 30;i++) 
            if (!x->ch[i])
                x->ch[i] = x == root  ?  root  :  x->fail->ch[i];
            else {
                x->ch[i]->fail = x == root  ?  root  :  x->fail->ch[i];
                x->ch[i]->next = x->ch[i]->fail->isword  ?  x->ch[i]->fail  :  x->ch[i]->fail->next;
                q[++r] = x->ch[i];
            }
    }
}
node* trans(node* x, int op) {
    x = x->ch[op];
    if (x->isword) x->apply();
    else if (x->next) x->next->apply();
    return x;
}
int main() {
    int n;scanf("%d\n", &n);
    for (int i = 1;i <= n;i++) scanf("%s\n", st[i]);
 
    init();
 
    for (int i = 1;i <= n;i++) db[i] = insert(root, st[i], st[i] + strlen(st[i]));
    build();
 
    node* cur = root;
    for (int i = 1;i <= n;i++) {
        for (int j = 0;j < strlen(st[i]);j++) cur = trans(cur, st[i][j] - 'a');
        cur = trans(cur, 27);
    }
     
    for (int i = 1;i <= n;i++) printf("%d\n", db[i]->cnt);
    return 0;
}
