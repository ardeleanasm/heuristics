#pragma once

namespace ga {
    template<typename T, size_t geneLength> 
        class Chromosome;

    template<typename T> 
	class Population;

    template<typename T>
	class GeneticAlgorithm;

}

#include "utilities.hpp"
#include "chromosome.hpp"
#include "population.hpp"
#include "geneticalgorithm.hpp"
