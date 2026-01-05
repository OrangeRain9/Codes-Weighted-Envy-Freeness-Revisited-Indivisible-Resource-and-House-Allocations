#include "common.hpp"
#include "instance_gen.hpp"
#include "solver.hpp"

/*
./build/batchtest_indivisible 5 8 0 100 10000 10000 IC
./build/batchtest_indivisible 5 8 100 100 10000 10000 IC
./build/batchtest_indivisible 5 8 0 100 10000 10000 SPUP
./build/batchtest_indivisible 5 8 100 100 10000 10000 SPUP

./build/batchtest_indivisible 6 8 0 100 10000 10000 IC
./build/batchtest_indivisible 6 8 100 100 10000 10000 IC
./build/batchtest_indivisible 6 8 0 100 10000 10000 SPUP
./build/batchtest_indivisible 6 8 100 100 10000 10000 SPUP

./build/batchtest_indivisible 7 8 0 100 10000 10000 IC
./build/batchtest_indivisible 7 8 100 100 10000 10000 IC
./build/batchtest_indivisible 7 8 0 100 10000 10000 SPUP
./build/batchtest_indivisible 7 8 100 100 10000 10000 SPUP

./build/batchtest_indivisible 8 8 0 100 10000 10000 IC
./build/batchtest_indivisible 8 8 100 100 10000 10000 IC
./build/batchtest_indivisible 8 8 0 100 10000 10000 SPUP
./build/batchtest_indivisible 8 8 100 100 10000 10000 SPUP
*/

//gcc ./src/batchtest_indivisible.cpp -o ./build/batchtest_indivisible -std=gnu++11 -O3 -lstdc++
//./build/batchtest_indivisible 5 8 0 100 10000 1000 IC                                          weights: 1-100
//./build/batchtest_indivisible 5 8 100 100 10000 1000 IC                                        weights: 101-200
// n, m, offsetw, maxweight, maxutility, times, setting = "IC" or "SPUP"
int main(int argc, char** argv) {
    srand(SEED);
    mt19937 rng(SEED);
    int n = atoi(argv[1]);
    int m = atoi(argv[2]);
    int offsetw = atoi(argv[3]);
    int mw = atoi(argv[4]);
    int mu = atoi(argv[5]);
    int times = atoi(argv[6]);
    string setting = argv[7];

    string logadr = "./results/mt19937_batch_indivisible";
    logadr.append(",n = ");
    logadr.append(to_string(n));
    logadr.append(",setting = ");
    logadr.append(setting);
    logadr.append(",offsetw = ");
    logadr.append(to_string(offsetw));
    logadr.append(".log");



    freopen(logadr.c_str(), "a", stdout);
    printf("run on [(n=%d,m=%d,offsetw=%d,mw=%d,mu=%d,times=%d,setting = %s)]:\n", n, m, offsetw, mw, mu, times, setting.c_str());
    int cntsum = 0;
    int cntavg = 0;
    int cntsumavg = 0;
    int cnt_sum_sumavg = 0;
    int cnt_avg_sumavg = 0;
    int cnt_sum_avg = 0;
    for (int tm = 1; tm <= times;tm++) {
        fprintf(stderr, "runs on test %d/%d\n", tm, times);
        instance_t ins;
        if(setting == "IC") ins = gen_house_IC(n, m, offsetw, mw, mu, setting, rng);
        if(setting == "SPUP") ins = gen_house_SPUP(n, m, offsetw, mw, mu, setting, rng);

        bool oksum = bruteforce_indivisible(ins, "sum");
        cntsum += (int)oksum;
        printf("sum: sol = %d,   ", (int)oksum);
        fflush(stdout);
        
        bool okavg = bruteforce_indivisible(ins, "avg");
        cntavg += (int)okavg;
        printf("avg: sol = %d,   ", (int)okavg);
        fflush(stdout);

        bool oksumavg = bruteforce_indivisible(ins, "sumavg");
        cntsumavg += (int)oksumavg;
        printf("sumavg: sol = %d,   ", (int)oksumavg);
        printf("\n");
        fflush(stdout);

        if(oksum&&!okavg)
            cnt_sum_sumavg++;
        if(!oksum&&okavg)
            cnt_avg_sumavg++;
        if(oksum&&okavg)
            cnt_sum_avg++;
    }
    printf("run on [(n=%d,m=%d,offsetw=%d,mw=%d,mu=%d,times=%d,setting = %s)]:\n", n, m, offsetw, mw, mu, times, setting.c_str());
    printf("finished!\n");
    printf("On sum setting, there are %d/%d yes-instances.\n", cntsum, times);
    printf("On avg setting, there are %d/%d yes-instances.\n", cntavg, times);
    printf("On sumavg setting, there are %d/%d yes-instances.\n", cntsumavg, times);

    printf("There are %d/%d instances yes on sum setting but no on avg setting.\n", cnt_sum_sumavg, times);
    printf("There are %d/%d instances yes on avg setting but no on sum setting.\n", cnt_avg_sumavg, times);
    printf("There are %d/%d yes-instances on both sum and avg setting.\n", cnt_sum_avg, times);

    return 0;
}