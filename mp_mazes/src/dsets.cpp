/* Your code here! */
#include "dsets.h"
#include <vector>
#include <algorithm>
#include <iostream>

void DisjointSets::addelements(int num){
    // int init = djs.size();
    // djs.resize(init+num);

    // for(int i=0; i<num; i++){
    //     djs[init+i] = -1;
    // }
    for (int i = 0; i < num; ++i) {
        djs.push_back(-1); 
    }
}


int DisjointSets::find(int elem){
    if (djs[elem]<0) return elem;
    else{
        return find(djs[elem]);
        return djs[elem];
    }
}


void DisjointSets::setunion(int a, int b){
    int a_ = find(a);
    int b_ = find(b);
    int newSize = djs[a_] + djs[b_];

    if (a_ == b_) return;
    if ( djs[a_] <= djs[b_] ) {
        djs[a_] = newSize;
        djs[b_] = a_;
    }
    else {
        djs[a_] = b_;
        djs[b_] = newSize;
    }
}


int DisjointSets::size(int elem){
    return -djs[find(elem)];
}
