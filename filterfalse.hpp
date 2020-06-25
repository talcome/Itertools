/*
 * Created by ko tal on 21/06/2020.
 */

/**
 * === FILTERFALSE ===
 */
#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <iterator>

namespace itertools
{
    template<typename T, typename F> class filterfalse{
        const T& container;
        const F& function;

    public:
        filterfalse(const T& cont, const F& func):
        container(cont), function(func){}
        ~filterfalse(){}

        class iterator{
        private:
            decltype(container.begin()) currval;
            const filterfalse& filterf;

        public:
            iterator(decltype(container.begin()) currVal, const filterfalse& ff): currval(currVal), filterf(ff){
                while (currval != ff.container.end() && ff.function(*currval)) currval++;
            }

            iterator& operator++(){
                ++currval;
                while(currval != filterf.container.end() && filterf.function(*currval)) ++currval;
                return *this;
            }

            const iterator operator++(int){
                iterator t = *this;
                ++currval;
                return t;
            }

            auto operator*(){return *currval;}

            bool operator==(const iterator &other) const{return currval == other.currval;}

            bool operator!=(const iterator &other) const{return !(currval == other.currval);}
        };

        iterator begin() const{return iterator(container.begin(),*this);}

        iterator end() const{return iterator(container.end(),*this);}
    };

} // end namespace itertools