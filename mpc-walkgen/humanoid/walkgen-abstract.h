////////////////////////////////////////////////////////////////////////////////
///
///\file	walkgen-abstract.h
///\brief	Abstract class to instanciate Walkgen algorithm for humanoid robot
///\author	Lafaye Jory
///\author      Keith François
///\author	Herdt Andrei
///\version	1.2
///\date	27/04/12
///
////////////////////////////////////////////////////////////////////////////////


#pragma once
#ifndef MPC_WALKGEN_HUMANOID_WALKGEN_ABSTRACT_H
#define MPC_WALKGEN_HUMANOID_WALKGEN_ABSTRACT_H



#include <mpc-walkgen/humanoid/sharedpgtypes.h>

#include <Eigen/Core>



namespace MPCWalkgen{
  namespace Humanoid{
    class  WalkgenAbstract
    {
      //
      // Public methods:
      //
    public:

      WalkgenAbstract();

      virtual ~WalkgenAbstract() =0;

      /// \brief Initialize the system
      /// \param[in] robotData: data relative to the robot
      /// \param[in] mpcData: data relative to the qp solver
      virtual void init(const RobotData &robotData, const MPCData &mpcData) = 0;
      virtual void init() = 0;

      /// \brief Call method to handle on-line generation of ZMP reference trajectory.
      /// \param[in] time : Current time.
      /// \param[in] previewBodiesNextState

      /// \return The associated solution
      ///   If solution.newTraj is true, the method has succeeded.
      virtual const MPCSolution & online(double time, bool previewBodiesNextState = true) = 0;
      virtual const MPCSolution & online(bool previewBodiesNextState=true) = 0;

      /// \name Accessors and mutators
      /// \{
      /// \brief Set the reference (velocity only as for now)
      virtual void reference(const double & dx, const double & dy, const double & dyaw) = 0;
      virtual void reference(const Eigen::VectorXd & dx, const Eigen::VectorXd & dy,
                             const Eigen::VectorXd & dyaw) = 0;
      /// \}

      /// \name accessors relative to the state of the robot.
      /// \{
      virtual const SupportState & currentSupportState() const = 0;
      virtual void currentSupportState(const SupportState & newSupportState)=0;

      virtual const BodyState & bodyState(BodyType body)const=0;
      virtual void bodyState(BodyType body, const BodyState & state)=0;
      /// \}

    };
    /*! Factory of Pattern generator interface. */
    MPC_WALKGEN_API WalkgenAbstract * createWalkgen(QPSolverType solvertype);
  }
}


#endif // MPC_WALKGEN_HUMANOID_WALKGEN_ABSTRACT_H
