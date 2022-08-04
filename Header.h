#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define Max 10
typedef struct course  //Define a new Course Type
{
    uint8_t ID;
    uint8_t Grade;
}Course;
typedef struct student //define a new Student Type
{
    uint8_t ID;
    uint8_t Year;
    Course Subjects[3];
}Student;
//Declare a global array Database of 10 students with initially all elements=0
Student Database[Max] = { 0 };
//APIs
bool SDB_IsFull();
uint8_t SDB_GetUsedSize();
bool SDB_AddEntry(uint8_t id, uint8_t year, uint8_t* subjects, uint8_t* grades);
void SDB_DeleteEntry(uint8_t id);
bool SDB_ReadEntry(uint8_t id, uint8_t* year, uint8_t* subjects, uint8_t* grades);
void SDB_GetIdList(uint8_t* count, uint8_t* list);
bool SDB_IsIdExist(uint8_t id);
// other useful functions
bool ID_Validation(uint8_t* id); //ID between 1 and 10
bool Grade_Validation(uint8_t* grade); // grade between 0 and 100
bool Year_Validation(uint8_t* year); // year between 1 and 12

#endif // HEADER_H_INCLUDED
