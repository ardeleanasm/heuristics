#pragma once

namespace ga
{
    template <typename T, Config conf>
    class GeneticAlgorithm
    {
	public:
	    GeneticAlgorithm(
		    std::function<void(Chromosome<T,conf> &)> chromosomeGenerator,
		    std::function<void(Chromosome<T,conf> &)> fitnessFunction
		    );
	    void Initialize();
	    void Run();
	private:
	    void Crossover();
	    void Mutate();
	    void Evolve();
	    void SelectIndividual();
	    Population<T,conf> gPopulation;
	    std::function<void(Chromosome<T,conf> &)> fChromosomeGenerator;
	    std::function<void(Chromosome<T,conf> &)> fFitnessFunction;
	    static constexpr std::size_t nNumberOfGenerations = conf.numberOfGenerations;
    };


template <typename T, Config conf>
GeneticAlgorithm<T,conf>::GeneticAlgorithm(
	std::function<void(Chromosome<T,conf> &)> chromosomeGenerator,
	std::function<void(Chromosome<T,conf> &)> fitnessFunction
	)
{
    fChromosomeGenerator = chromosomeGenerator;
    fFitnessFunction = fitnessFunction;
}


template <typename T, Config conf>
void GeneticAlgorithm<T,conf>::Initialize()
{
    gPopulation=Population<T,conf>();
    gPopulation.RegisterChromosomeGenerator(fChromosomeGenerator);
    gPopulation.RegisterFitnessFunction(fFitnessFunction);
    gPopulation.GeneratePopulation();
    gPopulation.EvaluatePopulation();
}


template <typename T, Config conf>
void GeneticAlgorithm<T,conf>::Run()
{
    std::size_t generationNumber = 0;
    auto bestIndividual = gPopulation.GetBestChromosome();
    spdlog::info("Best individual:{0}",bestIndividual.GetGenes());
    
    for(;generationNumber<nNumberOfGenerations;generationNumber++) {
	Evolve();
	bestIndividual = gPopulation.GetBestChromosome();
    }
}


template <typename T, Config conf>
void GeneticAlgorithm<T, conf>::Evolve()
{
    Population<T,conf>newPopulation;
    for (auto &item: gPopulation.GetPopulation())  {
	/* TODO: Implement iterator for population in order to avoid iterating on the
	 * contained structure.
	 * */
//	auto firstIndividual = SelectIndividual();
	SelectIndividual();
    }
}


template <typename T, Config conf>
void GeneticAlgorithm<T, conf>::Crossover()
{
}


template <typename T, Config conf>
void GeneticAlgorithm<T, conf>::Mutate()
{
}

template <typename T, Config conf>
void GeneticAlgorithm<T, conf>::SelectIndividual()
{ /* TODO: Selection is currently hardcoded to tournament. Allow user to choose from
     a list of available selections. (Decorator Pattern for a class Selection.
*/
    std::size_t tournamentSize = 2;
    Population<T,conf> newPopulation;
    for(std::size_t i; i<tournamentSize;i++) {
	auto randomIndividualIndex= uniform<std::size_t>(0,conf.populationSize); 
    }
}


}
