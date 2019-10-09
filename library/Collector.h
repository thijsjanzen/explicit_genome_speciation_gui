#ifndef EXPLICITGENOMESPECIATION_COLLECTOR_H
#define EXPLICITGENOMESPECIATION_COLLECTOR_H

#include "Types.h"
#include "Utilities.h"
#include "MetaPop.h"
#include "GenArch.h"
#include <fstream>
#include <cassert>

struct Locus
{
    Locus(const size_t &i, const size_t &t) :
        id(i),
        trait(t),
        varG(utl::zeros(3u)),
        varP(utl::zeros(3u)),
        varA(utl::zeros(3u)),
        varN(utl::zeros(3u)),
        varD(0.0),
        varI(0.0),
        Pst(0.0),
        Gst(0.0),
        Qst(0.0),
        Cst(0.0),
        Fst(0.0)
    {}

    size_t id;
    size_t trait;

    vecDbl varG; // per ecotype
    vecDbl varP; // per ecotype
    vecDbl varA; // per ecotype
    vecDbl varN; // per ecotype
    double varD;
    double varI;

    double Pst;
    double Gst;
    double Qst;
    double Cst;
    double Fst;
};

typedef std::vector<Locus> vecLoci;
typedef std::vector<std::shared_ptr<std::ofstream> > vecStreams;

class Collector
{

public:

    Collector(const GenArch &arch) :
        counts(utl::uzeros(3u, 3u)),
        mating(utl::uzeros(2u, 2u)),
        means(utl::zeros(3u, 3u, 3u)),
        varG(utl::zeros(3u, 3u)),
        varP(utl::zeros(3u, 3u)),
        varA(utl::zeros(3u, 3u)),
        varN(utl::zeros(3u, 3u)),
        varD(utl::zeros(3u)),
        varI(utl::zeros(3u)),
        Pst(utl::zeros(3u)),
        Gst(utl::zeros(3u)),
        Qst(utl::zeros(3u)),
        Cst(utl::zeros(3u)),
        Fst(utl::zeros(3u)),
        genomescan(emptyloci(arch)),
        EI(0.0),
        SI(0.0),
        RI(0.0)
	{
    }

    ~Collector()
    {
       
    }

    void analyze(const MetaPop&, const Param&);
    void print(const size_t&, const MetaPop&);

    // Getters called in tests
    double getEI() const
    {
        return EI;
    }
    double getSI() const
    {
        return SI;
    }
    double getRI() const
    {
        return RI;
    }

	std::vector<float> get_Fst() const
	{
		std::vector<float> output(genomescan.size());
		for (int i = 0; i < genomescan.size(); ++i) {
			output[i] = static_cast<float>(genomescan[i].Fst);
		}
		return output;
	}


private:

    vecStrings whattosave() const;
    vecLoci emptyloci(const GenArch&) const;

    MatUns counts; // per habitat per ecotype
    MatUns mating; // per male ecotype per female ecotype

    Matx3d means; // per trait per habitat per ecotype

    Matrix varG; // per trait per ecotype
    Matrix varP; // per trait per ecotype
    Matrix varA; // per trait per ecotype
    Matrix varN; // per trait per ecotype
    vecDbl varD; // per trait
    vecDbl varI; // per trait

    vecDbl Pst; // per trait
    vecDbl Gst; // per trait
    vecDbl Qst; // per trait
    vecDbl Cst; // per trait
    vecDbl Fst; // per trait

    vecLoci genomescan; // per locus

    double EI;
    double SI;
    double RI;

};

double Xst(const vecDbl&, const vecUns&);


#endif
