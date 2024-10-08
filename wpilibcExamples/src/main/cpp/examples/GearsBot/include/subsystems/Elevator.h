// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc/AnalogPotentiometer.h>
#include <frc/RobotBase.h>
#include <frc/motorcontrol/PWMSparkMax.h>
#include <frc2/command/PIDSubsystem.h>

#include "Constants.h"

/**
 * The elevator subsystem uses PID to go to a given height. Unfortunately, in
 * it's current
 * state PID values for simulation are different than in the real world do to
 * minor differences.
 */
class Elevator : public frc2::PIDSubsystem {
 public:
  Elevator();

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
   * by
   * the subsystem.
   */
  void UseOutput(double output, double setpoint) override;

  /**
   * Log the data periodically. This method is automatically called
   * by the subsystem.
   */
  void Periodic() override;

 private:
  frc::PWMSparkMax m_motor{ElevatorConstants::kMotorPort};

  // Conversion value of potentiometer varies between the real world and
  // simulation
  frc::AnalogPotentiometer m_pot =
      frc::RobotBase::IsReal()
          ? frc::AnalogPotentiometer{ElevatorConstants::kPotentiometerPort,
                                     -2.0 / 5}
          : frc::AnalogPotentiometer{
                ElevatorConstants::kPotentiometerPort};  // Defaults to meters

  static constexpr double kP_real = ElevatorConstants::kP_real;
  static constexpr double kI_real = ElevatorConstants::kI_real;

  static constexpr double kP_simulation = ElevatorConstants::kP_simulation;
  static constexpr double kI_simulation = ElevatorConstants::kI_simulation;

  static constexpr double kD = ElevatorConstants::kD;
};
