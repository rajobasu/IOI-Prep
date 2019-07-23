#include <iostream>
#include <vector>
#include <set>
#include <iomanip>
#include <algorithm>
#include <functional>
#include <stdio.h>
#include <cmath>
#include <queue>
#include <string>
#include <map>
#include <fstream>
#include <complex>
#include <random>
#include <stack>
#include <chrono>
#include <set>

#define FOR(i,n) for(int i=0;i<n;i++)
#define FORE(i,a,b) for(int i=a;i<=b;i++)
#define ll long long int
#define vi vector<int>
#define ii pair<int,int>
#define pb push_back
#define mp make_pair
#define ff first
#define il pair<int,ll>
#define li pair<ll,int>
#define ss second
#define pll pair<ll,ll>
#define cd complex<double> 
#define ld long double
#define pld pair<ld,ld>
#define plli pair<pll,ll>
#define vv vector
 
using namespace std;

const int MAXN = 3e5 + 10;
ll pe[MAXN];
vi g[MAXN];
ll a[MAXN];
ll b[MAXN];
multiset<ll,greater<ll> >* sp[MAXN];

void dfs(int node){
    if(g[node].size() == 0){
        // this is a leaf node;
        a[node] = 1;
        b[node] = -pe[node];
        sp[node] = new multiset<ll,greater<ll> >();
        sp[node]->insert(pe[node]);
        sp[node]->insert(pe[node]);
    }else{
        ll mx = 0;
        int ind = 0;
        for(auto e : g[node]){
            dfs(e);
            if(sp[e]->size() > mx){
                ind = e;
                mx = sp[e]->size();
            }
        }
        sp[node] = sp[ind];
        for(auto e : g[node]){
            a[node] += a[e];
            b[node] += b[e];
            if(e == ind)continue;
            for(auto x : *sp[e]){
                sp[node]->insert(x);
            }
        }
        while(a[node] > 1){
            ll pt = *(sp[node]->begin());
            sp[node]->erase(sp[node]->begin());
            a[node]--;b[node] += pt;
        }
        ll a1 = *(sp[node]->begin());sp[node]->erase(sp[node]->begin());
        ll b1 = *(sp[node]->begin());sp[node]->erase(sp[node]->begin());
        sp[node]->insert(a1 + pe[node]);
        sp[node]->insert(b1 + pe[node]);
        b[node] -= pe[node];
    }
}

int main(){
    int n,m;
    cin >> n >> m;
    FOR(i,n+m-1){
        int a,b;
        cin >> a >> b;
        a--;
        pe[i+1] = b;
        g[a].pb(i+1);
    }
    dfs(0);
    //FOR(i,n)cout << a[i] << " " << b[i] << endl;
    while(a[0] > 0){
        ll pt = *(sp[0]->begin());
        sp[0]->erase(sp[0]->begin());
        a[0]--;b[0] += pt;
    }
    cout << b[0] << endl;
    return 0;
}