/*  
    K.Szytko 19.04.2020
*/

#include <string> 
#include <vector>
#include <algorithm>
#include <set>
#include <stdexcept> 

struct romanSeq{
    unsigned int value;
    std::string chars;
    unsigned int maxCount;
};

const unsigned int MAX_NUMBER = 3999;
const unsigned int MAX_ROMAN_SIZE = 15;
const std::set<char> ROMAN_NUMERALS = {'M','D','C','L','X','V','I'};
const std::vector<romanSeq> ROMAN_SEQ = {
    {1000,	"M",	3},
    {900, 	"CM",	1},
    {500, 	"D",	1},
    {400, 	"CD",	1},
    {100, 	"C",	3},
    {90,  	"XC",	1},
    {50,  	"L",	1},
    {40,  	"XL",	1},
    {10,	"X",	3},
    {9,	 	"IX",	1},
    {5,	 	"V",	1},
    {4,	 	"IV",	1},
    {1,	 	"I",	3}};


std::string toRoman(const unsigned int & arabic){
    if(arabic > MAX_NUMBER || arabic == 0){
        throw std::out_of_range("Number out of range (min 1, max 3999)");
    }

    std::string result;
    unsigned int value = arabic;

    for(auto& element: ROMAN_SEQ){
        while(element.value <= value){
            value -= element.value;
            result += element.chars;
        }
    }

    return result;
}

unsigned int fromRoman(const std::string & roman ){
    if( roman.empty() || roman.size() > MAX_ROMAN_SIZE){
        throw std::length_error("Roman's lenght is invalid (min 1, max 15)"); 
    }

    auto check = std::set<char>{roman.begin(),roman.end()} ;
    if(! std::includes(ROMAN_NUMERALS.begin(), ROMAN_NUMERALS.end(), check.begin(), check.end())){
        throw std::logic_error("Invalid characters used");
    }

    size_t iter = 0;
    unsigned int result = 0, count = 0;

    for(auto element: ROMAN_SEQ){
        while(roman.find(element.chars, iter) == iter){
            if(++count > element.maxCount){
                throw std::logic_error("Invalid Roman syntax");   
            }
            result += element.value;
            iter += element.chars.size();       
        }  
        count = 0;
    }

    if(iter != roman.size()){
        throw std::logic_error("Invalid Roman syntax");
    }
    
    return result;
}
