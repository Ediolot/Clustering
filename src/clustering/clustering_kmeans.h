//
// Created by jsier on 15/06/2021.
//

#ifndef CLUSTERING_CLUSTERING_KMEANS_H
#define CLUSTERING_CLUSTERING_KMEANS_H


#include "clustering.h"

template<class VectorType>
class ClusteringKMeans: public Clustering<VectorType> {
    ClusteringKMeans() = default;
    ~ClusteringKMeans() = default;

    std::vector<int> cluster(const std::vector<VectorType>& vectors) override {
        
    };
};


#endif //CLUSTERING_CLUSTERING_KMEANS_H
