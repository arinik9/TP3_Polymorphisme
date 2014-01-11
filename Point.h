/*
 * Point.h
 *
 *  Created on: 17 déc. 2013
 *      Author: narinik
 */

#ifndef POINT_H_
#define POINT_H_

class Point {
public:
	Point(long x1,long y1):x(x1),y(y1){}
	virtual ~Point();
protected:
	long x;
	long y;
};

#endif /* POINT_H_ */
