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
  struct CameraSetup {

    // Camera Used

    /**
     * Sets the Camera up on Camera Server
     */
    cs::UsbCamera cam;
    cs::CvSink sink;
    int ResWidth;
    int ResHeight;

    /** 
     * Sets up the camera up using a Port, Height, Width and the Name of the Camera e.g Front
     */
    void CamSetup (int Port, int ResHeight, int ResWidth, std::string CamName);
  };

  struct KinectSetup {
    //@todo
  };
};