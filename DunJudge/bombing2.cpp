/*
SOLUTION : articulation points.
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
#define ii pair<int,int>
#define ll long long int
#define piil pair<pair<int,int>,ll> 
#define iii pair<pair<int,int>,int> 
#define vi vector<int>
#define pb push_back

using namespace std;

const int MAXN = 200000;

vi g[MAXN];
int dfslow[MAXN];
int score[MAXN];
int vis[MAXN];
int depth[MAXN];
void dfs(int node,int p){
    depth[node] = ((p==-1)?0:(depth[p]+1));
    vis[node] = 1;
    vi lows;
    dfslow[node] = depth[node];
    for(auto child:g[node]){
        if(vis[child]){
            if(child == p)continue;
            dfslow[node] = min(dfslow[node],depth[child]);
        }else{
            dfs(child,node);
            lows.pb(dfslow[child]);
        }
    }
    for(auto val : lows){
        if(val >= depth[node])score[node]++;
        dfslow[node] = min(val,dfslow[node]);
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n,m;
    cin >> n >> m;
    FOR(i,m){
    	int a,b;
    	cin >> a >> b;
    	g[a].pb(b);
    	g[b].pb(a);
    }

    dfs(0,-1);
    int mx = 1;
    FOR(i,n){
    	//if(isArt[i]){
    	//	cout << "all : " << i  << endl;
    	//	mx = max(starting[i]+1,mx);
    	//}
        if(i == 0){
            mx = max(mx,score[i]);
        }else{
            mx = max(mx,score[i] + 1);
        }
    }
    cout << mx << endl;
	return 0;
}