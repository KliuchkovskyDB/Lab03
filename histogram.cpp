#include "histogram.h"

struct Input {
	vector<double> numbers;
	size_t bin_count;
};

void find_minmax(vector<double> numbers, double& min, double& max)
 {
    if (numbers.size() == 0) {
        return;
    }
    min = numbers[0];
    max = numbers[0];
    for (double number : numbers) {
        if (number < min) {
            min = number;
        }
        if (number > max) {
            max = number;
        }
    }
 }

vector <size_t>make_histogram(struct Input input)
{
    double min, max;
    find_minmax(input.numbers, min, max);
    vector <size_t> bins (input.bin_count);
    for (double number: input.numbers)
    {
       size_t bin = (size_t)((number-min)/(max-min)*input.bin_count);
       if (bin == input.bin_count)
       {
           bin--;
       }
       bins[bin]++;
}
return bins;
}
