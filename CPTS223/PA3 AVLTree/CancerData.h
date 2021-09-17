#ifndef CANCERDATA_H
#define CANCERDATA_H

#include <iostream>
#include <string>

class CancerData 
{
    private:
    std::string country;
    float rate;

    public:
    CancerData(std::string s, float f);
    ~CancerData() {}

    bool operator==(CancerData& a);
    bool operator<(CancerData& b);
    bool operator>(CancerData& b);
    friend std::ostream& operator<<(std::ostream& output, const CancerData& n);
    

};

#endif