/*
 * Created by ko tal on 21/06/2020.
 */

/**
 * === ACCUMULATE ===
 */
#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <iterator>

namespace itertools
{
    struct{
        template<typename T> T operator()(const T& a, const T& b){return a+b;}
    }typedef plus;

    template<class T, class F = plus> class accumulate {
    private:
        const T& container;
        const F& function;

    public:
        accumulate(const T& cont, const F& func = plus()):
        container(cont), function(func){}
        ~accumulate(){}

        class iterator{
        private:
            decltype(container.begin()) itr;
            typename std::decay<decltype(*(container.begin()))>::type sum;
            const accumulate& accumulater;

        public:
            iterator(decltype(container.begin()) currVal, const accumulate& accumulater):
                    itr(currVal), accumulate(accumulater){
                if (currVal != accumulater.container.end()) sum = *currVal;
            }

            iterator& operator++(){
                ++itr;
                if (itr == accumulater.container.end())
                    return *this;
                sum = accumulater.function(sum,*(itr++));
                return *this;
            }

            const iterator operator++(int){
                iterator t = *this;
                itr++;
                sum = accumulater.function(sum,*itr);
                return t;
            }

            auto operator*(){return sum;}

            bool operator==(const iterator &other) const{return itr == other.itr;}

            bool operator!=(const iterator &other) const{return !(itr == other.itr);}
        };

        iterator begin() const{return iterator(container.begin(),*this);}

        iterator end() const{return iterator(container.end(),*this);}
    };

} // end namespace itertools


