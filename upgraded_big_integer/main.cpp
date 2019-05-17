#include <iostream>
#include "my_vector.h"
#include "big_integer.h"

using namespace std;

int main() {
    // big_integer a("18263123819238719182631238192387192381936138513613812381931826312381923871923818263123819238719238193613851361381193613851361381613851361381");
    // big_integer b("9127936123102379123812361236758236517598273182631238192387192381936138513613819587239857235");
    // cout << a / b;
    my_vector a;
    for (size_t i = 0; i < 10; ++i) {
        a.push_back(i);
    }
    my_vector b = a;
    for (size_t i = 0; i < a.size(); ++i) {
        cout << a[i] << " ";
    }
    cout << "\n";
    for (size_t i = 0; i < b.size(); ++i) {
        cout << b[i] << " ";
    }
    cout << "\n";
    b[0] = 228;
    for (size_t i = 0; i < a.size(); ++i) {
        cout << a[i] << " ";
    }
    cout << "\n";
    for (size_t i = 0; i < b.size(); ++i) {
        cout << b[i] << " ";
    }
    cout << "\n";

    return 0;
}