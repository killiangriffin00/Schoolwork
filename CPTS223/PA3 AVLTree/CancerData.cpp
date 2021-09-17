#include "CancerData.h"

CancerData::CancerData(std::string s, float f)
{
    country = s;
    rate = f;
}

bool CancerData::operator<(CancerData& b)
{
    return this->rate < b.rate;
}

bool CancerData::operator>(CancerData& b)
{
    return this->rate > b.rate;
}

std::ostream& operator<<(std::ostream &output, const CancerData &n)
{
    output << n.country << ": " << n.rate;
    return output;
}

bool CancerData::operator==(CancerData& a)
{
    return a.country == this->country && a.rate == this->rate;
}