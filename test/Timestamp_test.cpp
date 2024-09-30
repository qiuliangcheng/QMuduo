#include "Timestamp.h"
#include <iostream>
int main(){
    std::cout<<qlc::Timestamp::now().toString()<<std::endl;
    return 0;
}