ll mul(ll a, ll b, ll m) {
    return static_cast<lll>(a) * b % m;
}

ll qpow(ll a, ll b, ll m) {
    ll res = 1 % m;
    for(; b; b >>= 1, a = mul(a, a, m)){
        if(b & 1){
            res = mul(res, a, m);
        }
    }
    return res;
}

bool isprime(ll n) {
    if(n < 2){
        return false;
    }

    static constexpr int A[] = {2, 3, 5, 7, 11, 13, 17, 19, 23};
    int s = __builtin_ctzll(n - 1);
    ll d = (n - 1) >> s;
    for(auto a : A){
        if(a == n){
            return 1;
        }

        ll x = qpow(a, d, n);
        if(x == 1 || x == n - 1){
            continue;
        }

        bool ok = 0;
        for(int i = 0; i < s - 1; ++i){
            x = mul(x, x, n);
            if(x == n - 1){
                ok = 1;
                break;
            }
        }
        if(!ok){
            return 0;
        }
    }
    return 1;
}

vector<ll> factorize(ll n) {
    vector<ll> p;
    function<void(ll)> f = [&](ll n){
        if(n <= 10000){
            for(int i = 2; i * i <= n; ++i){
                for(; n % i == 0; n /= i){
                    p.push_back(i);
                }
            }
            if(n > 1){
                p.push_back(n);
            }
            return;
        }

        if (isprime(n)){
            p.push_back(n);
            return;
        }

        auto g = [&](ll x) {
            return (mul(x, x, n) + 1) % n;
        };

        ll x0 = 2;
        while(1){
            ll x = x0, y = x0, d = 1;
            ll power = 1, lam = 0;
            ll v = 1;

            while(d == 1){
                y = g(y);
                ++lam;
                v = mul(v, abs(x - y), n);

                if(lam % 127 == 0){
                    d = gcd(v, n);
                    v = 1;
                }

                if(power == lam){
                    x = y;
                    power *= 2;
                    lam = 0;
                    d = gcd(v, n);
                    v = 1;
                }
            }
            if(d != n){
                f(d);
                f(n / d);
                return;
            }
            ++x0;
        }
    };

    f(n);
    sort(p.begin(), p.end());
    return p;
}