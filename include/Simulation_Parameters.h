#ifndef SIMULATION_PARAMETERS_H
#define SIMULATION_PARAMETERS_H


#include <string>
class Simulation_Parameters
{
    private:
        int length;
        int width;
        int depth;
        int fiber_length;
        long fiber_count;

    public:
        //getter
        int get_length();
        int get_width();
        int get_depth();
        int get_fiber_length();
        long get_fiber_count();

        //setter
        int set_length(int _length);
        int set_width(int _width);
        int set_depth(int _depth);
        int set_fiber_length(int _fiber_length);
        long set_fiber_count(long _fiber_count);

        //functions
        int load_XML(std::string input_file);
};
#endif // SIMULATION_PARAMETERS_H
