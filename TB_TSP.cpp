//
//  TB_TSP.cpp
//  TB_TSP
//
//  Created by Young on 6/21/16.
//  Copyright © 2016 杨言. All rights reserved.
//

#include "TB_TSP.h"
#include <iostream>
#include <math.h>
using namespace std;

double TB_TSP::getEuclideanDistance(int i, int j)
{
    //to get the distance between city i and j.
    return sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
}

void TB_TSP::initTSP()
{
    //set the TSP problem, must run once and only once.
    if (n != -1)
        return;
    cout << "The total number of cities:";
    cin >> n;
    x = new double[n];
    y = new double[n];
    distance = new double*[n];
    for (int i = 0 ; i < n ; i ++)
        distance[i] = new double[n];
    for (int i = 0 ; i < n ; i ++)
    {
        cout << "CITY " << i << " :";
        cin >> x[i] >> y[i];
    }
    for (int i = 0 ; i < n ; i ++)
        for (int j = 0 ; j < n ; j ++)
        {
            distance[i][j] = getEuclideanDistance(i, j);
        }
    forbidTable = new int*[n];
    for (int i = 0 ; i < n ; i ++)
        forbidTable[i] = new int[n];
}