#pragma once
#ifndef MPC_WALKGEN_HUMANOID_STATE_SOLVER_H
#define MPC_WALKGEN_HUMANOID_STATE_SOLVER_H

////////////////////////////////////////////////////////////////////////////////
///
///\file	state-solver.h
///\brief	A abstract class to regroup all state-solvers
///\author	Herdt Andrei
///\version	1.2
///\date	27/04/12
///
////////////////////////////////////////////////////////////////////////////////

#include "types.h"

namespace MPCWalkgen{
  namespace Humanoid{
    class StateSolver{
    public:
      StateSolver(Reference * velRef, const MPCData * generalData);
      ~StateSolver();

      void setSupportState(double time, int pi, const std::vector<double> &samplingTimes_vec, SupportState & Support);

    protected:
      Reference * velRef_;
      const MPCData * generalData_;

    };
  }
}

#endif // MPC_WALKGEN_HUMANOID_STATE_SOLVER_H
