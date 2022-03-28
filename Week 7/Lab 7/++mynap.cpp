#include <iostream>
#include <vector>
#include <map>

int main() {

    std::vector vi{3 , 3, 4, 4, 6};
        std::map<int, size_t> myMap;

    for (const auto& i : vi) 
        ++myMap[i];

    for (const auto& [num, val] : myMap)
        std::cout << num << ' ' << val <<'\n';

    return 0;
}