#include "company.hh"
#include "utils.hh"
#include <iostream>
#include <set>

Company::Company()
{
}

Company::~Company()
{
    //std::cout << "Company destructor" << std::endl;

    // TODO: Deallocate staff

    // TODO: Deallocate projects

}

void Company::set_date(Params params)
{
    std::string day = params.at(0);
    std::string month = params.at(1);
    std::string year = params.at(2);
    if( not Utils::is_numeric(day, false) or
        not Utils::is_numeric(month, false) or
        not Utils::is_numeric(year, false) )
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    Utils::today.set(stoi(day), stoi(month), stoi(year));
    std::cout << "Date has been set to ";
    Utils::today.print();
    std::cout << std::endl;
}

void Company::advance_date(Params params)
{
    std::string amount = params.at(0);
    if( not Utils::is_numeric(amount, true) )
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    Utils::today.advance(stoi(amount));
    std::cout << "New date is ";
    Utils::today.print();
    std::cout << std::endl;
}

void Company::recruit(Params params)
{
    std::string employee_id = params.at(0);
    std::map<std::string, Employee*>::const_iterator
            iter = current_staff_.find(employee_id);

    if( iter != current_staff_.end() )
    {
        std::cout << ALREADY_EXISTS << employee_id << std::endl;
        return;
    }

    iter = all_staff_.find(employee_id);
    if( iter != all_staff_.end() )
    {
        current_staff_.insert(*iter);
        std::cout << EMPLOYEE_RECRUITED << std::endl;
        return;
    }

    Employee* new_employee = new Employee(employee_id);
    all_staff_.insert({employee_id, new_employee});
    current_staff_.insert({employee_id, new_employee});
    std::cout << EMPLOYEE_RECRUITED << std::endl;
}

void Company::leave(Params params)
{
    std::string employee_id = params.at(0);
    std::map<std::string, Employee*>::const_iterator
            iter = current_staff_.find(employee_id);
    if( iter == current_staff_.end() )
    {
        std::cout << CANT_FIND << employee_id << std::endl;
        return;
    }

    current_staff_.erase(iter); // Employee still stays in all_staff_
    std::cout << EMPLOYEE_LEFT << std::endl;
}

void Company::add_skill(Params params)
{
    std::string employee_id = params.at(0);
    std::string skill_name = params.at(1);

    std::map<std::string, Employee*>::const_iterator
            staff_iter = current_staff_.find(employee_id);
    if( staff_iter == current_staff_.end() )
    {
        std::cout << CANT_FIND << employee_id << std::endl;
        return;
    }

    staff_iter->second->add_skill(skill_name);
    std::cout << SKILL_ADDED << employee_id << std::endl;
}

void Company::print_current_staff(Params)
{
    if( current_staff_.empty() )
    {
        std::cout << "None" << std::endl;
        return;
    }

    for( auto employee : current_staff_ )
    {
        employee.second->print_id("");
        std::cout << std::endl;
    }
}

void Company::create_project(Params params)
{
    std::string id = params.at(0);
        if (projects_.find(id)!= projects_.end()){
            std::cout<<ALREADY_EXISTS<<std::endl;
            return;

        }
        Project *p =  new Project(params.at(0),Utils::today);
        projects_.insert({id,p});
        std::cout<< PROJECT_CREATED <<std::endl;
}

void Company::close_project(Params params)
{ std::string project_id = params.at(0);

    // Check if the project exists
    auto project_iter = projects_.find(project_id);
    if (project_iter == projects_.end()) {
        std::cout << CANT_FIND << project_id << std::endl;
        return;
    }

    // Check if the project is already closed
    if (project_iter->second->is_closed()) {
        std::cout << PROJECT_CLOSED << std::endl;
        return;
    }

    // Close the project and set the end date to the current date
    project_iter->second->close(Utils::today);
    std::cout << PROJECT_CLOSED << std::endl;

}

void Company::print_projects(Params)
{
    if (projects_.empty()) {
           std::cout << "None" << std::endl;
           return;
       }

       for (const auto& project_entry : projects_) {
           const Project* project = project_entry.second;
           std::cout<<project->get_id()<<" : ";
           project->print_start();
           std::cout<<" - ";
           if(project->is_closed()){
            project->print_end();
           }
           std::cout<<std::endl;

           }
                  }



void Company::add_requirement(Params params)
{
    std::string project_id = params.at(0);
       std::string requirement = params.at(1);

       // Check if the project exists
       auto project_iter = projects_.find(project_id);
       if (project_iter == projects_.end()) {
               std::cout << CANT_FIND << project_id << std::endl;
               return;
           }

           // Check if the project is closed
           if (project_iter->second->is_closed()) {
               std::cout << CANT_FIND << project_id << std::endl;
               return;
           }

           // Add the requirement to the project
           project_iter->second->add_requirement(requirement);
           std::cout << REQUIREMENT_ADDED << project_id << std::endl;

}

void Company::assign(Params params)
{
    std::string employee_id = params.at(0);
    std::string project_id = params.at(1);
    auto employee_iter = current_staff_.find(employee_id);

    if (employee_iter == current_staff_.end()) {
        std::cout << CANT_FIND<< employee_id << std::endl;
        return;
    }

    // Check if the project exists
    auto project_iter = projects_.find(project_id);
    if (project_iter == projects_.end()) {
        std::cout << CANT_FIND << project_id << std::endl;
        return;
    }

    // Check if the project is closed
    if (project_iter->second->is_closed()) {
        std::cout << CANT_ASSIGN << employee_iter->second->get_id() << std::endl;
        return;
    }

    // Check if the employee has the required skills for the project
    if (project_iter->second->check_requirements(employee_iter->second->get_skills())) {
        // Assign the employee to the project
        project_iter->second->assign_employee(*(employee_iter->second));
        active_staff_.insert(employee_id);
        std::cout << STAFF_ASSIGNED << project_id << std::endl;
    } else {
        std::cout << CANT_ASSIGN << employee_id << std::endl;
    }
}

void Company::print_project_info(Params params)
{   std::string id = params.at(0);
    if (projects_.find(id)!= projects_.end()){
    Project *p = projects_.at(params.at(0));
    std::cout<<p->get_id()<<" : ";
    p->print_start();
    std::cout<<" - ";
    if(p->is_closed()){
     p->print_end();
    }
    std::cout<<std::endl;
    std::set<std::string> requirements = p->get_requirements();
    std::cout << "** Requirements: ";
    if (requirements.empty()) {
        std::cout << "None";
    } else {
        auto iter = requirements.begin();
        while (iter != requirements.end()) {
            std::cout << *iter;
            ++iter;
            if (iter != requirements.end()) {
                std::cout << ",";
            }
        }
    }
    std::cout << std::endl;
    std::set<std::string> employess = p->get_employes();
    std::cout << "** Staff: ";
    if (employess.empty()) {
        std::cout << "None";
    } else {
        auto iter = employess.begin();
        while (iter != employess.end()) {
            std::cout << *iter;
            ++iter;
            if (iter != employess.end()) {
                std::cout << ",";
            }
        }
    }
    std::cout << std::endl;


    }
    else{
        std::cout<<CANT_FIND<<id<<std::endl;
    }

}

void Company::print_employee_info(Params params)
{ 
    std::string employee_id = params.at(0);

        // Check if the employee exists
        auto employee_iter = all_staff_.find(employee_id);
        if (employee_iter == all_staff_.end()) {
            std::cout << CANT_FIND << employee_id << std::endl;
            return;
        }

        // Print employee information
        employee_iter->second->print_skills();
        std::vector<Project> employes_project ;
        for(auto p : projects_){
             std::set<std::string> employes =  p.second->get_employes();

        } std::cout << "Projects:" << std::endl;
        for (const auto& project_pair : projects_) {
            const Project* p = project_pair.second;

            // Check if the employee is associated with the project
            if (p->has_employee(employee_id)) {
                std::cout << "** " << p->get_id() << " : " ;
                p->print_start();
                std::cout<<" - ";
                if(p->is_closed()){
                 p->print_end();
                }
                std::cout << std::endl;
      }
        }
}

void Company::print_active_staff(Params)
{
    if(active_staff_.empty()){
        std::cout << "None"<< std::endl;
    }
    else{
    // Iterate through the map of active staff
    for (const auto& staff : active_staff_) {
        std::cout << staff << std::endl;

    }
    }
}
