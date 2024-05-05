#include <iostream>
#include <chrono>
#include <algorithm>
#include "FlightStats.h"

using namespace std;
using namespace std::chrono;

int main() {

    // Initialize maps for storing flight stats
    StatsMap Stats;
    OrderedStatsMap orderedStats;

    // Load data from CSV into both maps
    loadCSVData("../data/airlines.csv", Stats, orderedStats);

    // Ask user to enter an airport code
    string airportCode;
    cout << "Enter the airport code: ";
    cin >> airportCode;

    // Ask user to enter the year and month in the format YYYY/MM
    string timeLabel;
    cout << "Enter the year/month (e.g., 2012/07): ";
    cin >> timeLabel;

    // Keep the time it takes to find data in the unordered map
    auto start = high_resolution_clock::now();
    auto it = Stats.find(timeLabel);
    auto end = high_resolution_clock::now();
    auto durationUnordered = duration_cast<microseconds>(end - start);

    // Keep the time it takes to find data in the ordered map
    start = high_resolution_clock::now();
    auto itOrdered = orderedStats.find(timeLabel);
    end = high_resolution_clock::now();
    auto durationOrdered = duration_cast<microseconds>(end - start);

    // Check if data found for the specified time label in both maps
    if (it != Stats.end() && itOrdered != orderedStats.end()) {
        const auto& stats = it->second;
        const auto& orderedStats = itOrdered->second;

        // Find stats for airport code
        auto airportStatsIt = find_if(stats.begin(), stats.end(), [&](const FlightStats& fs) {
            return fs.airportCode == airportCode;
        });

        // When stats are found, display the likelihood of delays
        if (airportStatsIt != stats.end()) {
            double likelihood = computeDelayLikelihood({*airportStatsIt});
            cout << "Likelihood of delay at airport " << airportCode << " in " << timeLabel << " is " << likelihood << "%\n";
        } else {
            cout << "No data available for airport " << airportCode << " in " << timeLabel << "\n";
        }
    } else {
        cout << "No data available for " << timeLabel << "\n";
    }

    // Show the time taken in both map types
    cout << "Unordered map lookup time: " << durationUnordered.count() << " microseconds\n";
    cout << "Ordered map lookup time: " << durationOrdered.count() << " microseconds\n";

    return 0;
}



