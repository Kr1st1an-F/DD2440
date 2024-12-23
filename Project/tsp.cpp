#include "tsp.h"
#include <cmath>
#include <algorithm>
#include <numeric>
#include <chrono>

int computeDistance(int i, int j, const vector<pair<double, double>>& points) {
    double dx = points[i].first - points[j].first;
    double dy = points[i].second - points[j].second;
    return static_cast<int>(round(sqrt(dx * dx + dy * dy)));
}

vector<vector<int>> computeDistanceMatrix(int N, const vector<pair<double, double>>& points) {
    vector<vector<int>> distanceMatrix(N, vector<int>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            distanceMatrix[i][j] = computeDistance(i, j, points);
            distanceMatrix[j][i] = distanceMatrix[i][j];
        }
    }
    return distanceMatrix;
}

int computeTourLength(const vector<int>& tour, const vector<vector<int>>& distanceMatrix) {
    int totalDistance = 0;
    int N = tour.size();
    for (int i = 0; i < N; ++i) {
        totalDistance += distanceMatrix[tour[i]][tour[(i + 1) % N]];
    }
    return totalDistance;
}

vector<int> greedyTour(const vector<vector<int>>& distanceMatrix, int start) {
    int N = distanceMatrix.size();
    vector<int> tour;
    vector<bool> used(N, false);
    int current = start;
    tour.push_back(current);
    used[current] = true;

    for (int i = 1; i < N; ++i) {
        int nearest = -1;
        int min_dist = numeric_limits<int>::max();

        for (int j = 0; j < N; ++j) {
            if (!used[j] && distanceMatrix[current][j] < min_dist) {
                min_dist = distanceMatrix[current][j];
                nearest = j;
            }
        }

        if (nearest != -1) {
            tour.push_back(nearest);
            used[nearest] = true;
            current = nearest;
        }
    }

    return tour;
}

bool twoOptSwap(vector<int>& tour, const vector<vector<int>>& distanceMatrix) {
    int N = tour.size();
    bool improved = false;
    for (int i = 1; i < N - 1; ++i) {
        for (int j = i + 1; j < N; ++j) {
            int a = tour[i - 1];
            int b = tour[i];
            int c = tour[j];
            int d = tour[(j + 1) % N];

            int currentDist = distanceMatrix[a][b] + distanceMatrix[c][d];
            int newDist = distanceMatrix[a][c] + distanceMatrix[b][d];

            if (newDist < currentDist) {
                reverse(tour.begin() + i, tour.begin() + j + 1);
                improved = true;
            }
        }
    }
    return improved;
}

vector<int> simulatedAnnealing(vector<int>& tour, const vector<vector<int>>& distanceMatrix, mt19937& rng, double initialTemp, double coolingRate) {
    vector<int> currentTour = tour;
    int currentLength = computeTourLength(currentTour, distanceMatrix);
    vector<int> bestTour = currentTour;
    int bestLength = currentLength;

    double temperature = initialTemp;
    uniform_int_distribution<int> dist(0, currentTour.size() - 1);

    while (temperature > 1) {
        vector<int> newTour = currentTour;
        int i = dist(rng), j = dist(rng);
        swap(newTour[i], newTour[j]);

        int newLength = computeTourLength(newTour, distanceMatrix);

        if (newLength < currentLength || exp((currentLength - newLength) / temperature) > (rng() % 100) / 100.0) {
            currentTour = newTour;
            currentLength = newLength;
        }

        if (currentLength < bestLength) {
            bestTour = currentTour;
            bestLength = currentLength;
        }

        temperature *= coolingRate;
    }

    return bestTour;
}
