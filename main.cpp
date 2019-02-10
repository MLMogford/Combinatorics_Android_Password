#include <iostream>
#include <cinttypes>
#include <array>
#include <vector>
#include <map>

/// Static table of intermediate nodes
/// Third element is the intermediate node in-between the first and second.
static std::vector<std::array<int, 3>> can_jump_reference_table = {
        {1, 3, 2},
        {1, 7, 4},
        {1, 9, 5},
        {2, 8, 5},
        {3, 1, 2},
        {3, 7, 5},
        {3, 9, 6},
        {4, 6, 5},
        {6, 4, 5},
        {7, 1, 4},
        {7, 3, 5},
        {7, 9, 8},
        {8, 2, 5},
        {9, 1, 5},
        {9, 7, 8},
        {9, 3, 6},
};

/// Determine whether a node has already been visited
/// \param visited vector representing the current node selection, in-order
/// \param node node to test
/// \return true if the node has been visited, false otherwise
bool is_node_in_stack(std::vector<std::pair<int, std::vector<int>>> const &visited, int node) {
    for (std::pair<int, std::vector<int>> pair: visited) {
        if (node == pair.first) {
            return false;
        }
    }
    return true;
}

/// Determine for a given in-order node selection set whether node is available to be selected
/// \param visited vector representing the current node selection, in-order
/// \param node candidate node
/// \return true if node is valid, false otherwise
bool can_jump_to(std::vector<std::pair<int, std::vector<int>>> const &visited, int node) {
    if (!is_node_in_stack(visited, node)) {
        return false;
    }
    for (int previously_visited: visited.back().second) {
        if (node == previously_visited) {
            return false;
        }
    }
    int origin = visited.back().first;
    int destination = node;
    for (std::array<int, 3> jump_reference_item : can_jump_reference_table) {
        if (jump_reference_item[0] == origin && jump_reference_item[1] == destination) {
            int middle = jump_reference_item[2];
            if (is_node_in_stack(visited, middle)) {
                return false;
            }
        }
    }
    return true;
}

/// Return the number of permutation considering a given selected node set
/// \param visited vector representing the current node selection, in-order
/// \return Number of possible combination of node selection starting from this point
int get_count_from_node(std::vector<std::pair<int, std::vector<int>>> &visited) {
    int count = 0;
    for (int node = 1; node < 10; ++node) {
        if (!can_jump_to(visited, node)) {
            continue;
        } else {
            visited.back().second.push_back(node);
            visited.emplace_back(node, std::vector<int>());
            count += get_count_from_node(visited);
            visited.pop_back();
        }
    }
    if (visited.size() > 3) {
        count += 1;
    }
    return count;
}

/// Entry point. Prints the results on stdout
/// \return 0 on success
int main() {
    std::vector<std::pair<int, std::vector<int>>> visited;
    int total = 0;
    for (int i = 1; i < 10; ++i) {
        visited.clear();
        visited.emplace_back(i, std::vector<int>());
        total += get_count_from_node(visited);
    }
    std::cout << total << std::endl;
    return EXIT_SUCCESS;
}# Combinatorics_Android_Password
