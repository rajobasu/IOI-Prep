/*
SOLUTION : the brute force soln, has some cases. uses the fact that there exists only M^1.5 triangles in
a graph.
*/

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
#include <complex>
#include <stack>
#include <set>
#include <fstream>

#define FOR(i,n) for(int i = 0;i < n; i++)
#define FORE(i,a,b) for(int i = a; i <= b ; i++)
#define ss second
#define ff first
#define ll long long int
#define ii pair<int,int>
#define il pair<int,ll>
#define li pair<ll,int>
#define x ff
#define y ss
#define lii pair<ll,pair<int,int> > 
#define piil pair<int ,pair<int,int> > 
#define iii pair<pair<int,int>,int> 
#define vi vector<int>
#define pb push_back
#define mp make_pair
using namespace std;

const int MAXK = 51;
const int MAXN = 100005;
const int INF = 1e9;

set<int> g[MAXN];
set<int> g2[MAXN];
int depth[MAXN];
int art[MAXN];


void dfs(int node,int p){
    if(p == -1)depth[node] = 0;
    else depth[node] = depth[p] + 1;

    for(auto child : g[node]){
        dfs(child, node);
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n,m,k,a,b;
    cin >> n >> m >> k >> a >> b;
    k--;

    FOR(i,m){
        int c,d;
        cin >> c >> d;
        c--;d--;
        g[c].insert(d);
        g[d].insert(c);
        g2[c].insert(d);
        g2[d].insert(c);
    }
    // input taken
    ll dist1[n];FOR(i,n)dist1[i] = INF;
    queue<ii> q;
    q.push({0,k});
    while(!q.empty()){
        ii node = q.front();q.pop();
        if(dist1[node.ss] <= node.ff)continue;
        dist1[node.ss] = node.ff;
        for(auto e:g[node.ss]){
            q.push({node.ff+1,e});
        }
    }
    ll dist2[n];FOR(i,n)dist2[i] = INF;

    bool usedAs[n][2];// 0 -> final, 1 -> relay
    FOR(i,n)usedAs[i][0] = usedAs[i][1] = 0;
    

    queue<ii> nq;
    bool gotF[n];
    FOR(i,n)gotF[i] = 0;
    nq.push({0,k});
    bool tmp[n];

    FOR(i,n)tmp[i] = 0;
    while(!nq.empty()){
        ii node = nq.front();nq.pop();
        if(dist2[node.ss] <= node.ff)continue;
        dist2[node.ss] = node.ff;
        for(auto e:g[node.ss])tmp[e] = 1;
        for(auto e:g[node.ss]){
            vector<ii> tmpp;
            for(auto f:g2[e]){

                if(gotF[f] or tmp[f])continue;
                else {
                    for(auto x:g[f]){
                        tmpp.pb({x,f});
                    }
                    nq.push({node.ff+1,f});
                    gotF[f] = 1;
                }
            }
            for(auto x:tmpp)g2[x.ff].erase(x.ss);
        }
        for(auto e:g[node.ss])tmp[e] = 0;
    }

    FOR(i,n){
        cout << min(a*dist1[i],min(dist2[i]*b , b*(dist1[i]/2) + a*(dist1[i]%2))) << endl;;
    }


    
    return 0;
}



