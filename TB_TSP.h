//
//  TB_TSP.h
//  TB_TSP
//
//  Created by Young on 6/21/16.
//  Copyright © 2016 杨言. All rights reserved.
//

#ifndef TB_TSP_h
#define TB_TSP_h

#include "Swap.h"
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <ctime>
using namespace std;

class TB_TSP{
private:
    int n;
    double* x;
    double* y;
    double** distance;
    int forbidLength;
    int candidateNumber;
    int** forbidTable;
    Swap* candidates;
    int* state;
    int* bestState;
    double adapt;
    double bestAdapt;
    int round;
    double getEuclideanDistance(int, int);
    void disturb(int*, int);
    double getAdaptValue(int*, int);
    void freeTable(int**, int);
public:
    TB_TSP()
    {
        n = -1;
        forbidLength = 3;
        candidateNumber = 5;
        state = 0;
        adapt = 0;
        round = 5;
    }
    ~TB_TSP()
    {
        delete[] candidates;
        if (state != 0)
            delete[] state;
        if (n != -1)
        {
            delete[] x;
            delete[] y;
            for (int i = 0 ; i < n ; i ++)
            {
                delete[] distance[i];
                delete[] forbidTable[i];
            }
            delete[] distance;
            delete[] forbidTable;
        }
    }
    void initTSP();
    void solve();
};

#endif /* TB_TSP_h */
