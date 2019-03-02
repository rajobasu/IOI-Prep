/*
SOLUTION: modified floyd warshall. code is self explainatory
COMPLEXITY: n^3
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

#define FOR(i,n) for(int i=0;i<n;i++)
#define FORE(i,a,b) for(int i=a;i<=b;i++)
#define ll long long int
#define vi vector<int>
#define ii pair<int,int>
#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define pll pair<ll,ll>
#define ld long double
#define pil pair<ll,int>

using namespace std;

const int MOD = 1000000007;
const ll INF = 1000000000000000;
const int MAXN = 101;

ll matrix[MAXN][MAXN];
ll dist[MAXN][MAXN];
ll numpaths[MAXN][MAXN];

inline void compute(int n){
    
    FOR(i,n)FOR(j,n)numpaths[i][j] = 1*(dist[i][j] != INF);
    FOR(k,n){
        FOR(i,n){
            FOR(j,n){
                if(i == j)continue;
                if(i == k or j == k)continue;
                if(dist[i][k] + dist[k][j] < dist[i][j]){
                    dist[i][j] = dist[i][k] + dist[k][j];
                    numpaths[i][j] = numpaths[i][k]*numpaths[k][j];
                }else if(dist[i][k] + dist[k][j] == dist[i][j]){
                    numpaths[i][j] += numpaths[i][k]*numpaths[k][j];
                }
            }
        }
    }
   
}



int main(){
    int n,m;
    cin >> n >> m;
    FOR(i,n)FOR(j,n)matrix[i][j] = -1;
    FOR(i,m){
        int a,b,c;cin >> a >> b >> c;a--;b--;
        matrix[a][b] = c;
        matrix[b][a] = c;
    }
    //FOR(i,n)matrix[i][i] = 0;
    FOR(j,n)FOR(k,n)numpaths[j][k] = 0;
        
    FOR(i,n){
        FOR(j,n){
            if(matrix[i][j] == -1){
                dist[i][j] = INF;
            }else {
                dist[i][j] = matrix[i][j];
            }
        }
    }
    compute(n);
   
    FOR(i,n){
        // for each vertex
        long double ans = 0;
        FOR(s,n){
            FOR(t,n){
                if(s == i or t == i or s == t)continue;
                ll pathsPasssing = 0;
                
                if(dist[s][t] == dist[s][i] + dist[i][t]){
                    pathsPasssing = numpaths[s][i]*numpaths[i][t];
                }
                ans += (pathsPasssing*1.0) / numpaths[s][t];
            }
        }
        cout << setprecision(4) << ans << endl;
    }

    return 0;
}
