// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc/AnalogPotentiometer.h>
#include <frc/motorcontrol/PWMSparkMax.h>
#include <frc2/command/PIDSubsystem.h>

#include "Constants.h"

/**
 * The wrist subsystem is like the elevator, but with a rotational joint instead
 * of a linear joint.
 */
class Wrist : public frc2::PIDSubsystem {
 public:
  Wrist();

  /**
   * The log method puts interesting information to the SmartDashboard.
   */
  void Log();

  /**
   * Use the potentiometer as the PID sensor. This method is automatically
   * called by the subsystem.
   */
  double GetMeasurement() override;

  /**
   * Use the motor as the PID output. This method is automatically called
   * by the subsystem.
   */
  void UseOutput(double output, double setpoint) override;

  /**
   * Log the data periodically. This method is automatically called
   * by the subsystem.
   */
  void Periodic() override;

 private:
  frc::PWMSparkMax m_motor{WristConstants::kMotorPort};

// Conversion value of potentiometer varies between the real world and
// simulation
#ifndef SIMULATION
  frc::AnalogPotentiometer m_pot{WristConstants::kPotentiometerPort,
                                 -270.0 / 5};
#else
  frc::AnalogPotentiometer m_pot{
      WristConstants::kPotentiometerPort};  // Defaults to degrees
#endif

  frc::PIDController m_PIDcontroller{
      WristConstants::kP,
      WristConstants::kI,
      WristConstants::kD,
  };
};
