/*
SOLUTION : 2ptr
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
const int MAXN = 1000005;

int arr[MAXN];
int a[MAXN];
int l[MAXN];
int x;
int n,m;
int num0;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    FOR(i,m)cin >> a[i];
    FOR(i,m){
        cin >> x;
        l[x] = a[i];
    }
    FOR(i,n)cin >> arr[i];
    num0 = n-m;
    int rptr = 0;
    int ctr = 0;
    FOR(i,n){
        l[arr[i]]--;
        if(!l[arr[i]])num0++;

        if(l[arr[i]] < 0){
            while(rptr <= i){
                l[arr[rptr]]++;
                if(l[arr[rptr]] == 1)num0--;
                rptr++;
                if(arr[rptr-1] == arr[i]){
                    break;
                }
            }
        }
        if(num0 == n){
            ctr++;
        }
    }
    cout << ctr;
    return 0;
}



