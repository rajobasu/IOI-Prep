/*
SOLUTION : Form the difference equations and apply bellman ford
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
#include <chrono>
#include <random>
#include <stack>
#include <set>
#include <fstream>

#define FOR(i,n) for(int i = 0;i < n; i++)
#define FORE(i,a,b) for(int i = a; i <= b ; i++)
#define ss second
#define ff first
#define ll long long int
#define ii pair<ll,ll>
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

const int INF = 10000000;

const ll MOD = 998244353;
const int MAXN = 1001;

vector<ii> g[MAXN];

int main(){
    int n,a0,b0,l0,a1,b1,l1;
    cin >> n >> a0 >> b0 >> l0 >> a1 >> b1 >> l1 ;
    // we add the constraints on the prefix sum array. 
    vector<iii> all;
    FORE(i,1,n){
        /* 
            the constraints can be listed as
            s[i] - s[i-1] <= 1 
            s[i-1] - s[i] <= 0
            
            s[i] - s[i-l0] <= l0-a0
            s[i-l0] - s[i] <= -(l0-b0)

            s[i] - s[i-l1] <= b1
            s[i-l1] - s[i] <= -a1
        */

        if(i >= 1){
            g[i-1].pb({i,1}); all.pb({{i-1,i},1});
            g[i].pb({i-1,0}); all.pb({{i,i-1},0});
        }
        if(i-l0 >= 0){
            g[i-l0].pb({i,l0-a0}); all.pb({{i-l0,i},l0-a0});
            g[i].pb({i-l0,b0-l0}); all.pb({{i,i-l0},b0-l0});
        }
        if(i-l1 >= 0){
            g[i-l1].pb({i,b1}); all.pb({{i-l1,i},b1});
            g[i].pb({i-l1,-a1}); all.pb({{i,i-l1},-a1});
        }
    }

    FOR(i,n+1){
        g[0].pb({i+1,0}); all.pb({{n+1,i},0});
    }

    int dist[n+2];FOR(i,n+2)dist[i] = INF;dist[0] = 0;

    FOR(i,n+1){
        for(auto e:all){
            dist[e.ff.ss] = min(dist[e.ff.ss],dist[e.ff.ff] + e.ss);
        }
    }

    //FOR(i,n+1)cout << dist[i] << " ";
    //cout << endl;
    FORE(i,1,n){
        cout << dist[i]-dist[i-1] << " ";
    }
    cout << endl;

    return 0;
}