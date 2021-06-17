//
// Created by jsier on 15/06/2021.
//

#ifndef CLUSTERING_CLUSTERING_KMEANS_H
#define CLUSTERING_CLUSTERING_KMEANS_H


#include "clustering.h"

template<class VectorType>
class ClusteringKMeans: public Clustering<VectorType> {
public:
    ClusteringKMeans() = default;
    ~ClusteringKMeans() = default;

    void cluster(const std::vector<VectorType>& vectors, uint32_t n_centroids) override;
    void assign_step(const std::vector<VectorType> &vectors);
    bool recalculate_centroids(const std::vector<VectorType> &vectors);
};

template<class VectorType>
void ClusteringKMeans<VectorType>::cluster(const std::vector<VectorType>& vectors, uint32_t n_centroids) {
    auto centroids_indices = this->random_sample_indices(n_centroids, vectors.size());  // Pick random centroids
    this->centroids = this->centroids_from_indices(vectors, centroids_indices);
    this->assignments = std::vector<int>(vectors.size());  // Prepare the assignment for each point to a cluster

    do {
        assign_step(vectors);
    } while (recalculate_centroids(vectors));
}

template<class VectorType>
void ClusteringKMeans<VectorType>::assign_step(const std::vector<VectorType> &vectors) {
    for (size_t i = 0; i < vectors.size(); ++i) {
        int closest = -1;
        double closest_dist = std::numeric_limits<double>::infinity();
        for (int j = 0; j < this->centroids.size(); ++j) {
            double dist = vectors[i].euclidean_distance(this->centroids[j]);
            if (dist < closest_dist) {
                closest_dist = dist;
                closest = j;
            }
        }
        this->assignments[i] = closest;
    }
}

template<class VectorType>
bool ClusteringKMeans<VectorType>::recalculate_centroids(const std::vector<VectorType> &vectors) {
    std::vector<int> centroid_count(this->centroids.size(), 0);
    std::vector<VectorType> old_centroids = this->centroids;
    for (auto& centroid : this->centroids) {
        centroid.fill(0);
    }

    for (int i = 0; i < vectors.size(); ++i) {
        int assigned = this->assignments[i];
        centroid_count[assigned] += 1;
        this->centroids[assigned] += vectors[i];
    }

    bool changed = false;
    for (int i = 0; i < this->centroids.size(); ++i) {
        this->centroids[i] /= centroid_count[i];
        if (this->centroids[i] != old_centroids[i]) {
            changed = true;
        }
    }
    return changed;
}


#endif //CLUSTERING_CLUSTERING_KMEANS_H
