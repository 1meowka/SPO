#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>

#define DATABASE_HOSTNAME "ExampleDataBase"
#define DATABASE_NAME "lab4.db"

#define TABLE_TEACH "teacher"
#define TEACH_ID "teacher_id"
#define TEACH_FIO "fio"
#define TEACH_DATE "date_of_birth"
#define TEACH_POS "position_id"
#define TEACH_DEP "department_id"

#define TABLE_POSITION "position"
#define POS_ID "position_id"
#define POS_NAME "name"

#define TABLE_DEPARTMENT "department"
#define DEP_ID "department_id"
#define DEP_NAME "name"

void on_activate(GApplication *app, gpointer user_data);

#endif /* DATABASE_H */
