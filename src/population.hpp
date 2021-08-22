#pragma once
#include "chromosome.hpp"
namespace ga {
template <typename T, std::size_t populationSize, std::size_t geneLength>
class Population {
  static_assert(populationSize > 0,
                "Population size cannot be negative or zero");

public:
  Population();
  Population(const Population<T, populationSize, geneLength> &population);
  Population(Population<T, populationSize, geneLength> &&) = delete;
  Population &
  operator=(const Population<T, populationSize, geneLength> &population);
  Population &operator=(Population<T, populationSize, geneLength> &&) = delete;
  void RegisterChromosomeGenerator(
      std::function<void(Chromosome<T, geneLength> &)> f);
  void
  RegisterFitnessFunction(std::function<void(Chromosome<T, geneLength> &)> f);
  void GeneratePopulation();
  void EvaluatePopulation();

private:
  std::array<Chromosome<T, geneLength>, populationSize> aChromosomePopulation;
  std::function<void(Chromosome<T, geneLength> &)> fChromosomeGenerator;
  std::function<void(Chromosome<T, geneLength> &)> fFitnessFunction;
};

template <typename T, std::size_t populationSize, std::size_t geneLength>
Population<T, populationSize, geneLength>::Population() {
  aChromosomePopulation.fill(Chromosome<T, geneLength>());
}

template <typename T, std::size_t populationSize, std::size_t geneLength>
Population<T, populationSize, geneLength>::Population(
    const Population<T, populationSize, geneLength> &population) {
  aChromosomePopulation = population.aChromosomePopulation;
  fChromosomeGenerator = population.fChromosomeGenerator;
}

template <typename T, std::size_t populationSize, std::size_t geneLength>
Population<T, populationSize, geneLength> &
Population<T, populationSize, geneLength>::operator=(
    const Population<T, populationSize, geneLength> &population) {
  aChromosomePopulation = population.aChromosomePopulation;
  fChromosomeGenerator = population.fChromosomeGenerator;
}

template <typename T, std::size_t populationSize, std::size_t geneLength>
void Population<T, populationSize, geneLength>::RegisterChromosomeGenerator(
    std::function<void(Chromosome<T, geneLength> &)> f) {
  fChromosomeGenerator = f;
}

template <typename T, std::size_t populationSize, std::size_t geneLength>
void Population<T, populationSize, geneLength>::RegisterFitnessFunction(
    std::function<void(Chromosome<T, geneLength> &)> f) {
  fFitnessFunction = f;
}

template <typename T, std::size_t populationSize, std::size_t geneLength>
void Population<T, populationSize, geneLength>::GeneratePopulation() {
  std::for_each(aChromosomePopulation.begin(), aChromosomePopulation.end(),
                fChromosomeGenerator);
}
template <typename T, std::size_t populationSize, std::size_t geneLength>
void Population<T, populationSize, geneLength>::EvaluatePopulation() {
  std::for_each(aChromosomePopulation.begin(), aChromosomePopulation.end(),
                fFitnessFunction);
}
} // namespace ga
