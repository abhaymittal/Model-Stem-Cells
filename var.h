#ifndef VAR_H
#define VAR_H


class Var
{
    private:

    char var_name;
    int index;
    int delta;
    int value;

    public:

    Var()
    {}

    Var(int var_n,int ind,int del, int val):var_name(var_n),index(ind),delta(del),value(val)
    {}

    char get_var_name();
    int set_var_name(char var_x);

    int get_index();
    int set_index(int in_val);

    int get_delta();
    int set_delta(int del);

    int get_value();
    int set_value(int val);
};
#endif // VAR_H
