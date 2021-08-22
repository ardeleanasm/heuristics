#include <fmt/core.h>
#include <spdlog/spdlog.h>

#include "heuristics.hpp"

void chromosomeGenerator(ga::Chromosome<double,8> &chromosome)
{
    ga::Randomize<8> rndGenerator;
    std::uint8_t rndGene = rndGenerator.generate();
    chromosome.SetGenes(ga::UintToString<std::uint8_t>(rndGene));
    spdlog::info("Gene generated!");
}

void fitnessFunction(ga::Chromosome<double,8> &chromosome)
{
    
    spdlog::info("Gene:{0}",chromosome.GetGenes());
}

int main(int argc,char **argv)
{
/*
    ga::Chromosome<double,8> c1;
    c1.Initialize();    
    spdlog::info(c1.GetGenes());
*/
/*
    ga::Population<double, 10,8> p1;
    p1.RegisterChromosomeGenerator(chromosomeGenerator);
    p1.RegisterChromosomeGenerator(std::bind(&chromosomeGenerator,std::placeholders::_1));
    p1.GeneratePopulation();
*/
    ga::GeneticAlgorithm<double,10,8>galgo(chromosomeGenerator,fitnessFunction);
    galgo.Initialize();
    galgo.Run();
    return 0;
}
