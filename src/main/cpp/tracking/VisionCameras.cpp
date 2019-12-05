#include "VisionCameras.h"



cs::UsbCamera wml::VisionCameraSetup::CamSetup(const cs::CvSource *output,  const int Port,  const double FPS,  const int ResHeight,  const int ResWidth,  const int Exposure,  const std::string CamName) {
  cs::UsbCamera cam{CamName, Port};
  cs::CvSink sink{"USB"};
  cam.SetResolution(ResWidth, ResHeight);
  sink.SetSource(cam);

  cam.SetExposureManual(Exposure);
  cam.SetFPS(FPS);
  
  return cam;
}

auto wml::VisionCameraSetup::VideoMode(const cs::UsbCamera cam) {
  auto video_mode = cam.GetVideoMode();
  return video_mode;
}

cv::Mat wml::VisionCameraSetup::ImageReturn(const cs::UsbCamera cam) {
  auto video_mode = wml::VisionCameraSetup::VideoMode(cam);
  cv::Mat ImageSrc{video_mode.height, video_mode.width};

  return ImageSrc;
}