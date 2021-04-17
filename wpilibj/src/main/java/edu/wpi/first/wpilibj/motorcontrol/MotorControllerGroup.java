// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

package edu.wpi.first.wpilibj.motorcontrol;

import edu.wpi.first.wpilibj.Sendable;
import edu.wpi.first.wpilibj.smartdashboard.SendableBuilder;
import edu.wpi.first.wpilibj.smartdashboard.SendableRegistry;
import java.util.Arrays;

/** Allows multiple {@link MotorController} objects to be linked together. */
public class MotorControllerGroup implements MotorController, Sendable, AutoCloseable {
  private boolean m_isInverted;
  private final MotorController[] m_motorControllers;
  private static int instances;

  /**
   * Create a new MotorControllerGroup with the provided MotorControllers.
   *
   * @param motorControllers The MotorControllers to add
   */
  @SuppressWarnings("PMD.AvoidArrayLoops")
  public MotorControllerGroup(
      MotorController motorController, MotorController... motorControllers) {
    m_motorControllers = new MotorController[motorControllers.length + 1];
    m_motorControllers[0] = motorController;
    for (int i = 0; i < motorControllers.length; i++) {
      m_motorControllers[i + 1] = motorControllers[i];
    }
    init();
  }

  public MotorControllerGroup(MotorController[] motorControllers) {
    m_motorControllers = Arrays.copyOf(motorControllers, motorControllers.length);
    init();
  }

  private void init() {
    for (MotorController controller : m_motorControllers) {
      SendableRegistry.addChild(this, controller);
    }
    instances++;
    SendableRegistry.addLW(this, "MotorControllerGroup", instances);
  }

  @Override
  public void close() {
    SendableRegistry.remove(this);
  }

  @Override
  public void set(double speed) {
    for (MotorController motorController : m_motorControllers) {
      motorController.set(m_isInverted ? -speed : speed);
    }
  }

  @Override
  public double get() {
    if (m_motorControllers.length > 0) {
      return m_motorControllers[0].get() * (m_isInverted ? -1 : 1);
    }
    return 0.0;
  }

  @Override
  public void setInverted(boolean isInverted) {
    m_isInverted = isInverted;
  }

  @Override
  public boolean getInverted() {
    return m_isInverted;
  }

  @Override
  public void disable() {
    for (MotorController motorController : m_motorControllers) {
      motorController.disable();
    }
  }

  @Override
  public void stopMotor() {
    for (MotorController motorController : m_motorControllers) {
      motorController.stopMotor();
    }
  }

  @Override
  public void initSendable(SendableBuilder builder) {
    builder.setSmartDashboardType("Motor Controller");
    builder.setActuator(true);
    builder.setSafeState(this::stopMotor);
    builder.addDoubleProperty("Value", this::get, this::set);
  }
}
