#include "project.hh"

#include <iostream>

#include <employee.hh>

Project::Project(const std::string & id,
    const std::string & start):
  id_(id), start_(start) {}

Project::Project(const std::string & id,
    const Date & start):
  id_(id), start_(start) {}

Project::~Project() {
  //std::cout << "Project " <<NOT_QUALIFIED_ANYMORE id_ << " destructed." << std::endl;
}

std::string Project::get_id() const {
  return id_;
}

void Project::print_start() const {
  start_.print();
}

void Project::close(Date today) {
  end_ = today;
}

bool Project::is_closed() const {
  return end_.check();
}

void Project::print_end() const {
  end_.print();
}
void Project::add_requirement(const std::string & requirement) {
  if (assigned_employees_.empty()) {
    requirements_.insert(requirement);
  } else {
    requirements_.insert(requirement);

    // Check if any assigned employee is no longer qualified
    std::vector < std::string > not_required_employees;
    for (const auto & [employee_id, employee]: assigned_employees_) {
      bool check = false;
      for (const std::string & element: employee.get_skills()) {
        if (requirements_.count(element) > 0) {
          // Found a common element
          check = true;
          break;
        }
      }
      if (!check) {
        not_required_employees.push_back(employee_id);
      }
    }

    // Handle not required employees as needed
    if (!not_required_employees.empty()) {
      std::cout << NOT_QUALIFIED;
      auto iter = not_required_employees.begin();
      while (iter != not_required_employees.end()) {
        assigned_employees_.erase( * iter);
        std::cout << * iter;
        ++iter;
        if (iter != not_required_employees.end()) {
          std::cout << ",";
        }
      }
      std::cout << std::endl;
    }
  }
}

bool Project::check_requirements(const std::set < std::string > & employee_skills) { // Check if the employee has at least one skill matching the project's requirements
  for (const auto & requirement: requirements_) {
    if (employee_skills.count(requirement) > 0) {
      return true;
    }
  }
  return requirements_.empty(); // Return true if no requirements (project has no specific skill requirements)
}

void Project::assign_employee(const Employee & employee) {
  assigned_employees_.insert({
    employee.get_id(),
    employee
  });
}

void Project::remove_employee(const std::string & employee_id) {
  assigned_employees_.erase(employee_id);
}

std::set < std::string > Project::get_requirements() {
  return requirements_;
}

std::set < std::string > Project::get_employes() {
  std::set < std::string > employees;

  // Iterate over the map and insert keys into the set
  for (const auto & pair: assigned_employees_) {
    employees.insert(pair.first);
  }

  return employees;
}

bool Project::has_employee(const std::string & employee_id) const {
  // Iterate through the set of assigned employees
  for (const auto & employee: assigned_employees_) {
    // Check if the employee_id matches
    if (employee.second.get_id() == employee_id) {
      return true; // Employee found
    }
  }

  // Employee not found
  return false;
}
