#include "tsp.h"
#include <iostream>
#include <chrono>
#include <random>
#include <limits>

int main() {
    int N;
    cin >> N;

    vector<pair<double, double>> points(N);
    for (int i = 0; i < N; ++i) {
        cin >> points[i].first >> points[i].second;
    }

    vector<vector<int>> distanceMatrix = computeDistanceMatrix(N, points);

    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

    vector<int> bestTour;
    int bestLength = numeric_limits<int>::max();

    for (int attempt = 0; attempt < 91; ++attempt) {
        auto tour = greedyTour(distanceMatrix, attempt % N);
        auto saTour = simulatedAnnealing(tour, distanceMatrix, rng, 1000.0, 0.995);

        while (twoOptSwap(saTour, distanceMatrix));

        int tourLength = computeTourLength(saTour, distanceMatrix);
        if (tourLength < bestLength) {
            bestLength = tourLength;
            bestTour = saTour;
        }
    }

    for (int node : bestTour) {
        cout << node << "\n";
    }

    return 0;
}
