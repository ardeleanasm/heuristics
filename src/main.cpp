#include <fmt/core.h>
#include <spdlog/spdlog.h>

#include "heuristics.hpp"


static constexpr ga::Config conf={
	.geneLength = 8,
	.populationSize = 1000,
	.numberOfGenerations = 10000,
	.tournamentSize = 100,
	.crossoverRate = 0.892,
	.mutationProbability = 0.2,
	.useElitism = false,
	.bestFitnessValue = 8
    };

void chromosomeGenerator(ga::Chromosome<double,conf> &chromosome)
{
    ga::Randomize<8> rndGenerator;
    std::uint8_t rndGene = rndGenerator.generate();
    chromosome.SetGenes(ga::UintToString<std::uint8_t>(rndGene));
}

void fitnessFunction(ga::Chromosome<double,conf> &chromosome)
{
    std::string genes = chromosome.GetGenes();
    double fitValue = 0.0;
    std::for_each(genes.begin(),genes.end(),[&fitValue](char const &c){
	if (c =='1') fitValue++;
    });
    chromosome.SetFitnessValue(fitValue);
}

int main(int argc,char **argv)
{
    spdlog::set_level(spdlog::level::debug); // Set global log level to debug
    ga::GeneticAlgorithm<double,conf>galgo(chromosomeGenerator,fitnessFunction);
    galgo.Initialize();
    galgo.Run();
    /*std::size_t position = ga::uniform<std::size_t>(0,conf.geneLength);
    spdlog::warn("Position:{0}",position);*/
    return 0;
}
