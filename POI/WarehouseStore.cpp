/*
SOLUTION : when deleting an item is inevitable, delete the maximum existing item in that prefix.
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
const int MAXN = 250005;


int main(){
    int n;
    cin >> n;
    ll a[n];
    ll b[n];
    FOR(i,n)cin >> a[i];
    FOR(i,n)cin >> b[i];

    set<ii> s;
    ll sum = 0;

    FOR(i,n){
        sum += a[i];
        if(sum >= b[i]){
            sum -= b[i];
            s.insert({-b[i],i});
        }else{
            if(s.empty())continue;
            ii x = *s.begin();
            if(-x.ff > b[i]){
                s.erase(s.begin());
                sum += -x.ff;
                s.insert({-b[i],i});
                sum -= b[i];
            }
        }
    }
    
    vi all;
    for(auto a:s){
        all.pb(a.ss+1);
    }
    sort(all.begin(), all.end());
    cout << all.size() << endl;
    for(auto a: all){
        cout << a << " ";
    }
    cout << endl;

    return 0;
}



