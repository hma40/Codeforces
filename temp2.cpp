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
ll mod = 1000000007;
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
struct TestCase {
    int n,k;
    string s;
};
void print_TC(TestCase tc) {
    cout << tc.n << " " << tc.k << endl << tc.s << endl;
}
TestCase randTC() {
    TestCase t;
    t.n=6;
    vt<int> factors;
    FOR(i, 1, t.n+1) {
        if(t.n%i==0) factors.add(i);
    }
    t.k = factors[rand()%factors.size()];
    F0R(i, t.n) {
        t.s+='0'+rand()%2;
    }
    return t;
}
struct WrongSol {
    int solve(TestCase tc) {
        int n = tc.n, k = tc.k;
        string s = tc.s;
        int count = 0;
        R0F(i, n) {
            if(s[i]==s[n-1]) count++;
            else break;
        }
        // cout << s << " " << count << endl;
        if(count>k) {
            return -1;
        } else if(count==k) {
            //whole string must be ok
            count = 0;
            bool bad = false;
            char prev = s[0];
            int found = -1;
            F0R(i, n) {
                if(s[i]==prev) count++;
                else {
                    if(count==2*k&&s[i-1]!=s[n-1]) {
                        found=i;
                    } else if(count!=k) {
                        bad=true;
                    }
                    count=1;
                    prev=s[i];
                }
            }
            if(bad) return -1;
            else if(found==-1) return n;
            else return found-k;
        } else {
            int missing = k-count;
            count = 0;
            bool bad = false;
            int found = -1;
            char prev = s[0];
            F0R(i, n) {
                // cout << i << " " << found << " " << prev << " " << count << " " << missing << endl;
                if(s[i]==prev) count++;
                else {
                    if(k+missing==count&&s[i-1]==s[n-1]) {
                        if(found==-1) found=i;
                        else bad=true;
                    } else if(k==count) {

                    } else if(count==missing&&s[i-1]==s[n-1]) {
                        found=i+k;
                    } else {
                        bad=true;
                    }
                    count=1;
                    prev=s[i];
                }   
            }
            if(bad) return -1;
            else if(found==-1) return -1;
            else {
                F0R(i, k) {
                    found--;
                }
                return found;
            }
        }
    }
};
struct CorrectSol {
    int n,k;
    string s;

        int get_idx()
    {
        int ptr1 = 1;
        int idx = inf;
        while(ptr1 <= n)
        {
            int ptr2 = ptr1;
            while (s[ptr1] == s[ptr2]) ptr2++;
            if (ptr2 - ptr1 < k)
            {
                idx = ptr2;
                return idx;
            }
            else if (ptr2 - ptr1 > k)
            {
                idx = ptr2 - k;
                return idx;
            }
            ptr1 = ptr2;
        }
        return idx;
    }
 
    int solve(TestCase t)
    {
        n = t.n;
        k = t.k;
        s = "@" + t.s;
        int idx = min(n,get_idx());
        ///cout << "idx = " << idx << endl;
        int ans = (idx == n ? n : idx-1);
        string arr = "";
        for (int i = idx ; i<=n ; i++)
        {
            arr += s[i];
        }
        for (int i=idx-1 ; i>=1 ; i--)
        {
            arr += s[i];
        }
    
        ///cout << "arr = " << arr  << " -- " << arr.size() << endl;
        for (int i=0 ; i<k ; i++)
        {
            if (arr[i] != arr[0])
            {
                return -1;
            }
        }
    
        for (int i=k ; i<n ; i++)
        {
            if (arr[i] == arr[i-k])
            {
                return -1;
                // return;
            }
        }
        return ans;
    }
};
signed main() {
    while(true) {
        TestCase tc = randTC();
        WrongSol w;
        CorrectSol c;
        int wa = w.solve(tc);
        int cor = c.solve(tc);
        if(wa==cor) {
            cout << "PASSED" << endl;
            print_TC(tc);
            cout << wa << endl << cor << endl;
        } else {
            cout << "WRONG ANSWER" << endl;
            print_TC(tc);
            cout << wa << endl << cor << endl;
            break;
        }
    }
    return 0;
}