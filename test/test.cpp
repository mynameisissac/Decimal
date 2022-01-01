//
// Created by kshou on 2022/1/1.
//

#include "Decimal.h"


int main(){

    Decimal ten("10");
    Decimal ten2(10);

    ten.add(ten2).print();

    return 0;
}