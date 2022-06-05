#include <iostream>
#include <curl/curl.h>
#include <vector>
#include "histogram.h"
#include "svg.h"

using namespace std;

struct Input {
    vector<double> numbers;
    size_t bin_count;
};

vector<double>input_numbers(istream& in, size_t count)
{
    vector<double> result(count);
    for (size_t i = 0; i < count; i++)
    {
        in >> result[i];
    }
    return result;
}

Input
read_input(istream& in,bool prompt) {
    Input data;

    if (prompt)
        cerr << "Enter number count: ";
    size_t number_count;
    in >> number_count;

    if (prompt)
        cerr << "Enter numbers: ";
    data.numbers = input_numbers(in, number_count);

    if (prompt)
        cerr << "Enter bin_count:";
    in >> data.bin_count;

    return data;
}

int main(int argc, char* argv[])
{
    if (argc > 1){
        CURL *curl = curl_easy_init();
        if (curl) {
            CURLcode res;
            curl_easy_setopt(curl, CURLOPT_URL, argv[1]);
            res = curl_easy_perform(curl);
            if(res != CURLE_OK){
                fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
                exit(1);
            }
            curl_easy_cleanup(curl);
        }
        return 0;
    }

    curl_global_init(CURL_GLOBAL_ALL);

    const auto input = read_input(cin, true);

    const auto bins = make_histogram(input);

    show_histogram_svg(bins);

    return 0;
}
