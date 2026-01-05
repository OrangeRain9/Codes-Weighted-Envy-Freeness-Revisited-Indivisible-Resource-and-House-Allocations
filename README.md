This is the experimental code of paper "Weighted Envy-Freeness Revisited: Indivisible Resource and House Allocations".

You can use gcc directly or cmake tools to compile and run.

batchtest_indivisible and batchtest_house both have 7 parameters:

1. n: the number of agents
2. m: the number of resources
3. offsetw
4. maxweight: the weights of each agent will be uniformly draw from offsetw + 1 to offsetw + maxweight
5. maxutility: the utility of each agent to each resource will be uniformly draw from 1 to maxutility
6. times: the number of test cases
7. setting: "IC" or "SPUP" to specify the method of data generations