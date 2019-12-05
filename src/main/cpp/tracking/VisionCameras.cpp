#include "VisionCameras.h"



cs::UsbCamera wml::VisionCameraSetup::CamSetup(const int Port,  const double FPS,  const int ResHeight,  const int ResWidth,  const int Exposure,  const std::string CamName) {
  cs::UsbCamera cam{CamName, Port};
  cam.SetResolution(ResWidth, ResHeight);
  sink.SetSource(cam);

  cam.SetExposureManual(Exposure);
  cam.SetFPS(FPS);
  
  return cam;
}

auto wml::VisionCameraSetup::VideoMode(const cs::UsbCamera cam, std::string camName) {
  auto video_mode = cam.GetVideoMode();
  output = frc::CameraServer::GetInstance()->PutVideo(camName, video_mode.width, video_mode.height);
  std::cout << "Width: " << video_mode.width << " Height: " << video_mode.height << std::endl;
  return video_mode;
}

cv::Mat wml::VisionCameraSetup::ImageReturn(const cs::UsbCamera cam, std::string camName) {
  if (CamStartUp) {
    video_modeStartup = wml::VisionCameraSetup::VideoMode(cam, camName);
    CamStartUp = false;
  }
  auto video_mode = video_modeStartup;
  cv::Mat ImageSrc{video_mode.height, video_mode.width, CV_8UC3};

  return ImageSrc;
}