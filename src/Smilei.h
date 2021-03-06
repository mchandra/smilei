// You can add interesting cite commands like this \cite Grech2011 (you need to put the BIBTEX record in doc/smilei.bib)

/*! \mainpage SMILEI overview

 \section intro Introduction

 The Particle-In-Cell (PIC) code SMILEI is an open-source project developed by the PIC community at the 
 Plateau de Saclay to support the development of the Apollon laser within the CILEX framework. 
 
 SMILEI stands for Simulation of Matter Irradiated by Light at Extreme Intensities, and is developed through a 
 collaboration between various teams at Ecole Polytechnique, at the CEA/Saclay and with strong support from the 
 Maison de la Simulation and IDRIS on the numerical side.
 
 To face the diverse needs of the teams involved in its development, SMILEI is developed in C++ based on an
 object-oriented architecture.
 Its modularity allows to run simulations in various dimensions and geometries. 
 
 Today, the one-dimensional in space three-dimensional in velocity (1D3V) and 2D3V versions of the code have been 
 developed and benchmarked.
 
 SMILEI modularity also allows to chose between various Maxwell solvers and particle pushers, 
 and different order of interpolation/projection are available. It should also be noted that Maxwell's equations 
 are solved on the so-called Yee-mesh with centered electric and magnetic fields using the finite-difference 
 time-domain (FDTD) method or related methods (see \cite Nuter2014).
 
 Moreover, charge deposition is computed following the charge conservation scheme proposed by Esirkepov \cite Esirkepov2001.
 Finally, Monte-Carlo routines are currently under development to account for (i) high-energy (gamma) photon emission 
 and its back-reaction on the electron dynamics, as well as (ii) electron-positron pair creation. 
 These developments are undertaken in collaboration with the team that has introduced similar routines in the PIC code CALDER
 \cite Lobet2013. 
 
 Such routines will be of particular importance for the modelling of strongly relativistic astrophysical scenarii.
 
 On the parallelisation side, SMILEI benefits from a state-of-the-art hybrid MPI/OpenMP parallelisation, 
 and an original particle sorting algorithm. Dynamical load balancing will also be developed within the next months. 
 
 SMILEI is therefore designed to run on massively parallel machines, and its flexibility should allow one to benefit
 from the newest and futures HPC architectures.

 \section download_sec Download

 Currently available upon registration on [Renater](https://sourcesup.renater.fr/projects/smilei/) 
 to the community of the Plateau de Saclay, SMILEI is intended as an open-source code.
 
 As such, it shall be made available to the astrophysics community involved in this ANR, and to the scientific community at large.
 
 \section install_sec Installation

 \subsection Dependencies
 The code needs hdf5 libraries installed with parallel support (on mac with macport you need to install the package with
 something like :
 <tt>sudo port install hdf5-18 +openmpi</tt> 
 
 If you need to recompile the hdf5 by hands, remember the <tt>--enable-parallel</tt> switch at configure.
 
 In order to specify the path to the HDF5 library you should set the evironemental variable <tt>HDF5_ROOT_DIR</tt>
 

 \subsection compile_sec Compile Smilei

 This is (o should be) a massive parallel code which heavily uses MPI routines.
 The compilation has been tested using <tt>gcc</tt> or intel <tt>icpc</tt> compilers and openmpi.

 The environemental variable <tt>SMILEICXX</tt> is used to set the mpi compiler.
 To compile you should do
 
 <tt>make smilei</tt> to compile in release mode (without OpenMP)
 
 To enable the OpenMP parallelization you can use the <tt>make smilei openmp=gnu</tt> command 
 (replace <tt>gnu</tt> with <tt>intel</tt> if you have an Intel compiler) 

 To enable de debugging features, do a <tt>make smilei config=debug</tt> (you can mix with the above OpenMP switch)

 
 
 */

/*! @file Pic.h

 @brief Pic.h

 @date 2013-02-15
 */

#include <string>

#include "Tools.h"

//! verbosity level use verbose keyword in data parameter
#ifdef  __DEBUG
int debug_level = 10;
#else
int debug_level = 0;
#endif

//! main function
int main (int argc, char* argv[]);

