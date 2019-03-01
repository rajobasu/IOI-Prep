/**
SOLUTION: Modified Kruskals
COMPLEXITY: O(nlogn)
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

using namespace std;

const int MOD = 1000000007;
const ll INF = 1000000000000000000;
const int MAXN = 100001;
const int MAXX = 1000002;

int main(){
    ifstream fin;
    ofstream fout;
    #define cin fin
    #define cout fout
    fin.open("fencedin.in");
    fout.open("fencedin.out");

    int A,B,n,m;
    cin >> A >> B >> n >> m;
    int arr1[n];
    int arr2[m];
    FOR(i,n)cin >> arr1[i];
    FOR(i,m)cin >> arr2[i];
    vector<ii> all;
    int prev = 0;
    sort(arr1,arr1+n);
    sort(arr2,arr2+m);

/*
    for(auto el:arr1)cout << el << " ";
        cout << endl;
    for(auto el:arr2)cout << el << " ";
        cout << endl;
*/

    FOR(i,n){
        all.pb({arr1[i] - prev ,0});
        prev = arr1[i];
    }
    all.pb({A-prev,0});


    prev = 0;
    FOR(i,m){
        all.pb({arr2[i] - prev ,1});
        prev = arr2[i];
    }
    all.pb({B-prev,1});


    sort(all.begin(), all.end());
    int R = m,C = n;
    ll cost = 0;
    int gotC = 0,gotR = 0;
    FOR(i,all.size()){
        ll val = all[i].ff;
        //cout << val << endl;
        if(gotC*gotR == (C+1)*(R+1))break;
        if(all[i].ss == 0 ){
            //gotC += 1;
            int cnt = R;
            if(gotC > 0){
                cnt -= max(0,gotR-1);
            }
            cost += cnt*val;
            gotC++;
        }else{
            int cnt = C;
            if(gotR > 0){
                cnt -= max(0,gotC-1);
            }
            cost += cnt*val;
            gotR++;
        }
    }
    cout << cost << endl;

    return 0;
}
