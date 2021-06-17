//
// Created by jsier on 15/06/2021.
//

#ifndef CLUSTERING_CLUSTERING_H
#define CLUSTERING_CLUSTERING_H


#include <vector>
#include <random>
#include <algorithm>
#include <optional>

template<class VectorType>
class Clustering {
public:
    Clustering() = default;
    virtual ~Clustering() = default;
    virtual void cluster(const std::vector<VectorType>& vectors, uint32_t n_centroids, std::optional<int> max_iter) = 0;

    [[nodiscard]] const std::vector<int>& get_assignments() const { return assignments; }
    [[nodiscard]] const std::vector<VectorType>& get_centroids() const { return centroids; }

private:
    std::random_device random_dev{};
    std::default_random_engine random_engine{random_dev()};

protected:
    std::vector<int> assignments;
    std::vector<VectorType> centroids;

    [[nodiscard]] std::vector<size_t> random_sample_indices(size_t amount, size_t max, bool allow_repeat = false);
    std::vector<VectorType> centroids_from_indices(const std::vector<VectorType>& vectors, const std::vector<size_t>& indices) const;
};

template<class VectorType>
std::vector<size_t> Clustering<VectorType>::random_sample_indices(size_t amount, size_t max, bool allow_repeat) {
    assert(("max must be grater than 1", max > 1));
    std::uniform_int_distribution<size_t> dist(0, max);
    std::vector<size_t> indices(amount);
    auto begin = std::cbegin(indices);

    indices[0] = dist(random_engine);
    for (size_t i = 1; i < amount; ++i) {
        auto end = std::next(begin, i - 1);
        do {
            indices[i] = dist(random_engine);
        } while (!allow_repeat && std::find(begin, end, indices[i]) != end);
    }
    return indices;
}

template<class VectorType>
std::vector<VectorType> Clustering<VectorType>::centroids_from_indices(const std::vector<VectorType>& vectors, const std::vector<size_t>& indices) const {
    std::vector<VectorType> centroids;
    centroids.reserve(indices.size());
    for (auto index : indices) {
        centroids.emplace_back(vectors[index]);
    }
    return centroids;
}


#endif //CLUSTERING_CLUSTERING_H
