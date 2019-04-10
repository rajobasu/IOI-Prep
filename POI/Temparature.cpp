/*
SOLUTION : 2pointers, basically in a subsegment no upper point should be below a prev lower point
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin >> n;
    ii arr[n];
    FOR(i,n)cin >> arr[i].ff >> arr[i].ss;

  
    deque<ii> dq;
    
    int best = 0;
    int ptr2 = -1;
    FOR(i,n){
        while(!dq.empty() and dq.back().ff < arr[i].ff)dq.pop_back();
        dq.push_back({arr[i].ff,i});
        while(!dq.empty() and dq.front().ff > arr[i].ss){
            ptr2 = dq.front().ss;
            dq.pop_front();
        }
        best = max(best, i-ptr2);
    }
    cout << best << endl;

    return 0;
}