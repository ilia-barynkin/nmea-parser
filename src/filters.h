#ifndef BUTTERWORTH_FILTER_H
#define BUTTERWORTH_FILTER_H

typedef struct butterworth_filter {
    int order;
    int cutoff_frequency;
    int sampling_frequency;

    float* a_coefficients;
    float* b_coefficients;
} butterworth_filter;

#endif // BUTTERWORTH_FILTER_H