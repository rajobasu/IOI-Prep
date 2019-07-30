#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <functional>
 
#define FOR(i,n) for(int i=0;i<n;i++)
#define FORE(i,a,b) for(int i = a;i<=b;i++)
#define ll long long int
#define pb push_back
#define vi vector<int>
#define ff first
#define ss second
#define vv vector
#define ii pair<int,int>
 
using namespace std;
 
const int MAXN = 2e5 + 1;
const ll INF = 1e17;
 
int n,m;
 
ll color[MAXN];
ll v[MAXN];
ll dp[MAXN];
ll sum = 0;
int lptr = 0;
int rptr  = -1;
multiset<ll> s1;
multiset<ll> s2;
 
inline __attribute__((always_inline)) void add(int ptr){
    s1.insert(v[ptr]);
    sum += v[ptr];
    if((int)s1.size() > m){
        ll v = *s1.begin();
        s1.erase(s1.begin());
        sum -= v;
        s2.insert(v);
    }
}
inline __attribute__((always_inline)) void remove(int ptr){
    if(!s2.empty() and s2.find(v[ptr]) != s2.end()){
        s2.erase(s2.find(v[ptr]));
    }else{
        sum -= v[ptr];
        s1.erase(s1.find(v[ptr]));
        if(!s2.empty()){
            auto it = s2.end();
            it--;
            s1.insert(*it);
            sum += *it;
            s2.erase(it);
        }
    }
    return;
}
 
inline __attribute__((always_inline)) ll cost(int l,int r){
    return s1.size() < m?-INF:sum;
}
 
inline __attribute__((always_inline)) void shiftRto(int x){
    while(rptr != x){
        if(rptr > x){
            remove(rptr--);
        }else{
            add(++rptr);
        }
    }
}
inline  __attribute__((always_inline)) void shiftLto(int x){
    while(lptr != x){
        if(lptr > x){
            add(--lptr);
        }else{
            remove(lptr++);
        }
    }
 
}
 
void recurse(int l,int r,int x,int y){
    if(l < 0 or r < 0 or l > r)return;
    int mid = (l+r)/2;
    ll mx = -INF;
    int optj = x;
    if(mid < x){
        dp[mid] = mx;
        return;
    }
    if(mid >= lptr){
        shiftRto(mid);
        shiftLto(x);
    }else{
        shiftLto(x);
        shiftRto(mid);
    }
    
    FORE(i,x,min(mid,y)){
        if(i > lptr)remove(lptr++);
        ll cst = cost(i,mid) - 2*(color[mid] - color[i]);
        if(cst > mx){
            optj = i;
            mx = cst;
        }
    }
    
    dp[mid] = mx;
    if(l == r)return;
    recurse(l,mid-1,x,optj);
    recurse(mid+1,r,optj,y);
}
 
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    vv<ii> all;
    FOR(i,n){
        int a,b;
        cin >> a >> b;
        all.pb({b,a});
    }
    sort(all.begin(),all.end());
    FOR(i,n)color[i] = all[i].ff,v[i] = all[i].ss;
    recurse(0,n-1,0,n-1);
    ll mx = -INF;
    FOR(i,n){
        mx = max(mx,dp[i]);
    }
    cout << mx << endl;
    return 0;
}