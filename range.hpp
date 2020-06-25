/*
 * Created by ko tal on 21/06/2020.
 */

/**
 * === RANGE ===
 */
#pragma once

#include <iostream>
#include <string>

namespace itertools
{
    class range {
    private:
        int startVal, endVal;

    public:
        range(int a, int b): startVal(a), endVal(b) {}

        class iterator {
        private:
            int currVal;

        public:
            iterator():
            currVal(0){}
            explicit iterator(int val) :
            currVal(val){}

            const iterator operator++(int){
                iterator t = *this;
                ++currVal;
                return t;
            }

            iterator &operator++(){
                ++currVal;
                return *this;
            }

            int operator*() const{return currVal;}

            bool operator==(const iterator &other) const{return currVal == other.currVal;}

            bool operator!=(const iterator &other) const{return !(*this == other);}
        };

        iterator begin() const{return range::iterator(startVal);}

        iterator end() const{return range::iterator(endVal);}
    };

} // end namespace itertools
