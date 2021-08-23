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
  Population(Population<T, populationSize, geneLength> &&population);
  Population &operator=(const Population<T, populationSize, geneLength> &population);
  Population &operator=(Population<T, populationSize, geneLength> &&population);
  void RegisterChromosomeGenerator(
      std::function<void(Chromosome<T, geneLength> &)> f);
  void
  RegisterFitnessFunction(std::function<void(Chromosome<T, geneLength> &)> f);
  void GeneratePopulation();
  void EvaluatePopulation();
  [[nodiscard]] std::array<Chromosome<T,geneLength>,populationSize> GetPopulation() const {
      return aChromosomePopulation;
  }
  void SetChromosome(const Chromosome<T,geneLength> &c, const std::size_t position);
  Chromosome<T,geneLength> GetBestChromosome() const;

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
  fFitnessFunction = population.fFitnessFunction;
}

template <typename T, std::size_t populationSize, std::size_t geneLength>
Population<T, populationSize, geneLength>::Population(
    Population<T, populationSize, geneLength> &&population) {
  aChromosomePopulation = population.aChromosomePopulation;
  fChromosomeGenerator = population.fChromosomeGenerator;
  fFitnessFunction = population.fFitnessFunction;
}

template <typename T, std::size_t populationSize, std::size_t geneLength>
Population<T, populationSize, geneLength> &
Population<T, populationSize, geneLength>::operator=(
    const Population<T, populationSize, geneLength> &population) {
  aChromosomePopulation = population.aChromosomePopulation;
  fChromosomeGenerator = population.fChromosomeGenerator;
  fFitnessFunction = population.fFitnessFunction;
  return *this;
}

template <typename T, std::size_t populationSize, std::size_t geneLength>
Population<T, populationSize, geneLength> &
Population<T, populationSize, geneLength>::operator=(
    Population<T, populationSize, geneLength> &&population) {
  aChromosomePopulation = population.aChromosomePopulation;
  fChromosomeGenerator = population.fChromosomeGenerator;
  fFitnessFunction = population.fFitnessFunction;
  return *this;
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

template <typename T, std::size_t populationSize, std::size_t geneLength>
void Population<T,populationSize,geneLength>::SetChromosome(const Chromosome<T,geneLength> &c, const std::size_t position)
{
    assert(position>=0 && position<populationSize);
    aChromosomePopulation[position] = c;
}

template <typename T, std::size_t populationSize, std::size_t geneLength>
Chromosome<T,geneLength> Population<T,populationSize,geneLength>::GetBestChromosome() const
{
    auto chromosome = std::max_element(aChromosomePopulation.begin(),aChromosomePopulation.end(),[](const auto &lhs, const auto &rhs){
	    return lhs.GetFitnessValue() < rhs.GetFitnessValue(); 
	    });

    return static_cast<Chromosome<T,geneLength>>(*chromosome);
}


} // namespace ga

