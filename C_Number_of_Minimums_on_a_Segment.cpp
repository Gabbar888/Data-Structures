#include<bits/stdc++.h>

#define for0(i, n) for (int i = 0; i < (int)(n); ++i) // 0 based indexing
#define for1(i, n) for (int i = 1; i <= (int)(n); ++i) // 1 based indexing

#define pb push_back
#define endl '\n'
#define fi first
#define se second
#define INF INT64_MAX-INT32_MAX
#define inf INT64_MIN - INT32_MIN
#define mp make_pair
#define int long long

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pii;
typedef vector<pii> vpii;

typedef long long ll;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef pair<ll,ll> pll;
typedef vector<pll> vpll;

#define all(x) (x).begin(), (x).end() //Forward traversal
#define rall(x) (x).rbegin, (x).rend() //reverse traversal

int M=1e9+7;

ll ceil(ll a,ll b)// ceil(a/b)
{
     if(a%b == 0)return a/b;
     else return (a/b)+1;
}

ll pow(long long x,int n, int m)
{
   if(n == 0)return 1;
     else
     {
         ll temp;
         temp = pow(x,n/2,m);
         temp = ((temp%m)*(temp%m))%m;
         if(n%2 == 1)return (temp*x)%m;
         return temp;
     }
}

int log(int x)
{
     return 31 - __builtin_clz(x);
}

struct item
{
    int m,c;
};

struct segtree
{
    int size;
    vector<item> values;
    item NEUTRAL_ELEMENT = {INF,0};

    void init(int n)
    {
        size =1;
        while(size<n)size*=2;
        values.resize(2*size);
    }

    item merge(item a,item b)
    {
        if(a.m<b.m)return a;
        if(a.m>b.m)return b;
        else return {a.m,a.c+b.c};
    }

    item single(int a)
    {
        return {a,1};
    }

    void build(vi &a,int x, int lx, int rx)
    {
        if(rx-lx == 1)
        {
            if(lx<(int)a.size())values[x] = single(a[lx]);
            return;
        }
        int m = (lx+rx)/2;
        build(a,2*x+1,lx,m);
        build(a,2*x+2,m,rx);
        values[x] = merge(values[2*x+1],values[2*x+2]);
    }
    void build(vi &a)
    {
        build(a,0,0,size);
    }
    void set(int i, int v,int x,int lx,int rx)
    {
        if(rx - lx == 1)
        {
            values[x] =single(v);
            return;
        }
        int m = (lx+rx)/2;
        if(i<m)
        {
            set(i,v,2*x+1,lx,m);
        }
        else set(i,v,2*x+2,m,rx);
        values[x] = merge(values[2*x+1],values[2*x+2]);
    }

    void set(int i, int v)
    {
        set(i,v,0,0,size);
    }

    item calc(int l, int r,int x,int lx, int rx)
    {
        if(lx>=l && rx <= r){
            return values[x];
        }
        if(lx>=r || rx <= l)return NEUTRAL_ELEMENT;
        int m = (lx+rx)/2;
        item s1 = calc(l,r,2*x+1,lx,m);
        item s2 = calc(l,r,2*x+2,m,rx);
        return merge(s1,s2);
    }

    item calc(int l, int r)
    {
        return calc(l,r,0,0,size);
    }
};

int32_t main()
{ // never use power function of c++ ever again
// vector <vector<int>> grid(n,vector<int>(n,-1)); declaring a 2d vector
ios :: sync_with_stdio(false);
cin.tie(NULL);
cout.tie(0);
int n,m;
cin>>n>>m;
vi a(n);
for0(i,n)cin>>a[i];
segtree st;
st.init(n);
st.build(a);
while(m--)
{
    int op;
    cin>>op;
    if(op == 1)
    {
        int i,v;
        cin>>i>>v;
        st.set(i,v);
    }
    else
    {
        int l,r;
        cin>>l>>r;
        item ans = st.calc(l,r);
        cout<<ans.m<<" "<<ans.c<<endl;
    }

    // st.print();
}

return 0;
}