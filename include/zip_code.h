#pragma once

#include <string>
#include <ostream>
#include <stdexcept>

class zip_code {

private:
    std::string coi, code;

public:
    explicit zip_code(const std::string& coi, const std::string& code) {
        if (coi.size() != 3)
            throw std::invalid_argument{"zip_code: coi must be exactly 3 characters"};
        this->coi = coi;
        this->code = code;
    }

    const std::string& get_coi() const noexcept { 
        return coi; 
    }
    const std::string& get_code() const noexcept { 
        return code; 
    }

    friend bool operator==(const zip_code& a, const zip_code& b) noexcept {
        return a.coi == b.coi && a.code == b.code;
    }
    friend bool operator!=(const zip_code& a, const zip_code& b) noexcept {
        return !(a == b);
    }
    friend bool operator<(const zip_code& a, const zip_code& b) noexcept {
        if (a.coi != b.coi) return a.coi < b.coi;
        return a.code < b.code;
    }
    friend bool operator>(const zip_code& a, const zip_code& b) noexcept { 
        return b < a; 
    }
    friend bool operator<=(const zip_code& a, const zip_code& b) noexcept {
        return !(b < a); 
    }
    friend bool operator>=(const zip_code& a, const zip_code& b) noexcept { 
        return !(a < b); 
    }
    
    friend std::ostream& operator<<(std::ostream& os, const zip_code& z) {
        return os << z.code;
    }

};