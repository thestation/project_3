// FlightStats.h
#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <map>

using namespace std;

struct FlightStats {
    string airportCode;
    string airportName;
    int month;
    int year;
    int totalDelays;
    int totalFlights;
    int minutesDelayed;

    FlightStats(string code, string name, int mon, int yr, int delays, int flights, int minutes);
};

typedef unordered_map<string, vector<FlightStats>> StatsMap;
typedef map<string, vector<FlightStats>> OrderedStatsMap;

void loadCSVData(const string& filename, StatsMap& stats, OrderedStatsMap& orderedStats);
double computeDelayLikelihood(const vector<FlightStats>& stats);