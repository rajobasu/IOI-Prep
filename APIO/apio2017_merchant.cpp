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

const ld INF = 1e18;
const int MAXN = 100 + 10;
const int MAXK = 1000 + 10;

vv<ll> B[MAXN];
vv<ll> S[MAXN];

ll mat[MAXN][MAXN];
ll dist1[MAXN][MAXN];
ll profit[MAXN][MAXN];




int n,m,k;

void precomp(){
    FOR(i,n)FOR(j,n)dist1[i][j] = mat[i][j];

    FOR(conn,n){
        FOR(i,n){
            FOR(j,n){
                if(dist1[i][conn] + dist1[conn][j] < dist1[i][j]){
                    dist1[i][j] = dist1[i][conn] + dist1[conn][j];
                }
            }
        }
    }
    FOR(i,n){
        FOR(j,n){
            FOR(item,k){
                if(B[i][item] == -1 or S[j][item] == -1)continue;
                profit[i][j] = max(profit[i][j] , S[j][item] - B[i][item]);
            }
        }
    }
}


ld route[MAXN][MAXN];

bool isPoss(ld x){

    FOR(i,n){
        FOR(j,n){
            if(i == j) route[i][j] = -INF;
            else route[i][j] = profit[i][j] - x*dist1[i][j];
        }
    }
    FOR(conn,n){
        FOR(i,n){
            FOR(j,n){
                if(route[i][conn] + route[conn][j] > route[i][j]){
                    route[i][j] = route[i][conn] + route[conn][j];
                }
            }
        }
    }
    FOR(i,n)if(route[i][i] >= 0)return 1;
    return 0;
}

int main(){
    
    cin >> n >> m >> k;
    FOR(i,n){
        FOR(j,k){
            int a,b;
            cin >> a >> b;
            B[i].pb(a);
            S[i].pb(b);
        }
    }
    FOR(i,n)FOR(j,n)mat[i][j] = INF;
    FOR(i,m){
        int a,b,c;
        cin >> a >> b >> c;
        a--;b--;
        mat[a][b] = c;
    }
    precomp();
    //cout << isPoss(2) << endl;
    FOR(i,n){
        FOR(j,n){
            //cout << dist1[i][j] << " ";
        }
        //cout << endl;
    }
    ld lo = 0;
    ld hi = INF;
    ld eps = 0.0001;
    ld best = 0;
    while(hi-lo > eps){
        ld mid = (hi + lo)/2;
        //cout << setprecision(10) << hi << " " << mid << " " << lo << endl;
        if(isPoss(mid)){
            best = max(best,mid);
            lo = mid;
        }else{
            hi = mid;
        }
    }
    if(isPoss((ll)hi))best = max(best,(ld)((ll)hi));
    cout << (ll)best << endl;

    return 0;
}