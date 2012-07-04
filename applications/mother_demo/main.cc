#include <iostream>
#include <libwavelet.h>
#ifndef WIN32
#include <unistd.h>
#endif /* WIN32 */

#define __GNU_LIBRARY__
#include <getopt.h>

namespace {

    NS_WAVELET::FunctorGabor2 gabor2;
    NS_WAVELET::FunctorGabor4 gabor4;
    NS_WAVELET::FunctorGabor8 gabor8;
    NS_WAVELET::FunctorMexicanHat mexicanhat;
    NS_WAVELET::FunctorFrenchHat frenchhat;
    NS_WAVELET::FunctorShannon shannon;
    NS_WAVELET::FunctorHaar haar;

} // namespace anonymous

void Usage() {
    std::cerr << "syntax: "
        << "mother_demo -a<scale parameter> -w<mother wavelet>" << std::endl
        << "scale parameter: This parameter must be unsigned integer value." << std::endl
        << "mother wavelet: This parameter must be chosen shown below:" << std::endl
        << "  - gabor2" << std::endl
        << "  - gabor4" << std::endl
        << "  - gabor8" << std::endl
        << "  - mexicanhat" << std::endl
        << "  - frenchhat" << std::endl
        << "  - shannon" << std::endl
        << "  - haar" << std::endl;
}

void PrintAggregator(NS_WAVELET::TraitsComplex::UnitAggregator& ua) {
    NS_WAVELET::TraitsComplex::UnitAggregator::const_iterator iter;
    for (iter = ua.begin(); iter != ua.end(); iter++)
        std::cout << *iter << std::endl;
}

void PrintAggregator(NS_WAVELET::TraitsReal::UnitAggregator& ua) {
    NS_WAVELET::TraitsReal::UnitAggregator::const_iterator iter;
    for (iter = ua.begin(); iter != ua.end(); iter++)
        std::cout << *iter << std::endl;
}

int main(int argc, char* argv[]) 
{
    int ch;
    int scale = -1;
    std::string mother;

    while ((ch = getopt(argc, argv, "a:w:")) != -1) {
        switch (ch) {
        case 'a':
            scale = atoi(optarg);
            break;
        case 'w':
            mother = optarg;
            break;
        case ':':
        case '?':
            Usage();
            return EXIT_FAILURE;
        }
    }
    
    if (scale <= 0) {
        std::cerr << "Invalid scale." << std::endl;
        Usage();
        return EXIT_FAILURE;
    }

    if (mother == "gabor2") {
        NS_WAVELET::TraitsComplex::UnitAggregator ua;
        gabor2(scale, ua);
        PrintAggregator(ua);
    } else if (mother == "gabor4") {
        NS_WAVELET::TraitsComplex::UnitAggregator ua;
        gabor4(scale, ua);
        PrintAggregator(ua);
    } else if (mother == "gabor8") {
        NS_WAVELET::TraitsComplex::UnitAggregator ua;
        gabor8(scale, ua);
        PrintAggregator(ua);
    } else if (mother == "mexicanhat") {
        NS_WAVELET::TraitsReal::UnitAggregator ua;
        mexicanhat(scale, ua);
        PrintAggregator(ua);
    } else if (mother == "frenchhat") {
        NS_WAVELET::TraitsReal::UnitAggregator ua;
        frenchhat(scale, ua);
        PrintAggregator(ua);
    } else if (mother == "shannon") {
        NS_WAVELET::TraitsReal::UnitAggregator ua;
        shannon(scale, ua);
        PrintAggregator(ua);
    } else if (mother == "haar") {
        NS_WAVELET::TraitsReal::UnitAggregator ua;
        haar(scale, ua);
        PrintAggregator(ua);
    } else {
        std::cerr << "Invalid wavelet type." << std::endl;
        Usage();
        return EXIT_FAILURE;
    }

    return 0;
}
