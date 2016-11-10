//
//  Point.hpp
//  TreeSimulation
//
//  Created by Steven Liao on 4/4/16.
//  Copyright © 2016 Steven Liao. All rights reserved.
//

#ifndef Point_hpp
#define Point_hpp

class CPoint
{
    public:
        float x, y;
        CPoint();
        CPoint(float x, float y);
        ~CPoint();
        CPoint& operator+(CPoint &);
        CPoint& operator-(CPoint &);
        float norm();
        bool intersect = false;
        bool selected = false;
};

#endif /* Point_h */
