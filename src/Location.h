#ifndef DA2324_PRJ1_G17_4_LOCATION_H
#define DA2324_PRJ1_G17_4_LOCATION_H

#include <string>

class Location {
    private:
        unsigned int id;
        double longitude, latitude;
        std::string label;
    public:
        Location(unsigned int id, double longitude, double latitude): id(id), longitude(longitude), latitude(latitude) {}
        Location(unsigned int id, std::string label) : id(id), label(label) {}
        Location(unsigned int id) : id(id) {}
        unsigned int getId();
        double getLongitude();
        double getLatitude();
        std::string getLabel();
        void setId(unsigned int Id);
        void setLongitude(double Longitude);
        void setLatitude(double Latitude);
        void setLabel(std::string Label);

        bool operator==(const Location &b) const;
};


#endif //DA2324_PRJ1_G17_4_LOCATION_H
