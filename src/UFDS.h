#ifndef DA2324_PRJ1_G17_4_UFDS_H
#define DA2324_PRJ1_G17_4_UFDS_H

#include <vector>

using namespace std;
class UFDS {
public:
    UFDS(unsigned int N);
    unsigned long findSet(unsigned int i);
    void linkSets(unsigned int i, unsigned int j);
    bool isSameSet(unsigned int i, unsigned int j);
private:
    vector<unsigned int> path;
    vector<unsigned int> rank;
};


#endif //DA2324_PRJ1_G17_4_UFDS_H
