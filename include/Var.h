#ifndef VAR_H_
#define VAR_H_


class Var
{
private:
    char varName;
    int index;
    int delta;
    int value;

public:
    Var();
    Var(int varN, int ind, int del, int val):varName(varN),index(ind),delta(del),value(val)
    {}
    virtual ~Var();

    char getVarName() const {
		return varName;
	}

	void setVarName(char varName) {
		this->varName = varName;
	}

	int getIndex() const {
		return index;
	}

	void setIndex(int index) {
		this->index = index;
	}

	int getDelta() const {
		return delta;
	}

	void setDelta(int delta) {
		this->delta = delta;
	}

	int getValue() const {
		return value;
	}

	void setValue(int value) {
		this->value = value;
	}
};
#endif // VAR_H_
