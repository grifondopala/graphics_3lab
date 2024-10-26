#ifndef LIB_H 
#define LIB_H

#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <limits>

using namespace cv;
using namespace std;

struct MyPoint {
	int x;
	int y;
};

const Vec3b BLACK  = { 0, 0, 0 };
const Vec3b WHITE  = { 255, 255, 255 };
const Vec3b RED    = { 0, 0, 255 };      
const Vec3b GREEN  = { 0, 255, 0 };    
const Vec3b BLUE   = { 255, 0, 0 };
const Vec3b YELLOW = { 0, 255, 255 };


void setPixel(int x, int y, Mat& image, Vec3b color);

void fillBackground(Mat& image, Vec3b color);

vector<MyPoint> drawLine(int x1, int y1, int x2, int y2, int thickness, Mat& image, Vec3b color);

vector<MyPoint> drawDashLine(int x1, int y1, int x2, int y2, int thickness, Mat& image, Vec3b color);

void drawPolygon(const vector<MyPoint>& points, Mat& image, Vec3b borderColor, Vec3b background, string method);

bool hasIntersections(const vector<MyPoint>& points);

bool isConvex(const vector<MyPoint>& points);

#endif