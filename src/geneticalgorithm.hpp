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
	    Chromosome<T,conf> Crossover(const Chromosome<T,conf>& x,const Chromosome<T,conf>& y) const;
	    void Mutate();
	    void Evolve();
	    Chromosome<T,conf> GetBestChromosome();
	    void EvaluatePopulation();
	    population_t <conf,conf.populationSize> gPopulation;
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
    //Initialize population
    gPopulation.fill(Chromosome<double,conf>());
}


template <typename T, Config conf>
void GeneticAlgorithm<T,conf>::Initialize()
{
    /*
    gPopulation=Population<T,conf>();
    gPopulation.RegisterChromosomeGenerator(fChromosomeGenerator);
    gPopulation.RegisterFitnessFunction(fFitnessFunction);
    gPopulation.GeneratePopulation();
    gPopulation.EvaluatePopulation();
    */
    // generate population
    std::for_each(gPopulation.begin(), gPopulation.end(), fChromosomeGenerator);

    // evaluate population
    EvaluatePopulation();

    pSelectionObjectFactory = std::make_shared<SelectionObjectFactory<T,conf>>();
    pSelectionObject = pSelectionObjectFactory->CreateSelectionObject(
	    //SelectionMechanism::TOURNAMENT_SELECTION);
	    SelectionMechanism::ROULETTE_SELECTION);


}

template <typename T, Config conf>
Chromosome<T,conf> GeneticAlgorithm<T,conf>::GetBestChromosome() 
{
    auto chromosome = std::max_element(gPopulation.begin(),gPopulation.end(),[](const auto &lhs, const auto &rhs){
	    return lhs.GetFitnessValue() < rhs.GetFitnessValue(); 
	    });

    return static_cast<Chromosome<T,conf>>(*chromosome);
}

template <typename T, Config conf>
void GeneticAlgorithm<T,conf>::EvaluatePopulation() 
{
  std::for_each(gPopulation.begin(), gPopulation.end(),
                fFitnessFunction);
}

template <typename T, Config conf>
void GeneticAlgorithm<T,conf>::Run()
{
    std::size_t generationNumber = 0;

    auto bestIndividual = GetBestChromosome();
    


    
    for(;generationNumber<nNumberOfGenerations;generationNumber++) {
	spdlog::info("Generation {0} Best Fitness {1}",generationNumber,bestIndividual.GetFitnessValue());
	Evolve();
	bestIndividual = GetBestChromosome();
	
        if (bestIndividual.GetFitnessValue()==conf.bestFitnessValue) {
	    generationNumber++;
	    break;
	}
	
    }
    spdlog::info("Best individual: {0} Fitness: {1} Generation: {2}",bestIndividual.GetGenes(),
	    bestIndividual.GetFitnessValue(),generationNumber);

}


template <typename T, Config conf>
void GeneticAlgorithm<T, conf>::Evolve()
{
    std::size_t elitismOffset = 0;
    population_t<conf, conf.populationSize> newPopulation=gPopulation;
    if (conf.useElitism == true) {
	auto bestIndividual = GetBestChromosome();
	newPopulation[0] = bestIndividual;
	elitismOffset = 1; 
    }
    for (std::size_t i = elitismOffset; i<conf.populationSize;i++)  {
	auto bestFirstIndividual = pSelectionObject->Select(gPopulation);

	auto bestSecondIndividual = pSelectionObject->Select(gPopulation);
	auto breededIndividual = Crossover(bestFirstIndividual,bestSecondIndividual);
	newPopulation[i] = breededIndividual;
    }
    gPopulation = newPopulation;
    EvaluatePopulation();
    Mutate();
    EvaluatePopulation();
}


template <typename T, Config conf>
Chromosome<T,conf> GeneticAlgorithm<T, conf>::Crossover(const Chromosome<T,conf>& x,const Chromosome<T,conf>& y) const
{
    std::string genesX = x.GetGenes();
    std::string genesY = y.GetGenes();

    for (std::size_t i=0;i<conf.geneLength;i++) {
	double crossoverProbability = uniform<double>(0,1);
	if (definitelyLessThan<double>(crossoverProbability,conf.crossoverRate,std::numeric_limits<double>::epsilon())) {
	    genesY[i] = genesX[i];    
	}
    }
    Chromosome<T,conf> newChromosome(genesY);
    return newChromosome;
}


template <typename T, Config conf>
void GeneticAlgorithm<T, conf>::Mutate()
{

    for (std::size_t i = 0; i<conf.populationSize; i++) {
	double mutationProbability = uniform<double>(0,1);
	if (definitelyLessThan<double>(mutationProbability,conf.mutationProbability,std::numeric_limits<double>::epsilon())) {
	    std::string genes = gPopulation[i].GetGenes();
	    std::size_t position = uniform<std::size_t>(0,conf.geneLength);
	    if (genes[position] == '0') {
		genes[position] == '1';
	    }
	    else {
		genes[position] == '0';
	    }
	    Chromosome<T,conf>newChromosome(genes);
	    gPopulation[i] = newChromosome;
	}
    }
}



}
