#include <iostream>
#include <random>
#include <vector>
#include <chrono>

#include "learned_sort.h"
#include "radix_sort.h"

using namespace std;
using namespace std::chrono;

int main(int argc, char *argv[])
{
    // Define some constants
    static constexpr size_t INPUT_SIZE = 1e6;
    static constexpr int MIN_KEY = 0;
    static constexpr int MAX_KEY = 1;
    static constexpr int MEAN = 0;
    static constexpr int STD = 1;

    // Generate some random uniformly distributed data
    std::random_device rd;
    std::mt19937 g(rd());
    //std::uniform_real_distribution <> distribution(MIN_KEY, MAX_KEY);
    std::normal_distribution <> distribution(MEAN, STD);
    
    // Populate the input
    std::vector<double> arr1;
    std::vector<double> arr2;
    std::vector<double> arr3;
    double x;
    for (int i = 0; i < INPUT_SIZE; i++) 
    {
        x = distribution(g);
        arr1.push_back(x);
        arr2.push_back(x);
        arr3.push_back(x);
    }

    //TwoLayerRMI<double>::Params p;
    //TwoLayerRMI<double>::Params p (0.01, 1.1, 1000, 10, 100, {1,1000});

    // Sorting before algorithms
    //std::sort(arr1.begin(), arr1.end()); // sorting in ascending order
    //std::sort(arr2.begin(), arr2.end()); // sorting in ascending order
    //std::sort(arr1.begin(), arr1.end(), greater<int>()); // sorting in descending order
    //std::sort(arr2.begin(), arr2.end(), greater<int>()); // sorting in descending order

    // Starting sorting LearnedSort
    cout << "Starting sorting with LearnedSort..." << endl;
    auto start = high_resolution_clock::now();

    learned_sort::sort(arr1.begin(), arr1.end());

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    if(std::is_sorted(arr1.begin(), arr1.end()))
        std::cout << "Finished!" << std::endl;
    
    cout << "Time taken with LearnedSort: " << duration.count() << " microseconds" << endl;

    // Starting sorting with RadixSort
    cout << "Starting sorting with RadixSort..." << endl;
    start = high_resolution_clock::now();

    radix_sort(arr2.begin(), arr2.end());

    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);

    if(std::is_sorted(arr2.begin(), arr2.end()))
        std::cout << "Finished!" << std::endl;

    cout << "Time taken with RadixSort: " << duration.count() << " microseconds" << endl;

    // Starting sorting with stdsort
    cout << "Starting sorting with std::sort..." << endl;
    start = high_resolution_clock::now();

    std::sort(arr3.begin(), arr3.end());

    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);

    if(std::is_sorted(arr3.begin(), arr3.end()))
        std::cout << "Finished!" << std::endl;

    cout << "Time taken with std::sort: " << duration.count() << " microseconds" << endl;

}
