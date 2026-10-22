#include "worker.h"

Worker::Worker(const QString& fio, const QString& position, int salary, int firstYear)
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
QString Worker::getFio() const
{
    return fio;
}
QString Worker::getPosition() const
{
    return position;
}

void Worker::setSalary(int newSalary){
    salary = newSalary;
}

void Worker::setFirstYear(int newFirstYear){
    firstYear = newFirstYear;
}

void Worker::setFio(const QString& newFio){
    fio = newFio;
}

void Worker::setPosition(const QString& newPosition){
    position = newPosition;
}

int Worker::getExperience(int currentYear) const{
    return currentYear - firstYear;
}