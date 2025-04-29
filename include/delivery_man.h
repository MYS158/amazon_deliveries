#pragma once

#include <set>
#include <queue>
#include <string>
#include <vector>
#include <ostream>
#include <stdexcept>

#include "package.h"
#include "zip_code.h"
#include "delivery_man_id.h"

class delivery_man {

private:
    bool active;
    int assigned_areas, assigned_packages;
    std::string last_name, first_name;
    delivery_man_id id;
    std::set<zip_code> delivery_areas;
    std::queue<package> packages;

public:
    delivery_man(const delivery_man_id& id,
                 const std::string& last_name,
                 const std::string& first_name,
                 bool active = true)
        : active(active),
          assigned_areas(0),
          assigned_packages(0),
          last_name(last_name),
          first_name(first_name),
          id(id)
    {}

    int get_assigned_areas() const noexcept { 
        return assigned_areas; 
    }
    int get_assigned_packages() const noexcept { 
        return assigned_packages;
    }
    const std::string& get_last_name() const noexcept { 
        return last_name; 
    }
    const std::string& get_first_name() const noexcept { 
        return first_name; 
    }
    const delivery_man_id& get_id() const noexcept { 
        return id; 
    }

    bool is_active() const noexcept { 
        return active; 
    }
    void set_active(bool a) noexcept { 
        active = a; 
    }

    void add_area(const zip_code& z) {
        if (delivery_areas.insert(z).second) ++assigned_areas;
    }
    void remove_area(const zip_code& z) {
        if (delivery_areas.erase(z) > 0) --assigned_areas;
    }
    bool covers_area(const zip_code& z) const noexcept {
        return delivery_areas.count(z) > 0;
    }

    void assign_package(const package& p) {
        packages.push(p);
        ++assigned_packages;
    }

    const package& peek_next_package() const {
        if (packages.empty()) throw std::out_of_range{"no packages assigned"};
        return packages.front();
    }

    // success = true  => delivered: record externally and remove
    // success = false => push to back for retry
    void deliver_next(bool success) {
        if (packages.empty()) throw std::out_of_range{"no packages to deliver"};
        package p = packages.front();
        packages.pop();
        if (success) {
            --assigned_packages;
            // record p.get_id(), id externally...
        } else {
            packages.push(p);
            // on third failure, external logic should detect and record incident
        }
    }

    void abandon_packages(std::vector<delivery_man>& drivers, std::vector<package>& incidents) {
        while (!packages.empty()) {
            package p = packages.front();
            packages.pop();
            --assigned_packages;
            delivery_man* best = nullptr;
            for (auto& d : drivers) {
                if (&d == this || !d.is_active() || !d.covers_area(p.get_zip_code())) continue;
                if (!best || d.get_assigned_areas() < best->get_assigned_areas()) best = &d;
            }
            if (best) best->assign_package(p);
            else incidents.push_back(p);
        }
    }

    friend bool operator==(const delivery_man& a, const delivery_man& b) noexcept {
        return a.id == b.id;
    }
    friend bool operator!=(const delivery_man& a, const delivery_man& b) noexcept {
        return !(a == b);
    }
    friend bool operator<(const delivery_man& a, const delivery_man& b) noexcept {
        return a.id < b.id;
    }
    friend bool operator>(const delivery_man& a, const delivery_man& b) noexcept {
        return b < a;
    }
    friend bool operator<=(const delivery_man& a, const delivery_man& b) noexcept {
        return !(b < a);
    }
    friend bool operator>=(const delivery_man& a, const delivery_man& b) noexcept {
        return !(a < b);
    }

    friend std::ostream& operator<<(std::ostream& os, const delivery_man& d) {
        os << '{'
           << d.id << ' '
           << d.last_name << ", " << d.first_name << ' '
           << (d.active ? "active" : "inactive") << ' '
           << "areas=" << d.assigned_areas << ' '
           << "packages=" << d.assigned_packages
           << '}';
        return os;
    }

};