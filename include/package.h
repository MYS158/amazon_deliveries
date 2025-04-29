#pragma once

#include <string>
#include <ostream>

#include "zip_code.h"
#include "package_id.h"

class package {

private:
    std::string address;
    zip_code code;
    package_id id;

public:
    package(const package_id& id, const std::string& address, const zip_code& code)
        : id(id), address(address), code(code) {}

    const std::string& get_address() const noexcept { 
        return address; 
    }
    const zip_code& get_zip_code() const noexcept { 
        return code; 
    }
    const package_id& get_id() const noexcept { 
        return id; 
    }

    friend bool operator==(const package& a, const package& b) noexcept {
        return a.id == b.id && a.address == b.address && a.code == b.code;
    }
    friend bool operator!=(const package& a, const package& b) noexcept {
        return !(a == b);
    }
    friend bool operator<(const package& a, const package& b) noexcept {
        if (a.id != b.id) return a.id < b.id;
        if (a.address != b.address) return a.address < b.address;
        return a.code < b.code;
    }
    friend bool operator>(const package& a, const package& b) noexcept { 
        return b < a; 
    }
    friend bool operator<=(const package& a, const package& b) noexcept { 
        return !(b < a); 
    }
    friend bool operator>=(const package& a, const package& b) noexcept { 
        return !(a < b); 
    }

    friend std::ostream& operator<<(std::ostream& os, const package& pkg) {
        return os << '{' << pkg.id << ' ' << pkg.address << ' ' << pkg.code << '}';
    }

};