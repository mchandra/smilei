#ifndef DiagnosticPhaseSpace_H
#define DiagnosticPhaseSpace_H

#include <cmath>

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include <hdf5.h>

#include "Tools.h"

#include "Species.h"
#include "Interpolator.h"
#include "Particles.h"

#include "DiagnosticPhase.h"

class PicParams;
class SmileiMPI;
class DiagParams;
class ElectroMagn;

//! mother class of all the DiagnosticPhase* it creates all the sub-diagnostics and creates and fills the hdf5 file
class DiagnosticPhaseSpace {

public:

    DiagnosticPhaseSpace(PicParams &params, DiagParams &diagParams, SmileiMPI* smpi);
    ~DiagnosticPhaseSpace();

	void run(int timestep, std::vector<Species*>& vecSpecies);
	
	void close();
private:
    
    //! this vector will hold all the diagnostics created
	std::vector<DiagnosticPhase*> vecDiagPhase;
	
    //! this is the hdf5 file id (we need to keep it to close at the right time)
	hid_t fileId;

    //! this is always handy to know (number of particle dimension)
	unsigned int ndim;
    
    partStruct my_part;

	
};
#endif
