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
	 //	Point center( objects[i].x + objects[i].width/2, objects[i].y + objects[i].height/2 );
 	//	ellipse( image, center, Size( objects[i].width/2, objects[i].height/2 ), 0, 0, 360, Scalar( 255, 0, 255 ), 4 );
		
		//Drawing a rectangle over the detected object
		Point leftcorn(objects[i].x, objects[i].y);
		Point rightcorn(objects[i].x+objects[i].width, objects[i].y+objects[i].height);

		rectangle(image, leftcorn, rightcorn,Scalar(255, 0, 0),3, LINE_8);
		}
		//output image with circle over the detected object
		namedWindow("Detected-plates", WINDOW_AUTOSIZE);
		imshow("Detected-plates",image);
		waitKey(0);
		return 0;
	}
