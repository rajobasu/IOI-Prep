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
#include <stack>
#include <set>

#define FOR(i,n) for(int i=0;i<n;i++)
#define FORE(i,a,b) for(int i=a;i<=b;i++)
#define ll long long int
#define vi vector<int>
#define ii pair<int,int>
#define pb push_back
#define mp make_pair
#define vv vector
#define ff first
#define ss second
#define pll pair<ll,ll>
#define cd complex<double> 
#define ld long double
#define pld pair<ld,ld>
#define iii pair<ii,int>

using namespace std;

const int MAXN = 3000;
const int MAXK = 100+10;

int main(){
    int n,m;
    cin >> n >> m;
    vi frames;
    vv<ii> pics;
    FOR(i,n){
        int a,b;cin >> a >> b;
        pics.pb({a,b});
    }
    FOR(i,m){
        int a;cin >> a;
        frames.pb(a);
    }
    sort(pics.begin(), pics.end(),greater<ii>());
    sort(frames.begin(), frames.end(),greater<int>());
    set<ii,greater<ii> > s;
    int PTR = 0;
    FOR(i,n){
        s.insert({pics[i].ss,-i});
    }

    int ind = 0;
    int ctr = 0;
    int lst = 1e9+10;
    while(ind < n and PTR < m and !s.empty()){
        while(ind < n and pics[ind].ff > frames[PTR]){
            ii x = {pics[ind].ss,-ind};
            if(s.lower_bound(x) != s.end())s.erase(x);
            ind++;
        }
        if(ind >= n)break;
        // ======== //
        //cout << ind << " " << PTR << endl;
        while(!s.empty()){
            ii x = *s.begin();
            s.erase(s.begin());
            if(x.ff <= lst){
                lst = x.ff;
                ctr++;
                break;
            }
        }
        // ======== //
        PTR++;
    }
    cout << ctr << endl;
    return 0;
}