# Master of Delays

This project analyzes flight delay data to determine the likelihood of delays at many airports in the US during specific months. It utilizes hash tables to compare performance and uses a CSV parser to handle input data.

## Prerequisites

Before you begin, ensure you have met the following requirements:
- You have a modern C++ compiler that supports C++11 (e.g., GCC, Clang).
- You have installed the csv-parser library.

## Installing csv-parser

To install csv-parser, add the library to your project. You can clone it directly from the GitHub repository:

git clone https://github.com/vincentlaucsb/csv-parser.git

## To Run Project
- cd src
- ./FlightStatsApp

## Example Run

- Enter the airport code: LAX
- Enter the year/month (e.g., 2012/07): 2010/05
- Likelihood of delay at airport LAX in 2010/05 is 16.6253%
- Unordered map lookup time: 4 microseconds
- Ordered map lookup time: 2 microseconds