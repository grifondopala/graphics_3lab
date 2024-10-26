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

   drawLine(10, 100, 200, 50, 1, lines, BLACK);

   drawLine(100, 100, 200, 200, 1, lines, BLACK);

   drawLine(200, 200, 100, 100, 1, lines, BLACK);

   drawLine(100, 100, 10, 200, 1, lines, BLACK);

   drawLine(10, 200, 10, 100, 1, lines, BLACK);

   drawLine(200, 50, 300, 50, 1, lines, BLACK);

   drawLine(350, 100, 200, 150, 1, lines, GREEN);

   drawLine(200, 150, 350, 100, 1, lines, GREEN);

   saveImage(&lines, "lines.jpg");
}

void DefaultPolygons() {
    Mat polygonsDraw = Mat::zeros({ 600, 600 }, CV_8UC3);

    fillBackground(polygonsDraw, WHITE);

    vector<MyPoint> square = {
        {50, 50},
        {150, 50},
        {150, 150},
        {50, 150},
        {50, 50},
    };

    vector<MyPoint> triangle = {
        {200, 50},
        {150, 150},
        {250, 150},
        {200, 50},
    };

    vector<MyPoint> hexagon = {
        {300, 100},
        {350, 125}, 
        {350, 175},
        {300, 200}, 
        {250, 175},  
        {250, 125},
        {300, 100}, 
    };

    vector<MyPoint> star = {
        {400, 100},  
        {450, 200},  
        {550, 200},  
        {475, 275},  
        {500, 400},  
        {400, 325},  
        {300, 400},  
        {325, 275},  
        {250, 200},  
        {350, 200},   
        {400, 100},
    };

    drawPolygon(square, polygonsDraw, BLACK, RED, "even");

    drawPolygon(triangle, polygonsDraw, BLACK, BLUE, "even");
    drawPolygon(hexagon, polygonsDraw, BLACK, YELLOW, "non");

    drawPolygon(star, polygonsDraw, BLACK, YELLOW, "non");

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

    drawLine(40, 200, 200, 40, 50, thickLines, BLACK);

    drawDashLine(60, 300, 200, 140, 40, thickLines, BLACK);

    drawLine(300, 200, 300, 300, 20, thickLines, RED);

    drawLine(250, 350, 350, 350, 20, thickLines, RED);

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

