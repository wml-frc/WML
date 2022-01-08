#include "Files.h"

#include <frc/RobotBase.h>
#include <frc/Filesystem.h>
#include <wpi/SmallString.h>

#include <cstdarg>

using namespace wml;

std::string files::GetDeployDirectory(std::string project) {
  // GradleRIO launches sim in the project root. This project is a bit special so 
  // we have to do it ourself.
  wpi::SmallString<256> result;
  if (frc::RobotBase::IsReal()) {
    frc::filesystem::GetDeployDirectory();
    return std::string(result.c_str());
  } else {
    frc::filesystem::GetLaunchDirectory();

    // fs::path::append(result);
    return std::string(result.c_str());
  }
}
