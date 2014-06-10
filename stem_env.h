#ifndef STEM_ENV_H
#define STEM_ENV_H

class Point_3d
{
private:
    int x;
    int y;
    int z;

public:
    int get_x();
    int get_y();
    int get_z();

    int set_x(int xval);
    int set_y(int yval);
    int set_z(int zval);
};

class Stem_env
{
private:
int create_line(int i, Point_3d box[8], Point_3d** lines, int f2, int d2, int xmin, int xmax, int xdiff1, int length, int width, int depth);

public:
  int** draw_3D_line(int x1, int y1, int z1, int x2, int y2, int z2);
  Point_3d** setup_environment(int length, int width, int depth, int fiber_count, int fiber_length);
};

#endif
