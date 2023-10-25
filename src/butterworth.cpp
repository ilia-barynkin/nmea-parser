#include <iostream>
#include <cmath>

// Рекурсивная реализация фильтра Баттерворта
class ButterworthFilter {
public:
    ButterworthFilter(int order, double cutoffFrequency, double samplingFrequency) {
        this->order = order;
        this->cutoffFrequency = cutoffFrequency;
        this->samplingFrequency = samplingFrequency;

        // Рассчитываем коэффициенты фильтра
        calculateCoefficients();
    }

    double filter(double input) {
        double output = 0.0;

        // Применяем фильтр к входному сигналу
        for (int i = 0; i < order; ++i) {
            output += bCoefficients[i] * input;
            input = input - aCoefficients[i] * output;
        }

        return output;
    }

private:
    int order;              // Порядок фильтра
    double cutoffFrequency; // Частота среза
    double samplingFrequency; // Частота дискретизации

    // Коэффициенты фильтра
    double* bCoefficients;
    double* aCoefficients;

    // Расчет коэффициентов фильтра
    void calculateCoefficients() {
        bCoefficients = new double[order];
        aCoefficients = new double[order];

        double wc = 2.0 * M_PI * cutoffFrequency / samplingFrequency;
        double c = 1.0 / tan(wc / 2.0);
        double sqrt2 = sqrt(2.0);

        for (int i = 0; i < order; ++i) {
            bCoefficients[i] = 0.0;
            aCoefficients[i] = 0.0;
        }

        for (int i = 0; i < order; ++i) {
            bCoefficients[i] = pow(c, order - 1 - i);
            aCoefficients[i] = pow(sqrt2, order - 1 - i) * c;
        }

        // Нормализуем коэффициенты фильтра
        double a0 = aCoefficients[0];
        for (int i = 0; i < order; ++i) {
            bCoefficients[i] /= a0;
            aCoefficients[i] /= a0;
        }
    }
};

int main() {
    // Параметры фильтра
    int order = 4;
    double cutoffFrequency = 1000.0;
    double samplingFrequency = 44100.0;

    // Создание экземпляра фильтра
    ButterworthFilter filter(order, cutoffFrequency, samplingFrequency);

    // Пример использования фильтра
    double inputSignal = 0.5;
    double filteredSignal = filter.filter(inputSignal);

    std::cout << "Filtered Signal: " << filteredSignal << std::endl;

    return 0;
}