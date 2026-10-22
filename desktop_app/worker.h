#ifndef WORKER_H
#define WORKER_H
#include <QString>

class Worker
{
public:
    Worker();
    Worker(const QString& fio, const QString& position, int salary, int firstYear);
    ~Worker();
    int getSalary() const;
    int getFirstYear() const;
    QString getFio() const;
    QString getPosition() const;
    void setSalary(int newSalary);
    void setFirstYear(int newFirstYear);
    void setFio(const QString& newFio);
    void setPosition(const QString& newPosition);
    int getExperience(int currentYear) const;

private:
    QString fio;
    QString position;
    int salary;
    int firstYear;
};



#endif // WORKER_H
