/*
SOLUTION: we root at each node. Now, we try to match things on same level so that they are in 
different subtrees of the children of roots. 
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <queue>
#include <deque>
#include <iomanip>
#include <list>
#include <cmath>
#include <set>
#include <stack>
#include <map>
#include <unordered_map>

#define FOR(i,n) for(int i=0;i<n;i++)
#define FORE(i,a,b) for(int i=a;i<=b;i++)
#define ll long long 
//#define int long long
#define ld long double
#define vi vector<ll>
#define pb push_back
#define ff first
#define ss second
#define ii pair<int,int>
#define iii pair<int,ii>
#define il pair<ll,ll>
#define vv vector
#define endl '\n'

using namespace std;

const int MAXN = 5001;
int n;
vi g[MAXN];
int depth[MAXN];
ll atDepth[MAXN];

ll atDepthSum[MAXN]; // sum of all nodes under all subtrees processed till now
ll atDepthSquare[MAXN]; // sum of A*B that are possible so that A and B belong to different child-subtrees 
ll ans = 0;
void dfs(int node,int p = -1){
    if(p == -1)depth[node] = 0;else depth[node] = depth[p]+1;
    atDepth[depth[node]]++;
    for(auto e : g[node]){
        if(e == p)continue;
        dfs(e,node);
        if(p == -1){

            FOR(i,n){
                ans += atDepth[i]*atDepthSquare[i];
                atDepthSquare[i] += atDepth[i]*atDepthSum[i];
                atDepthSum[i] += atDepth[i];
                atDepth[i] = 0;
            }

        }
    }
}


void count(){
    FOR(i,n){
        ll k = atDepth[i];
        ans += k*(k-1)*(k-2)/6;
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    //int n;
    cin >> n;
    FOR(i,n-1){
        int a,b;
        cin >> a >> b;
        a--;b--;
        g[a].pb(b);
        g[b].pb(a);
    }  
    FOR(i,n){
        FOR(j,n)atDepth[j] = atDepthSum[j] = atDepthSquare[j] = 0;
        dfs(i);
        //count();
       // cout << ans << endl;
    }
    cout << ans << endl;
    // divided into components;
    return 0;

}