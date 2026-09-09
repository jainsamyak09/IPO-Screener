#pragma once

#include "IPO.h"
#include "C:\Users\Lenovo\Desktop\IPO-Screener\include/json.hpp"
#include <vector>
#include <string>

using json = nlohmann::json;

double toDouble(const std::string& value);

double extractGMP(const std::string& gmpHTML);

IPO createIPO(const json& data);

std::vector<IPO> filterIPOs(const json& data, double minGMP);

double est_listing_price(const IPO& ipo);

double est_listing_gain(const IPO& ipo);