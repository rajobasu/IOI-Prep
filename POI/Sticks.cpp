/*
SOLUTION : maintain the previous closest elements of each stick, 
and then choose the min and second min of different colors.
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

const int MAXK = 51;
const int MAXN = 1000005;

int best[MAXK];

int main(){
    int k;
    cin >> k;
    vi all[k];
    vector<ii> overall;
    FOR(i,k){
        int n;
        cin >> n;
        FOR(j,n){
            int a;
            cin >> a;
            overall.pb({a,i});
      //      all[i].pb(a);
        }
    }
    //FOR(i,k)sort(all[i].begin(), all[i].end());
    sort(overall.begin(), overall.end());
    // preprocessing done.
    int ptra[k];
    FOR(i,k)best[i] = -1;
    FOR(i,overall.size()){
        ii ele = overall[i];
        int maxi,max2i;maxi = max2i = -1;
        FOR(j,k){
            if(j == ele.ss){
                continue;
            }else{
                if(best[j] > maxi){
                    max2i = maxi;
                    maxi = best[j];
                }else if(best[j] > max2i){
                    max2i = best[j];
                }
            }
        }
        if(maxi != -1 and max2i != -1 and overall[maxi].ff + overall[max2i].ff > ele.ff){
            cout << overall[maxi].ss+1 << " " << overall[maxi].ff << " " <<  overall[max2i].ss+1 << " " << overall[max2i].ff << " "<< overall[i].ss+1 << " " << overall[i].ff << endl;
            return 0;
        }else{
            best[ele.ss] = i;
        }

    }
    cout << "NIE" << endl;
    return 0;
}