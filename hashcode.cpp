#include <bits/stdc++.h>
#include <sys/time.h>
 
using namespace std;
 
#define INLINE   inline __attribute__ ((always_inline))
#define NOINLINE __attribute__ ((noinline))
 
#define ALIGNED __attribute__ ((aligned(16)))
 
#define likely(x)   __builtin_expect(!!(x),1)
#define unlikely(x) __builtin_expect(!!(x),0)
 
#define SSELOAD(a)     _mm_load_si128((__m128i*)&a)
#define SSESTORE(a, b) _mm_store_si128((__m128i*)&a, b)
 
#define byte        unsigned char
#define FOR(i,a,b)  for(int i=(a);i<(b);++i)
#define REP(i,a)    FOR(i,0,a)
#define ZERO(m)     memset(m,0,sizeof(m))
#define ALL(x)      x.begin(),x.end()
#define PB          push_back
#define S           size()
#define LL          long long
#define ULL         unsigned long long
#define LD          long double
#define MP          make_pair
#define X           first
#define Y           second
#define VC          vector
#define PII         pair <int, int>
#define VB          VC < byte >
#define VVB         VC < VB >
#define VI          VC < int >
#define VVI         VC < VI >
#define VVVI        VC < VVI >
#define VPII        VC < PII >
#define VD          VC < double >
#define VVD         VC < VD >
#define VVVD        VC < VVD >
#define VF          VC < float >
#define VVF         VC < VF >
#define VVVF        VC < VVF >
#define VS          VC < string >
#define VVS         VC < VS >
#define DB(a)       cerr << #a << ": " << (a) << endl;
 
template<class A, class B> ostream& operator<<(ostream &os, pair<A,B> &p) {os << "(" << p.X << "," << p.Y << ")"; return os;}
template<class A, class B, class C> ostream& operator<<(ostream &os, tuple<A,B,C> &p) {os << "(" << get<0>(p) << "," << get<1>(p) << "," << get<2>(p) << ")"; return os;}
template<class T> ostream& operator<<(ostream &os, VC<T> &v) {os << "{"; REP(i, v.S) {if (i) os << ", "; os << v[i];} os << "}"; return os;}
template<class T> ostream& operator<<(ostream &os, set<T> &s) {VS vs(ALL(s)); return os << vs;}
template<class T> string i2s(T x) {ostringstream o; o << x; return o.str();}
VS splt(string s, char c = ' ') {VS all; int p = 0, np; while (np = s.find(c, p), np >= 0) {if (np != p) all.PB(s.substr(p, np - p)); p = np + 1;} if (p < s.S) all.PB(s.substr(p)); return all;}
 
double getTime() {
    timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec * 1e-6;
}
 
struct RNG {
    unsigned int MT[624];
    int index;
   
    RNG(int seed = 1) {
        init(seed);
    }
   
    void init(int seed = 1) {
        MT[0] = seed;
        FOR(i, 1, 624) MT[i] = (1812433253UL * (MT[i-1] ^ (MT[i-1] >> 30)) + i);
        index = 0;
    }
   
    void generate() {
        const unsigned int MULT[] = {0, 2567483615UL};
        REP(i, 227) {
            unsigned int y = (MT[i] & 0x8000000UL) + (MT[i+1] & 0x7FFFFFFFUL);
            MT[i] = MT[i+397] ^ (y >> 1);
            MT[i] ^= MULT[y&1];
        }
        FOR(i, 227, 623) {
            unsigned int y = (MT[i] & 0x8000000UL) + (MT[i+1] & 0x7FFFFFFFUL);
            MT[i] = MT[i-227] ^ (y >> 1);
            MT[i] ^= MULT[y&1];
        }
        unsigned int y = (MT[623] & 0x8000000UL) + (MT[0] & 0x7FFFFFFFUL);
        MT[623] = MT[623-227] ^ (y >> 1);
        MT[623] ^= MULT[y&1];
    }
   
    unsigned int rand() {
        if (index == 0) {
            generate();
        }
       
        unsigned int y = MT[index];
        y ^= y >> 11;
        y ^= y << 7  & 2636928640UL;
        y ^= y << 15 & 4022730752UL;
        y ^= y >> 18;
        index = index == 623 ? 0 : index + 1;
        return y;
    }
   
    INLINE int next(int x) {
        return rand() % x;
    }
   
    INLINE int next(int a, int b) {
        return a + (rand() % (b - a));
    }
   
    INLINE double nextDouble() {
        return (rand() + 0.5) * (1.0 / 4294967296.0);
    }
};
 
static RNG rng;
 
int MR, MC, D, T, L, W, P, C;
int PL[2000];
int WX[2000];
int WY[2000];
int WP[2000][2000];
int OWP[2000][2000];
int CX[2000];
int CY[2000];
int CN[2000];
VI  OCP[2000];
VI CP[2000];
int COK[2000];
 
int CT[2000];
 
int DX[2000];
int DY[2000];
int DT[2000];
 
struct Order {
    int op;
    int id;
    int prod;
    int load;
   
    Order(int a, int b, int c, int d) {
        op = a;
        id = b;
        prod = c;
        load = d;
    }
};
 
VC<Order> ORDERS[50];
 
 
const int MAX_DIST = 500000;
int predist[MAX_DIST+10000];
int dist(int x1, int y1, int x2, int y2) {
    int x = (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
    return predist[x];
}
 
int dist(int x1, int y1, int x2, int y2, int x3, int y3) {
    return dist(x1,y1,x2,y2)+dist(x1,y1,x3,y3);
}
 
void reset() {
    REP(i, D) DX[i] = WX[0], DY[i] = WY[0], DT[i] = 0;
    REP(i, W) REP(j, P) WP[i][j] = OWP[i][j];
    REP(i, C) CP[i] = OCP[i], CT[i] = 0, COK[i] = true;
    REP(i, C) ORDERS[i].clear();
}
 
 
struct Solution {
    VI order;
    VD storeValue;
};
 
void savecrap(string fn) {
    ofstream fs(fn.c_str());
    VS output;
    REP(i, D) REP(j, ORDERS[i].S) {
        Order &o = ORDERS[i][j];
        output.PB(i2s(i) + (o.op == 1 ? " L " : " D ") + i2s(o.id) + " " + i2s(o.prod) + " 1");
    }
    fs << output.S << endl;
    REP(i, output.S) fs << output[i] << endl;
    fs.close();
}
 
int test(Solution &s, bool sf = false, string fn = "") {
    reset();
    int score = 0;
   
    VS output;
    const int MAX_CUSTOMERS = 250;
    int MAX_CLIENT = 0;
#define BLABLA
    while (true) {
        int d = 0; REP(i, D) if (DT[i] < DT[d]) d = i;
        int PW = -1; int PC = -1; int POS = -1; VI PP;
        double bv = 0;
        REP(x, min(MAX_CLIENT + MAX_CUSTOMERS, C)) {
            int c = s.order[x];
            if (!COK[c]) continue;
            // if (bv > 1.0 / (dist(DX[d], DY[d], CX[c], CY[c])+1) * 1.21) continue;
           
            VI AP;
            REP(w, W) {
                int t = dist(WX[w], WY[w], DX[d], DY[d], CX[c], CY[c]);
                int load = 0;
                AP.clear();
                REP(i, CP[c].S) if (CP[c][i] != -1 && WP[w][CP[c][i]] && load+PL[CP[c][i]]<=L) {
                    AP.PB(CP[c][i]);
                    load += PL[CP[c][i]];
                    WP[w][CP[c][i]]--;
                }
                for (int x : AP) WP[w][x]++;
                int cnt = 0; REP(i, CP[c].S) if (CP[c][i] != -1) cnt++;
                double av = 1.0 / (t+1) * (AP.S + 0.2) / cnt * (AP.S == cnt ? 1.20 : 1);
               
                if (DT[d] + t + AP.S * 2 >= T) continue;
                if (AP.S == 0) continue;
                if (av < bv) continue;
                PW = w;
                PC = c;
                PP = AP;
                bv = av;
                POS = -1;
            }
           
            int loadleft = L;
            REP(i, min((int)ORDERS[d].S-1, 20)) {
                int po = ORDERS[d].S-1-i;
                if (ORDERS[d][po].op == 0) continue;
                int t = dist(DX[d], DY[d], CX[c], CY[c]);
                loadleft = min(loadleft, L - ORDERS[d][po].load);
                AP.clear();
                int w = ORDERS[d][po].id;
                int load = 0;
                REP(i, CP[c].S) if (CP[c][i] != -1 && WP[w][CP[c][i]] && load+PL[CP[c][i]]<=loadleft) {
                    AP.PB(CP[c][i]);
                    load += PL[CP[c][i]];
                    WP[w][CP[c][i]]--;
                }
                for (int x : AP) WP[w][x]++;
                int cnt = 0; REP(i, CP[c].S) if (CP[c][i] != -1) cnt++;
                double av = 1.0 / (t+1) * (AP.S + 0.2) / cnt * (AP.S == cnt ? 1.20 : 1);
               
                if (DT[d] + t + AP.S * 2 >= T) continue;
                if (AP.S == 0) continue;
                if (av < bv) continue;
                PW = w;
                PC = c;
                PP = AP;
                bv = av;
                POS = po;
            }
        }
       
        if (PW == -1) break;
       
        if (POS == -1) {
            for (int p : PP) ORDERS[d].PB(Order(1, PW, p, (ORDERS[d].S == 0 ? 0 : ORDERS[d].back().load) + PL[p]));
            for (int p : PP) ORDERS[d].PB(Order(0, PC, p, ORDERS[d].back().load - PL[p]));
            DT[d] += dist(WX[PW], WY[PW], DX[d], DY[d], CX[PC], CY[PC]) + PP.S * 2;
        } else {
            for (int p : PP) ORDERS[d].insert(ORDERS[d].begin() + POS, Order(1, PW, p, 0));
            for (int p : PP) ORDERS[d].PB(Order(0, PC, p, 0));
            int curload = 0;
            REP(i, ORDERS[d].S) {
                if (ORDERS[d][i].op) curload += PL[ORDERS[d][i].prod];
                else curload -= PL[ORDERS[d][i].prod];
                ORDERS[d][i].load = curload;
            }
            DT[d] += dist(DX[d], DY[d], CX[PC], CY[PC]) + PP.S * 2;
        }
        DX[d] = CX[PC];
        DY[d] = CY[PC];
        CT[PC] = max(CT[PC], DT[d]);
       
        for (int p : PP) {
            WP[PW][p]--;
            REP(i, CP[PC].S) if (CP[PC][i] == p) {CP[PC][i] = -1; break;}
        }
       
        bool done = true; for (int x : CP[PC]) done &= x == -1;
        if (done) {
            score += (int)(1 + 100.0 * (T - CT[PC]) / T - 1e-9);
            COK[PC] = false;
            MAX_CLIENT++;
        }
       
    }
   
    if (sf) savecrap(fn);
    return score;
}
 
 
int main(int argc, char **argv) {
    double startTime = getTime();
 
    int value = 1;
    int d = 1;
    predist[0] = 0;
    while (true) {
        if (d > MAX_DIST) break;
        while (d <= value*value) predist[d++] = value;
        value++;
    }
   
    cin >> MR >> MC >> D >> T >> L;
    cin >> P;
    REP(i, P) cin >> PL[i];
    cin >> W;
    REP(i, W) {
        cin >> WX[i] >> WY[i];
        REP(j, P) cin >> OWP[i][j];
    }
    cin >> C;
    REP(i, C) {
        cin >> CX[i] >> CY[i] >> CN[i];
        OCP[i] = VI(CN[i]);
        REP(j, CN[i]) cin >> OCP[i][j];
    }
   
    reset();
    Solution s;
    s.order = VI(C);
    VI used(C, -1);
    REP(i, C) {
        int b = -1;
        double bv = -1e9;
        REP(j, C) if (used[j] == -1) {
            double av = -CN[j] * 10000;
            // REP(k, CN[j]) av += CP[j][k];
            if (av > bv) {
                bv = av;
                b = j;
            }
        }
        s.order[i] = b;
        used[b] = 1;
    }
    s.storeValue = VD(W, 1.0);
   
    int tries = argc > 2 ? atoi(argv[2]) : 1000;
    int XV = test(s, false);
    DB(XV);
    REP(step, tries) {
        int t, a, b, p;
        t = rng.next(2);
        if (t == 0) {
            a = rng.next(C);
            b = rng.next(C - 1);
            b += b >= a;
            swap(s.order[a], s.order[b]);
        } else {
            p = rng.next(C);
            if (CN[p]==1) continue;
            a = rng.next(CN[p]);
            b = rng.next(CN[p]-1);
            b += b >= a;
            swap(OCP[p][a], OCP[p][b]);
        }
        int AV = test(s, false);
        if (AV >= XV) {
            if (AV > XV) {
                XV = AV;
                cerr << "Score: " << XV << " Step: " << step << " Time: " << (getTime() - startTime) << endl;
                test(s, true, argv[1]);
            }
        } else {
            if (t == 0) {
                swap(s.order[a], s.order[b]);
            } else {
                swap(OCP[p][a], OCP[p][b]);
            }
        }
    }
    DB(getTime() - startTime);
   
    return 0;
}
