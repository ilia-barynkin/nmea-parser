#ifndef BUTTERWORTH_FILTER_HPP
#define BUTTERWORTH_FILTER_HPP

#include <iostream>
#include <cmath>
#include <vector>

template <typename T>
class LowPassFilter {
public:
    virtual T operator()(const T& input) const = 0;
    virtual ~LowPassFilter();
};

template <typename T>
class ButterworthFilter : public LowPassFilter<T> {
public:
    ButterworthFilter(int order = 4, T cutoffFrequency = 5, T samplingFrequency = 5 * 4.41);
    ButterworthFilter::ButterworthFilter(int order, T cutoffFrequency, T samplingFrequency) :
        order(order), cutoffFrequency(cutoffFrequency), samplingFrequency(samplingFrequency), 
        bCoefficients(order), aCoefficients(order) {    
            T wc = 2.0 * M_PI * cutoffFrequency / samplingFrequency;
            T c = 1.0 / tan(wc / 2.0);
            T sqrt2 = sqrt(2.0);
            T a0 = pow(sqrt2, order - 1) * c;

            for (int i = 0; i < order; ++i) {
                bCoefficients[i] = pow(c, order - 1 - i) / a0;
                aCoefficients[i] = pow(sqrt2, order - 1 - i) * c / a0;
            }
    }

    T operator()(const T& input) const override {
         output = 0.0;

        for (int i = 0; i < order; ++i) {
            output += (bCoefficients[i] * input);
            input = input - (aCoefficients[i] * output);
        }

        return output;
    };

private:
    int order;              
    T cutoffFrequency; 
    T samplingFrequency;

    std::vector<T> bCoefficients;
    std::vector<T> aCoefficients;
};

#endif // BUTTERWORTH_FILTER_HPP