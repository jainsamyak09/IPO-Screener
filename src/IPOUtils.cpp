#include "C:\Users\Lenovo\Desktop\IPO-Screener\include\IPOUtils.h"
#include <bits/stdc++.h>
#include <stdexcept>
#include <curl/curl.h>
#include "C:\Users\Lenovo\Desktop\IPO-Screener\include/json.hpp"
#include<algorithm>

using namespace std;

double toDouble(const string &value)
{
    try
    {
        return stod(value);
    }
    catch (const invalid_argument &)
    {
        return 0.0;
    }
    catch (const out_of_range &)
    {
        return 0.0;
    }
}

double extractGMP(const string& gmpHTML){
    size_t start = gmpHTML.find("<b>");
    size_t end = gmpHTML.find("</b>");

    if(start == string::npos || end == string::npos){
        return 0.0;
    }

    start +=3;

    string gmpValue = gmpHTML.substr(start, end - start);

    return toDouble(gmpValue);
}

IPO createIPO(const json &data)
{
    IPO ipo;

    // Text fields
    ipo.name = data.value("~ipo_name", "Unknown");

    ipo.ipoSize = data.value("IPO Size", "Unknown");

    ipo.openDate = data.value("~Srt_Open", "Unknown");

    ipo.closeDate = data.value("~Srt_Close", "Unknown");

    ipo.listingDate = data.value("~Str_Listing", "Unknown");

    ipo.status = data.value("~ipo_status1", "Unknown");

    // Numeric fields
    ipo.gmpPercent =
        toDouble(data.value("~gmp_percent_calc", "0"));

    ipo.gmpAmount =
        extractGMP(data.value("GMP", ""));

    ipo.issuePrice =
        toDouble(data.value("Price (₹)", "0"));

    return ipo;
}

double est_listing_price(const IPO& ipo){
    double lis_price = ipo.issuePrice + ipo.gmpAmount;
    return lis_price;
}
double est_listing_gain(const IPO& ipo){
    double lis_gain = (ipo.gmpAmount/ipo.issuePrice)*100;
    return lis_gain;
}

vector<IPO> filterIPOs(const json& data, double minGMP){
    vector<IPO> result;

    for(auto& item : data["reportTableData"]){
        if(item["~IPO_Category"] != "IPO")
        {
            continue;
        }

        try
        {
            IPO currentIPO = createIPO(item);

            if(currentIPO.gmpPercent > minGMP && currentIPO.status == "O")
            {
                
                result.push_back(currentIPO);
            }
        }
        catch(const exception& e)
        {
            continue;
        }
    }
    return result;
}