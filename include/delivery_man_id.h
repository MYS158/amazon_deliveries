#pragma once

#include <string>
#include <ostream>
#include <stdexcept>

class delivery_man_id {

private:
    std::string id;

public:
    explicit delivery_man_id(const std::string& code) {
        if (code.size() != 6) 
            throw std::invalid_argument{"delivery_man_id: code must be exactly 6 characters"};
        id = 'R' + code;
    }

    const std::string& get_id() const noexcept {
        return id;
    }

    friend bool operator==(const delivery_man_id& a, const delivery_man_id& b) noexcept {
        return a.id == b.id;
    }
    friend bool operator!=(const delivery_man_id& a, const delivery_man_id& b) noexcept {
        return !(a == b);
    }
    friend bool operator< (const delivery_man_id& a, const delivery_man_id& b) noexcept {
        return a.id < b.id;
    }
    friend bool operator> (const delivery_man_id& a, const delivery_man_id& b) noexcept {
        return b < a;
    }
    friend bool operator<=(const delivery_man_id& a, const delivery_man_id& b) noexcept {
        return !(b < a);
    }
    friend bool operator>=(const delivery_man_id& a, const delivery_man_id& b) noexcept {
        return !(a < b);
    }

    friend std::ostream& operator<<(std::ostream& os, const delivery_man_id& dm) {
        return os << dm.id;
    }

};