#include <bits/stdc++.h>
using namespace std;

#define FOR(i,n) for(int i=0;i<n;i++)
int main() {
    int n,k;
    cin >> n >> k;
    int arr[n];
    FOR(i,n)cin >> arr[i];
    int ss = 0;
    FOR(i,n)ss += arr[i];
    int lo = 1,hi = ss;
    int best = ss;
    while(lo <= hi){
        
        int mid = (lo+hi)/2;
        int ctr = 1;
        int sum = 0;
        FOR(i,n){
            sum += arr[i];
            if(sum > mid){
                sum = arr[i];
                ctr++;
            }
        }
        if(ctr <= k){
            best = min(best, mid);
            hi = mid-1;
        }else{
            lo = mid+1;
        }
        //if(lo == hi)break;
    }
    cout << best << endl;
}