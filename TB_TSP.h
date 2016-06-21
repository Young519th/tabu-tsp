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
    double getEuclideanDistance(int, int);
public:
    TB_TSP()
    {
        n = -1;
        forbidLength = 3;
        candidateNumber = 5;
        candidates = new Swap[candidateNumber];
    }
    ~TB_TSP(){}
    void initTSP();
};

#endif /* TB_TSP_h */
