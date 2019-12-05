#pragma once 

#include <opencv2/opencv.hpp>
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include <stdio.h>
#include <iostream>

#include <cameraserver/CameraServer.h>
#include <cscore.h>

namespace wml {
  struct VisionCameraSetup {

    /** 
     * Sets up the camera up using a Port, Framerate, Height, Width, Exposure level and the Name of the Camera e.g Front
     */
    cs::UsbCamera CamSetup(static const cs::CvSource *output, static const int Port, static const double FPS, static const int ResHeight, static const int ResWidth, static const int Exposure, static const std::string CamName);

    /**
     * Get's the Video Mode from the camera
     */
    auto VideoMode(static const cs::UsbCamera cam);


    /**
     * Returns the image as a Mat from the Camera
     */
    cv::Mat ImageReturn(static const cs::UsbCamera cam);

  };

  struct VisionKinectSetup {
    //@todo
  };
};