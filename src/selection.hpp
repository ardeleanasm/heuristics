#pragma once

namespace ga
{
    template<typename T, Config conf>
    class Selection 
    {
	public:
	    virtual ~Selection() {}
	    virtual void Select()=0;
    };

    template<typename T, Config conf>
    class TournamentSelection: public Selection<T,conf>
    {
	public:
	    void Select() override
	    {
		//TODO:Some implementation
	    }
	private:
    };

    template<typename T, Config conf>
    class SelectionObjectAbstractFactory {

	public:
	    virtual std::shared_ptr<Selection<T,conf>> CreateSelectionObject() const = 0;	    
    };

    template<typename T, Config conf>
    class SelectionObjectFactory: public SelectionObjectAbstractFactory<T,conf> {
	std::shared_ptr<Selection<T,conf>> CreateSelectionObject() const override {
	    return std::shared_ptr<Selection<T,conf>>(new TournamentSelection<T,conf>());
	}
    };
}
