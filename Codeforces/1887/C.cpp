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
        q.pop();
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
__int128_t mod = (1LL<<61)-1;
vt<__int128_t> pw;
int sd = 0;
void initialize() {
    sd = rnd()%mod;
    pw.add(1);
    F0R(i, 500050) {
        pw.add(pw.back()*sd%mod);
    }
}
struct SegTree {
    int n;
    vt<__int128_t> tree;
    SegTree(int nn) {
        int np = 1;
        while(np<nn) np*=2;
        tree.resize(2*np);
        n=np;
    }
    void set(int pos, __int128_t x) {
        pos+=n;
        tree[pos]=x;
        for(pos/=2; pos; pos/=2) {
            //CHANGE HERE
            tree[pos]=(tree[2*pos]+tree[2*pos+1])%mod;
        }
    }
    void setPos(int pos, int x) {
        __int128_t setTo = x;
        setTo*=pw[pos];
        setTo%=mod;
        setTo+=mod;
        setTo%=mod;
        set(pos, setTo);
    }
    int rangeQuery(int a, int b) {
        a+=n;
        __int128_t ans = 0;
        b+=n;
        while(a<=b) {
            if(a%2==1) ans+=tree[a++];
            if(b%2==0) ans+=tree[b--];
            a/=2;
            b/=2;
            ans%=mod;
        }
        return ans;
    }
};
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    initialize();
    int t = 1;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vt<int> a(n);
        F0R(i, n) cin >> a[i];
        vt<int> diff(n+1);
        diff[0]=a[0];
        FOR(i, 1, n) diff[i]=a[i]-a[i-1];
        SegTree before(n+1), here(1+n);
        F0R(i, n) {
            before.setPos(i, diff[i]);
            here.setPos(i, diff[i]);
        }
        vt<int> curDiff = diff;
        int q;
        cin >> q;
        vt<pair<int,int>> cumQueries;
        while(q--) {
            int l,r,x;
            cin >> l >> r >> x;
            l--;
            curDiff[l]+=x;
            curDiff[r]-=x;
            cumQueries.add({l,x});
            cumQueries.add({r, -x});
            here.setPos(l, curDiff[l]);
            here.setPos(r, curDiff[r]);
            // cout << q << diff << curDiff << cumQueries << endl;
            // cout << before.tree << here.tree << endl;
            if(before.tree[1]==here.tree[1]) continue;
            int treeInd = 1;
            while(treeInd<before.n) {
                // cout << treeInd << endl;
                if(before.tree[2*treeInd]==here.tree[2*treeInd]) {
                    treeInd=treeInd*2+1;
                } else {
                    treeInd=treeInd*2;
                }
            }
            treeInd-=before.n;
            // cout << treeInd << endl;
            if(diff[treeInd]>curDiff[treeInd]) {
                //new smallest array
                while(cumQueries.size()) {
                    diff[cumQueries.back().f]+=cumQueries.back().s;
                    before.setPos(cumQueries.back().f, diff[cumQueries.back().f]);
                    cumQueries.pop_back();
                }
            }
        }
        // cout << diff << endl;
        FOR(i, 1, n+1) diff[i]+=diff[i-1];
        F0R(i, n) cout << diff[i] << " ";
        cout << endl;
    }
    return 0;
}