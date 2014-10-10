// Author: Wheeler Law (wpl3499@rit.edu)
// Date: 2/26/14
// Description: Implements the Jarvis (gift wrapping) algorithm. 

#include <stdio.h>
#include "points.h"

/** main
 ** The main Jarvis algorithm. Takes no arguments. Calculates the 
 ** convex hull based on the points using the gift wrapping algorithm. 
 ** Takes input from standard input. 
 **/
int main(int argc, char** argv){

	struct Point points[MAX_POINTS];
	int numPoints=readPoints(points);
	
	printf("Set of points:\n");
	displayPoints(points,numPoints);
	
	struct Point hullPoints[MAX_POINTS];
	struct Point pointOnHull=leftmostPoint(points,numPoints);

	struct Point endpoint;
	
	int i=0;
	do{
		hullPoints[i]=pointOnHull;
		endpoint=points[0];
		
		for(int j=1;j<numPoints;j++){
			if(equal(endpoint,pointOnHull) || ccw(hullPoints[i],
			   endpoint,points[j])>0){ //Splitting the line
				endpoint=points[j];
			}
		}
		i++;
		pointOnHull=endpoint;
	}while(!equal(endpoint,hullPoints[0]));
	
	printf("Convex hull:\n");
	displayPoints(hullPoints,i);
	return 0;
}
	
