//
//  TB_TSP.cpp
//  TB_TSP
//
//  Created by Young on 6/21/16.
//  Copyright © 2016 杨言. All rights reserved.
//

#include "TB_TSP.h"

double TB_TSP::getEuclideanDistance(int i, int j)
{
    //to get the distance between city i and j.
    return sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
}

void TB_TSP::disturb(int * state, int n)
{
    //to random the order of the solution
    for (int i = 0 ; i < n ; i ++)
    {
        int t = rand() % (n - i) + i;
        int temp = state[i];
        state[i] = state[t];
        state[t] = temp;
    }
}

double TB_TSP::getAdaptValue(int * state, int n)
{
    //to get the adapatation value of one solution
    double result = 0;
    for (int i = 0 ; i < n - 1 ; i ++)
    {
        result += distance[state[i]][state[i + 1]];
    }
    result += distance[state[n - 1]][state[0]];
    return (double)1 / result;
}

void TB_TSP::freeTable(int ** table, int n)
{
    for (int i = 0 ; i < n ; i ++)
        for (int j = 0 ; j < n ; j ++)
        {
            if (table[i][j] > 0)
                table[i][j] --;
        }
}

void TB_TSP::initTSP()
{
    //configure the TSP problem, must run once and only once.
    if (n != -1)
        return;
    cout << "The total number of cities:";
    cin >> n;
    if (n <= 0)
        return;
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
    candidates = new Swap[candidateNumber];
    cout << "TSP start!" << endl;
}

void TB_TSP::solve()
{
    //(must init TSP first) to solve TSP problem.
    if (n == -1)
        return;
    bestState = new int[n];
    bestAdapt = 0;
    for (int i = 0 ; i < n ; i ++)
        for (int j = 0 ; j < n ; j ++)
            forbidTable[i][j] = 0;
    if (state != 0)
        delete[] state;
    state = new int[n];
    for (int i = 0 ; i < n ; i ++)
        state[i] = i;
    disturb(state, n);
    adapt = getAdaptValue(state, n);
    if (adapt > bestAdapt)
    {
        bestAdapt = adapt;
        for (int i = 0 ; i < n ; i ++)
            bestState[i] = state[i];
    }
    for (int p = 0 ; p < round ; p ++)
    {
        for (int q = 0 ; q < candidateNumber ; q ++)
            candidates[q].reset();
        for (int i = 0 ; i < n ; i ++)
            for (int j = i + 1 ; j < n ; j ++)
            {
                int temp = state[i];
                state[i] = state[j];
                state[j] = temp;
                double deltaAdapt = getAdaptValue(state, n) - adapt;
                int k = 0;
                if (deltaAdapt > candidates[candidateNumber - 1].income)
                {
                    while (k < candidateNumber)
                    {
                        if (deltaAdapt > candidates[k].income)
                        {
                            for (int l = candidateNumber - 1 ; l > k ; l --)
                            {
                                candidates[l] = candidates[l - 1];
                            }
                            candidates[k].first = i;
                            candidates[k].last = j;
                            candidates[k].income = deltaAdapt;
                            break;
                        }
                        k ++;
                    }
                }
                state[j] = state[i];
                state[i] = temp;
            }
        if (adapt + candidates[0].income > bestAdapt)
        {
            int temp = state[candidates[0].first];
            state[candidates[0].first] = state[candidates[0].last];
            state[candidates[0].last] = temp;
            forbidTable[candidates[0].first][candidates[0].last] = forbidLength + 1;
            adapt = getAdaptValue(state, n);
            bestAdapt = adapt;
            for (int q = 0 ; q < n ; q ++)
                bestState[q] = state[q];
        }
        else
        {
            bool isAllForbid = true;
            for (int q = 0 ; q < candidateNumber ; q ++)
            {
                if (candidates[q].first < 0)
                    break;
                if (forbidTable[candidates[q].first][candidates[q].last] == 0)
                {
                    isAllForbid = false;
                    int temp = state[candidates[q].first];
                    state[candidates[q].first] = state[candidates[q].last];
                    state[candidates[q].last] = temp;
                    forbidTable[candidates[q].first][candidates[q].last] = forbidLength + 1;
                    adapt = getAdaptValue(state, n);
                    if (adapt > bestAdapt)
                    {
                        bestAdapt = adapt;
                        for (int i = 0 ; i < n ; i ++)
                            bestState[i] = state[i];
                    }
                    break;
                }
            }
            if (isAllForbid)
            {
                int temp = state[candidates[0].first];
                state[candidates[0].first] = state[candidates[0].last];
                state[candidates[0].last] = temp;
                adapt = getAdaptValue(state, n);
                forbidTable[candidates[0].first][candidates[0].last] = forbidLength + 1;
            }
        }
        freeTable(forbidTable, n);
    }
    cout << "The minimum cost of the TSP is " << 1 / bestAdapt << endl;
    cout << "The specific path is ";
    for (int i = 0 ; i < n - 1 ; i ++)
        cout << bestState[i] << "-";
    cout << bestState[n - 1] << endl;
    delete[] bestState;
}
