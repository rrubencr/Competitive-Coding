//Persistent segment tree operations
//Sample program : SPOJ - MKTHNUM
//Memeory Requirements: mostly O(nlogn + 4*n)

#include <bits/stdc++.h>
using namespace std;
 
const int MAX = 100005;
const int LIM = 263005;
 
#define inchar getchar_unlocked
 
template<typename T> void inPos(T &x){x=0;register T c=inchar();while(((c<48)||(c>57))&&(c!='-'))c=inchar();bool neg=false;if(c=='-')neg=true;for(;c<48||c>57;c=inchar());for(;c>47&&c<58;c=inchar())x=(x<<3)+(x<<1)+(c&15);if(neg)x=-x;}
 
int compress[MAX];
vector< pair<int,int> > nums;
 
struct node {
    int cnt;
    node *lc, *rc;
    node (int val, node *left, node *right) {
        this->cnt = val; 
        this->lc = left; 
        this->rc = right;
    }
    node* insert(int l, int r, int x, int val);
};
 
node *null, *root[MAX];
 
void init() {
    null = new node(0, NULL, NULL);
    null->lc = null;
    null->rc = null;
    root[0] = null;
}

//Complexity: O(n logn) 
node* node::insert(int l, int r, int x, int val) {
    if (l > x || r < x) {
        return this;
    }
    else if (l == r) {
        return new node(this->cnt + val, null, null);
    }
    int mid = (l+r)/2;
    return new node(this->cnt + val, this->lc->insert(l, mid, x, val), this->rc->insert(mid+1, r, x, val));
}
 
//Complexity : O(log n)
int query(node *a, node *b, int l, int r, int k) {
    if (l==r) {
        return l;
    }
    int total = b->lc->cnt - a->lc->cnt, mid = (l+r)/2;
    if (total >= k) {
        return query(a->lc, b->lc, l, mid, k);
    }
    else {
        return query(a->rc, b->rc, mid+1, r, k-total);
    }
}
 
//Sample "print function" for debugging
void traverse(node *a) {
    if (a==null) {
        return;
    }
    printf("%d ", a->cnt);
    traverse(a->lc);
    traverse(a->rc);
}
 
//MKTHNUM solution using persistent segment tree
int main() {
    #ifndef ONLINE_JUDGE
        freopen("inp.txt", "r", stdin);
    #endif
    init();
    int n, q, x, l, r, k, idx, ans;
    inPos(n), inPos(q);
    for(int i=1; i<=n; ++i) {
        inPos(x);
        nums.push_back({x, i});
    }
    sort(nums.begin(), nums.end());
    idx = 1;
    for(int i=1; i<=n; ++i) {
        compress[nums[i-1].second] = idx;
        idx += 1;
    }
    for(int i=1; i<=n; ++i) {
        root[i] = root[i-1]->insert(1, n, compress[i], 1);
    }
    while (q--) {
        inPos(l), inPos(r), inPos(k);
        idx = query(root[l-1], root[r], 1, n, k);
        ans = nums[idx-1].first;
        printf("%d\n", ans);
    }
    return 0;
}