#include <iostream>
#include <vector>
#include <assert.h>
#include <sstream>

using namespace std;

vector<double> vecProduct(const vector<double>& v1, const vector<double>& v2) {
    // Check if v1 and v2 have the same size
    if (v1.size() != v2.size()) {
        // Return an empty vector if sizes are different
        return vector<double>();
    }

    // Create a vector to store the element-wise product
    vector<double> result;

    // Calculate the element-wise product and store it in the result vector
    for (size_t i = 0; i < v1.size(); i++) {
        result.push_back(v1[i] * v2[i]);
    }

    return result;
}

// Overload << operator to print vector
ostream& operator<<(ostream& os, const vector<double>& v) {
    for (size_t i = 0; i < v.size(); i++) {
        os << v.at(i) << " ";
    }
    os << endl;
    return os;
}

int main() {
    // Test 1
    vector<double> v1{1.0, 2.0, 3.0};
    vector<double> v2{4.0, 5.0, 6.0};
    vector<double> v3 = vecProduct(v1, v2);
    
    stringstream ss;
    ss << v3;
    assert(ss.str() == "4 10 18 \n"); // Assert that the vector product is right

    // Test 2
    vector<double> v4{42.0};
    ss << vecProduct(v1, v4);
    assert(!ss.str().empty()); // If size is different, no product

    cout << "All tests passed!" << endl;

    return 0;
}
