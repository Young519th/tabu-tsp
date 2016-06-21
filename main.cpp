//
//  main.cpp
//  TB_TSP
//
//  Created by Young on 6/21/16.
//  Copyright © 2016 杨言. All rights reserved.
//

#include "TB_TSP.h"

int main(int argc, const char * argv[]) {
    srand((unsigned)time(0));
    TB_TSP tsp;
    tsp.initTSP();
    tsp.solve();
    return 0;
}
