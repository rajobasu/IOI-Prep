//#pragma GCC optimize("Ofast")
//#pragma GCC target("avx,avx2,fma")

#include <stdio.h>     
#include <stdlib.h>    
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <queue>
#include <deque>
#include <iomanip>
#include <cmath>
#include <set>
#include <stack>
#include <map>
#include <unordered_map>
#include "factories.h"
 
#define FOR(i,n) for(int i=0;i<n;i++)
#define FORE(i,a,b) for(int i=a;i<=b;i++)
#define ll long long 
#define ld long double
#define vi vector<int>
#define pb push_back
#define ff first
#define ss second
#define il pair<int,ll>
#define ii pair<int,int>
#define lii pair<pair<ll,int>,il>
#define iii pair<int,ii>
#define iiii pair<iii,int>
#define pll pair<ll,ll>
#define plll pair<ll,pll>
#define vv vector
#define endl '\n'
 
using namespace std;

const ll INF = 1e18;
const int MAXN = 5e5+5;
const int LOGN = 24;

int n;
// ==================== Sparse table and basic graph setup ============================
vv<ii> g[MAXN];
ll dist[MAXN];
int depth[MAXN];

ii minCost[LOGN][4*MAXN];
int euler[MAXN*2];
int tin[MAXN*2];
int tout[MAXN*2];
int T = 0;
void dfs_init_setup_lca(int node,int p = -1){
    tin[node] = T;
    tout[node] = T;
    euler[T++] = node;
    for(auto e: g[node]){
        if(e.ff == p)continue;

        dist[e.ff] = e.ss + dist[node];
        depth[e.ff] = 1+ depth[node];
        dfs_init_setup_lca(e.ff,node);
        tout[node] = T;
        euler[T++] = node;
    }
}
inline ii combine(ii a,ii b){
    if(a.ff <= b.ff)return a;
    else return b;
}

int _log[4*MAXN+1];
void calculateSparseTables(){
    _log[1] = 0;
    for (int i = 2; i <= T; i++)
        _log[i] = _log[i/2] + 1;
    
    FOR(i,LOGN){   
        FOR(j,T){
            if(i == 0){
                minCost[i][j] = {depth[euler[j]],euler[j]};
                continue;       
            }
            int add = (1<<(i-1));
            int nxt = j+add;
            if(nxt >= T){
                minCost[i][j] = minCost[i-1][j];
            }else{
                ii a = minCost[i-1][j];
                ii b = minCost[i-1][nxt];
                minCost[i][j] = combine(a,b);
            }
        }
    }
}



int LCA(int a,int b){
    if(a == b)return a;
    if(tin[a] > tin[b])swap(a,b);
    //if(tout[a] > tout[b])return a;
    int L = tin[a];
    int R = tin[b];
    int j = _log[R - L + 1];
    return combine(minCost[j][L], minCost[j][R - (1 << j) + 1]).ss;
}

ll distance(int a,int b){
    return dist[a] + dist[b] - 2*dist[LCA(a,b)];
}
// ==================== Centroid tree construction ====================================
bool blocked[MAXN];
int subtree[MAXN];
int centroidParent[MAXN];

void dfs_centroid_setup(int node,int p = -1){
    subtree[node] = 1;
    for(auto e: g[node]){
        if(blocked[e.ff] or e.ff == p)continue;
        dfs_centroid_setup(e.ff,node);
        subtree[node] += subtree[e.ff];
    }
}
int getCentroid(int node,int tot,int p = -1){
    for(auto e: g[node]){
        if(blocked[e.ff] or e.ff == p)continue;
        if(2*subtree[e.ff] > tot)return getCentroid(e.ff,tot,node); 
    }
    return node;
}
queue<ii> subtrees_remaining;
void processCentroid(int node,int par){
    dfs_centroid_setup(node);
    int c = getCentroid(node,subtree[node]);
    centroidParent[c] = par;
    for(auto e: g[c]){
        if(blocked[e.ff])continue;
        subtrees_remaining.push({e.ff,c});
    }
    blocked[c] = 1;
}

void centroidDecomp(){
    subtrees_remaining.push({0,-1});
    while(!subtrees_remaining.empty()){
        auto e = subtrees_remaining.front();subtrees_remaining.pop();
        processCentroid(e.ff,e.ss);
    }
}
// ==================== Problem Specific Stuff =======================================
ll ans[MAXN];


void Init(int n, int A[], int B[], int D[]) {
    ::n = n;
    FOR(i,n-1){
        g[A[i]].pb({B[i],D[i]});
        g[B[i]].pb({A[i],D[i]});
    }
    dfs_init_setup_lca(0);
    calculateSparseTables();
    centroidDecomp();
    //cout << ctr << endl;
    FOR(i,n)ans[i] = INF;
    // FOR(i,n){
    //     FOR(j,i)cout << j << " " << i << " " << LCA(j,i) << endl;
    // }
}

ll Query(int S, int X[], int T, int Y[]) {
    vv<int> affectedNodes;
    //cout << "LCA: " << LCA(2,5) << " " << distance(2,5) << endl;
    FOR(i,S){
        int item = X[i];
        while(item != -1){
            affectedNodes.pb(item);
            ans[item] = min(ans[item],distance(item,X[i]));
            item = centroidParent[item];
        }
    }
    ll d = INF;
    FOR(i,T){
        int item = Y[i];
        while(item != -1){
            d = min(d,distance(item,Y[i])+ans[item]);
            item = centroidParent[item];
        }
    }
    for(auto e: affectedNodes)ans[e] = INF;
    return d;
}



