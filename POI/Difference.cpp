/*
SOLUTION : for each pair of characters, do a linear search, where ans is max subarray sum such that atleast
one -1 is included. Complexity is N*26 instead of N*26*26 due to amortizaton
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

using namespace std;

const int MAXN = 300005;

vi pos[26];
vi overall;
int getBest(int a,int b){
    overall.clear();
    {
        int p1,p2;p1=p2=0;
        while(p1 < pos[a].size() and p2 < pos[b].size()){
            if(pos[a][p1] < pos[b][p2]){
                overall.pb(-1);
                p1++;
            }else{
                overall.pb(+1);
                p2++;
            }
        }
        while(p1++ < pos[a].size())overall.pb(-1);
        while(p2++ < pos[b].size())overall.pb(+1);
    }
    // merging has been done.
    int latest = -1; // stores highest location of -1 encountered till now.
    int currsum = 0;// stores the running sum for the second ptr
    int totsum = 0;// running sum for the first pointer
    int minsum = 0;//stores the prefix min for the running sum;
    int best = 0;
    int p1 = -1;

    FOR(i,overall.size()){
      //  cout << overall[i] << " ";
        totsum += overall[i];
        if(overall[i] == 1){
        }else{
            latest = i;
        }
        while(p1 < latest-1){
            p1++;
            currsum += overall[p1];
            minsum = min(minsum,currsum);
        }
        if(latest == -1)continue;
        best = max(best,totsum - minsum);

    }
    //cout << endl;
    return best;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;cin >> n;
    string s;
    cin >> s;

    FOR(i,n){
        pos[s[i]-'a'].pb(i);
    }
    int best = 0;
    FOR(i,26){
        FOR(j,26){
            if(i == j or pos[i].size() == 0 or pos[j].size() == 0)continue;
            best = max(best,getBest(i,j));
        }
    }

    cout << best << endl;
	return 0;
}