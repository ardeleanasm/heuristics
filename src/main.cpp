#include <fmt/core.h>
#include <spdlog/spdlog.h>

#include "heuristics.hpp"

int main(int argc,char **argv)
{
    const std::string s = "ana";
    const std::string s2 = "ion";
    ga::Chromosome<double,5> c1(s);
    ga::Chromosome<double,5> c2(s2);
    c1 = c2;
    spdlog::info(c1.GetGenes());
    spdlog::info(ga::CALCULATE_MAX_VALUE<8>::value);
    return 0;
}
