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
#ifndef SQLSERVERCONNECTION_INCLUDED
#define SQLSERVERCONNECTION_INCLUDED
#define T ConnectionDelegate_T
T SqlServerConnection_new(URL_T url, char **error);
void SqlServerConnection_free(T *C);
void SqlServerConnection_setQueryTimeout(T C, int ms);
void SqlServerConnection_setMaxRows(T C, int max);
int SqlServerConnection_ping(T C);
int SqlServerConnection_beginTransaction(T C);
int SqlServerConnection_commit(T C);
int SqlServerConnection_rollback(T C);
long long int SqlServerConnection_lastRowId(T C);
long long int SqlServerConnection_rowsChanged(T C);
int SqlServerConnection_execute(T C, const char *sql, va_list ap);
ResultSet_T SqlServerConnection_executeQuery(T C, const char *sql, va_list ap);
PreparedStatement_T SqlServerConnection_prepareStatement(T C, const char *sql, va_list ap);
const char *SqlServerConnection_getLastError(T C);
#undef T
#endif

