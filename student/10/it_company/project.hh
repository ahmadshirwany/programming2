/* Class Project
 * ----------
 * COMP.CS.110 FALL 2023
 * ----------
 * Class for describing a project in an IT company.
 *
 * Note: Students need to implement almost all of this class by themselves.
 * */
#ifndef PROJECT_HH
#define PROJECT_HH

#include "employee.hh"

#include "date.hh"

#include "utils.hh"

#include <string>

#include <map>

const std::string NOT_QUALIFIED = "Not qualified any more: ";

class Project {
  public:
    /**
     * @brief Project constructor
     * @param : id
     * @param : start (given as string ddmmyyyy)
     */
    Project(const std::string & id,
      const std::string & start);

  /**
   * @brief Project constructor
   * @param : id
   * @param : start (given as Date object)
   */
  Project(const std::string & id,
    const Date & start);

  /**
   * @brief Project destructor
   */
  ~Project();

  // More public methods
  std::string get_id() const;
  void print_start() const;
  void close(Date today);
  bool is_closed() const;
  void print_end() const;
  void add_requirement(const std::string & requirment);
  bool check_requirements(const std::set < std::string > & employee_skills);
  void assign_employee(const Employee & employee);
  void remove_employee(const std::string & employee_id);
  std::set < std::string > get_requirements();
  std::set < std::string > get_employes();
  bool has_employee(const std::string & employee_id) const;

  private:
    /**
     * @brief obvious attributes
     */
    std::string id_; // Can be a name or any other identifier
  Date start_;
  Date end_;

  // More attributes and private methods
  std::set < std::string > requirements_;
  std::map < std::string,
  Employee > assigned_employees_;

};

#endif // PROJECT_HH
