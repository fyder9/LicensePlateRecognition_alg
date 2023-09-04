	#include <opencv2/opencv.hpp>
	#include <iostream>
	using namespace std;
	using namespace cv; 
	/**
	 * Function to detect objects in an image using OpenCV.
	 *
	 * @param image The image to detect objects in.
	 * @return A vector of rectangles containing the detected objects.
	 */
	std::vector<cv::Rect> detectObjects(const cv::Mat image) {
		// Create a cascade classifier object
		cv::CascadeClassifier cascade;
		// Load the cascade classifier from the file
		cascade.load("haarcascade_license_plate_rus_16stages.xml");
		
		// Create a vector to store the detected objects
		std::vector<cv::Rect> objects;
		
		// Detect objects in the image
		cascade.detectMultiScale(image, objects, 1.01, 3);
		
		// Return the vector of detected objects
		return objects;
	}


	void crop(cv::Mat img, Point lcorn,Point rcorn){
		//cv::Rect myROI(lcorn.y,lcorn.x,rcorn.y,rcorn.x);
		cv::Mat cropped_image = img(cv::Rect(lcorn.x,lcorn.y,rcorn.x-lcorn.x,rcorn.y-lcorn.y));
		//cv::Mat cropped_image = img(cv::Range(lcorn.y,lcorn.x),cv::Range(rcorn.y,rcorn.x));
	 	namedWindow("Cropped image", WINDOW_AUTOSIZE);
		imshow("Cropped Image", cropped_image);
		} 


		
	int main(int argc, char** argv) {

		// Read the image
		cv::Mat image = cv::imread(argv[1]);
		
		// Check if the image was loaded successfully
		if (image.empty()) {
			std::cerr << "Error: Could not load image!" << std::endl;
			return 1;
		}
		
		// Detect objects in the image
		std::vector<cv::Rect> objects = detectObjects(image);
		
		// Print the number of detected objects
		std::cout << "Number of plates detected: " << objects.size() << std::endl;
		
		//draw a rectangle on  any recognized object
		 for ( size_t i = 0; i < objects.size(); i++ )
 		{
	
		Point leftcorn(objects[i].x, objects[i].y);
		Point rightcorn(objects[i].x+objects[i].width, objects[i].y+objects[i].height);
		rectangle(image, leftcorn, rightcorn,Scalar(255, 0, 0),3, LINE_8);
		crop(image,leftcorn,rightcorn);
		
		}
		
		namedWindow("Detected-plates", WINDOW_AUTOSIZE);
		imshow("Detected-plates",image);
		
 
		waitKey(0);
		return 0;
	}
