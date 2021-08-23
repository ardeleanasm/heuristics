#pragma once

namespace ga {
    template<typename T, std::size_t geneLength> 
        class Chromosome;

    template<typename T, std::size_t populationSize,std::size_t geneLength> 
	class Population;

    template<typename T,std::size_t populationSize,std::size_t geneLength,std::size_t numberOfGenerations>
	class GeneticAlgorithm;

    template<typename T, std::size_t populationSize, std::size_t geneLength>
	class SelectionMechanism;

    template<unsigned int N> class Randomize;

}

#include "utilities.hpp"
#include "chromosome.hpp"
#include "population.hpp"
#include "geneticalgorithm.hpp"
#include "selection.hpp"
