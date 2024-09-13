// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

package edu.wpi.first.wpilibj.xrp;

import edu.wpi.first.hal.SimDevice;
import edu.wpi.first.hal.SimDevice.Direction;
import edu.wpi.first.hal.SimDouble;
import java.util.HashMap;
import java.util.HashSet;

/**
 * XRPServo.
 *
 * <p>A SimDevice based servo
 */
public class XRPServo {
  private static HashMap<Integer, String> s_simDeviceNameMap = new HashMap<>();
  private static HashSet<Integer> s_registeredDevices = new HashSet<>();

  private static void checkDeviceAllocation(int deviceNum) {
    if (!s_simDeviceNameMap.containsKey(deviceNum)) {
      throw new IllegalArgumentException("Invalid XRPServo device number. Should be 4-5");
    }

    if (s_registeredDevices.contains(deviceNum)) {
      throw new IllegalArgumentException("XRPServo " + deviceNum + " already allocated");
    }

    s_registeredDevices.add(deviceNum);
  }

  static {
    s_simDeviceNameMap.put(4, "servo1");
    s_simDeviceNameMap.put(5, "servo2");
  }

  private final SimDouble m_simPosition;

  /** XRPServo. */
  public XRPServo(int deviceNum) {
    checkDeviceAllocation(deviceNum);

    // We want this to appear on WS as type: "XRPServo", device: <servo name>
    String simDeviceName = "XRPServo:" + s_simDeviceNameMap.get(deviceNum);
    SimDevice xrpServoSimDevice = SimDevice.create(simDeviceName);

    if (xrpServoSimDevice != null) {
      xrpServoSimDevice.createBoolean("init", Direction.kOutput, true);
      // This should mimic PWM position [0.0, 1.0]
      m_simPosition = xrpServoSimDevice.createDouble("position", Direction.kOutput, 0.5);
    } else {
      m_simPosition = null;
    }
  }

  /**
   * Set the servo angle.
   *
   * @param angle Desired angle in degrees
   */
  public void setAngle(double angle) {
    if (angle < 0.0) {
      angle = 0.0;
    }

    if (angle > 180.0) {
      angle = 180.0;
    }

    double pos = angle / 180.0;

    if (m_simPosition != null) {
      m_simPosition.set(pos);
    }
  }

  /**
   * Get the servo angle.
   *
   * @return Current servo angle
   */
  public double getAngle() {
    if (m_simPosition != null) {
      return m_simPosition.get() * 180.0;
    }

    return 90.0;
  }

  /**
   * Set the servo position.
   *
   * @param pos Desired position (Between 0.0 and 1.0)
   */
  public void setPosition(double pos) {
    if (pos < 0.0) {
      pos = 0.0;
    }

    if (pos > 1.0) {
      pos = 1.0;
    }

    if (m_simPosition != null) {
      m_simPosition.set(pos);
    }
  }

  /**
   * Get the servo position.
   *
   * @return Current servo position
   */
  public double getPosition() {
    if (m_simPosition != null) {
      return m_simPosition.get();
    }

    return 0.5;
  }
}
