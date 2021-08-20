#include <fmt/core.h>
#include <spdlog/spdlog.h>

#include "heuristics.hpp"

int main(int argc,char **argv)
{
    ga::Chromosome<double,8> c1;
    c1.Initialize();    
    spdlog::info(c1.GetGenes());
    return 0;
}
