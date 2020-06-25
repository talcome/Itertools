/*
 * Created by ko tal on 21/06/2020.
 */

/**
 * === COMPRESS ===
 */
#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <iterator>

namespace itertools {
    template<class T1, class T2> class compress {
        const T1& container1;
        const T2& container2;

    public:
        compress(const T1& cont1, const T2& cont2):
        container1(cont1), container2(cont2){}

        class iterator {
            decltype(container1.begin()) currVal1;
            decltype(container2.begin()) currVal2;
            const compress &comp;

        public:
            iterator(decltype(container1.begin()) it1, decltype(container2.begin()) it2, const compress &compress) :
                    currVal1(it1), currVal2(it2), comp(compress) {
                if (currVal2 != compress.container2.end()) currVal2 = it2;
                while (currVal2 != comp.container2.end() && *currVal2 == false){
                    currVal1++;
                    currVal2++;
            }
        }

        iterator& operator++(){
                ++currVal1;
                ++currVal2;
                while(currVal2 != comp.container2.end() && !(*currVal2)){
                    ++currVal1;
                    ++currVal2;
                }
                return *this;
            }

            const iterator operator++(int){
                iterator t = *this;
                ++currVal1;
                ++currVal2;
                return t;
            }

            auto operator*(){return *currVal1;}

            bool operator==(const iterator &other) const{return currVal1 == other.currVal1;}

            bool operator!=(const iterator &other) const{return !(currVal1 == other.currVal1);}
        };

        iterator begin() const{return iterator(container1.begin(),container2.begin(),*this);}

        iterator end() const{return iterator(container1.begin(),container2.begin(),*this);}
    };
} // end namespace itertools
