
#include "SimWindow.h"
#include "PicParams.h"
#include "Species.h"
#include "ElectroMagn.h"
#include "Interpolator.h"
#include "Projector.h"
#include "SmileiMPI.h"
using namespace std;

SimWindow::SimWindow(PicParams& params)
{
    nspace_win_x_ = params.nspace_win_x;
    cell_length_x_   = params.cell_length[0];
    x_moved = 0.;      //The window has not moved at t=0. Warning: not true anymore for restarts.
    vx_win_ = params.vx_win; 
    t_move_win_ = params.t_move_win;      
}

SimWindow::~SimWindow()
{
}

void SimWindow::operate(vector<Species*> vecSpecies, ElectroMagn* EMfields, Interpolator* Interp, Projector* Proj, SmileiMPI* smpi, PicParams& params)
{

    unsigned int clrw;

    if (vecSpecies.size() > 0) {
        clrw = vecSpecies[0]->clrw; //clrw must be the same for all species
    } else {
        clrw = params.clrw; //This is not correct, just an ugly patch. clrw should take the correct global value even when there are no particles.
    }

    smpi->getCellStartingGlobalIndex(0)+= clrw;
    smpi->getDomainLocalMin(0)+= cell_length_x_*clrw;
    smpi->getDomainLocalMax(0)+= cell_length_x_*clrw;

    if (vecSpecies.size() > 0) {
        for (unsigned int ispec=0 ; ispec<vecSpecies.size(); ispec++) {
            vecSpecies[ispec]->movingWindow_x(clrw,smpi,params);
        }
        Interp->mv_win(clrw);
        Proj->mv_win(clrw);
    }
    EMfields->movingWindow_x(clrw, smpi);
    x_moved += cell_length_x_*clrw;


}

bool SimWindow::isMoving(double time_dual)
{
    return ( (nspace_win_x_) && ((time_dual - t_move_win_)*vx_win_ > x_moved) );
}

void SimWindow::setOperators(vector<Species*> vecSpecies, Interpolator* Interp, Projector* Proj, SmileiMPI* smpi)
{
    smpi->updateMvWinLimits( x_moved, round(x_moved/cell_length_x_) );

    for (unsigned int ispec=0 ; ispec<vecSpecies.size(); ispec++) {
	vecSpecies[ispec]->updateMvWinLimits(x_moved);
    }

    Interp->setMvWinLimits( smpi->getCellStartingGlobalIndex(0) );
    Proj->setMvWinLimits  ( smpi->getCellStartingGlobalIndex(0) );

}
