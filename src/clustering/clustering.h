//
// Created by jsier on 15/06/2021.
//

#ifndef CLUSTERING_CLUSTERING_H
#define CLUSTERING_CLUSTERING_H


#include <vector>

template<class VectorType>
class Clustering {
public:
    Clustering() = default;
    virtual ~Clustering() = default;

    virtual std::vector<int> cluster(const std::vector<VectorType>& vectors) = 0;
};


#endif //CLUSTERING_CLUSTERING_H
