    #include "../include/Var.h"

    char Var::get_var_name()
    {
        return var_name;
    }

    int Var::set_var_name(char var_x)
    {
        var_name=var_x;
        return 0;
    }

    int Var::get_index()
    {
        return index;
    }

    int Var::set_index(int in_val)
    {
        index=in_val;
        return 0;
    }

    int Var::get_delta()
    {
        return delta;
    }

    int Var::set_delta(int del)
    {
        delta=del;
        return 0;
    }

    int Var::get_value()
    {
        return value;
    }
    int Var::set_value(int val)
    {
        value=val;
        return 0;
    }
