#ifndef MPC_WALKGEN_ZEBULON_RIGID_BODY_SYSTEM_H
#define MPC_WALKGEN_ZEBULON_RIGID_BODY_SYSTEM_H

////////////////////////////////////////////////////////////////////////////////
///
///\file	rigid-body-system.h
///\brief	A class to store the rigid body model
///\author	Lafaye Jory
///\version	1.0
///\date	02/05/12
///
////////////////////////////////////////////////////////////////////////////////


#include "types.h"
#include "rigid-body.h"

#include <Eigen/Dense>
#include <vector>

namespace MPCWalkgen{
  namespace Zebulon{
    class RigidBodySystem{

    public:
      RigidBodySystem(const MPCData * generalData,
                      const RobotData * robotData,
                      const Interpolation *interpolation);
      ~RigidBodySystem();

      void computeDynamics();
      void computeDynamicsCoP();

      void computeQPDynamics();
      void computeInterpolationDynamics();

      void interpolateBodies(GlobalSolution &solution, double currentTime, const Reference &velRef);

      void updateBodyState(const GlobalSolution &solution);

      RigidBody *body(BodyType type);
      const RigidBody *body(BodyType type) const;


    private:
      const MPCData * generalData_;
      const RobotData * robotData_;

      RigidBody *CoM_;
      RigidBody *base_;


    };

  }
}

/*! \fn MPCWalkgen::RigidBodySystem::RigidBodySystem(const MPCData *generalData
                                        , const Interpolation *interpolation)
* \brief Constructor
*/

/*! \fn MPCWalkgen::RigidBodySystem::computeDynamics()
* \brief Compute dynamic matrices of the rigid body system
*/

/*! \fn void MPCWalkgen::RigidBodySystem::updateBodyState(const MPCSolution & solution)
* \brief Update state of bodies
* \param solution [out] the solution
*/

/*! \fn void MPCWalkgen::RigidBodySystem::firstIterationDuration(double firstIterationDuration)
* \brief Setter to define the duration of the first iteration in the QP horizon
*/

/*! \fn DynamicMatrix & MPCWalkgen::RigidBodySystem::dynamic(DynamicMatrixType type)
* \brief Return dynamic matrices of desired type
*/

/*! \fn BodyState & MPCWalkgen::RigidBodySystem::state(BodyType type)
* \brief Return state of desired body
*/

/*! \fn ConvexHull MPCWalkgen::RigidBodySystem::convexHull(HullType type,
* const SupportState & prwSupport, bool computeLinearSystem=true, bool rotateHull=true) const
* \brief Return convex hull data of hull type
* \param prwSupport previewed support associated with the convexhull
* \param computeLinearSystem if false, linear inequalities will not be computed
*/

#endif // MPC_WALKGEN_ZEBULON_RIGID_BODY_SYSTEM_H
