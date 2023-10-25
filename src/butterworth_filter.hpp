#ifndef BUTTERWORTH_FILTER_HPP
#define BUTTERWORTH_FILTER_HPP

#include <iostream>
#include <cmath>
#include <vector>

class ButterworthFilter {
public:
    ButterworthFilter(int order = 4, double cutoffFrequency = 5, double samplingFrequency = 5 * 4.41);

    double filter(double input);

private:
    int order;              
    double cutoffFrequency; 
    double samplingFrequency;

    std::vector<double> bCoefficients;
    std::vector<double> aCoefficients;
    void calculateCoefficients();
};

#endif // BUTTERWORTH_FILTER_HPP