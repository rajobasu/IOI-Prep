#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <queue>
#include <deque>
#include <iomanip>
#include <cmath>
#include <set>
#include <stack>
#include <map>
#include <unordered_map>

#define FOR(i,n) for(int i=0;i<n;i++)
#define FORE(i,a,b) for(int i=a;i<=b;i++)
#define ll long long 
//#define int long long
#define ld long double
#define vi vector<ll>
#define pb push_back
#define ff first
#define ss second
#define ii pair<int,int>
#define iii pair<int,ii>
#define il pair<ll,ll>
#define vv vector
#define endl '\n'

using namespace std;

const int MAXN = 20*100*1000+5;//0*1000+5;
const ll MOD = 1e9 + 7;


struct SegmentTree{
    il st[4*MAXN];
    SegmentTree(){
        FOR(i,4*MAXN)st[i] = {MAXN,0};
    }
    // il = pair<int,long long>
    il combine(il a,il b){
        if(a.ff < b.ff)return a;
        if(b.ff < a.ff)return b;
        else return {a.ff,(a.ss+b.ss)%MOD};
    }

    void update(int node,int ss,int se,int i,il data){
        if(i < ss or i > se)return;
        if(ss == se){
            st[node] = data;
            return;
        }
        int mid = (ss+se)/2;
        update(node*2+1,ss,mid,i,data);
        update(node*2+2,mid+1,se,i,data);

        st[node] = combine(st[node*2+1],st[node*2+2]);
        // if(st[node*2+1].ff < st[node*2+2].ff)st[node] = st[node*2+1];
        // else if(st[node*2+1].ff > st[node*2+2].ff)st[node] = st[node*2+2];
        // else st[node] = {st[node*2+1].ff,(st[node*2+1].ss + st[node*2+2].ss)%MOD};
    }

    il get(int node,int ss,int se,int l,int r){
        if(l > se or r < ss)return {MAXN,0};
        if(l <= ss and se <= r)return st[node];
        int mid = (ss+se)/2;
        return combine(get(node*2+1,ss,mid,l,r),get(node*2+2,mid+1,se,l,r));
        // if(a.ff < b.ff)return a;
        // if(a.ff > b.ff)return b;
        // return {a.ff,(a.ss+b.ss)%MOD};
    }

} segtree;


void solve(){
    int n,m;
    cin >> n >> m;
    vv<ii> all;
    FOR(i,m){   
        int a,b;
        cin >> a >> b;
        all.pb({a,b});
    }
    sort(all.begin(), all.end());
    stack<ii> st;
    FOR(i,m){
        auto e = all[i];
        while(!st.empty() and e.ss <= st.top().ff)st.pop();
        st.push({e.ss,i});
    }
    vv<ii> xx;
    while(!st.empty()){
        xx.pb(all[st.top().ss]);st.pop();
    }
    all = xx;

    // we have reduced our list to something that is usable. 

    sort(all.begin(), all.end());
    m = all.size();
    int startPos[m];
    int endPos[m];
    ll numPos[4*m];

    //deque<int> covering;
    vv<iii> events;
    FOR(i,m){
        events.pb({all[i].ff,{1,i}});
        events.pb({all[i].ss,{0,i}});
    }

    sort(events.begin(), events.end());
    int ptr = 0;
    int prev = 0;
    int ctr = 0;
    for(auto e : events){
        if(ctr == 0){
            startPos[e.ss.ss] = ptr;
            ctr++;
        }else{
            if(e.ss.ff == 0){
                ctr--;
                endPos[e.ss.ss] = ptr;
            }else{
                ctr++;
                startPos[e.ss.ss] = ptr+1;
            }
            numPos[ptr] = e.ff - prev; 
            ptr++;
        }
        prev = e.ff;
    }
    vv<ii> startpoints;
    FOR(i,m)startpoints.push_back({startPos[i],i});
    sort(startpoints.begin(), startpoints.end());


    pair<ll,ll> dp[ptr];// .ff = dp[i], .ss = dp2[i]
    ll suffixSum[ptr];
    int mins[ptr];
    FOR(i,ptr)mins[i] = ptr+1;
    FOR(i,ptr)suffixSum[i] = 0;
    for(int i = ptr-1;i>=0;i--){
        int nextSegment = -1;
        auto it = lower_bound(startpoints.begin(), startpoints.end(),make_pair(i+1,-2));
        if(it != startpoints.end()){
            nextSegment = (*it).ss;
        }

        if(nextSegment == -1){
            dp[i] = {1,numPos[i]};
        }else{
            /*
            ll sum = 0;
            int mn = m+1;
            FORE(j,startPos[nextSegment],endPos[nextSegment]){
                if(dp[j].ss < mn){
                    mn = dp[j].ss;
                    sum = dp[j].ff;
                }else if(dp[j].ss == mn){
                    sum += dp[j].ff;
                    sum %= MOD;
                }
            }*/
            int mn = dp[endPos[nextSegment]].ff;
            int st = lower_bound(mins,mins+ptr,mn,greater<int>()) - mins;
            //cout << "DP: " << mn << " " << dp[st].ff << endl;
            //auto e = segtree.get(0,0,MAXN,startPos[nextSegment],endPos[nextSegment]);
            ll e = suffixSum[st];
            if(endPos[nextSegment]<ptr-1)e -= suffixSum[endPos[nextSegment]+1];
            e += MOD;
            e %= MOD;
            dp[i] = {1+mn,(numPos[i]*e)%MOD};

        }
        //cout << i << " " << dp[i].ff << " " << dp[i].ss << endl;
        //segtree.update(0,0,MAXN,i,dp[i]);
        suffixSum[i] = (dp[i].ss + (i<ptr-1?suffixSum[i+1]:0))%MOD;
        mins[i] = dp[i].ff;
    }
    /*
    ll sum = 0;
    int mn = m+1;
    FORE(j,startPos[0],endPos[0]){
        if(dp[j].ss < mn){
            mn = dp[j].ss;
            sum = dp[j].ff;
        }else if(dp[j].ss == mn){
            sum += dp[j].ff;
            sum %= MOD;
        }
    }*/
    //auto e = segtree.get(0,0,MAXN,startPos[0],endPos[0]);
    //FOR(i,ptr)cout << dp[i].ff << " ";cout << endl;
    //FOR(i,ptr)cout << dp[i].ss << " ";cout << endl;

    int mn = dp[endPos[0]].ff;
    int stt = lower_bound(mins,mins+ptr,mn,greater<int>()) - mins;
            
    ll e = suffixSum[stt] - (endPos[0]+1>= ptr?0:suffixSum[endPos[0]+1]);
    e += MOD;
    e %= MOD;
    cout << mn << " " << e << endl;


}



int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}