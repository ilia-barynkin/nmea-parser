#ifndef BUTTERWORTH_FILTER_H
#define BUTTERWORTH_FILTER_H

typedef struct butterworth_filter {
    int order;
    int cutoff_frequency;
    int sampling_frequency;

    float* a_coefficients;
    float* b_coefficients;
} butterworth_filter;

butterworth_filter* init_butterworth_filter(int order, float cutoffFrequency, float samplingFrequency);
float apply_butterworth_filter(butterworth_filter* filter, float input);
void butterworth_filter_free(butterworth_filter* filter);
void butterworth_filter_free(butterworth_filter* filter);

#endif // BUTTERWORTH_FILTER_H