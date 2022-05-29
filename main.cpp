#include <iostream>
#include <vector>

using namespace std;

vector<double>input_numbers(size_t count)
{
    vector<double> result(count);
    for (size_t i = 0; i < count; i++)
    {
        cin >> result[i];
    }
    return result;
}

void find_minmax(vector<double> numbers, double& min, double& max)
 {
      for (double number : numbers) {
        if (number < min) {
            min = number;
        }
        if (number > max) {
            max = number;
        }
    }
 }

vector <size_t>make_histogram(const vector<double>& numbers,  size_t &bin_count , double min, double max)
{
    vector <size_t> bins (bin_count);
    for (double number: numbers)
    {
       size_t bin = (size_t)((number-min)/(max-min)*bin_count);
       if (bin==bin_count)
       {
           bin--;
       }
       bins[bin]++;
}
return bins;
}

void show_histogram_text (vector<size_t> bins)
{
    const size_t SCREEN_WIDTH = 80;
    const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;

    size_t max_bins = bins [0];
    for (size_t bin : bins)
    {
        if (bin > max_bins)
        {
            max_bins = bin;
        }
    }
    for (size_t bin : bins)
    {
        size_t height = bin;
        if (max_bins > MAX_ASTERISK)
        {
            height = MAX_ASTERISK * (static_cast<double>(bin) / max_bins);
        }
        if (bin<100)
        {
            cout<< " ";
        }
        if (bin < 10)
        {
            cout<< " ";
        }
        cout << bin << "|";
        for (size_t i=0; i<height; i++)
        {
            cout<<"*";
        }
        cout<<'\n';
    }
}

void svg_begin(double width, double height)
{
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void svg_end()
{
    cout << "</svg>\n";
}

void svg_text(double left, double baseline, string text)
{
    cout << "<text x='" << left << "' y='" << baseline << "'>" << text << "</text>";
}

void svg_rect(double x, double y, double width, double height, string stroke = "black", string fill = "black")
{
    cout << "<rect x='" << x << "' y='" << y << "' width='" << width << "' height='" << height << "' stroke='" << stroke << "' fill='" << fill <<"' />";
}

void show_histogram_svg(const vector<size_t>& bins)
{
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;

    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);

    const auto MAX_BIN_WIDTH = IMAGE_WIDTH - TEXT_WIDTH;

	size_t max_bins_width = bins[0];
	for (size_t bin : bins)
	{
		if (bin > max_bins_width)
		{
			max_bins_width = bin;
		}
	}

	max_bins_width = max_bins_width * BLOCK_WIDTH;

	double top = 0;
	for (size_t bin : bins)
	{
		double bin_width = BLOCK_WIDTH * bin;
		if (max_bins_width >= MAX_BIN_WIDTH)
		{
			bin_width = MAX_BIN_WIDTH * (bin_width / max_bins_width) - 1;
		}

		svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
		svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT, "blue", "#aaffaa");
		top += BIN_HEIGHT;
	}

	svg_end();
}

int main()
{
    size_t number_count;
    cerr << "Enter number count: ";
    cin >> number_count;
    cerr << "Enter numbers: ";
    const auto numbers = input_numbers(number_count);

    size_t bin_count;
    cerr << "Enter bin count: \n";
    cin >> bin_count;

    double min = numbers[0];
    double max = numbers[0];
    find_minmax(numbers, min, max);

    const auto bins = make_histogram(numbers,bin_count , min, max);

    show_histogram_svg(bins);

    return 0;
}
