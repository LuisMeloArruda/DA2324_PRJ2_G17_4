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
         * @brief Constructor of Location class with the given id, longitude, and latitude.
         *
         * Complexity: O(1)
         *
         * @param id Identifier of the location.
         * @param longitude Longitude of the location.
         * @param latitude
         */
        Location(unsigned int id, double longitude, double latitude): id(id), longitude(longitude), latitude(latitude) {}
        /**
         * @brief Default constructor of Location class, initializing all values to its default.
         *
         * Complexity: O(1)
         *
         */
        Location(): id(0), longitude(0.0), latitude(0.0), label("") {}
        /**
         * @brief Constructor of Location class with the given id and label.
         *
         * Complexity: O(1)
         *
         * @param id Identifier of the location.
         * @param label Label of the location.
         */
        Location(unsigned int id, std::string label): id(id), label(label) {}
        /**
         * @brief Constructor of Location class with the given id.
         *
         * Complexity: O(1)
         *
         * @param id Identifier of the location.
         */
        Location(unsigned int id) : id(id) {}
        /**
         * @brief Get the id of the location.
         *
         * Complexity: O(1)
         *
         * @return Id of the location.
         */
        unsigned int getId() const;
        /**
         * @brief Get the longitude of the location.
         *
         * Complexity: O(1)
         *
         * @return Longitude of the location.
         */
        double getLongitude();
        /**
         * @brief Get the latitude of the location.
         *
         * Complexity: O(1)
         *
         * @return Latitude of the location.
         */
        double getLatitude();
        /**
         * @brief Get the label of the location.
         *
         * Complexity: O(1)
         *
         * @return Label of the location.
         */
        std::string getLabel();
        /**
         * @brief Set the id of the location.
         *
         * Complexity: O(1)
         *
         * @param Id New identifier of the location.
         */
        void setId(unsigned int Id);
        /**
         * @brief Set the longitude of the location.
         *
         * Complexity: O(1)
         *
         * @param Longitude New longitude for the location.
         */
        void setLongitude(double Longitude);
        /**
         * @brief Set the latitude of the location.
         *
         * Complexity: O(1)
         *
         * @param Latitude New latitude for the location.
         */
        void setLatitude(double Latitude);
        /**
         * @brief Set the label of the location.
         *
         * Complexity: O(1)
         *
         * @param Label New label for the location.
         */
        void setLabel(std::string Label);
        /**
         * @brief Equality operator to compare two locations based on their id.
         *
         * Complexity: O(1)
         *
         * @param b The other location to compare with.
         *
         * @return True if the ids of both locations are equal, false otherwise.
         */
        bool operator==(const Location &b) const;
};


#endif //DA2324_PRJ1_G17_4_LOCATION_H
