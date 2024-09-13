// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <wpi/SymbolExports.h>
#include <wpi/struct/Struct.h>

#include "frc/geometry/Pose2d.h"

template <>
struct WPILIB_DLLEXPORT wpi::Struct<frc::Pose2d> {
  static constexpr std::string_view GetTypeString() { return "struct:Pose2d"; }
  static constexpr size_t GetSize() {
    return wpi::GetStructSize<frc::Translation2d>() +
           wpi::GetStructSize<frc::Rotation2d>();
  }
  static constexpr std::string_view GetSchema() {
    return "Translation2d translation;Rotation2d rotation";
  }

  static frc::Pose2d Unpack(std::span<const uint8_t> data);
  static void Pack(std::span<uint8_t> data, const frc::Pose2d& value);
  static void ForEachNested(
      std::invocable<std::string_view, std::string_view> auto fn) {
    wpi::ForEachStructSchema<frc::Translation2d>(fn);
    wpi::ForEachStructSchema<frc::Rotation2d>(fn);
  }
};

static_assert(wpi::StructSerializable<frc::Pose2d>);
static_assert(wpi::HasNestedStruct<frc::Pose2d>);
