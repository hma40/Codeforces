#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define add push_back 
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define f first
#define s second
#define trav(a,x) for (auto& a: x)
#define int long long
#define vt vector
#define endl "\n"
ll mod = 998244353;
ll inf = 1e18;
template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}
template<typename T> std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
    os << "[ ";
    for(const auto& elem : vec) {
        os << elem << " ";
    }
    os << "]";
    return os;
}
template<typename T> std::ostream& operator<<(std::ostream& os, const std::set<T>& s) {
    os << "{ ";
    for(const auto& elem : s) {
        os << elem << " ";
    }
    os << "}";
    return os;
}
template<typename T> std::ostream& operator<<(std::ostream& os, const std::multiset<T>& s) {
    os << "{ ";
    for(const auto& elem : s) {
        os << elem << " ";
    }
    os << "}";
    return os;
}
template<typename K, typename V> std::ostream& operator<<(std::ostream& os, const std::map<K, V>& m) {
    os << "{ ";
    for(const auto& pair : m) {
        os << pair.first << " : " << pair.second << ", ";
    }
    os << "}";
    return os;
}
struct RMQ {
    vt<vt<int>> sparse;
    vt<int> lg;
    RMQ(vt<int> v, int log) {
        lg.resize(v.size()+5);
        FOR(i, 2, lg.size()) {
            lg[i]=lg[i/2]+1;
        }
        sparse.resize(v.size(), vt<int>(log, -1));
        F0R(i, v.size()) {
            sparse[i][0]=v[i];
        }
        FOR(i, 1, log) {
            F0R(j, (int)v.size()-(1LL<<i)+1) {
                // cout << (int)v.size()-(1LL<<i)+1 << endl;
                cout << i << " " << j << endl;
                sparse[j][i]=min(sparse[j][i-1], sparse[j+(1<<(i-1))][i-1]);
            }
        }
    }
    int getMin(int lo, int hi) {
        int log = lg[hi-lo+1];
        return min(sparse[lo][log], sparse[hi-(1<<log)+1][log]);
    }
};
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int n,q;
    cin >> n >> q;
    int ans = 1;
    set<int> notSeen;
    set<int> seen;
    F0R(i, n) notSeen.insert(i);
    vt<pair<int,int>> constraints(q);
    F0R(i, q) {
        cin >> constraints[i].f;
    }
    F0R(i, q) cin >> constraints[i].s;
    F0R(i, q) {
        constraints[i].f--;
        constraints[i].s--;
        notSeen.erase(constraints[i].f);
        notSeen.erase(constraints[i].s);
    }
    cout << constraints << endl;
    vt<int> lastSeen(n, -1), par(q, -1), which(q, 0);
    lastSeen[constraints[0].f]=lastSeen[constraints[0].s]=0;
    vt<vt<int>> child(q);
    FOR(i, 1, q) {
        if(lastSeen[constraints[i].f]==-1) {
            par[i]=lastSeen[constraints[i].s];
            which[i]=1;
            child[]
        } else {
            par[i]=lastSeen[constraints[i].f];
        }
        lastSeen[constraints[i].f]=lastSeen[constraints[i].s]=i;
    }
    cout << par << lastSeen << endl;
    return 0;
}
/*   
  
  
     ?
    / \
    6 5
   /\ /\
   6 15 4



6 5 6  
5 4 1
*/