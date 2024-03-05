#include <iostream>
#include <string>

#include "lush.h"

struct Student {
    std::string id;
    std::string name;
    double grade;
};

int main() {
    std::string impl;
    std::cout << "Impl (vec, list): ";
    std::getline(std::cin, impl);
    impl = impl.substr(0, impl.find('\n'));

    if (impl == "vec") {
        return lyn::impl_fn<lyn::ImplArg::ImplVec>();
    } else if (impl == "list") {
        return lyn::impl_fn<lyn::ImplArg::ImplList>();
    } else {
        std::cout << "Unknown arg: " << impl << " (abort)" << std::endl;
        return 1;
    }
}
