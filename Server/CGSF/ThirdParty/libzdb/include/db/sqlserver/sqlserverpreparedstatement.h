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

#ifndef SQLSERVERPREPAREDSTATEMENT_INCLUDED
#define SQLSERVERPREPAREDSTATEMENT_INCLUDED
#define T PreparedStatementDelegate_T
T SqlServerPreparedStatement_new(SQLSERVER *db, void *stmt, int maxRows);
void SqlServerPreparedStatement_free(T *P);
void SqlServerPreparedStatement_setString(T P, int parameterIndex, const char *x);
void SqlServerPreparedStatement_setInt(T P, int parameterIndex, int x);
void SqlServerPreparedStatement_setLLong(T P, int parameterIndex, long long int x);
void SqlServerPreparedStatement_setDouble(T P, int parameterIndex, double x);
void SqlServerPreparedStatement_setBlob(T P, int parameterIndex, const void *x, int size);
void SqlServerPreparedStatement_execute(T P);
ResultSet_T SqlServerPreparedStatement_executeQuery(T P);
#undef T
#endif
 