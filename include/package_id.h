#pragma once

#include <string>
#include <ostream>
#include <stdexcept>

class package_id {

private:
    std::string first, second, third;

public:
    explicit package_id(const std::string& part1,
                        const std::string& part2,
                        const std::string& part3)
        : first(part1), second(part2), third(part3)
    {
        if (first.size() != 3)
            throw std::invalid_argument{"package_id: first part must be exactly 3 characters"};
        if (second.size() != 6)
            throw std::invalid_argument{"package_id: second part must be exactly 6 characters"};
        if (third.size() != 6)
            throw std::invalid_argument{"package_id: third part must be exactly 6 characters"};
    }

    const std::string& get_first() const noexcept { 
        return first;  
    }
    const std::string& get_second() const noexcept { 
        return second;
    }
    const std::string& get_third() const noexcept { 
        return third;  
    }

    friend bool operator==(const package_id& a, const package_id& b) noexcept {
        return a.first == b.first && a.second == b.second && a.third == b.third;
    }
    friend bool operator!=(const package_id& a, const package_id& b) noexcept {
        return !(a == b);
    }
    friend bool operator<(const package_id& a, const package_id& b) noexcept {
        if (a.first  != b.first) return a.first < b.first;
        if (a.second != b.second) return a.second < b.second;
        return a.third < b.third;
    }
    friend bool operator>(const package_id& a, const package_id& b) noexcept {
        return b < a;
    }
    friend bool operator<=(const package_id& a, const package_id& b) noexcept {
        return !(b < a);
    }
    friend bool operator>=(const package_id& a, const package_id& b) noexcept {
        return !(a < b);
    }

    friend std::ostream& operator<<(std::ostream& os, const package_id& pkg) {
        return os << pkg.first << '-' << pkg.second << '-' << pkg.third;
    }

};