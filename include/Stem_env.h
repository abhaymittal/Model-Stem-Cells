#ifndef STEM_ENV_H
#define STEM_ENV_H
/**
*   @class  Stem_env
*   @brief  Class for environment
*   @author Abhay Mittal
*   @author Pratik Varshney
*/
#include "Point_3d.h"
#include "Line_3d.h"
class Stem_env
{
private:
/**
*   @brief
*/
int create_line(int i, Point_3d box[8], Point_3d** lines, int f2, int d2, int xmin, int xmax, int xdiff1, int length, int width, int depth);

public:
  Line_3d draw_3D_line(Point_3d p1, Point_3d p2);
  Point_3d** setup_environment(int length, int width, int depth, int fiber_count, int fiber_length);
};

#endif
