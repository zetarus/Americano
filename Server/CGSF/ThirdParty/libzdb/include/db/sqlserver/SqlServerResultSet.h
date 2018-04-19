/*
 * Copyright (C) Tildeslash Ltd. All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef SQLSERVERRESULTSET_INCLUDED
#define SQLSERVERRESULTSET_INCLUDED
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <sql.h>      
#include <sqlext.h>      
#include <sqltypes.h>      
#include <odbcss.h> 
#include "Thread.h"

typedef struct st_sqlserver
{
	SQLHENV henv;
	SQLHDBC hdbc;
}SQLSERVER;

#define SQLSERVERSUCCESS(rc) ((rc==SQL_SUCCESS)||(rc==SQL_SUCCESS_WITH_INFO))

#define T ResultSetDelegate_T
T SqlServerResultSet_new(void *stmt, int maxRows, int keep);
void SqlServerResultSet_free(T *R);
int SqlServerResultSet_getColumnCount(T R);
const char *SqlServerResultSet_getColumnName(T R, int column);
int SqlServerResultSet_next(T R);
long SqlServerResultSet_getColumnSize(T R, int columnIndex);
const char *SqlServerResultSet_getString(T R, int columnIndex);
const void *SqlServerResultSet_getBlob(T R, int columnIndex, int *size);
#undef T
#endif
