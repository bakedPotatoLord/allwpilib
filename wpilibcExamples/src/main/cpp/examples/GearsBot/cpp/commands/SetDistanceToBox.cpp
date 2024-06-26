// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/SetDistanceToBox.h"

#include <frc/controller/PIDController.h>

#include "Robot.h"

SetDistanceToBox::SetDistanceToBox(units::meter_t distance,
                                   Drivetrain& drivetrain)
    : frc2::CommandHelper<frc2::PIDCommand, SetDistanceToBox>{
          frc::PIDController{BoxAlignConstants::kP, BoxAlignConstants::kI,
                             BoxAlignConstants::kD},
          [&drivetrain] { return drivetrain.GetDistanceToObstacle(); },
          distance.value(),
          [&drivetrain](double output) { drivetrain.Drive(output, output); },
          {&drivetrain}},
      m_drivetrain{&drivetrain} {
  m_controller.SetTolerance(BoxAlignConstants::kTolerance);
}

// Called just before this Command runs the first time
void SetDistanceToBox::Initialize() {
  // Get everything in a safe starting state.
  m_drivetrain->Reset();
  frc2::PIDCommand::Initialize();
}

bool SetDistanceToBox::IsFinished() {
  return m_controller.AtSetpoint();
}
