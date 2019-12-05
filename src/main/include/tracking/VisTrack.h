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

// Tracking Libraires
#include "VisionCameras.h"
#include "VisionProcessingType.h"
#include "VisionOutput.h"

#include <cameraserver/CameraServer.h>
#include <cscore.h>

namespace wml {
  struct VisionConfig {

    cv::Mat imgOrigin;
    
    /** 
     * Sets up vision using OpenCV & Camera Servers
     */
    void SetupVision(int CamPort, int ResHeight, int ResWidth, std::string Name);


    /**
     * Track using retro reflective tape, Using low exposure and Green pixle filtering
     * Using the defaults for the colour spectrum and exposure settings.
     */
    void RetroTrack(cv::Mat Img, int ErosionSize);

    /**
     * Track using your own adjusted settings for the colour spectrum and exposure
     */
    void CustomTrack(cv::Mat Img, int HSVColourLowRange, int HSVColourHighRange, int CamExposure, int ErosionSize);
  };
};