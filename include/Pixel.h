#ifndef PIXEL_H
#define PIXEL_H


class Pixel
{
    private:
    long int cellID;
    public:
        /** Default constructor */
        Pixel();
        /** Default destructor */
        virtual ~Pixel();

        long int getCellID() const {
            return cellID;
        }

        int setCellID(long cellID_) {
            cellID=cellID_;
            return 0;
        }
};

#endif // PIXEL_H
