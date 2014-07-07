#include "Cell.h"

Cell::Cell():id(0),radius(0),senseRadius(0),eCadherin(0.0),centroid(*new Point(0,0,0)),EB(0.0)
{}

Cell::~Cell()
{}

long int Cell::getId() const {
    return id;
}

int Cell::setId(long id_) {
    id=id_;
    return 0;
}

int Cell::getRadius() const {
    return radius;
}
int Cell::setRadius(int radius_) {
    radius=radius_;
    return 0;
}

int Cell::getSenseRadius() const {
    return senseRadius;
}
int Cell::setSenseRadius(int senseRadius_) {
    senseRadius=senseRadius_;
    return 0;
}

Point Cell::getCentroid() const {
    return centroid;
}
int Cell::setCentroid(Point centroid_) {
    centroid.setX(centroid_.getX());
    centroid.setY(centroid_.getY());
    centroid.setZ(centroid_.getZ());
    return 0;
}

int Cell::setECadherin(float eCadherin_) {
    eCadherin=eCadherin_;
    return 0;
}
float Cell::getECadherin() const {
    return eCadherin;
}

int Cell::setEB(float EB_) {
    EB=EB_;
}
float Cell::getEB() const {
    return EB;
}
