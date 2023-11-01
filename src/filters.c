#include <errno.h>
#include <stdlib.h>
#include <math.h>

#include "filters.h"

butterworth_filter* init_butterworth_filter(int order, float cutoffFrequency, float samplingFrequency) {
    butterworth_filter* filter = (butterworth_filter*) malloc(sizeof(butterworth_filter));
    if (!filter) {
        errno = ENOMEM;
        return NULL;
    }

    filter->a_coefficients = malloc(order * sizeof(float));
    filter->b_coefficients = malloc(order * sizeof(float));

    if (!filter->a_coefficients || !filter->b_coefficients) {
        free(filter);
        errno = ENOMEM;
        return NULL;
    }

    filter->order = order;
    filter->cutoff_frequency = cutoffFrequency;
    filter->sampling_frequency = samplingFrequency;

    float wc = 2.0 * M_PI * cutoffFrequency / samplingFrequency;
    float c = 1.0 / tan(wc / 2.0);
    float sqrt2 = sqrt(2.0);
    float a0 = pow(sqrt2, order - 1) * c;

    for (int i = 0; i < order; ++i) {
        filter->a_coefficients[i] = pow(c, order - 1 - i) / a0;
        filter->b_coefficients[i] = pow(sqrt2, order - 1 - i) * c / a0;
    }

    return filter;
}

float apply_butterworth_filter(butterworth_filter* filter, float input) {
    float output = 0.f;

    for (int i = 0; i < filter->order; ++i) {
        output += (filter->b_coefficients[i] * input);
        input = input - (filter->a_coefficients[i] * output);
    }

    return output;
}

void butterworth_filter_free(butterworth_filter* filter) {
    free(filter->a_coefficients);
    free(filter->b_coefficients);
    free(filter);
}