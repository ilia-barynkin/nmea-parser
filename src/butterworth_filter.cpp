#include "butterworth_filter.hpp"

ButterworthFilter::ButterworthFilter(int order, double cutoffFrequency, double samplingFrequency) {
        this->order = order;
        this->cutoffFrequency = cutoffFrequency;
        this->samplingFrequency = samplingFrequency;

        // Рассчитываем коэффициенты фильтра
        calculateCoefficients();
}

double ButterworthFilter::filter(double input) {
        double output = 0.0;

        // Применяем фильтр к входному сигналу
        output += bCoefficients[0] * input;

        for (int i = 1; i < order; ++i) {
            output += bCoefficients[i] * input;
            input = input - aCoefficients[i] * output;
        }

        return output;
    }

void ButterworthFilter::calculateCoefficients() {
    bCoefficients.resize(order);
    aCoefficients.resize(order);

    double wc = 2.0 * M_PI * cutoffFrequency / samplingFrequency;
    double c = 1.0 / tan(wc / 2.0);
    double sqrt2 = sqrt(2.0);
    double a0 = 0.0;

    for (int i = 0; i < order; ++i) {
        bCoefficients[i] = pow(c, order - 1 - i);
        aCoefficients[i] = pow(sqrt2, order - 1 - i) * c;
        if (i == 0) {
            a0 = aCoefficients[i];
        }
    }

    for (int i = 0; i < order; ++i) {
        bCoefficients[i] /= a0;
        aCoefficients[i] /= a0;
    }
}