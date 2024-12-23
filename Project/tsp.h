#ifndef TSP_H
#define TSP_H

#include <vector>
#include <utility>
#include <random>

using namespace std;

int computeDistance(int i, int j, const vector<pair<double, double>>& points);
vector<vector<int>> computeDistanceMatrix(int N, const vector<pair<double, double>>& points);
int computeTourLength(const vector<int>& tour, const vector<vector<int>>& distanceMatrix);
vector<int> greedyTour(const vector<vector<int>>& distanceMatrix, int start);
bool twoOptSwap(vector<int>& tour, const vector<vector<int>>& distanceMatrix);
vector<int> simulatedAnnealing(vector<int>& tour, const vector<vector<int>>& distanceMatrix, mt19937& rng, double initialTemp, double coolingRate);

#endif // TSP_H
