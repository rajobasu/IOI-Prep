/*
SOLUTION : Do a binsrch on number of workers. Now try assigning. note that in subtrees, we might have some 
deficit of workers, which we try to fill in beforehand. This can be handled by a dp.
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
#define ii pair<ll,int>
#define ll long long int
#define piil pair<pair<int,int>,ll> 
#define iii pair<pair<int,int>,int> 
#define vi vector<int>
#define pb push_back
#define mp make_pair

using namespace std;

const int MAXK = 51;
const int MAXN = 300005;


vi g[MAXN];

int dfs(int node,int p,int ANS){   
    int vals = 0;
    for(auto a:g[node]){
        if(a != p)
          vals += dfs(a,node,ANS) + 1;
    }
    return max(0,vals-ANS);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    if(n == 1){
        cout << 0 << endl;
        return 0;
    }
    FOR(i,n-1){
        int a,b;
        cin >> a >> b;
        a--;b--;
        g[a].pb(b);
        g[b].pb(a);
    }
    int lo = 0;int hi = n;
    int best = n;
    while(lo <= hi){
        bool b = lo == hi;
        int mid = (lo+hi)/2;
        if(dfs(0,-1,mid) == 0){
            best = min(best, mid);
            hi = mid-1;
        }else{
            lo = mid+1;
        }
        if(b)break;
    }
    cout << max(1,best) << endl;

    return 0;
}



