// Author: Wheeler Law (wpl3499@rit.edu)
// Date: 2/26/14
// Description: Implements the quickhull algorithm. 

#include <stdio.h>
#include "points.h"

int quickHull(struct Point lps[],struct Point leftmost,
	      struct Point rightmost,int numPointsLps);

/** The main quickhull algorithm. Takes no arguments and prints out the results
 ** to standard output. Calculates the convex hull utilising the quickhull
 ** algorithm. Takes input from standard input.
 **/
int main(int argc, char** argv){
	struct Point points[MAX_POINTS];
	int numPoints=readPoints(points);
	
	struct Point hullPoints[MAX_POINTS];
	
	printf("Set of points:\n");
	displayPoints(points,numPoints);
	
	struct Point leftmost=leftmostPoint(points,numPoints);
	struct Point rightmost=rightmostPoint(points,numPoints);
	
	struct Point lps[MAX_POINTS];
	int numPointsLps=leftPointSet(leftmost,rightmost,points,numPoints,lps);
	
	struct Point rps[MAX_POINTS];
	int numPointsRps=leftPointSet(rightmost,leftmost,points,numPoints,rps);
	
	
	// Quickhull() modifies the arrays, so we need to update the length of 
	// said arrays.
	numPointsLps=quickHull(lps,leftmost,rightmost,numPointsLps);
	numPointsRps=quickHull(rps,rightmost,leftmost,numPointsRps);
	
	hullPoints[0]=leftmost;
	for(int i=0;i<numPointsLps;i++){
		hullPoints[i+1]=lps[i];
	}
	hullPoints[numPointsLps+1]=rightmost;
	for(int i=0;i<numPointsRps;i++){
		hullPoints[i+2+numPointsLps]=rps[i];
	}
	
	printf("Convex hull:\n");
	displayPoints(hullPoints,numPointsRps+numPointsLps+2);
	return 0;
}

/** The recursive portion of the quickhull algorithm. 
 ** @param points A native array of the points to the left of line l <-> r.
 ** @param leftmost The left most point.
 ** @param rightmost The right most point.
 ** @param numPoints The number of points left of the line l <-> r.
 ** @return The length of the points[] array since it was modified. 
 **/
int quickHull(struct Point points[], struct Point leftmost,
	      struct Point rightmost,int numPoints){
	if(!numPoints)
		return numPoints;
	struct Point furthest=furthestLeftPoint(leftmost,rightmost,points,
						numPoints);
	
	struct Point lps[numPoints]; // numPoints is just a space optimization
	int numPointsLps=leftPointSet(leftmost,furthest,points,numPoints,lps);
	
	struct Point rps[numPoints];
	int numPointsRps=leftPointSet(furthest,rightmost,points,numPoints,rps);

	
	// Modifying the array, so we need to update the length of the array.
	numPointsLps=quickHull(lps,leftmost,furthest,numPointsLps);
	numPointsRps=quickHull(rps,furthest,rightmost,numPointsRps);
	
	for(int i=0;i<numPointsLps;i++){
		points[i]=lps[i];
	}
	points[numPointsLps]=furthest;
	for(int i=0;i<numPointsRps;i++){
		points[i+numPointsLps+1]=rps[i];
	}
		
	// Return the length of the points[] array. 
	return numPointsLps+numPointsRps+1;
}