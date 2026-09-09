#include <bits/stdc++.h>
#include <stdexcept>
#include <curl/curl.h>
// #include "C:\Users\Lenovo\Desktop\IPO-Screener\include/json.hpp"
#include "../include/json.hpp"
#include<algorithm>
// #include "C:\Users\Lenovo\Desktop\IPO-Screener\include\IPOUtils.h"
#include "../include/IPOUtils.h"

using namespace std;
using json = nlohmann::json;

size_t write_callback(
    void *contents,
    size_t size,
    size_t nmemb,
    void *userp)
{
    std::string *output =
        static_cast<std::string *>(userp);

    output->append(
        static_cast<char *>(contents),
        size * nmemb);

    return size * nmemb;
}

int main()
{
    CURL *curl = curl_easy_init();

    if (!curl)
    {
        std::cout << "Curl initialization failed\n";
        return 1;
    }

    std::string response;

    curl_easy_setopt(
        curl,
        CURLOPT_URL,
        "https://webnodejs.investorgain.com/cloud/v2/report/data-read/331/1/9/2026/2026-27/0/all?search=&v=23-18");

    curl_easy_setopt(
        curl,
        CURLOPT_WRITEFUNCTION,
        write_callback);

    curl_easy_setopt(
        curl,
        CURLOPT_WRITEDATA,
        &response);

    CURLcode result = curl_easy_perform(curl);

    json data = json::parse(response);

    curl_easy_cleanup(curl);

    double minGMP;
    cout<<"Enter minimum GMP Percentage : "<<endl;
    cin>>minGMP;

    vector<IPO> matchingIPOs = filterIPOs(data, minGMP);

    sort(matchingIPOs.begin(), matchingIPOs.end(),
    [](const IPO& a, const IPO& b) // -_> lambda function 
    {
        return est_listing_gain(a) > est_listing_gain(b);
    });

    for (auto& item : matchingIPOs)
    {
        cout << "IPO: " << item.name << endl;
        cout << "GMP: " << item.gmpPercent << "%" << endl;
        cout << "GMP Amount: " << item.gmpAmount << endl;
        cout << "Issue Price: " << item.issuePrice << endl;

        cout << "Open: " << item.openDate << endl;
        cout << "Close: " << item.closeDate << endl;
        cout << "Listing: " << item.listingDate << endl;

        cout<<"Estimated Listing Price: "<<est_listing_price(item)<<endl;
        cout<<"Estimated Listing Gain: "<<est_listing_gain(item)<<"%"<<endl;

        cout << "-----------------------------\n";
    }

    return 0;
}


