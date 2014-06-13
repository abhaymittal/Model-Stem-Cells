#include "Point_3d.h"
#include "Line_3d.h"

#ifndef STEM_ENV_H
#define STEM_ENV_H

class Stem_env
{
private:
  Line_3d create_line(int length, int width, int depth, Point_3d box[8], int f2, int d2, int xmin, int xmax, int xdiff1);

public:
  Line_3d draw_3D_line(Point_3d p1, Point_3d p2);
  Line_3d* setup_environment(int length, int width, int depth, int fiber_count, int fiber_length);
};

#endif
