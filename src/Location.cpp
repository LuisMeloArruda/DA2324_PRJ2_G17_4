#include "Location.h"

unsigned int Location::getId() const {
    return this->id;
}

double Location::getLongitude() {
    return this->longitude;
}

double Location::getLatitude() {
    return this->latitude;
}

std::string Location::getLabel() {
    return this->label;
}

void Location::setId(unsigned int Id) {
    this->id = Id;
}

void Location::setLongitude(double Longitude) {
    this->longitude = Longitude;
}

void Location::setLatitude(double Latitude) {
    this->latitude = Latitude;
}

void Location::setLabel(std::string Label) {
    this->label = Label;
}

bool Location::operator==(const Location &b) const {
    return this->id == b.id;
}