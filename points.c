// Author: Wheeler Law (wpl3499@rit.edu)
// Date: 2/19/14
// Description: Declares the interface for a 2-D point library

#include "points.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/** Indicates the winding order of the triangle formed by points
 ** p, q, and r.  In other words, given the line formed by pq,
 ** is r to the left (ccw), right(cw) or on (collinear) the line.
 ** @param p First point (usually the "anchor" point)
 ** @param q Second point
 ** @param r Third point
 ** @returns: ccw > 0, cw < 0, coll = 0
 **/
int ccw(struct Point p, struct Point q, struct Point r){
	return (q.x - p.x)*(r.y - p.y) - (q.y - p.y)*(r.x - p.x);
}

/** Display a single point to standard output as:
 **     label: (x,y)
 ** @param p The point to display
 **/
void displayPoint(struct Point p){
	printf("%c: (%d,%d)\n",p.label,p.x,p.y);
}

/** Displays a collection of points, one per line to standard output.
 ** Assumes numPoints is valid.
 ** @param points A native array of Point's (immutable)
 ** @param numPoints The number of valid Point's in points
 **/
void displayPoints(struct Point points[], int numPoints){
	for(int i=0;i<numPoints;i++){
		displayPoint(points[i]);
	}
}

/** Two points are equal if the label, x and y coordinates
 ** are all equal to each other.
 ** @param p1 first point
 ** @param p2 second point
 ** @return 1 if equal, 0 if not equal
 **/
int equal(struct Point p1, struct Point p2){
	if((p1.label==p2.label) && (p1.x==p2.x) && (p1.y==p2.y)){
		return 1;
	}else
		return 0;
}

/** Return the index of p in points.
 ** Assumes numPoints is valid.
 ** @param p The point to search for
 ** @param points A native array of Point's (immutable)
 ** @param numPoints The number of valid Point's in points
 ** @return the index, if found, otherwise -1
 **/
int indexOf(struct Point p, struct Point points[], int numPoints){
	for(int i=0;i<numPoints;i++){
		if(p.label==points[i].label && p.x==points[i].x &&
		p.y==points[i].y){
			return i;
		}
	}
	return -1;
}

/** Determine the point with the smallest x-coordinate.
 ** Assumes numPoints is valid.
 ** @param points A native array of Point's (immutable)
 ** @param numPoints The number of valid Point's in points
 ** @return The resulting Point
 **/
struct Point leftmostPoint(struct Point points[], int numPoints){
	struct Point leftmostPoint=points[0];
	
	for(int i=1;i<numPoints;i++){
		if(points[i].x<leftmostPoint.x){
			leftmostPoint=points[i];
		}else if(points[i].x==leftmostPoint.x){
			if(points[i].y<leftmostPoint.y){
				leftmostPoint=points[i];
			}
		}
	}
	
	return leftmostPoint;
}

/** Determine the point with the largest x-coordinate.
 ** Assumes numPoints is valid.
 ** @param points A native array of Point's (immutable)
 ** @param numPoints The number of valid Point's in points
 ** @return The resulting Point
 **/
struct Point rightmostPoint(struct Point points[], int numPoints){
	struct Point rightmostPoint=points[0];
	
	for(int i=1;i<numPoints;i++){
		if(points[i].x>rightmostPoint.x){
			rightmostPoint=points[i];
		}else if(points[i].x==rightmostPoint.x){
			if(points[i].y>rightmostPoint.y){
				rightmostPoint=points[i];
			}
		}
	}
	
	return rightmostPoint;
}

/** Determine the point furthest "left" of the line a->z
 ** Assumes numPoints is valid.
 ** @param a Starting point of a line
 ** @param z Ending point of a line
 ** @param points A native array of Point's (immutable)
 ** @param numPoints The number of valid Point's in points
 ** @return The resulting Point
 **/
struct Point furthestLeftPoint(struct Point a, struct Point z,
			struct Point points[], int numPoints){
	struct Point leftmostPoint;
	double maxDistance=0.0;
	
	for(int i=0;i<numPoints;i++){
		// http://en.wikipedia.org/wiki/Distance_from_a_point_to_a_line
		// #Line_defined_by_two_points
		// To be read as one link^
		double d=fabs((a.y-z.y)*points[i].x-(a.x-z.x)*points[i].y+a.x*
		z.y-z.x*a.y)/sqrt((a.x-z.x)*(a.x-z.x)+(a.y-z.y)*(a.y-z.y));
		if(d>maxDistance && ccw(a,z,points[i])>0){
			leftmostPoint=points[i];
		}
	}
	return leftmostPoint;
	
	
}

/** Determine the set of points to the "left" of the line formed
 ** from 'a' to 'z' (a->z).
 ** Assumes numPoints is valid.
 ** @param a Starting point of a line
 ** @param z Ending point of a line
 ** @param points A native array of Point's (immutable)
 ** @param numPoints The number of valid Point's in points
 ** @param lps A native array of Point's (set of Points to the left of a->z)
 ** @return The number of points in the left point set
 **/
int leftPointSet(struct Point a, struct Point z, struct Point points[],
				 int numPoints, struct Point lps[]){
	int j=0;
	for(int i=0;i<numPoints;i++){
		if(ccw(a,z,points[i])>0){
			lps[j]=points[i];
			j++;
		}
	}
	
	return j;
}

/** Determine the index of the point with the smallest y-coordinate.
 ** If the lowest y coordinate exists in more than one point in the
 ** set, the lowest x coordinate out of the candidates should be selected.
 ** Assumes numPoints is valid.
 ** @param points A native array of Point's (immutable)
 ** @param numPoints The number of valid Point's in points
 ** @return the lowest Point
 **/
struct Point lowestPoint(struct Point points[], int numPoints){
	struct Point lowest=points[0];
	
	for(int i=1;i<numPoints;i++){
		if(points[i].y<lowest.y){
			lowest=points[i];
		}else if(points[i].y==lowest.y){
			if(points[i].x<lowest.x){
				lowest=points[i];
			}
		}
	}
	
	return lowest;
}

/** Reads a collection of points from standard input into a 
 ** native array of points (between MIN_POINTS and MAX_POINTS)
 ** @param points A native array of Point's to populate (mutable)
 ** @return 0 if there is an error, otherwise the number of 
 **  points read.
 **/
int readPoints(struct Point points[]){
	int numPoints=0;
	char buff[MAX_LINE];
	
	printf("Number of points (3-100): ");
	if(!fgets(buff,MAX_LINE,stdin)){
		printf("Error reading number of point.\n");
		return 0;
	}
	
	for(int j=0;j<MAX_LINE;j++){
		if(buff[j]=='\0' || buff[j]=='\n'){
			buff[j]='\0';
			break;
		}
	}
	numPoints=atoi(buff);
	
	if(numPoints<MIN_POINTS || numPoints>MAX_POINTS){
		printf("Number of points must be between 3 and 100.\n");
		return 0;
	}
	
	for(int i=0;i<numPoints;i++){
		printf("Enter label (character): ");
		if(!fgets(buff,MAX_LINE,stdin)){
			printf("Error reading point label.\n");
			printf("Error reading x coordinate.\n");
			printf("Error reading y coordinate.\n");
			return 0;
		}
		
		for(int j=0;j<MAX_LINE;j++){
			if(buff[j]=='\0' || buff[j]=='\n'){
				buff[j]='\0';
				break;
			}
		}
		points[i].label=buff[0];
		
		// X coordinate
		printf("Enter x (int): ");
		if(!fgets(buff,MAX_LINE,stdin)){
			printf("Error reading point label.\n");
			printf("Error reading x coordinate.\n");
			printf("Error reading y coordinate.\n"); 
			return 0;
		}

		for(int j=0;j<MAX_LINE;j++){
			if(buff[j]=='\0' || buff[j]=='\n'){
				buff[j]='\0';
				break;
			}
		}
		
		points[i].x=atoi(buff);
		
		// Y coordinate
		printf("Enter y (int): ");
		if(fgets(buff,MAX_LINE,stdin)==NULL){
			printf("Error reading point label.\n");
			printf("Error reading x coordinate.\n");
			printf("Error reading y coordinate.\n"); 
			return 0;
		}
		
		for(int j=0;j<MAX_LINE;j++){
			if(buff[j]=='\0' || buff[j]=='\n'){
				buff[j]='\0';
				break;
			}
		}
		
		points[i].y=atoi(buff);
	}
	
	return numPoints;
}	

/** Swap two Point's in an array of Point's.  If either
 ** point is out of range this function should not
 ** alter the array.
 ** Assumes numPoints is valid.
 ** @param a the index of first value to swap
 ** @param b the index of second value to swap
 ** @param points A native array of Point's (mutable)
 ** @param numPoints The number of points in the points array.
 **/
void swap(int a, int b, struct Point points[], int numPoints){
	if(a>=numPoints || b>=numPoints){
		return;
	}

	struct Point temp=points[a];
	points[a]=points[b];
	points[b]=temp;
	
	return;
}
