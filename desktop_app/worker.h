#ifndef WORKER_H
#define WORKER_H
#include <QString>

class Worker
{
public:
    Worker();
    Worker(const QString& fio,
           const QString& position,
           const QString& disciplines,
           const QString& educationLevel,
           const QString& academicDegree,
           const QString& academicTitle,
           const QString& qualificationImprovement,
           const QString& professionalRetraining,
           const QString& experience,
           const QString& educationalPrograms);

    ~Worker();

    QString getFio() const;
    QString getPosition() const;
    QString getExperience() const;
    QString getDisciplines() const;
    QString getEducationLevel() const;
    QString getAcademicDegree() const;
    QString getAcademicTitle() const;
    QString getQualificationImprovement() const;
    QString getProfessionalRetraining() const;
    QString getEducationalPrograms() const;

    void setFio(const QString& newFio);
    void setPosition(const QString& newPosition);
    void setExperience(const QString& newExperience);
    void setDisciplines(const QString& newDisciplines);
    void setEducationLevel(const QString& newEducationLevel);
    void setAcademicDegree(const QString& newAcademicDegree);
    void setAcademicTitle(const QString& newAcademicTitle);
    void setQualificationImprovement(const QString& newQualificationImprovement);
    void setProfessionalRetraining(const QString& newProfessionalRetraining);
    void setEducationalPrograms(const QString& newEducationalPrograms);

private:
    QString fio;
    QString position;
    QString experience;
    QString disciplines;
    QString educationLevel;             // Уровень профессионального образования, квалификация
    QString academicDegree;             // Ученая степень
    QString academicTitle;              // Ученое звание
    QString qualificationImprovement;   // Сведения о повышении квалификации
    QString professionalRetraining;     // Сведения о профессиональной переподготовке
    QString educationalPrograms;        // Наименование образовательных программ
};

#endif // WORKER_H

/*
    "Ф.И.О.", <<<
    "Должность преподавателя",
    "Перечень преподаваемых дисциплин",
    "Уровень (уровни) профессионального образования, квалификация",
    "Ученая степень (при наличии)",
    "Ученое звание (при наличии)",
    "Сведения о повышение квалификации (за последние 3 года)",
    "Сведения о профессиональной переподготовке (при наличии)",
    "Сведения о продолжительности опыта (лет) работы в профессиональной сфере",
    "Наименование образовательных программ, в реализации которых участвует педагогический работник"
*/
