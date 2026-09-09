# IPO Screener

A C++ command-line application that fetches live IPO data and filters IPOs based on GMP and IPO status.

## Features

- Fetches IPO data from the internet using libcurl
- Parses JSON using nlohmann/json
- Filters Mainboard IPOs
- Filters currently open IPOs
- Filters IPOs based on minimum GMP percentage
- Extracts GMP amount
- Calculates estimated listing price
- Calculates estimated listing gain
- Sorts IPOs by GMP

## Technologies

- C++
- libcurl
- nlohmann/json
- HTTP
- JSON
- Git & GitHub

## How It Works

The program:

1. Fetches IPO data from InvestorGain.
2. Parses the JSON response.
3. Converts the raw data into `IPO` objects.
4. Filters Mainboard IPOs that are currently open.
5. Filters them based on the minimum GMP percentage entered by the user.
6. Calculates the estimated listing price and listing gain.
7. Displays the results sorted by GMP.

## Example

```text
Enter minimum GMP Percentage :
10

ESDS Software Solution
GMP : 72.49%
Estimated Listing Price : ₹740
Estimated Listing Gain : 72.49%

##Disclaimer

GMP (Grey Market Premium) is unofficial market information and should not be considered a guaranteed prediction of listing price or investment returns.