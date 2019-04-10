/*
SOLUTION : take out cycles whenever possible. consider only edges that needs to be flipped. 
No solution in case any node has odd degree.
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
#define mp make_pair

using namespace std;

const int MAXN = 1000005;

bool vis[MAXN];
bool vis2[MAXN];
vector<vi> allCycles;
stack<int> nodes;

bool allEdges[MAXN];
int edgePTR_CURR[MAXN];
ii edges[MAXN];

vi curr;
vector<ii> g[MAXN];

int target;
bool itsRewindTime;

void dfs(int node,int p){
    vis2[node] = 1;


    vis[node] = 1;
    nodes.push(node);
    //cout << "At NOde: "  << node << endl;

    FORE(i,edgePTR_CURR[node]+1, (int)(g[node].size())-1){
        ii child = g[node][i];

        if(child.ff == p or allEdges[child.ss] == 0)continue;
            allEdges[child.ss] = 0;
        if(vis[child.ff]){
            target = child.ff;
            itsRewindTime = true;
            curr.pb(target);
            curr.pb(node);
            if(nodes.size() == 0)while(1);
            nodes.pop();
            edgePTR_CURR[node] = i;
            vis[node] = 0;
            return;
        }else{

            dfs(child.ff,node);
            if(itsRewindTime){
                if(target == node){ // we continue in another direction next time.
                    curr.pb(nodes.top());
                    allCycles.pb(curr);
                    curr.clear();
                    itsRewindTime = false;
                }else{ // we further go behind
                    curr.pb(nodes.top());

                    vis[node] = 0;
                    if(nodes.size() == 0)while(1);
                    nodes.pop();

                    edgePTR_CURR[node] = i;
                    return;
                }
            }
        }
    }
    edgePTR_CURR[node] = (int)g[node].size();
    if(nodes.size() == 0)while(1);
    nodes.pop();
    vis[node] = 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n,m;
    cin >> n >> m;
    FOR(i,m){
        int a,b,c,d;
        cin >> a >> b >> c >> d;
        a--;b--;
        if((c^d) == 1){
            g[a].pb(mp(b,i));
            g[b].pb(mp(a,i));
            edges[i] = mp(a,b);
            allEdges[i] = 1;
        }else{
            allEdges[i] = 0;
        }
    }
    //cout << "<- REPORT -> " << endl;
    FOR(i,m){
    //    cout << edges[i].ff << " " << edges[i].ss << endl;
    }
    //cout << "NIE" << endl;
    //return 0;
    FOR(i,n){
        if((int)(g[i].size()) % 2 == 1){
            cout << "NIE" << endl;
            return 0;
        }
    }
    FOR(i,n)edgePTR_CURR[i] = -1;
    FOR(i,n){
        if(1 or edgePTR_CURR[i] < (int)(g[i].size())-1){
            //cout << "STARTING NEW DFS" << endl;
            dfs(i,-1);
        }else{
            //cout << edgePTR_CURR[i] << " " << g[i].size() << endl;
        }
    }

    cout << allCycles.size() << endl;
    for(auto cyc : allCycles){
        cout << cyc.size()-1 << " ";
        for(auto a : cyc){
            cout << a+1 << " ";
        }
        cout << endl;
    }
	return 0;
}