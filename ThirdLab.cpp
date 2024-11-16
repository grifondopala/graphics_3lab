#include "lib.h" 

using namespace std;
using namespace cv;


void showImage(const Mat image) {
    imshow("Display window", image);
}

void saveImage(Mat* image, string name) {
    imwrite("D:/MEPHI/KG/ThirdLab/ThirdLab/result/" + name, *image);
}

void Lines() {
   Mat lines = Mat::zeros({400, 400}, CV_8UC3);

   fillBackground(lines, WHITE);

   drawLine(10, 100, 200, 50, lines, BLACK);

   drawLine(100, 100, 200, 200, lines, BLACK);

   drawLine(200, 200, 100, 100, lines, BLACK);

   drawLine(100, 100, 10, 200, lines, BLACK);

   drawLine(10, 200, 10, 100, lines, BLACK);

   drawLine(200, 50, 300, 50, lines, BLACK);

   vector<MyPoint> points1 = drawLine(350, 100, 200, 150, lines, GREEN);

   vector<MyPoint> points2 = drawLine(200, 150, 350, 100, lines, GREEN);

   bool isEqual = true;
   for (int i = 0; i < points1.size(); ++i) {
       if (points1.at(i).x != points2.at(points1.size() - i - 1).x || points1.at(i).y != points2.at(points1.size() - i - 1).y) {
           isEqual = false;
       }
   }

   cout << isEqual << endl;

   saveImage(&lines, "lines.jpg");
}

void DefaultPolygons() {
    Mat polygonsDraw = Mat::zeros({ 1000, 1000 }, CV_8UC3);

    fillBackground(polygonsDraw, WHITE);

    vector<MyPoint> star = {
        {200, 600},
        {250, 500},
        {300, 600},
        {150, 550},
        {350, 550},
        {200, 600},
    };

    vector<MyPoint> star2 = {
        {200, 700},
        {250, 600},
        {300, 700},
        {150, 650},
        {350, 650},
        {200, 700},
    };


    vector<MyPoint> fig1 = {
     {200, 200},
     {300, 300},
     {200, 400},
     {400, 400},
     {500, 300},
     {400, 200},
     {300, 100},
     {250, 250},
     {350, 350},
     {450, 250},
     {350, 150},
     {250, 150},
     {200, 200}
    };

    vector<MyPoint> fig2 = {
        {600, 200},
        {700, 300},
        {600, 400},
        {800, 400},
        {900, 300},
        {800, 200},
        {700, 100},
        {650, 250},
        {750, 350},
        {850, 250},
        {750, 150},
        {650, 150},
        {600, 200} 
    };



    drawPolygon(star, polygonsDraw, BLACK, YELLOW, "even"); 

    drawPolygon(star2, polygonsDraw, BLACK, RED, "non");

    drawPolygon(fig1, polygonsDraw, BLACK, RED, "non");

    drawPolygon(fig2, polygonsDraw, BLACK, YELLOW, "even");

    saveImage(&polygonsDraw, "polygons.jpg");
}

void Intersactions() {
    Mat intersactionsDraw = Mat::zeros({ 1000, 1000 }, CV_8UC3);

    fillBackground(intersactionsDraw, WHITE);

    vector<vector<MyPoint>> shapes = {
        {
            {100, 100},
            {150, 50},
            {200, 100},
            {150, 150},
            {200, 200},
            {100, 150},
            {190, 120},
            {100, 100}
        },

        {
            {300, 300},
            {350, 250},
            {400, 300},
            {350, 350},
            {400, 400},
            {300, 350},
            {250, 400},
            {300, 300} 
        },
   
        {
            {500, 100},
            {600, 100},
            {550, 50},
            {600, 150},
            {550, 200},
            {500, 150},
            {450, 100},
            {500, 100} 
        },
  
        {
            {700, 600},
            {700, 700},
            {800, 700},
            {800, 600},
            {750, 650},
            {700, 600}
        },
        {
            {800, 400},
            {850, 400},
            {825, 350},
            {825, 450},
            {810, 450},
            {840, 470},
            {800, 400}
        }
    };

    for (int i = 0; i < 5; ++i) {
        Vec3b color = GREEN;

        if (hasIntersections(shapes[i])) {
            color = RED;
        }
        
        string method = (i & 1) == 0 ? "even" : "non";

        drawPolygon(shapes[i], intersactionsDraw, BLACK, color, method);
    }


    saveImage(&intersactionsDraw, "intersections.jpg");
}

void ConvexPolygons() {
    Mat convexDraw = Mat::zeros({ 1000, 1000 }, CV_8UC3);

    fillBackground(convexDraw, WHITE);

    vector<vector<MyPoint>> shapes = {
        {
            {100, 300},
            {150, 250},
            {200, 300},
            {200, 400},
            {150, 450},
            {100, 400},
            {100, 300}
        },
        {
            {300, 700},
            {350, 650},
            {400, 700},
            {450, 650},
            {475, 700},
            {450, 750},
            {400, 800},
            {350, 750},
            {300, 800},
            {300, 700}
        },
        {
            {500, 300},
            {550, 250},
            {575, 275},
            {600, 350},
            {550, 400},
            {500, 350},
            {500, 300}
        },
        {
            {700, 200},
            {750, 250},
            {800, 200},
            {775, 150},
            {800, 100},
            {700, 100},
            {650, 150},
            {700, 200}
        },
        {
            {850, 500},
            {900, 550},
            {950, 500},
            {900, 600},
            {950, 650},
            {850, 600},
            {800, 650},
            {850, 500}
        }
    };


    for (int i = 0; i < 5; ++i) {
        Vec3b color = RED;

        if (isConvex(shapes[i])) {
            color = GREEN;
        }

        string method = (i & 1) == 0 ? "even" : "non";

        drawPolygon(shapes[i], convexDraw, BLACK, color, method);
    }

    saveImage(&convexDraw, "convex.jpg");
}

void ThickLines() {
    Mat thickLines = Mat::zeros({ 400, 400 }, CV_8UC3);

    fillBackground(thickLines, WHITE);

    drawThickLine(40, 200, 200, 40, 50, thickLines, BLACK);

    drawDashLine(300, 200, 300, 300, 6, 2, 20, thickLines, RED);

    drawDashLine(250, 350, 350, 350, 3, 7, 20, thickLines, RED);

    drawDashLine(200, 350, 150, 250, 5, 5, 50, thickLines, RED);

    drawDashLine(40, 350, 150, 150, 5, 5, 1, thickLines, RED);

    saveImage(&thickLines, "thickLines.jpg");
}

int main()
{
    Lines();

    DefaultPolygons();

    Intersactions();

    ConvexPolygons();

    ThickLines();
    
    waitKey(0);

    return 0;
}

