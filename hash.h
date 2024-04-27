#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        std::string kcopy = k;
        HASH_INDEX_T w[5];
        for(int i = 0; i< 5; i++){
            w[i] = 0;
        }
        int i = 4;
        while(kcopy.length() > 6){
            for(int j = 0; j < 6; j++){
                w[i] += (letterDigitToNumber(kcopy[kcopy.length() - 1]) * pow(36, j));
                kcopy.pop_back();
            }
            i--;
        }
        int j = 0;
        while(!kcopy.empty()){
            w[i] += (letterDigitToNumber(kcopy[kcopy.length() - 1]) * pow(36, j));
            kcopy.pop_back();
            j++;
        }
        HASH_INDEX_T hk = rValues[0] * w[0] + rValues[1] * w[1] + rValues[2] * w[2] + rValues[3] * w[3] + rValues[4] * w[4];
        return hk;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        if((letter >= 48) && (letter <= 57)){
            return ((HASH_INDEX_T) (letter - 22));
        }
        if((letter >= 65) && (letter <= 90)){
            return ((HASH_INDEX_T) (letter - 65));
        }
        if((letter >= 97) && (letter <= 122)){
            return ((HASH_INDEX_T) (letter - 97));
        }
        return -1;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
