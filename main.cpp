//
//  main.cpp
//  Project_#2
//
//  Created by Tianyu He on 10/5/23.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Point {
    double x, y;
};

Point p0; // Starting point

//Returns the square of the direct distance between two points
double distanceSq(Point p1, Point p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}


//Determine the directional relationship between the three points p, q and r.
int orientation(Point p, Point q, Point r) {
    double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;  // collinear
    return (val > 0) ? 1 : 2; // clock or counterclockwise
}

//Determine if the three points are collinear
bool compare(Point p1, Point p2) {
    int o = orientation(p0, p1, p2);
    if (o == 0)
        return (distanceSq(p0, p2) >= distanceSq(p0, p1));
    return (o != 2);
}

vector<Point> grahamScan(vector<Point> points) {
    // Find P0
    int n = points.size();
    int ymin = points[0].y, min = 0;
    for (int i = 1; i < n; i++) {
        int y = points[i].y;
        if ((y < ymin) || (ymin == y && points[i].x < points[min].x)) {
            static_cast<void>(ymin = points[i].y), min = i;
        }
    }
    //sort all the points
    swap(points[0], points[min]);
    p0 = points[0];
    sort(points.begin() + 1, points.end(), compare);


    vector<Point> hull;
    hull.push_back(p0);
    for (int i = 1; i < n; i++) {
        //If the three points are not clockwise, pop out of the stack
        while (hull.size() > 1 && orientation(hull[hull.size()-2], hull.back(), points[i]) != 1)
        {
            hull.pop_back();
        }

        hull.push_back(points[i]);
        
    }

    return hull;
}

int main() {
    int n;
    vector<Point> points;

    while (true) {
        cout << "Enter the number of points: ";
        cin >> n;

        if (n < 3) {
            cout << "Error: At least 3 points are required to form a convex hull. Try again.\n";
            continue;
        }

        points.clear();
        cout << "Enter the coordinates of the points (x y):\n";
        for (int i = 0; i < n; i++) {
            Point p;
            cin >> p.x >> p.y;

            if (!cin) {  // check if input operation was successful
                cout << "Invalid input. Please enter the coordinates again." << endl;
                cin.clear();  // clear the error state
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // discard invalid input
                i--;  // decrement the loop counter to retry input for the same point
                continue;
            }

            points.push_back(p);
            cout << "Current size of points: " << points.size() << endl;
        }


        auto hull = grahamScan(points);
        if (hull.size() < 3) {
            cout << "Error: The given points do not form a convex hull. Try again.\n";
            continue;
        }

        cout << "Convex Hull:\n";
        for (const auto &p : hull) {
            cout << "(" << p.x << ", " << p.y << ")\n";
        }
        break;
    }

    return 0;
}
