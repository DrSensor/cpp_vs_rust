#include <iterator>
#include <type_traits>
#include <vector>

template<typename Iterator>
auto partial_next(Iterator it, typename std::iterator_traits<Iterator>::difference_type n = 1) 
    -> decltype(std::next(it, std::min(n, std::distance(it, std::declval<Iterator>())))) 
{
    using difference_type = typename std::iterator_traits<Iterator>::difference_type;
    
    // Get the distance to the end if possible
    difference_type remaining;
    if constexpr (std::is_base_of_v<std::random_access_iterator_tag, 
                                   typename std::iterator_traits<Iterator>::iterator_category>) {
        // For random access iterators, we can calculate distance efficiently
        remaining = std::distance(it, Iterator{});
    } else {
        // For other iterators, assume we can advance by n
        remaining = n;
    }
    
    // Advance by the minimum of n and remaining distance
    return std::next(it, std::min(n, remaining));
}

// Example usage with different container types
void example() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    
    // With random access iterator
    auto it1 = vec.begin();
    auto result1 = partial_next(it1, 2);  // Advances 2 positions
    
    // With reverse iterator
    auto rit = vec.rbegin();
    auto result2 = partial_next(rit, 3);  // Advances 3 positions backward
}