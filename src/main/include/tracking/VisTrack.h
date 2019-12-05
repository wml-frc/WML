#pragma once

#include <opencv2/opencv.hpp>
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include "tracking/Cameras.h"
#include <stdio.h>
#include <iostream>

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
     */
    void RetroTrack()
  };
};