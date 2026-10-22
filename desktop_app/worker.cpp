#include "worker.h"

Worker::Worker(std::string fio, std::string position, int salary, int firstYear)
    : fio(fio)
    , position(position)
    , salary(salary)
    , firstYear(firstYear)
{

}

Worker::Worker()
    : fio("Иванов Иван Иванович")
    , position("Сотрудник")
    , salary(0)
    , firstYear(1990)
{

}

Worker::~Worker()
{

}

int Worker::getSalary() const
{
    return salary;
}
int Worker::getFirstYear() const
{
    return firstYear;
}
std::string Worker::getFio() const
{
    return fio;
}
std::string Worker::getPosition() const
{
    return position;
}

void Worker::setSalary(int newSalary){
    salary = newSalary;
}

void Worker::setFirstYear(int newFirstYear){
    firstYear = newFirstYear;
}

void Worker::setFio(std::string newFio){
    fio = newFio;
}

void Worker::setPosition(std::string newPosition){
    position = newPosition;
}