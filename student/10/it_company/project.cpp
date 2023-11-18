#include "project.hh"
#include <iostream>

Project::Project(const std::string& id, const std::string& start):
    id_(id), start_(start)
{
}

Project::Project(const std::string& id, const Date &start):
    id_(id), start_(start)
{
}

Project::~Project()
{
    //std::cout << "Project " << id_ << " destructed." << std::endl;
}

std::string Project::get_id() const
{
    return id_ ;
}

void Project::print_start() const
{
    start_.print();
}

void Project::close(Date today)
{
    end_ = today;
}

bool Project::is_closed() const
{
    return end_.check();
}



void Project::print_end() const
{
    end_.print();
}

void Project::add_requirement(std::string requirment)
{
    requirements_.insert(requirment);
}


