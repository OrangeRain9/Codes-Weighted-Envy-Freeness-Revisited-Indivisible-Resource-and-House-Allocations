#ifndef INSTANCE_GEN_HPP
#define INSTANCE_GEN_HPP
#include "common.hpp"

/*
n: the number of agents
m: the number of resources
offsetw: the offset of weights
maxweight: generate weight from 1 + offsetw to maxweight + offsetw. Note that w_1 \leq w_2 \leq ... \leq w_n
maxutility: generate utility from 1 to maxutility
setting: the way to gen preference
setting = "IC"
*/
instance_t gen_house_IC(int n, int m, int offsetw, int maxweight, int maxutility, string setting, mt19937 &rng) {
    // mt19937 rng(SEED);
    uniform_int_distribution<int> distmaxweight(1, maxweight);
    uniform_int_distribution<int> distmaxutility(1, maxutility);
    instance_t ins(n, m); 
    vector<int> wtmp;
    for (int i = 1; i <= n; i++) {
        int tmp = distmaxweight(rng);
        wtmp.push_back(tmp);
    }
    sort(wtmp.begin(), wtmp.end());
    for (int i = 1; i <= n; i++) {
        ins.w[i] = wtmp[i - 1] + offsetw;
    }

    vector<int> ptmp;
    
    for (int i = 1; i <= m; i++) {
        ptmp.push_back(i);
    }
    for (int i = 1; i <= n;i++) {
        random_shuffle(ptmp.begin(), ptmp.end()); 
        vector<int> utmp;
        for (int i = 1; i <= m;i++) {
            int tmp = distmaxutility(rng);
            utmp.push_back(tmp);
        }
        sort(utmp.begin(), utmp.end());

        for (int j = 1; j <= m; j++) {
            ins.utility[i][j] = utmp[ptmp[j - 1] - 1];
        }
        
    }
    return ins;
}


/*
n: the number of agents
m: the number of resources
offsetw: the offset of weights
maxweight: generate weight from 1 + offsetw to maxweight + offsetw. Note that w_1 \leq w_2 \leq ... \leq w_n
maxutility: generate utility from 1 to maxutility
setting: the way to gen preference
setting = "SPUP"
given axis: 1, 2, \dots, m.
*/
instance_t gen_house_SPUP(int n, int m, int offsetw, int maxweight, int maxutility, string setting, mt19937 &rng) {
    // mt19937 rng(SEED);
    uniform_int_distribution<int> distmaxweight(1, maxweight);
    uniform_int_distribution<int> distmaxutility(1, maxutility);
    uniform_int_distribution<int> distm(1, m);
    uniform_int_distribution<int> dist2(1, 2);
    instance_t ins(n, m); 
    vector<int> wtmp;
    for (int i = 1; i <= n; i++) {
        int tmp = distmaxweight(rng);
        wtmp.push_back(tmp);
    }
    sort(wtmp.begin(), wtmp.end());
    for (int i = 1; i <= n; i++) {
        ins.w[i] = wtmp[i - 1] + offsetw;
    }

    vector<int> ptmp;

    for (int i = 1; i <= n; i++) {
        int peak = distm(rng);
        ptmp.clear();
        ptmp.push_back(peak);
        int cnt = m - 1;
        int nowleft = peak;
        int nowright = peak;
        while(cnt--) {
            int lr = rand() % 2; //speedup
            if(nowleft == 1)
                lr = 1;
            if(nowright == m)
                lr = 0;
            if(nowleft == 1 && nowright == m)
                break;
            if(lr == 0) {
                nowleft--;
                ptmp.push_back(nowleft);
            }
            if(lr == 1) {
                nowright++;
                ptmp.push_back(nowright);
            }
        }
        vector<int> utmp;
        for (int i = 1; i <= m;i++) {
            int tmp = distmaxutility(rng);
            utmp.push_back(tmp);
        }
        sort(utmp.begin(), utmp.end(), greater<int>());

        for (int j = 1; j <= m; j++) {
            ins.utility[i][ptmp[j - 1]] = utmp[j - 1];
        }
        
    }
    return ins;
}


#endif