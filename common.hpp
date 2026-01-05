#ifndef COMMON_HPP
#define COMMON_HPP

#include <bits/stdc++.h>
using namespace std;
const int MAXN = 105;
const int SEED = 19937;


struct instance_t {
    int n;                        // the number of agents
    int m;                        // the number of resources
    vector<int> w;                // weight
    vector<vector<int> > utility; // utility function

    instance_t() {}
    instance_t(int n_, int m_): n(n_), m(m_) {
        w.resize(n_ + 1);
        utility.resize(n_ + 1);
        for (int i = 1; i <= n_; i++) {
            utility[i].resize(m_ + 1);
    }
    }
    instance_t(const vector<vector<int> >& utility_, const vector<int>& w_, int n_, int m_): utility(utility_), w(w_), n(n_), m(m_) {}
};

struct allocation_t {
    int n;                        // the number of agents
    int m;                        // the number of resources
    vector<set<int> > pi;         // pi: A \rightarrow 2^R, size = n

    allocation_t() {}
    allocation_t(const vector<set<int> >& pi_, int n_, int m_): pi(pi_), n(n_), m(m_) {}
};

/*
    //n, m
    //w_1, w_2, \dots, w_n
    //u_1(r_1), u_1(r_2), \dots, u_1(r_m)
    //...
    //u_n(r_1), u_n(r_2), \dots, u_n(r_m)
*/
void read_instance(string filename, instance_t& Ins) {
    freopen(filename.c_str(), "r", stdin);
    int n, m;
    scanf("%d %d", &Ins.n, &Ins.m);
    Ins.w.resize(Ins.n + 1);
    Ins.utility.resize(Ins.n + 1);
    for (int i = 1; i <= Ins.n; i++) {
        Ins.utility[i].resize(Ins.m + 1);
    }
    

    for (int i = 1; i <= Ins.n; i++) {
        scanf("%d\n", &Ins.w[i]);
    }

    for (int i = 1; i <= Ins.n; i++) {
        for (int j = 1; j <= Ins.m; j++) {
            scanf("%d\n", &Ins.utility[i][j]);
        }
    }

        

    fprintf(stderr, "instance : %d agents, %d resources\n",
                Ins.n, Ins.m);

    fclose(stdin);
}

void output_Instance(const instance_t & ins) {
    printf("%d %d\n", ins.n, ins.m);
    for (int i = 1; i <= ins.n; i++ )
        printf("%d ", ins.w[i]);
    printf("\n");
    for (int i = 1; i <= ins.n; i++) {
        for (int j = 1; j <= ins.m; j++) {
            printf("%d ", ins.utility[i][j]);
        }
        printf("\n");
    }
}

void output_Allocation(const allocation_t& S) {
    fprintf(stderr, "allocation:\n");
    for (int i = 1; i <= S.n; i++) {
        fprintf(stderr, "%d:", i);
        for(auto a : S.pi[i]) 
            fprintf(stderr, "<%d>, ", a);
            
        fprintf(stderr, "\n");
    }
}


bool verify(const instance_t& ins, const allocation_t& t, string setting) {
    bool ok = 1;
    for (int i = 1; i <= ins.n; i++) {
        for (int j = 1; j <= ins.n; j++) {
            int vi = 0;
            int vj = 0;
            for (auto a : t.pi[i]) {
                vi += ins.utility[i][a];
            }
            for (auto a : t.pi[j]) {
                vj += ins.utility[i][a];
            }
            if(setting == "sum") {
                if(vj > vi) {
                    ok = false;
                    goto L;
                }
            }else if (setting == "avg") {
                if(vj * ins.w[i] > vi* ins.w[j]){
                    ok = false;
                    goto L;
                }
            }else if (setting == "sumavg") {
                if(vj * ins.w[i] > vi* ins.w[j] && vj > vi){
                    ok = false;
                    goto L;
                }
            }
            
        }
    }
L:;
    return ok;
}


#endif