// Author: Wheeler Law (wpl3499@rit.edu)
// Date: 2/26/14
// Description: Declares the interface for a 2-D point library

#ifndef POINT_H
#define POINT_H

// The minimum points required to run the algorithms
#define MIN_POINTS		3

// The maximum number of points to consider
#define MAX_POINTS 		100

// The maximum line size, including newlines and null character
#define MAX_LINE		80

// A 2-D point
struct Point {
	char label;     // a unique identifier for the point
	int x;          // the x coordinate
	int y;          // the y coordinate
};

// Indicates the winding order of the triangle formed by points
// p, q, and r.  In other words, given the line formed by pq,
// is r to the left (ccw), right(cw) or on (collinear) the line.
// @param p First point (usually the "anchor" point)
// @param q Second point
// @param r Third point
// @returns: ccw > 0, cw < 0, coll = 0
int ccw(struct Point p, struct Point q, struct Point r);

// Display a single point to standard output as:
//      label: (x,y)
// @param p The point to display
void displayPoint(struct Point p);

// Displays a collection of points, one per line to standard output.
// Assumes numPoints is valid.
// @param points A native array of Point's (immutable)
// @param numPoints The number of valid Point's in points
void displayPoints(struct Point points[], int numPoints);

// Two points are equal if the label, x and y coordinates
// are all equal to each other.
// @param p1 first point
// @param p2 second point
// @return 1 if equal, 0 if not equal
int equal(struct Point p1, struct Point p2);

// Return the index of p in points.
// Assumes numPoints is valid.
// @param p The point to search for
// @param points A native array of Point's (immutable)
// @param numPoints The number of valid Point's in points
// @return the index, if found, otherwise -1
int indexOf(struct Point p, struct Point points[], int numPoints);

// Determine the point with the smallest x-coordinate.
// Assumes numPoints is valid.
// @param points A native array of Point's (immutable)
// @param numPoints The number of valid Point's in points
// @return The resulting Point
struct Point leftmostPoint(struct Point points[], int numPoints);

// Determine the point with the largest x-coordinate.
// Assumes numPoints is valid.
// @param points A native array of Point's (immutable)
// @param numPoints The number of valid Point's in points
// @return The resulting Point
struct Point rightmostPoint(struct Point points[], int numPoints);

// Determine the point furthest "left" of the line a->z
// Assumes numPoints is valid.
// @param a Starting point of a line
// @param z Ending point of a line
// @param points A native array of Point's (immutable)
// @param numPoints The number of valid Point's in points
// @return The resulting Point
struct Point furthestLeftPoint(struct Point a, struct Point z, struct Point points[], int numPoints);

// Determine the set of points to the "left" of the line formed
// from 'a' to 'z' (a->z).
// Assumes numPoints is valid.
// @param a Starting point of a line
// @param z Ending point of a line
// @param points A native array of Point's (immutable)
// @param numPoints The number of valid Point's in points
// @param lps A native array of Point's (set of Points to the left of a->z)
// @return The number of points in the left point set
int leftPointSet(struct Point a, struct Point z, struct Point points[], int numPoints, struct Point lps[]);

// Determine the index of the point with the smallest y-coordinate.
// If the lowest y coordinate exists in more than one point in the
// set, the lowest x coordinate out of the candidates should be selected.
// Assumes numPoints is valid.
// @param points A native array of Point's (immutable)
// @param numPoints The number of valid Point's in points
// @return the lowest Point
struct Point lowestPoint(struct Point points[], int numPoints);

// Reads a collection of points from standard input into a 
// native array of points (between MIN_POINTS and MAX_POINTS)
// @param points A native array of Point's to populate (mutable)
// @return 0 if there is an error, otherwise the number of 
//  points read.
int readPoints(struct Point points[]);

// Swap two Point's in an array of Point's.  If either
// point is out of range this function should not
// alter the array.
// Assumes numPoints is valid.
// @param a the index of first value to swap
// @param b the index of second value to swap
// @param points A native array of Point's (mutable)
// @param numPoints, 
void swap(int a, int b, struct Point points[], int numPoints);

#endif
