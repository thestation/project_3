#include "FlightStats.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include "csv.hpp"

// Constructor for FlightStats object with flight information
FlightStats::FlightStats(string code, string name, int mon, int yr, int delays, int flights, int minutes)
    : airportCode(code), airportName(name), month(mon), year(yr), totalDelays(delays), totalFlights(flights), minutesDelayed(minutes) {}

// Loads data from a CSV file into both maps
void loadCSVData(const string& filename, StatsMap& stats, OrderedStatsMap& orderedStats) {
    csv::CSVReader reader(filename);

    // Goes over each row of the CSV file
    for (auto& row : reader) {
        // Parse columns from the CSV file
        string timeLabel = row["Time.Label"].get<>();
        int month = row["Time.Month"].get<int>();
        int year = row["Time.Year"].get<int>();
        int carrierDelays = row["Statistics.# of Delays.Carrier"].get<int>();
        int lateAircraftDelays = row["Statistics.# of Delays.Late Aircraft"].get<int>();
        int nationalAviationSystemDelays = row["Statistics.# of Delays.National Aviation System"].get<int>();
        int securityDelays = row["Statistics.# of Delays.Security"].get<int>();
        int weatherDelays = row["Statistics.# of Delays.Weather"].get<int>();
        int totalDelays = carrierDelays + lateAircraftDelays + nationalAviationSystemDelays + securityDelays + weatherDelays;

        int totalFlights = row["Statistics.Flights.Total"].get<int>();
        int carrierMinutesDelayed = row["Statistics.Minutes Delayed.Carrier"].get<int>();
        int lateAircraftMinutesDelayed = row["Statistics.Minutes Delayed.Late Aircraft"].get<int>();
        int nationalAviationSystemMinutesDelayed = row["Statistics.Minutes Delayed.National Aviation System"].get<int>();
        int securityMinutesDelayed = row["Statistics.Minutes Delayed.Security"].get<int>();
        int weatherMinutesDelayed = row["Statistics.Minutes Delayed.Weather"].get<int>();
        int totalMinutesDelayed = carrierMinutesDelayed + lateAircraftMinutesDelayed + nationalAviationSystemMinutesDelayed + securityMinutesDelayed + weatherMinutesDelayed;

        // Create FlightStats object with the csv data
        FlightStats flightStats(
            row["Airport.Code"].get<>(),
            row["Airport.Name"].get<>(),
            month,
            year,
            totalDelays,
            totalFlights,
            totalMinutesDelayed
        );

        // Store in both maps
        stats[timeLabel].push_back(flightStats);
        orderedStats[timeLabel].push_back(flightStats);
    }

}

// Calculates the likelihood of flight delays and returns a percentage
double computeDelayLikelihood(const vector<FlightStats>& stats) {
    int totalDelays = 0, totalFlights = 0;
    
    // Sum delays and flights across all provided statistics
    for (auto& stat : stats) {
        totalDelays += stat.totalDelays;
        totalFlights += stat.totalFlights;
    }

    // Return the percentage of flights delayed
    return totalFlights > 0 ? static_cast<double>(totalDelays) / totalFlights * 100.0 : 0.0;
}


