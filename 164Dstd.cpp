#include <bits/stdc++.h>
using namespace std;
 
#define REP(i,n) for((i)=0;(i)<(int)(n);(i)++)
#define snuke(c,itr) for(__typeof((c).begin()) itr=(c).begin();itr!=(c).end();itr++)
 
int N;
int x[1010],y[1010],dist[1010][1010];
bool graph[1010][1010];
int deg[1010];
bool used[1010];
bool ans[1010];
 
void use(int x){
    int i;
	cerr << "RM " << x << endl;
    used[x] = true;
    REP(i,N) if(graph[x][i]){
        deg[x]--;
        deg[i]--;
    }
}
 
void unuse(int x){
    int i;
    used[x] = false;
cerr << "RECOVER " << x << endl;
    REP(i,N) if(graph[x][i]){
        deg[x]++;
        deg[i]++;
    }
}
 
bool dfs(int K){
    int x=-1,leaf=-1,maxdeg=0,i;
    
    REP(i,N) if(!used[i] && deg[i] == 1){
        leaf = i;
        break;
    }
    
    if(leaf != -1){
        REP(i,N) if(!used[i] && graph[leaf][i]) break;
        use(i);
        if(K > 0 && dfs(K-1)) return true;
        unuse(i);
        return false;
    }
    
    REP(i,N) if(!used[i] && deg[i] > maxdeg){
        maxdeg = deg[i];
        x = i;
    }
    
    if(maxdeg == 0) return true;
    if(K == 0) return false;
    
    use(x);
    if(dfs(K-1)) return true;
    unuse(x);
    
    if(maxdeg > 1 && maxdeg <= K){
        vector <int> v;
        REP(i,N) if(!used[i] && graph[x][i]) v.push_back(i);
        REP(i,v.size()) use(v[i]);
        if(dfs(K - maxdeg)) return true;
        REP(i,v.size()) unuse(v[i]);
    }
    
    return false;
}
 
bool func(int maxdist, int K){
    int i,j;
    
    REP(i,N) REP(j,N) graph[i][j] = (dist[i][j] > maxdist);
    REP(i,N) deg[i] = 0;
    REP(i,N) REP(j,N) if(graph[i][j]) deg[i]++;
    REP(i,N) used[i] = false;
    
    return dfs(K);
}
 
int main(void){
    int K,i,j;
    
    cin >> N >> K;
    REP(i,N) cin >> x[i] >> y[i];
    REP(i,N) REP(j,N) dist[i][j] = (x[i]-x[j]) * (x[i]-x[j]) + (y[i]-y[j]) * (y[i]-y[j]);
    
    int low = -1, high = 2100000000;
    while(high-low > 1){
        int mid = (low + high) / 2;
        if(func(mid, K)){
            REP(i,N) ans[i] = used[i];
            high = mid;
        } else {
            low = mid;
        }
    }
    
    int cnt = K;
    REP(i,N) if(ans[i]) cnt--;
    REP(i,N) if(cnt > 0 && !ans[i]){
        ans[i] = true;
        cnt--;
    }
    
    bool first = true;
    REP(i,N) if(ans[i]){
        if(!first) cout << ' ';
        first = false;
        cout << i+1;
    }
    cout << endl;
    
    return 0;
}
