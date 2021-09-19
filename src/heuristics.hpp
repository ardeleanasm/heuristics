#pragma once

namespace ga {
struct Config {
  std::size_t geneLength;
  std::size_t populationSize;
  std::size_t numberOfGenerations;
  std::size_t tournamentSize;
  double crossoverRate;
  double mutationProbability;
  bool useElitism;
  double bestFitnessValue;
  uint8_t selectionMechanism;
};
template <typename T, Config conf> class Chromosome;

template <typename T, Config conf> class Population;

template <typename T, Config conf> class GeneticAlgorithm;

template <typename T, Config conf> class Selection;

template <typename T, Config conf> class TournamentSelection;

template <typename T, Config conf> class SelectionObjectAbstractFactory;

template <typename T, Config conf> class SelectionObjectFactory;
template <unsigned int N> class Randomize;

enum class SelectionMechanism : std::uint8_t {
  TOURNAMENT_SELECTION = 0,
  ROULETTE_SELECTION
};
} // namespace ga

#include "chromosome.hpp"
#include "geneticalgorithm.hpp"
#include "population.hpp"
#include "selection.hpp"
#include "utilities.hpp"
