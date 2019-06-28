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
#include <unordered_map>
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
#define ss second
#define pll pair<ll,ll>
#define cd complex<double> 
#define ld long double
#define pld pair<ld,ld>
#define iii pair<ii,int>
#define vv vector

using namespace std;

vi lst;
set<int> res;
void ans(int n,int x,int sum){

    if(n == 1)res.insert(sum);
    else{
        for(int i = x;i < lst.size();i++){
            if(lst[i]*2 > n)break;
            if(n%lst[i] == 0){
                ans(n/lst[i],i,sum + lst[i]-1);
            }
        }
        ans(1,0,sum + n -1);
    }
}
#define endl '\n'
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    //cout.tie(0);
    int n;
    cin >> n;
    set<int> st;
    int xx = (int)sqrt(n);
    FORE(i,1,xx){
        if(i*i > n)break;
        if(n%i == 0){
            st.insert(i);
            if(i*i != n)st.insert(n/i);
        }
    }   
    for(auto e : st){
        if(e > 1)lst.pb(e);
    }
    ans(n,0,0);
    cout << res.size() << endl;
    for(auto e : res){
        cout << e << " ";
    }
    cout << endl;

    return 0;
}