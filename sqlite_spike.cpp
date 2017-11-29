

/* 
 * File:   main.cpp
 * Author: Khrys' Pc
 *
 * Created on November 16, 2017, 5:47 PM
 */

#include <cstdlib>
#include <stdio.h>
#include "sqlite3.h"
#include "player.h"

using namespace std;

/*
 * 
 */

static int callback(void *data, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

int main(int argc, char** argv) {

 player p1;
 p1.set_pscore(15);

 
sqlite3 *db;
   char *zErrMsg = 0;
   int rc;

      /* Open database */
   rc = sqlite3_open("game.db", &db);

   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   } else {
      fprintf(stderr, "Opened database successfully\n");
   }
   
    /* Create SQL statement */
   sql = "CREATE TABLE game_db ("  \
         "NAME           TEXT    NOT NULL," \
         "score            INT     NOT NULL," \
         "milkbread        VARCHAR(50)," \
         "oilpetrol        VARCHAR(50)," \
         "beatcandy        VARCHAT(50)," \
         "nucleons         VARCHAR(50);";

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   
   if( rc != SQLITE_OK ){
   fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Table created successfully\n");
   }

     /* Create SQL statement */
   sql = "SELECT * from COMPANY";

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);

   
   sqlite3_close(db);

      
      
      
    
    
    
    
    return 0;
}

