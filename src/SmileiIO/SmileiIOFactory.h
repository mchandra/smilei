#ifndef SMILEIIOFACTORY_H
#define SMILEIIOFACTORY_H

#include "SmileiIO.h"
#include "SmileiIO_Cart1D.h"
#include "SmileiIO_Cart2D.h"

#include "PicParams.h"
#include "SmileiMPI.h"

#include "Tools.h"

//  --------------------------------------------------------------------------------------------------------------------
//! Class SmileiIOFactory
//  --------------------------------------------------------------------------------------------------------------------
class SmileiIOFactory {
public:
    //  --------------------------------------------------------------------------------------------------------------------
    //! Create appropriate IO environment for the geometry 
    //! \param params : Parameters
    //! \param diagParams : Diagnostic parameters
    //! \param smpi : MPI environment
    //  --------------------------------------------------------------------------------------------------------------------
    static SmileiIO* create(PicParams& params, DiagParams& diagParams, SmileiMPI* smpi) {
        SmileiIO* sio = NULL;
        if ( params.geometry == "1d3v" ) {
            sio = new  SmileiIO_Cart1D(params, diagParams, smpi);
        }
        else if ( params.geometry == "2d3v" ) {
            sio = new  SmileiIO_Cart2D(params, diagParams, smpi);
        }
        else {
            ERROR( "Geometry " << params.geometry << " not implemented" );
        }

        return sio;
    }

};

#endif

