#include "lib.h"

using namespace std;
using namespace cv;

void setPixel(int x, int y, Mat& image, Vec3b color) {
	image.at<Vec3b>(y, x) = color;
}

void fillBackground(Mat& image, Vec3b color) {
    for (int y = 0; y < image.rows; ++y) {
        for (int x = 0; x < image.cols; ++x) {
            setPixel(x, y, image, color);
        }
    }
}


vector<MyPoint> drawLine(int x1, int y1, int x2, int y2, int thickness, Mat& image, Vec3b color) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int ix = (x1 < x2) ? 1 : -1;
    int iy = (y1 < y2) ? 1 : -1;

    vector<MyPoint> points = {};

    int currentX1;
    int currentY1;

    for (int offset = -(thickness / 2); offset <= (thickness / 2); ++offset) {
        int E = (dx > dy) ? (2 * dy - dx) : (2 * dx - dy);

        int currentX1 = dy == 0 ? x1 : x1 + offset;
        int currentY1 = dy == 0 ? y1 + offset : y1;

        if (dx >= dy) {
            for (int i = 0; i <= dx; ++i) {
                setPixel(currentX1, currentY1, image, color);
                points.push_back({ currentX1, currentY1 });
                if (E >= 0) {
                    currentY1 += iy;
                    E -= 2 * dx;
                }
                currentX1 += ix;
                E += 2 * dy;
            }
        }
        else {
            for (int i = 0; i <= dy; ++i) {
                setPixel(currentX1, currentY1, image, color);
                points.push_back({ currentX1, currentY1 });
                if (E >= 0) {
                    currentX1 += ix;
                    E -= 2 * dy;
                }
                currentY1 += iy;
                E += 2 * dx;
            }
        }
    }

    return points;
}


vector<MyPoint> drawDashLine(int x1, int y1, int x2, int y2, int thickness, Mat& image, Vec3b color) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int ix = (x1 < x2) ? 1 : -1;
    int iy = (y1 < y2) ? 1 : -1;

    vector<MyPoint> points = {};

    int lengthPart = 20;
    int startDash = 15;

    for (int offset = -(thickness / 2); offset <= (thickness / 2); ++offset) {
        int E = (dx > dy) ? (2 * dy - dx) : (2 * dx - dy);
        int currentX1 = x1;
        int currentY1 = y1 + offset;

        int i = 0;

        if (dx >= dy) {
            for (i = 0; i <= dx; ++i) {
                if ((i % lengthPart) < startDash) {
                    setPixel(currentX1, currentY1, image, color);
                }
                points.push_back({ currentX1, currentY1 });
                if (E >= 0) {
                    currentY1 += iy;
                    E -= 2 * dx;
                }
                currentX1 += ix;
                E += 2 * dy;
            }
        }
        else {
            for (i = 0; i <= dy; ++i) {
                if ((i % lengthPart) < startDash) {
                    setPixel(currentX1, currentY1, image, color);
                }
                points.push_back({ currentX1, currentY1 });
                if (E >= 0) {
                    currentX1 += ix;
                    E -= 2 * dy;
                }
                currentY1 += iy;
                E += 2 * dx;
            }
        }
    }

    return points;
}



int cross(const MyPoint& p1, const MyPoint& p2, const MyPoint& p3) {
    return (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
}


bool intersect(const MyPoint& p1, const MyPoint& p2, const MyPoint& p3, const MyPoint& p4) {
    int d1 = cross(p1, p2, p3);
    int d2 = cross(p1, p2, p4);
    int d3 = cross(p3, p4, p1);
    int d4 = cross(p3, p4, p2);

    if (d1 * d2 < 0 && d3 * d4 < 0) {
        return true;
    }

    return false;
}

bool hasIntersections(const vector<MyPoint>& points) {
    int n = points.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 2; j < n - 1; ++j) {
            if (j != i + 1) {
                if (intersect(points[i], points[i + 1], points[j], points[j + 1])) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool isConvex(const vector<MyPoint>& points) {
    int n = points.size();
    if (n < 3) return false;

    int res = 0; 

    for (int i = 0; i < n; ++i) {
        int dx1 = points[(i + 1) % n].x - points[i].x;
        int dy1 = points[(i + 1) % n].y - points[i].y;
        int dx2 = points[(i + 2) % n].x - points[(i + 1) % n].x;
        int dy2 = points[(i + 2) % n].y - points[(i + 1) % n].y;

        int cross = dx1 * dy2 - dy1 * dx2;

        if (res == 0) {
            res = cross;
        }
        else {
            if (res * cross < 0) {
                return false;
            }
        }
    }
    return true; 
}


bool EvenOdd(const vector<MyPoint>& points, MyPoint point) {
    double x = point.x, y = point.y;
    int collisions = 0;

    for (int i = 0; i < points.size(); i++) {
        MyPoint p1 = points[i];
        MyPoint p2 = points[(i + 1) % points.size()];

        if (y > min(p1.y, p2.y) && y <= max(p1.y, p2.y)) {
            double x_intersection = (y - p1.y) * (p2.x - p1.x) / (p2.y - p1.y) + p1.x;

            if (x <= x_intersection) {
                collisions++;
            }
        }
    }

    return (collisions % 2) == 1;
}

bool NonZeroWinding(const vector<MyPoint>& points, MyPoint point) {
    int windingNumber = 0;

    size_t numPoints = points.size();
    for (size_t i = 0; i < numPoints; ++i) {
        const MyPoint& p1 = points[i];
        const MyPoint& p2 = points[(i + 1) % numPoints];

        if (p1.y <= point.y) {
            if (p2.y > point.y && cross(p1, p2, point) > 0) {
                windingNumber++;
            }
        }
        else {
            if (p2.y <= point.y && cross(p1, p2, point) < 0) {
                windingNumber--;
            }
        }
    }

    return windingNumber != 0;
}


void floodFill8(const vector<MyPoint>& points, const vector<MyPoint> borderPoints, Vec3b background, Vec3b borderColor, Mat& image, string method)
{
    int dx[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
    int dy[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
    
    vector<MyPoint> stack = borderPoints;

    while (!stack.empty()) {
        MyPoint currentPoint = stack.back();
        stack.pop_back();

        Vec3b currentColor = image.at<Vec3b>(currentPoint.y, currentPoint.x);

        if (currentColor != borderColor) {
            setPixel(currentPoint.x, currentPoint.y, image, background);
        }

        for (int i = 0; i < 8; i++) {
            int nx = currentPoint.x + dx[i];
            int ny = currentPoint.y + dy[i];

            bool isInside = method == "even" ? EvenOdd(points, { nx, ny }) : NonZeroWinding(points, { nx, ny });

            if (nx >= 0 && nx < image.cols && ny >= 0 && ny < image.rows && isInside) {
                Vec3b currentColor = image.at<Vec3b>(ny, nx); 
                
                if (currentColor != background && currentColor != borderColor)
                    stack.push_back({nx, ny});
            }
        }
    }
}


void drawPolygon(const vector<MyPoint>& points, Mat& image, Vec3b borderColor, Vec3b background, string method) {   
    vector<MyPoint> borderPoints = {};
    
    for (int i = 0; i < points.size() - 1; ++i) {
        vector<MyPoint> border = drawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y, 1, image, borderColor);

        borderPoints.insert(borderPoints.end(), border.begin(), border.end());
    }

    floodFill8(points, borderPoints, background, borderColor, image, method);
}

