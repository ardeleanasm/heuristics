#pragma once

namespace ga {
    enum class SelectionMechanism:std::uint8_t {
	TOURNAMENT_SELECTION = 0,
	ROULETTE_SELECTION
    };
    struct Config
    {
	std::size_t geneLength;
	std::size_t populationSize;
	std::size_t numberOfGenerations;
	std::size_t tournamentSize;
	double crossoverRate;
	double mutationProbability;
	bool useElitism;
	double bestFitnessValue;
	enum SelectionMechanism selectionMechanism;
    };
    template<typename T, Config conf> 
        class Chromosome;

    template<typename T, Config conf> 
	class Population;

    template<typename T,Config conf>
	class GeneticAlgorithm;

    template<typename T, Config conf>
	class Selection;

    template<typename T, Config conf>
	class TournamentSelection;

    template<typename T, Config conf>
	class SelectionObjectAbstractFactory;

    template<typename T, Config conf>
	class SelectionObjectFactory;
    template<unsigned int N> class Randomize;

}

#include "utilities.hpp"
#include "chromosome.hpp"
#include "population.hpp"
#include "geneticalgorithm.hpp"
#include "selection.hpp"
