#ifndef WORKER_H
#define WORKER_H
#include <string>

class Worker
{
public:
    Worker();
    Worker(std::string fio, std::string position, int salary, int firstYear);
    ~Worker();
    int getSalary() const;
    int getFirstYear() const;
    std::string getFio() const;
    std::string getPosition() const;
    void setSalary(int newSalary);
    void setFirstYear(int newFirstYear);
    void setFio(std::string newFio);
    void setPosition(std::string newPosition);
    int getExperience(int currentYear) const;

private:
    std::string fio;
    std::string position;
    int salary;
    int firstYear;
};



#endif // WORKER_H
