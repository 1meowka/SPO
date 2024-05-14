#include "database.h"

static sqlite3 *db;

static int callback(void *data, int argc, char **argv, char **azColName) {
    int i;
    fprintf(stderr, "%s: ", (const char*)data);

    for(i = 0; i<argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    printf("\n");
    return 0;
}

void add_data(const char *table, const char *values) {
    char *sql = g_strdup_printf("INSERT INTO %s VALUES (%s);", table, values);
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

    if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "Record inserted successfully\n");
    }

    g_free(sql);
}

void delete_data(const char *table, const char *condition) {
    char *sql = g_strdup_printf("DELETE FROM %s WHERE %s;", table, condition);
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

    if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "Record deleted successfully\n");
    }

    g_free(sql);
}

void on_activate(GApplication *app, gpointer user_data) {
    // Connect to SQLite database
    int rc = sqlite3_open(DATABASE_NAME, &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(0);
    } else {
        fprintf(stderr, "Opened database successfully\n");
    }

    // Add data example
    add_data(TABLE_TEACH, "'John Smith', '1980-01-01', 1, 1");

    // Delete data example
    delete_data(TABLE_TEACH, "teacher_id = 1");

    // Close SQLite database connection
    sqlite3_close(db);
}
