#include <bits/stdc++.h>
std::string to_string(__int128_t value) {
    if (value == 0) return "0";
    
    std::string result;
    bool negative = (value < 0);
    if (negative) value = -value;
    
    while (value > 0) {
        result += '0' + (value % 10);
        value /= 10;
    }
    
    if (negative) result += '-';
    
    std::reverse(result.begin(), result.end());
    return result;
}

// Overload << operator for __int128
std::ostream& operator<<(std::ostream& os, __int128_t value) {
    return os << to_string(value);
}
template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}
template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
    os << "[";
    for (std::size_t i = 0; i < N; ++i) {
        os << arr[i];
        if (i < N - 1) {
            os << ", ";
        }
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

template<typename T> std::ostream& operator<<(std::ostream& os, std::queue<T> q) {
    // Print each element in the queue
    os << "{ ";
    while (!q.empty()) {
        os << q.front() << " ";
        q.pop();
    }
    os << "}";
    // Print a newline at the end
    return os;
}
template<typename T> std::ostream& operator<<(std::ostream& os, std::deque<T> q) {
    // Print each element in the queue
    os << "{ ";
    while (!q.empty()) {
        os << q.front() << " ";
        q.pop_front();
    }
    os << "}";
    // Print a newline at the end
    return os;
}
template<typename T> std::ostream& operator<<(std::ostream& os, std::stack<T> q) {
    // Print each element in the queue
    os << "{ ";
    while (!q.empty()) {
        os << q.top() << " ";
        q.pop();
    }
    os << "}";
    // Print a newline at the end
    return os;
}
template<typename T> std::ostream& operator<<(std::ostream& os, std::priority_queue<T> q) {
    // Print each element in the queue
    os << "{ ";
    while (!q.empty()) {
        os << q.top() << " ";
        q.pop();
    }
    os << "}";
    // Print a newline at the end
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
template<typename K, typename V> std::ostream& operator<<(std::ostream& os, const std::map<K, V>& m) {
    os << "{ ";
    for(const auto& pair : m) {
        os << pair.first << " : " << pair.second << ", ";
    }
    os << "}";
    return os;
}
template<typename T>
using min_pq = std::priority_queue<T, std::vector<T>, std::greater<T>>;
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
#define double long double
ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
typedef unsigned long long ull;
typedef __uint128_t L;
ll mod = 1000000007;
struct FastMod {
	ull b, m;
	FastMod(ull bb) : b(bb), m(ull((L(1) << 64) / b)) {}
	ull reduce(ull a) {
		ull q = (ull)((L(m) * a) >> 64);
		ull r = a - q * b; // can be proven that 0 <= r < 2*b
		return r >= b ? r - b : r;
	}
};
struct DSU {
    int n;
    vector<int> sz, par, beg, end;
    vt<bool> odd,even;
    DSU(int nn) {
        n=nn;
        sz.resize(n,1);
        par.resize(n,-1);
        beg.resize(n);
        end.resize(n);
        F0R(i, n) beg[i]=end[i]=i;
        odd.resize(n);
        even.resize(n);
    }
    int find(int x) {
        if(par[x]==-1) return x;
        return par[x]=find(par[x]);
    }
    void unite(int x, int y) {
        x=find(x);
        y=find(y);
        if(sz[x]>sz[y]) swap(x,y);
        //put x as child of y
        sz[y]+=sz[x];
        par[x]=y;
        beg[y]=min(beg[y], beg[x]);
        end[y]=max(end[y], end[x]);
        odd[y]=odd[y]||odd[x];
        even[y]=even[y]||even[x];
    }
};
FastMod fs(mod);
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t = 1;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        DSU dsu(n);
        vt<int> a(n);
        F0R(i, n) cin >> a[i];
        int mx = 0;
        F0R(i, n) mx=max(mx,a[i]);
        F0R(i, n) {
            if(a[i]==mx) {
                if(i%2) {
                    dsu.odd[i]=true;
                } else {
                    dsu.even[i]=true;
                }
            }
        }
        set<int> active;
        priority_queue<pair<int,int>> pq;
        F0R(i, n) pq.push({a[i], i});
        int sz = 0;
        set<int> maxCont;
        int ans = 0;
        int min = 0;
        while(pq.size()) {
            auto f = pq.top();
            pq.pop();
            min = f.f;
            active.insert(f.s);
            if(active.count(f.s-1)) {
                int find = dsu.find(f.s-1);
                int size = dsu.end[find]-dsu.beg[find]+1;
                sz-=(size+1)/2;
                maxCont.erase(find);
                dsu.unite(f.s, f.s-1);
            }
            if(active.count(f.s+1)) {
                int find = dsu.find(f.s+1);
                int size = dsu.end[find]-dsu.beg[find]+1;
                sz-=(size+1)/2;
                maxCont.erase(find);
                dsu.unite(f.s, f.s+1);
            }
            int find = dsu.find(f.s);
            if(dsu.beg[find]%2!=dsu.end[find]%2) {
                if(dsu.odd[find]||dsu.even[find]) {
                    maxCont.insert(find);
                }
            } else if(dsu.beg[find]%2) {
                if(dsu.odd[find]) {
                    maxCont.insert(find);
                }
            } else {
                if(dsu.even[find]) {
                    maxCont.insert(find);
                }
            }
            int size = dsu.end[find]-dsu.beg[find]+1;
            sz+=(size+1)/2;
            if(maxCont.size()) {
                ans=max(ans, sz+mx+min);
            } else {
                ans=max(ans, sz+mx+min-1);
            }
        }
        cout << ans << endl;
    }
    return 0;
}
/*
Loop through min
to maximize answer, greedily take leftmost possible

*/