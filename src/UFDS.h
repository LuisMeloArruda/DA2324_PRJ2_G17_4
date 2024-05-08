#ifndef DA2324_PRJ1_G17_4_UFDS_H
#define DA2324_PRJ1_G17_4_UFDS_H

#include <vector>

using namespace std;
class UFDS {
public:
    /**
     * @brief
     *
     * Complexity:
     *
     * @param N
     */
    UFDS(unsigned int N);
    /**
     * @brief
     *
     * Complexity:
     *
     * @param i
     * @return
     */
    unsigned long findSet(unsigned int i);
    /**
     * @brief
     *
     * Complexity:
     *
     * @param i
     * @param j
     */
    void linkSets(unsigned int i, unsigned int j);
    /**
     * @brief
     *
     * Complexity:
     *
     * @param i
     * @param j
     * @return
     */
    bool isSameSet(unsigned int i, unsigned int j);
private:
    vector<unsigned int> path;
    vector<unsigned int> rank;
};


#endif //DA2324_PRJ1_G17_4_UFDS_H
