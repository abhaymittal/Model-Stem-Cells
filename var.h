#ifndef VAR_H
#define VAR_H


class var
{
    private:

    char var;
    int index;
    int delta;
    int value;

    public:

    char get_var();
    int set_var(char var_name);

    int get_index();
    int set_index(int in_val);

    int get_delta();
    int set_delta();

    int get_value();
    int set_value();
}
#endif // VAR_H
