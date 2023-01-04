#pragma once
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>
#include <leptonica/allheaders.h>
#include <tesseract/baseapi.h>
#include <iostream>
#include "CNIC.h"
using namespace cv;
using namespace tesseract;
using namespace std;


class Util
{

	
public:	
	
	static Mat image;
	static Mat temp;

	static bool state;

	static CNIC cnic;
	

	static void init();


	static bool readText(Mat image);

	static Mat addContour(Mat image);

	static Mat detectCircle(Mat frame);
};

