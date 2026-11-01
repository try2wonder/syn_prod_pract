#include "worker.h"
#include <QDebug>

Worker::Worker(const QString& fio,
               const QString& position,
               const QString& experience,
               const QString& disciplines,
               const QString& educationLevel,
               const QString& academicDegree,
               const QString& academicTitle,
               const QString& qualificationImprovement,
               const QString& professionalRetraining,
               const QString& educationalPrograms)
    : fio(fio)
    , position(position)
    , experience(experience)
    , disciplines(disciplines)
    , educationLevel(educationLevel)
    , academicDegree(academicDegree)
    , academicTitle(academicTitle)
    , qualificationImprovement(qualificationImprovement)
    , professionalRetraining(professionalRetraining)
    , educationalPrograms(educationalPrograms)
{

}

// Конструктор по умолчанию
Worker::Worker()
    : fio("Иванов Иван Иванович")
    , position("Сотрудник")
    , experience("10 лет 2 месяца")
    , disciplines("Математика")
    , educationLevel("Высшее")
    , academicDegree("отсутствует")
    , academicTitle("отсутствует")
    , qualificationImprovement("-")
    , professionalRetraining("-")
    , educationalPrograms("ООО")
{
    qDebug() << "Default constructor was used";
}

Worker::~Worker()
{

}

QString Worker::getFio() const
{
    return fio;
}
QString Worker::getPosition() const
{
    return position;
}
QString Worker::getExperience() const
{
    return experience;
}
QString Worker::getDisciplines() const
{
    return disciplines;
}
QString Worker::getEducationLevel() const
{
    return educationLevel;
}
QString Worker::getAcademicDegree() const
{
    return academicDegree;
}
QString Worker::getAcademicTitle() const
{
    return academicTitle;
}
QString Worker::getQualificationImprovement() const
{
    return qualificationImprovement;
}
QString Worker::getProfessionalRetraining() const
{
    return professionalRetraining;
}
QString Worker::getEducationalPrograms() const
{
    return educationalPrograms;
}


void Worker::setFio(const QString& newFio){
    fio = newFio;
}
void Worker::setPosition(const QString& newPosition){
    position = newPosition;
}
void Worker::setExperience(const QString& newExperience){
    experience = newExperience;
}
void Worker::setDisciplines(const QString& newDisciplines){
    disciplines = newDisciplines;
}
void Worker::setEducationLevel(const QString& newEducationLevel){
    educationLevel = newEducationLevel;
}
void Worker::setAcademicDegree(const QString& newAcademicDegree){
    academicDegree = newAcademicDegree;
}
void Worker::setAcademicTitle(const QString& newAcademicTitle){
    academicTitle = newAcademicTitle;
}
void Worker::setQualificationImprovement(const QString& newQualificationImprovement){
    qualificationImprovement = newQualificationImprovement;
}
void Worker::setProfessionalRetraining(const QString& newProfessionalRetraining){
    professionalRetraining = newProfessionalRetraining;
}
void Worker::setEducationalPrograms(const QString& newEducationalPrograms){
    educationalPrograms = newEducationalPrograms;
}

// int Worker::getExperience(int currentYear) const{
//     return currentYear - firstYear;
// }