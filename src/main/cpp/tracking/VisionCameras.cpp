#include "VisionCameras.h"


cs::UsbCamera wml::VisionCameraSetup::CameraSetup::CamSetup(int Port,  double FPS,  int ResHeight,  int ResWidth,  int Exposure,  std::string CamName) {
  cs::UsbCamera cam{CamName, Port};
  cam.SetResolution(ResWidth, ResHeight);
  sink.SetSource(cam);

  cam.SetExposureManual(Exposure);
  cam.SetFPS(FPS);
  
  return cam;
}

auto wml::VisionCameraSetup::CameraSetup::VideoMode(cs::UsbCamera cam, std::string camName) {
  auto video_mode = cam.GetVideoMode();
  output = frc::CameraServer::GetInstance()->PutVideo(camName, video_mode.width, video_mode.height);
  std::cout << "Width: " << video_mode.width << " Height: " << video_mode.height << std::endl;
  return video_mode;
}

cv::Mat wml::VisionCameraSetup::CameraSetup::ImageReturn(cs::UsbCamera cam, std::string camName) {
  if (CamStartUp) {
    video_modeStartup = wml::VisionCameraSetup::CameraSetup::VideoMode(cam, camName);
    CamStartUp = false;
  }
  auto video_mode = video_modeStartup;
  cv::Mat ImageSrc{video_mode.height, video_mode.width, CV_8UC3};

  return ImageSrc;
}