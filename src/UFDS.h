#ifndef DA2324_PRJ1_G17_4_UFDS_H
#define DA2324_PRJ1_G17_4_UFDS_H

#include <vector>

using namespace std;
class UFDS {
public:
    /**
     * @brief A class representing a Union-Find Disjoint Set
     *
     * Complexity: O(N), where N is the number of elements in the UFDS.
     *
     * @param N The number of elements in the UFDS.
     */
    UFDS(unsigned int N);
    /**
     * @brief Finds the set representative for the element i belongs to.
     *
     * Complexity: O(log N), where N is the number of elements in the UFDS.
     *
     * @param i The element whose representative needs to be found.
     * @return unsigned long Representative element of the set containing i.
     */
    unsigned long findSet(unsigned int i);
    /**
     * @brief Unites the sets that contain elements i and j.
     *
     * Complexity: O(log N), where N is the number of elements in the UFDS.
     *
     * @param i First Element.
     * @param j Second Element.
     */
    void linkSets(unsigned int i, unsigned int j);
    /**
     * @brief Checks if elements i and j belong to the same set.
     *
     * Complexity: O(log N), where N is the number of elements in the UFDS.
     *
     * @param i First Element.
     * @param j Second Element.
     * @return bool True if i and j belong to the same set, otherwise false.
     */
    bool isSameSet(unsigned int i, unsigned int j);
private:
    vector<unsigned int> path;
    vector<unsigned int> rank;
};


#endif //DA2324_PRJ1_G17_4_UFDS_H
