#pragma once

namespace ga
{
    template <typename T,std::size_t populationSize, std::size_t geneLength,std::size_t numberOfGenerations>
    class GeneticAlgorithm
    {
	public:
	    GeneticAlgorithm(
		    std::function<void(Chromosome<T,geneLength> &)> chromosomeGenerator,
		    std::function<void(Chromosome<T,geneLength> &)> fitnessFunction
		    );
	    void Initialize();
	    void Run();
	private:
	    void Crossover();
	    void Mutate();
	    void Evolve();
	    void SelectIndividual();
	    Population<T,populationSize,geneLength> gPopulation;
	    std::function<void(Chromosome<T,geneLength> &)> fChromosomeGenerator;
	    std::function<void(Chromosome<T,geneLength> &)> fFitnessFunction;
	    static constexpr std::size_t nNumberOfGenerations = numberOfGenerations;
    };


template <typename T, std::size_t populationSize,std::size_t geneLength,std::size_t numberOfGenerations>
GeneticAlgorithm<T,populationSize,geneLength,numberOfGenerations>::GeneticAlgorithm(
	std::function<void(Chromosome<T,geneLength> &)> chromosomeGenerator,
	std::function<void(Chromosome<T,geneLength> &)> fitnessFunction
	)
{
    fChromosomeGenerator = chromosomeGenerator;
    fFitnessFunction = fitnessFunction;
}


template <typename T, std::size_t populationSize, std::size_t geneLength,std::size_t numberOfGenerations>
void GeneticAlgorithm<T,populationSize,geneLength,numberOfGenerations>::Initialize()
{
    gPopulation=Population<T,populationSize,geneLength>();
    gPopulation.RegisterChromosomeGenerator(fChromosomeGenerator);
    gPopulation.RegisterFitnessFunction(fFitnessFunction);
    gPopulation.GeneratePopulation();
    gPopulation.EvaluatePopulation();
}


template <typename T, std::size_t populationSize, std::size_t geneLength,std::size_t numberOfGenerations>
void GeneticAlgorithm<T,populationSize,geneLength,numberOfGenerations>::Run()
{
    std::size_t generationNumber = 0;
    auto bestIndividual = gPopulation.GetBestChromosome();
    spdlog::info("Best individual:{0}",bestIndividual.GetGenes());
    
    for(;generationNumber<nNumberOfGenerations;generationNumber++) {
	Evolve();
	bestIndividual = gPopulation.GetBestChromosome();
    }
}


template <typename T, std::size_t populationSize, std::size_t geneLength,std::size_t numberOfGenerations>
void GeneticAlgorithm<T, populationSize, geneLength, numberOfGenerations>::Evolve()
{
    Population<T,populationSize,geneLength>newPopulation;
    for (auto &item: gPopulation.GetPopulation())  {
	/* TODO: Implement iterator for population in order to avoid iterating on the
	 * contained structure.
	 * */
//	auto firstIndividual = SelectIndividual();
	SelectIndividual();
    }
}


template <typename T, std::size_t populationSize, std::size_t geneLength,std::size_t numberOfGenerations>
void GeneticAlgorithm<T, populationSize, geneLength, numberOfGenerations>::Crossover()
{
}


template <typename T, std::size_t populationSize, std::size_t geneLength,std::size_t numberOfGenerations>
void GeneticAlgorithm<T, populationSize, geneLength, numberOfGenerations>::Mutate()
{
}

template <typename T, std::size_t populationSize, std::size_t geneLength,std::size_t numberOfGenerations>
void GeneticAlgorithm<T, populationSize, geneLength, numberOfGenerations>::SelectIndividual()
{ /* TODO: Selection is currently hardcoded to tournament. Allow user to choose from
     a list of available selections. (Decorator Pattern for a class Selection.
*/
    std::size_t tournamentSize = 2;
    Population<T,populationSize,geneLength> newPopulation;
    for(std::size_t i; i<tournamentSize;i++) {
	auto randomIndividualIndex= uniform<std::size_t>(0,populationSize); 
    }
}


}
