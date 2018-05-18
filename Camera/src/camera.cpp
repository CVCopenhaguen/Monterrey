#include <iostream>
#include <fstream>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <string>
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	ofstream csv_file;
	csv_file.open("../genfiles/2Dpoints.txt");
	int th = 195;
	int const maxval = 255;
	int th_type = 0;
    	VideoCapture cap;
	int ss = 3;
	//bool nd = true;
	Mat ele = getStructuringElement(cv::MORPH_RECT, cv::Size(ss, ss), cv::Point(1, 1) );
	vector<int> a;
	size_t a_size = a.size();
	size_t i2 = 40;
	size_t i1 = 420;
	size_t ref_i = 413;// row
	size_t ref_j = 443;// column
    	// open(1) for usb cam located in /dev/video1
    	if(!cap.open(1))
        	return 0;
	
    	for(;;)
    	{
        	Mat frame;
          	cap >> frame;
          	if( frame.empty() ) break; // end of video stream
		
		Rect Rct(85,30,555,450);
		Mat ROI = frame(Rct);

		// Detection starts here
		
		cvtColor(ROI, ROI, COLOR_BGR2GRAY);
		Mat thresholded;
		threshold( ROI, thresholded, th, maxval, th_type);
		//erode(thresholded, thresholded, ele);

		// Detection ends here		
          	imshow("Nat View", frame);
		imshow("ROI", ROI);
		imshow("USB external camera)", thresholded);
		//waitKey(5000);
       		//if( waitKey(10) == 27 ) break; // stop capturing by pressing ESC 		

		// Get two points separated 20cm (between image rows 1 and 460)
		if( a_size < 4 )
		{
		for( size_t j=0; j<thresholded.cols; j++)
		{
			if (thresholded.at<uchar>(i1,j) == 255)
			{
				cout << "Point 1 (X, Y) = (" << i1 << ", " << j << ")" << endl;
				for( size_t v=j; v<thresholded.cols; v++)
				{
					size_t t = v-j;
					if (thresholded.at<uchar>(i2,v) == 255 && t<8)
					{
						
						cout << "Point 2 (X, Y) = (" << i2 << ", " << v << ")" << endl;
						int pX1 = (int) j-ref_j;
						a.push_back(pX1);
						int pY1 = (int) i1-ref_i;
						a.push_back(pY1);
						int pX2 = (int) v-ref_j;
						a.push_back(pX2);
						int pY2 = (int) i2-ref_i;
						a.push_back(pY2);
						csv_file << pX1 << " " << pY1 << " " << pX2 << " " << pY2 << endl;
						csv_file.close();
						a_size = a.size();					
					}
				}
			}
		}
		} // if

		else {cout << "Points were stored" << endl;
			a.clear();}
		
		cout << endl;
		cout << endl;
		cout << endl;
		cout << "--------------------------------------------------  NEW FRAME --------------------------------------" << endl;
		cout << endl;
		cout << endl;
		cout << endl;
		waitKey(10000);
		//a.clear();

	} // for ;;	
	
    	// the camera will be closed automatically upon exit
    	// cap.close();
    	return 0;
}
