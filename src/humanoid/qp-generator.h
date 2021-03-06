#pragma once
#ifndef MPC_WALKGEN_HUMANOID_QP_GENERATOR_H
#define MPC_WALKGEN_HUMANOID_QP_GENERATOR_H

////////////////////////////////////////////////////////////////////////////////
///
///\file	qp-generator.h
///\brief	A class to compute QP elements (objective, constraints, warmstart)
///\author	Lafaye Jory
///\author      Keith François
///\author	Herdt Andrei
///\version	1.2
///\date	27/04/12
///
////////////////////////////////////////////////////////////////////////////////



#include "types.h"

#include "../common/qp-solver.h"
#include "qp-preview.h"

#include <Eigen/Dense>
#include <vector>

namespace MPCWalkgen{
  namespace Humanoid{
    class QPGenerator{

    public:
      QPGenerator(QPPreview * preview, QPSolver * solver,
                  Reference * velRef, QPWeighting * weighting,
                  RigidBodySystem * robot, const MPCData * generalData);
      ~QPGenerator();

      void precomputeObjective();

      void buildObjective(const MPCSolution & result);

      void buildConstraints(const MPCSolution & result);

      void computeWarmStart(MPCSolution & result);

      void convertCopToJerk(MPCSolution & result);

      void computeReferenceVector(const MPCSolution & result);

      void display(const MPCSolution & result, const std::string & filename) const;

    private:

      void buildInequalitiesFeet(const MPCSolution & result);

      void buildConstraintsFeet(const MPCSolution & result);

      void buildConstraintsCOP(const MPCSolution & result);

    private:

      QPPreview * preview_;
      QPSolver * solver_;
      RigidBodySystem * robot_;
      Reference * velRef_;
      QPWeighting * weighting_;
      const MPCData * generalData_;

      Eigen::VectorXd tmpVec_;
      Eigen::VectorXd tmpVec2_;
      Eigen::MatrixXd tmpMat_;
      Eigen::MatrixXd tmpMat2_;

      RelativeInequalities feetInequalities_;//TODO: Maybe should be instantiated in robot_

      std::vector<Eigen::MatrixXd> Qconst_;
      std::vector<Eigen::MatrixXd> QconstN_;
      std::vector<Eigen::MatrixXd> choleskyConst_;
      std::vector<Eigen::MatrixXd> pconstCoM_;
      std::vector<Eigen::MatrixXd> pconstVc_;
      std::vector<Eigen::MatrixXd> pconstRef_;

      ConvexHull FootFeasibilityEdges;
      ConvexHull COPFeasibilityEdges;
      ConvexHull hull;
    };
  }
}

/*! \fn MPCWalkgen::QPGenerator::QPGenerator(QPPreview * preview, QPSolver * solver,
*					VelReference * velRef, QPWeighting * weighting,
*					RigidBodySystem * robot, const MPCData * generalData)
* \brief Constructor
*/

/*! \fn MPCWalkgen::QPGenerator::buildObjective(const MPCSolution & result)
* \brief Build matrix Q and vector p for the QP
*/

/*! \fn MPCWalkgen::QPGenerator::buildConstraints(const MPCSolution & result)
* \brief build matrix A and vectors BU, BL, XU, XL for the QP
*/

/*! \fn MPCWalkgen::QPGenerator::computeWarmStart(MPCSolution & result)
* \brief Compute a feasible solution and an active-set of previewed constraints
*/

/*! \fn MPCWalkgen::QPGenerator::convertCopToJerk(MPCSolution & result)
* \brief the current QP generate a solution in CoP position. for the interpolation, we must to convert the solution into CoM Jerk
*/

/*! \fn MPCWalkgen::QPGenerator::computeReferenceVector(const MPCSolution & result)
* \brief Compute the reference vector (constant over the horizon)
*/

/*! \fn MPCWalkgen::QPGenerator::display(const MPCSolution & result, const std::string & filename) const
* \brief display some informations of the solution in a file (previewed CoM, CoP and feet and CoP constraints)
* \param result   the solution
* \param filename the file to display solution
*/

#endif // MPC_WALKGEN_HUMANOID_QP_GENERATOR_H
