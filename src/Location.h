#ifndef DA2324_PRJ1_G17_4_LOCATION_H
#define DA2324_PRJ1_G17_4_LOCATION_H

#include <string>

class Location {
    private:
        unsigned int id;
        double longitude, latitude;
        std::string label;
    public:
        /**
         * @brief
         *
         * Complexity:
         *
         * @param id
         * @param longitude
         * @param latitude
         */
        Location(unsigned int id, double longitude, double latitude): id(id), longitude(longitude), latitude(latitude) {}
        /**
         * @brief
         *
         * Complexity:
         *
         */
        Location(): id(0), longitude(0.0), latitude(0.0), label("") {}
        /**
         * @brief
         *
         * Complexity:
         *
         * @param id
         * @param label
         */
        Location(unsigned int id, std::string label): id(id), label(label) {}
        /**
         * @brief
         *
         * Complexity:
         *
         * @param id
         */
        Location(unsigned int id) : id(id) {}
        /**
         * @brief
         *
         * Complexity:
         *
         * @return
         */
        unsigned int getId();
        /**
         * @brief
         *
         * Complexity:
         *
         * @return
         */
        double getLongitude();
        /**
         * @brief
         *
         * Complexity:
         *
         * @return
         */
        double getLatitude();
        /**
         * @brief
         *
         * Complexity:
         *
         * @return
         */
        std::string getLabel();
        /**
         * @brief
         *
         * Complexity:
         *
         * @param Id
         */
        void setId(unsigned int Id);
        /**
         * @brief
         *
         * Complexity:
         *
         * @param Longitude
         */
        void setLongitude(double Longitude);
        /**
         * @brief
         *
         * Complexity:
         *
         * @param Latitude
         */
        void setLatitude(double Latitude);
        /**
         * @brief
         *
         * Complexity:
         *
         * @param Label
         */
        void setLabel(std::string Label);
        /**
         * @brief
         *
         * Complexity:
         *
         * @param b
         * @return
         */
        bool operator==(const Location &b) const;
};


#endif //DA2324_PRJ1_G17_4_LOCATION_H
