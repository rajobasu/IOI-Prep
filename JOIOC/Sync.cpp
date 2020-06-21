/*
Solution: Firstly, we identify a component by its LCA. Now, when we connect a child and parent, we are "attaching" the child to the parent's component, and to its LCA we add the amount of contribution this child added. We also make sure that we dont add the same stuff again and again while we are toggling edges, so we keep track of the lastAdded value,and only add the excess value. 

*/

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
#define pll pair<ll,ll>
#define il pair<ll,ll>
#define vv vector
#define endl '\n'

using namespace std;

const int MAXN = 1e5+5;

int n,m,q;
int tin[MAXN];
int tout[MAXN];
int sparseTable[MAXN][20];

int side1[MAXN];
int side2[MAXN];

vi g[MAXN];

int T = 0;
void dfs(int x,int p = -1){
    tin[x] = ++T;
    sparseTable[x][0]=p;
    // sparseTable
    for(int i=1;i<17;i++)
        sparseTable[x][i] = sparseTable[sparseTable[x][i-1]][i-1];
    //
    for(auto e: g[x])
        if(e != p)
            dfs(e,x);

    tout[x] = T;
}

int BIT[MAXN];
void update(int i,int v){
    for(;i<=n;i+=i&(-i))BIT[i]+=v;
}
int query(int i){
    int ans=0;
    for(;i>=1;i-=i&(-i))ans+=BIT[i];
    return ans;
}
int findRoot(int x){
    int cur=query(tin[x]);
    for(int i=16;i>=0;i--)if(query(tin[sparseTable[x][i]])==cur)x=sparseTable[x][i];
    return x;
}


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m >> q;
    ii all[n-1];
    FORE(i,1,n-1){
        int x,y;
        cin >> x >> y;
        all[i] = {x,y};
        g[x].pb(y);
        g[y].pb(x);
    }
    dfs(1);

    FORE(i,1,n){
        update(tin[i],1);
        update(tout[i]+1,-1);
        side1[i]=1;
    }
    FORE(i,1,n-1)
        if(tin[all[i].ff]>tin[all[i].ss])
            swap(all[i].ff,all[i].ss);

    while(m--){
        int edge;
        cin >> edge;
        int x=all[edge].ff;
        int y=all[edge].ss;
        int z=findRoot(x);
        if(side2[edge]==-1){
            update(tin[y],1);
            update(tout[y]+1,-1);
            side2[edge]=side1[y]=side1[z];
        }
        else{
            update(tin[y],-1);
            update(tout[y]+1,1);
            side1[z]+=side1[y]-side2[edge];
            side2[edge]=-1;
        }
    }
    while(q--){
        int x;
        cin >> x;
        cout << side1[findRoot(x)] << endl;
    }
    return 0;
}