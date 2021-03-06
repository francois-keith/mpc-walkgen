#pragma once
#ifndef MPC_WALKGEN_ZEBULON_WAKGEN_H
#define MPC_WALKGEN_ZEBULON_WAKGEN_H

////////////////////////////////////////////////////////////////////////////////
///
///\file	walkgen.h
///\brief	Main program of the MPC
///\author	Lafaye Jory
///\version	1.0
///\date	02/05/12
///
////////////////////////////////////////////////////////////////////////////////

#include <mpc-walkgen/zebulon/walkgen-abstract.h>
#include "types.h"

namespace MPCWalkgen{

  class QPSolver;
  class Interpolation;

  namespace Zebulon{

    class QPGenerator;
    class QPGeneratorOrientation;
    class RigidBodySystem;

    class Walkgen :
        public WalkgenAbstract
    {

    public:
      EIGEN_MAKE_ALIGNED_OPERATOR_NEW
      Walkgen(::MPCWalkgen::QPSolverType solvertype);
      virtual ~Walkgen();

      virtual void robotData(const RobotData &robotData);
      virtual void mpcData(const MPCData &mpcData);
      virtual void envData(const EnvData &envData);
      virtual const MPCData& mpcData();
      virtual const RobotData& robotData();
      virtual const MPCSolution& mpcSolution();
      virtual const EnvData& envData();
      virtual void QPBasePosition(Eigen::VectorXd& position);

      virtual void init(const RobotData &robotData, const MPCData &mpcData);
      virtual void init(const MPCData &mpcData);
      virtual void init(const RobotData &robotData);
      virtual void init();

      virtual const MPCSolution &online(double time, bool previewBodiesNextState=true);

      virtual const MPCSolution &online(bool previewBodiesNextState=true);

      /// \name Accessors and mutators
      /// \{
      virtual void velReferenceInLocalFrame(double dx, double dy, double dyaw);
      virtual void velReferenceInLocalFrame(Eigen::VectorXd dx, Eigen::VectorXd dy, Eigen::VectorXd dyaw);
      virtual void velReferenceInGlobalFrame(double dx, double dy, double dyaw);
      virtual void velReferenceInGlobalFrame(Eigen::VectorXd dx, Eigen::VectorXd dy, Eigen::VectorXd dyaw);
      virtual void posReferenceInGlobalFrame(double dx, double dy, double dyaw);
      virtual void posReferenceInGlobalFrame(Eigen::VectorXd dx, Eigen::VectorXd dy, Eigen::VectorXd dyaw);
      virtual void posIntReferenceInGlobalFrame(double dx, double dy, double dyaw);
      virtual void posIntReferenceInGlobalFrame(Eigen::VectorXd dx, Eigen::VectorXd dy, Eigen::VectorXd dyaw);
      virtual void copReferenceInLocalFrame(double dx, double dy);
      virtual void copReferenceInLocalFrame(Eigen::VectorXd dx, Eigen::VectorXd dy);
      virtual void comReferenceInLocalFrame(double dx, double dy);
      virtual void comReferenceInLocalFrame(Eigen::VectorXd dx, Eigen::VectorXd dy);

      virtual const BodyState & bodyState(BodyType body)const;
      virtual void bodyState(BodyType body, const BodyState & state);
      /// \}


    private:
      ::MPCWalkgen::QPSolverType qpSolverType_;
      MPCData mpcData_;
      RobotData robotData_;
      EnvData envData_;
      ::MPCWalkgen::QPSolver * solver_;
      ::MPCWalkgen::QPSolver * solverOrientation_;
      QPGenerator * generator_;
      QPGeneratorOrientation * generatorOrientation_;
      ::MPCWalkgen::Interpolation * interpolation_;
      RigidBodySystem * robot_;

      GlobalSolution solution_;
      Reference velRef_;
      Reference posRef_;
      Reference posIntRef_;
      Reference comRef_;
      Reference copRef_;
      /// \brief The new value of references, updated with in online method
      Reference newVelRef_;
      Reference newPosRef_;
      Reference newPosIntRef_;
      Reference newcomRef_;
      Reference newcopRef_;

      /// \brief Time at which the problem should be updated
      double upperTimeLimitToUpdate_;
      double upperTimeLimitToFeedback_;

      /// \brief Synchronised time with QP sampling
      double currentTime_;
      double currentRealTime_;

      bool initAlreadyCalled_;

    };
  }
}

#endif // MPC_WALKGEN_ZEBULON_WAKGEN_H
