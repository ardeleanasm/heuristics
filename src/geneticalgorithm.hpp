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
	    Population<T,conf> gPopulation;
	    std::function<void(Chromosome<T,conf> &)> fChromosomeGenerator;
	    std::function<void(Chromosome<T,conf> &)> fFitnessFunction;
	    static constexpr std::size_t nNumberOfGenerations = conf.numberOfGenerations;
	    std::shared_ptr<SelectionObjectAbstractFactory<T,conf>> pSelectionObjectFactory;
	    std::shared_ptr<Selection<T,conf>> pSelectionObject;
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

    pSelectionObjectFactory = std::make_shared<SelectionObjectFactory<T,conf>>();
    pSelectionObject = pSelectionObjectFactory->CreateSelectionObject();


}


template <typename T, Config conf>
void GeneticAlgorithm<T,conf>::Run()
{
    std::size_t generationNumber = 0;
    auto bestIndividual = gPopulation.GetBestChromosome();
    


    spdlog::info("Best individual:{0} Fitness: {1}",bestIndividual.GetGenes(),bestIndividual.GetFitnessValue());
    
//    for(;generationNumber<nNumberOfGenerations;generationNumber++) {

	Evolve();
	for(auto chromosome:gPopulation.GetPopulation())
	{
	    spdlog::debug("Gene:{0} Fitness: {1} Selected:{2}",chromosome.GetGenes(),chromosome.GetFitnessValue(),chromosome.IsSelected());
	}
	bestIndividual = gPopulation.GetBestChromosome();
  //  }

}


template <typename T, Config conf>
void GeneticAlgorithm<T, conf>::Evolve()
{
    Population<T,conf>newPopulation;
    for (auto &item: gPopulation.GetPopulation())  {
	auto bestFirstIndividual = pSelectionObject->Select(gPopulation);
	auto bestSecondIndividual = pSelectionObject->Select(gPopulation);
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



}
