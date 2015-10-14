// ODBCTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <assert.h>
#ifdef WIN32
#  include <windows.h>
#endif
#include <string>
#include <sstream>
#include <sql.h>
#include <sqlext.h>
#include <sqlncli.h>
#define DESC_LEN 51
#define ARRAY_SIZE 1000

void TestBCP(SQLHANDLE hDbConn)
{
   int idCompany1,idCompany2;
   int nErr = bcp_init(hDbConn, "[dbo].t1", NULL, NULL, DB_IN);
   nErr = bcp_bind(hDbConn, (LPCBYTE) &idCompany1, 0, sizeof(idCompany1), NULL, 0,SQLINT4, 1);

   nErr = bcp_init(hDbConn, "[dbo].t2", NULL, NULL, DB_IN);
   nErr = bcp_bind(hDbConn, (LPCBYTE) &idCompany2, 0, sizeof(idCompany2), NULL, 0,SQLINT4, 1);
 
   nErr = bcp_sendrow(hDbConn);
   nErr = bcp_done(hDbConn);
}

void TestColumnWiseBindParams(SQLHANDLE hDbConn)
{
	//SQLHSTMT hstmt; //语句句柄
	//SQLRETURN sr = SQLAllocHandle(SQL_HANDLE_STMT, hDbConn, &hstmt); 

	//SQLCHAR *      Statement = (SQLCHAR*)("INSERT INTO [dbo].Parts (PartID) VALUES (?)");
	//SQLUINTEGER    PartIDArray[ARRAY_SIZE];
	//SQLCHAR        DescArray[ARRAY_SIZE][DESC_LEN];
	//SQLREAL        PriceArray[ARRAY_SIZE];
	//SQLINTEGER     PartIDIndArray[ARRAY_SIZE], DescLenOrIndArray[ARRAY_SIZE],
	//	PriceIndArray[ARRAY_SIZE];
	//SQLUSMALLINT   i, ParamStatusArray[ARRAY_SIZE];
	//SQLULEN ParamsProcessed;

	//memset(DescLenOrIndArray, 0, sizeof(DescLenOrIndArray));
	//memset(PartIDIndArray, 0, sizeof(PartIDIndArray));
	//memset(PriceIndArray, 0, sizeof(PriceIndArray));

	//SQLSetConnectAttr(hstmt, SQL_ATTR_AUTOCOMMIT, (SQLPOINTER)SQL_AUTOCOMMIT_OFF, 0);


	//// Set the SQL_ATTR_PARAM_BIND_TYPE statement attribute to use
	//// column-wise binding.
	//sr = SQLSetStmtAttr(hstmt, SQL_ATTR_PARAM_BIND_TYPE, (SQLPOINTER)SQL_PARAM_BIND_BY_COLUMN, 0);

	//// Specify the number of elements in each parameter array.
	//sr = SQLSetStmtAttr(hstmt, SQL_ATTR_PARAMSET_SIZE, (SQLPOINTER)ARRAY_SIZE, 0);

	//// Specify an array in which to return the status of each set of
	//// parameters.
	//sr = SQLSetStmtAttr(hstmt, SQL_ATTR_PARAM_STATUS_PTR, ParamStatusArray, 0);

	//// Specify an SQLUINTEGER value in which to return the number of sets of
	//// parameters processed.
	//sr = SQLSetStmtAttr(hstmt, SQL_ATTR_PARAMS_PROCESSED_PTR, &ParamsProcessed, 0);

	//// Bind the parameters in column-wise fashion.
	//sr = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_ULONG, SQL_INTEGER, 5, 0,
	//	PartIDArray, 0, PartIDIndArray);
	////SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, DESC_LEN - 1, 0,
	////	DescArray, DESC_LEN, DescLenOrIndArray);
	////SQLBindParameter(hstmt, 3, SQL_PARAM_INPUT, SQL_C_FLOAT, SQL_REAL, 7, 0,
	////	PriceArray, 0, PriceIndArray);

	//// Set part ID, description, and price.
	//for (i = 0; i < ARRAY_SIZE; i++) {
	//	//GetNewValues(&PartIDArray[i], DescArray[i], &PriceArray[i]);
	//	PartIDArray[i] = i;
	//	PartIDIndArray[i] = 0;
	//	DescLenOrIndArray[i] = SQL_NTS;
	//	PriceIndArray[i] = 0;
	//}

	//// Execute the statement.
	//sr = SQLExecDirect(hstmt, Statement, SQL_NTS);

	//sr = SQLSetStmtAttr(hstmt, SQL_ATTR_PARAMSET_SIZE, (SQLPOINTER)5, 0);
	//for (i = 0; i < ARRAY_SIZE; i++) {
	//	//GetNewValues(&PartIDArray[i], DescArray[i], &PriceArray[i]);
	//	PartIDArray[i] = i + ARRAY_SIZE;
	//	PartIDIndArray[i] = 0;
	//	DescLenOrIndArray[i] = SQL_NTS;
	//	PriceIndArray[i] = 0;
	//}
	//sr = SQLExecDirect(hstmt, Statement, SQL_NTS);

	// SQLEndTran(SQL_HANDLE_DBC, hstmt, SQL_COMMIT);
	///*SQLCHAR pStatus[100],pMsg[100];
	//SQLSMALLINT SQLmsglen;
	//SQLCHAR error[200]={0};
	//SQLINTEGER SQLerr;
	//sr = SQLGetDiagRec(SQL_HANDLE_STMT,hstmt,1,(SQLCHAR*)pStatus,&SQLerr,(SQLCHAR*)pMsg,100,&SQLmsglen);*/

	//
	//// Check to see which sets of parameters were processed successfully.
	//for (i = 0; i < ParamsProcessed; i++) {
	//	printf("Parameter Set  Status\n");
	//	printf("-------------  -------------\n");
	//	switch (ParamStatusArray[i]) {
	//  case SQL_PARAM_SUCCESS:
	//  case SQL_PARAM_SUCCESS_WITH_INFO:
	//	  printf("%13d  Success\n", i);
	//	  break;

	//  case SQL_PARAM_ERROR:
	//	  printf("%13d  Error\n", i);
	//	  break;

	//  case SQL_PARAM_UNUSED:
	//	  printf("%13d  Not processed\n", i);
	//	  break;

	//  case SQL_PARAM_DIAG_UNAVAILABLE:
	//	  printf("%13d  Unknown\n", i);
	//	  break;

	//	}
	//}
	//// Close the cursor.
	//SQLCloseCursor(hstmt);
}

void TestColumnInfos(SQLHANDLE hDbConn)
{
	SQLCHAR szSQL[] = "select id,name,binary  FROM [test].[dbo].[Table_1]";
	SQLCHAR szSQL2[] = "select id,name FROM [test].[dbo].[Table_2]";
	SQLHSTMT hstmt,hstmt2; //语句句柄
	int preFetch = 10;
	int nBufferLen = 4;
	//int areaid[ARRAY_SIZE];
	//unsigned char buffer[ARRAY_SIZE][1000];
	SQLLEN indicator1[ ARRAY_SIZE ];
	SQLUSMALLINT   i, rowStatusArray[ARRAY_SIZE];

	SQLRETURN sr = SQLAllocHandle(SQL_HANDLE_STMT, hDbConn, &hstmt); 
	sr = SQLAllocHandle(SQL_HANDLE_STMT, hDbConn, &hstmt2); 
	//sr = SQLSetScrollOptions( hstmt, SQL_CONCUR_VALUES, SQL_SCROLL_FORWARD_ONLY, SQL_IS_INTEGER);
	//sr = SQLSetStmtAttr( hstmt2, SQL_ATTR_CONCURRENCY , (SQLPOINTER)SQL_CONCUR_ROWVER , SQL_IS_INTEGER);
	 
	sr = SQLSetStmtAttr(hstmt2, SQL_ATTR_ROW_BIND_TYPE, (SQLPOINTER)nBufferLen, SQL_IS_INTEGER);
	sr = SQLSetStmtAttr(hstmt2, SQL_SOPT_SS_CURSOR_OPTIONS, (SQLPOINTER)SQL_CO_FFO  , SQL_IS_INTEGER);
	//sr = SQLSetStmtAttr(hstmt2, SQL_ATTR_CURSOR_TYPE , (SQLPOINTER)SQL_CURSOR_DYNAMIC ,SQL_IS_INTEGER);
	//sr = SQLSetStmtAttr(hstmt2, SQL_ATTR_ROWS_FETCHED_PTR, &rowStatusArray, 0);
	//sr = SQLSetStmtAttr(hstmt2, SQL_ATTR_ROW_STATUS_PTR, rowStatusArray, 0);
	//sr = SQLSetStmtAttr(hstmt2, SQL_ATTR_ROW_ARRAY_SIZE  , (SQLPOINTER)preFetch ,SQL_IS_INTEGER);
 //
	//sr = SQLPrepare(hstmt,szSQL,SQL_NTS);
	/*sr = SQLCancel(hstmt);
	sr = SQLCloseCursor(hstmt);*/
	sr = SQLPrepare(hstmt2,szSQL2,SQL_NTS);


	SQLSMALLINT nColumnCount,nColumnCount2;
	//sr = SQLNumResultCols(hstmt,&nColumnCount);
	sr = SQLNumResultCols(hstmt2,&nColumnCount2);
	SQLCHAR pStatus[100],pMsg[100];
	SQLSMALLINT SQLmsglen;
	SQLCHAR error[200]={0};
	SQLINTEGER SQLerr;
	sr = SQLGetDiagRec(SQL_HANDLE_STMT,hstmt2,1,(SQLCHAR*)pStatus,&SQLerr,(SQLCHAR*)pMsg,100,&SQLmsglen);
	sr = 0;

	sr = SQLExecute(hstmt);
	sr = SQLExecute(hstmt2);
	
	sr = SQLFetch(hstmt);
	sr = SQLFetch(hstmt2);


	
	//SQLINTEGER sCustID;
	//SQLINTEGER cbCustID = 0;

	////sr = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER,0, 0, &sCustID, 0, &cbCustID);
	//
	//SQLCHAR szCatalog[100] = {0};
	//SQLCHAR szData[100] = {0};
	//SQLCHAR szSChema[100] = {0};
	//SQLSMALLINT StringLength;
	//sr = SQLColAttribute(hstmt, 1, SQL_DESC_CATALOG_NAME , &szCatalog, 100, &StringLength, NULL);
	//sr = SQLColAttribute(hstmt, 1, SQL_DESC_BASE_COLUMN_NAME , &szData, 100, &StringLength, NULL);
 //
	//sr = SQLColAttribute(hstmt, 1, SQL_DESC_SCHEMA_NAME , &szSChema, 100, &StringLength, NULL);




	//sr = SQLBindCol( hstmt, 1, SQL_C_LONG,areaid, sizeof( areaid[ 0 ] ), indicator1 );
	//sCustID = 1;
	//sr = SQLExecute(hstmt);
	//sr = SQLFetch(hstmt);

	//sr = SQLSetPos(hstmt,1,SQL_POSITION,SQL_LOCK_NO_CHANGE  );

	//SQLCHAR pStatus[100],pMsg[100];
	//SQLSMALLINT SQLmsglen;
	//SQLCHAR error[200]={0};
	//SQLINTEGER SQLerr;
	//sr = SQLGetDiagRec(SQL_HANDLE_STMT,hstmt,1,(SQLCHAR*)pStatus,&SQLerr,(SQLCHAR*)pMsg,100,&SQLmsglen);

	//sr = SQLGetData(hstmt, 2, SQL_C_BINARY, buffer[0], 1000, &cbCustID);

	//sr = SQLSetPos(hstmt,2,SQL_POSITION,SQL_LOCK_NO_CHANGE  );
	//sr = SQLGetData(hstmt, 2, SQL_C_BINARY, buffer[1], 1000, &cbCustID);
	//
	//SQLULEN  cursorType;
	//sr = SQLGetStmtAttr(hstmt,SQL_ATTR_CURSOR_TYPE ,(PTR)&cursorType,0,NULL); 
	//
	//SQLCloseCursor(hstmt);
	//sCustID = 2;
	//sr = SQLExecute(hstmt);
	//sr = SQLFetch(hstmt);
	//
	////sr = SQLFetch(hstmt);

	int a = 0;
}

void TestBulkInsert(SQLHANDLE hDbConn)
{
	SQLHSTMT hstmt,hstmt2; //语句句柄
	SQLRETURN sr = SQLAllocHandle(SQL_HANDLE_STMT, hDbConn, &hstmt); 
	//sr = SQLAllocHandle(SQL_HANDLE_STMT, hDbConn, &hstmt2); 
	int nBatch = 512;
	int nRowSize = sizeof(int) + sizeof(wchar_t) * 256 + sizeof(wchar_t) * 256 + sizeof(int) + 4 * sizeof(SQLINTEGER);
	SQLCHAR *      Statement = (SQLCHAR*)("INSERT INTO [dbo].Table_1 (id,name,city,age) VALUES (?,?,?,?)");
	SQLCHAR *      Statement2 = (SQLCHAR*)("INSERT INTO [dbo].Table_2 (id,name,city) VALUES (?,?,?)");
	char* pBuffer = (char*)malloc(nRowSize *nBatch);
	SQLUSMALLINT* ParamStatusArray = new SQLUSMALLINT[nBatch];
	SQLULEN ParamsProcessed;

	long begin = GetTickCount();
	sr = SQLSetConnectAttr(hDbConn, SQL_ATTR_AUTOCOMMIT, (SQLPOINTER)SQL_AUTOCOMMIT_OFF, SQL_IS_INTEGER);

	sr = SQLSetStmtAttr(hstmt, SQL_ATTR_PARAM_BIND_TYPE, (SQLPOINTER)nRowSize, SQL_IS_INTEGER);
	sr = SQLSetStmtAttr(hstmt, SQL_ATTR_PARAMSET_SIZE, (SQLPOINTER)nBatch, SQL_IS_INTEGER);
	sr = SQLSetStmtAttr(hstmt, SQL_ATTR_PARAM_STATUS_PTR, ParamStatusArray, SQL_IS_INTEGER);
	sr = SQLSetStmtAttr(hstmt, SQL_ATTR_PARAMS_PROCESSED_PTR, &ParamsProcessed, SQL_IS_INTEGER);


	/*sr = SQLSetStmtAttr(hstmt2, SQL_ATTR_PARAM_BIND_TYPE, (SQLPOINTER)nRowSize, SQL_IS_INTEGER);
	sr = SQLSetStmtAttr(hstmt2, SQL_ATTR_PARAMSET_SIZE, (SQLPOINTER)nBatch, SQL_IS_INTEGER);
	sr = SQLSetStmtAttr(hstmt2, SQL_ATTR_PARAM_STATUS_PTR, ParamStatusArray, SQL_IS_INTEGER);
	sr = SQLSetStmtAttr(hstmt2, SQL_ATTR_PARAMS_PROCESSED_PTR, &ParamsProcessed, SQL_IS_INTEGER);*/

	
	sr = SQLPrepare(hstmt,Statement,SQL_NTS);
	/*sr = SQLPrepare(hstmt2,Statement2,SQL_NTS);*/
	//SQLSMALLINT    DataTypePtr;
	//SQLULEN       ParameterSizePtr;
	//SQLSMALLINT    DecimalDigitsPtr;
	//SQLSMALLINT    NullablePtr;

	//SQLDescribeParam(hstmt,1,&DataTypePtr,&ParameterSizePtr,&DecimalDigitsPtr,&NullablePtr);
	//SQLDescribeParam(hstmt,2,&DataTypePtr,&ParameterSizePtr,&DecimalDigitsPtr,&NullablePtr);
	//SQLDescribeParam(hstmt,3,&DataTypePtr,&ParameterSizePtr,&DecimalDigitsPtr,&NullablePtr);
	{
		int nPos = 0;
		SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 10, 0,pBuffer + nPos, 0, (SQLINTEGER *)(pBuffer + nPos + sizeof(int)) );
		nPos += (sizeof(int) + sizeof(SQLINTEGER));
		SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, 255, 0,pBuffer + nPos, 0, (SQLINTEGER *)(pBuffer + nPos + sizeof(wchar_t) * 256 ));
		nPos += (sizeof(wchar_t) * 256 + sizeof(SQLINTEGER));
		SQLBindParameter(hstmt, 3, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR,255, 0,pBuffer + nPos, 0, (SQLINTEGER *)(pBuffer + nPos + sizeof(wchar_t) * 256 ));
		nPos += (sizeof(wchar_t) * 256 + sizeof(SQLINTEGER));
		SQLBindParameter(hstmt, 4, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 10, 0,pBuffer + nPos, 0, (SQLINTEGER *)(pBuffer + nPos + sizeof(int)) );
	}
	
	//{
	//	int nPos = 0;
	//	SQLBindParameter(hstmt2, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 10, 0,pBuffer + nPos, 0, (SQLINTEGER *)(pBuffer + nPos + sizeof(int)) );
	//	nPos += (sizeof(int) + sizeof(SQLINTEGER));
	//	SQLBindParameter(hstmt2, 2, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, 255, 0,pBuffer + nPos, 0, (SQLINTEGER *)(pBuffer + nPos + sizeof(wchar_t) * 256 ));
	//	nPos += (sizeof(wchar_t) * 256 + sizeof(SQLINTEGER));
	//	SQLBindParameter(hstmt2, 3, SQL_PARAM_INPUT, SQL_C_BINARY, SQL_VARBINARY, 0, 0,pBuffer + nPos, 0, (SQLINTEGER *)(pBuffer + nPos + 10240));
	//}
	

	const wchar_t* pszName = L"helloworld";
	//char binary[10240] = {0};
	int nCount = 274;
	int id;
	int index = 0;
	for (int k = 0;k < nCount;k++)
	{
		int nPos = 0;
		SQLINTEGER    ind = 0;
		for (int i = 0; i < nBatch; i++) 
		{
			//id
			id = k * nBatch + i;
			memcpy(pBuffer + nPos,&id,sizeof(id));
			nPos += sizeof(id);
			memcpy(pBuffer + nPos,&ind,sizeof(ind));
			nPos += sizeof(ind);

			//name
			memcpy(pBuffer + nPos,pszName,sizeof(wchar_t) * wcslen(pszName));
			pBuffer[nPos + sizeof(wchar_t) * wcslen(pszName)] = 0;
			pBuffer[nPos + sizeof(wchar_t) * wcslen(pszName) + 1] = 0;
			nPos += sizeof(wchar_t) * 256;
			ind = sizeof(wchar_t) * wcslen(pszName);
			memcpy(pBuffer + nPos,&ind,sizeof(ind));
			nPos += sizeof(ind);
			
			//city
			memcpy(pBuffer + nPos,pszName,sizeof(wchar_t) * wcslen(pszName));
			pBuffer[nPos + sizeof(wchar_t) * wcslen(pszName)] = 0;
			pBuffer[nPos + sizeof(wchar_t) * wcslen(pszName) + 1] = 0;
			nPos += sizeof(wchar_t) * 256;
			ind = sizeof(wchar_t) * wcslen(pszName);
			memcpy(pBuffer + nPos,&ind,sizeof(ind));
			nPos += sizeof(ind);

			//age
			memcpy(pBuffer + nPos,&id,sizeof(id));
			nPos += sizeof(id);
			memcpy(pBuffer + nPos,&ind,sizeof(ind));
			nPos += sizeof(ind);

			//assert((nPos % nRowSize) == 0);
			index++;
		}
		sr = SQLExecute(hstmt);
		//sr = SQLExecute(hstmt2);
		/*SQLCHAR pStatus[100],pMsg[100];
		SQLSMALLINT SQLmsglen;
		SQLCHAR error[200]={0};
		SQLINTEGER SQLerr;
		sr = SQLGetDiagRec(SQL_HANDLE_STMT,hstmt,1,(SQLCHAR*)pStatus,&SQLerr,(SQLCHAR*)pMsg,100,&SQLmsglen);
		sr = 0;*/
	}	
	SQLEndTran(SQL_HANDLE_DBC, hDbConn, SQL_COMMIT);
	sr = SQLSetConnectAttr(hDbConn, SQL_ATTR_AUTOCOMMIT, (SQLPOINTER)SQL_AUTOCOMMIT_ON, SQL_IS_INTEGER);
	long end = GetTickCount();
	std::cout << "total" << index <<std::endl;
	std::cout << (end - begin) << "ms" <<std::endl;
	std::cout << "ave" <<(end - begin) * 1.0/(nCount*nBatch) <<std::endl;;
	std::cout << "ave" <<(nCount*nBatch)  * 1000.0 / (end - begin) <<std::endl;;
}

void TestBulkInsert2(SQLHANDLE hDbConn)
{
	SQLHSTMT hstmt; //语句句柄
	SQLRETURN sr = SQLAllocHandle(SQL_HANDLE_STMT, hDbConn, &hstmt); 
	//sr = SQLAllocHandle(SQL_HANDLE_STMT, hDbConn, &hstmt2); 
	int nBatch = 512;
	int nRowSize = sizeof(int) + sizeof(wchar_t) * 256 + sizeof(wchar_t) * 256 + sizeof(int) + 4 * sizeof(SQLINTEGER);
	nRowSize = nRowSize * nBatch;
	std::stringstream stream;
	stream << "INSERT INTO [dbo].Table_1 (id,name,city,age) VALUES (?,?,?,?)";
	for(int i = 1;i < nBatch;i++)
		stream << ",(?,?,?,?)";
	std::string pszSQL = stream.str();
	SQLCHAR *      Statement = (SQLCHAR*)pszSQL.c_str();
	int _nBatch = 1;
	char* pBuffer = (char*)malloc(nRowSize);
	SQLUSMALLINT* ParamStatusArray = new SQLUSMALLINT[nBatch];
	SQLULEN ParamsProcessed;

	long begin = GetTickCount();
	sr = SQLSetConnectAttr(hDbConn, SQL_ATTR_AUTOCOMMIT, (SQLPOINTER)SQL_AUTOCOMMIT_OFF, SQL_IS_INTEGER);

	sr = SQLSetStmtAttr(hstmt, SQL_ATTR_PARAM_BIND_TYPE, (SQLPOINTER)nRowSize, SQL_IS_INTEGER);
	
	sr = SQLSetStmtAttr(hstmt, SQL_ATTR_PARAMSET_SIZE, (SQLPOINTER)_nBatch, SQL_IS_INTEGER);
	sr = SQLSetStmtAttr(hstmt, SQL_ATTR_PARAM_STATUS_PTR, ParamStatusArray, SQL_IS_INTEGER);
	sr = SQLSetStmtAttr(hstmt, SQL_ATTR_PARAMS_PROCESSED_PTR, &ParamsProcessed, SQL_IS_INTEGER);

	sr = SQLPrepare(hstmt,Statement,SQL_NTS);
	{
		int nPos = 0;
		for(int i = 0;i < nBatch;i++)
		{
			SQLBindParameter(hstmt, 1 + i * 4, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 10, 0,pBuffer + nPos, 0, (SQLINTEGER *)(pBuffer + nPos + sizeof(int)) );
			nPos += (sizeof(int) + sizeof(SQLINTEGER));
			SQLBindParameter(hstmt, 2  + i * 4, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, 255, 0,pBuffer + nPos, 0, (SQLINTEGER *)(pBuffer + nPos + sizeof(wchar_t) * 256 ));
			nPos += (sizeof(wchar_t) * 256 + sizeof(SQLINTEGER));
			SQLBindParameter(hstmt, 3  + i * 4, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR,255, 0,pBuffer + nPos, 0, (SQLINTEGER *)(pBuffer + nPos + sizeof(wchar_t) * 256 ));
			nPos += (sizeof(wchar_t) * 256 + sizeof(SQLINTEGER));
			SQLBindParameter(hstmt, 4  + i * 4, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 10, 0,pBuffer + nPos, 0, (SQLINTEGER *)(pBuffer + nPos + sizeof(int)) );
			nPos += (sizeof(int) + sizeof(SQLINTEGER));
		}
	}
	

	const wchar_t* pszName = L"helloworld";
	int nCount = 274;
	int id;
	int index = 0;
	for (int k = 0;k < nCount;k++)
	{
		int nPos = 0;
		SQLINTEGER    ind = 0;
		for (int i = 0; i < nBatch; i++) 
		{
			//id
			id = k * nBatch + i;
			memcpy(pBuffer + nPos,&id,sizeof(id));
			nPos += sizeof(id);
			memcpy(pBuffer + nPos,&ind,sizeof(ind));
			nPos += sizeof(ind);

			//name
			memcpy(pBuffer + nPos,pszName,sizeof(wchar_t) * wcslen(pszName));
			pBuffer[nPos + sizeof(wchar_t) * wcslen(pszName)] = 0;
			pBuffer[nPos + sizeof(wchar_t) * wcslen(pszName) + 1] = 0;
			nPos += sizeof(wchar_t) * 256;
			ind = sizeof(wchar_t) * wcslen(pszName);
			memcpy(pBuffer + nPos,&ind,sizeof(ind));
			nPos += sizeof(ind);
			
			//city
			memcpy(pBuffer + nPos,pszName,sizeof(wchar_t) * wcslen(pszName));
			pBuffer[nPos + sizeof(wchar_t) * wcslen(pszName)] = 0;
			pBuffer[nPos + sizeof(wchar_t) * wcslen(pszName) + 1] = 0;
			nPos += sizeof(wchar_t) * 256;
			ind = sizeof(wchar_t) * wcslen(pszName);
			memcpy(pBuffer + nPos,&ind,sizeof(ind));
			nPos += sizeof(ind);

			//age
			memcpy(pBuffer + nPos,&id,sizeof(id));
			nPos += sizeof(id);
			memcpy(pBuffer + nPos,&ind,sizeof(ind));
			nPos += sizeof(ind);

			//assert((nPos % nRowSize) == 0);
			index++;
		}
		sr = SQLExecute(hstmt);
	}	
	SQLEndTran(SQL_HANDLE_DBC, hDbConn, SQL_COMMIT);
	sr = SQLSetConnectAttr(hDbConn, SQL_ATTR_AUTOCOMMIT, (SQLPOINTER)SQL_AUTOCOMMIT_ON, SQL_IS_INTEGER);
	long end = GetTickCount();
	std::cout << "total" << index <<std::endl;
	std::cout << (end - begin) << "ms" <<std::endl;
	std::cout << "ave" <<(end - begin) * 1.0/(nCount*nBatch) <<std::endl;;
	std::cout << "ave" <<(nCount*nBatch)  * 1000.0 / (end - begin) <<std::endl;;
}

void TestBulkInsert3(SQLHANDLE hDbConn)
{
	SQLHSTMT hstmt; //语句句柄
	SQLRETURN sr = SQLAllocHandle(SQL_HANDLE_STMT, hDbConn, &hstmt); 
	//sr = SQLAllocHandle(SQL_HANDLE_STMT, hDbConn, &hstmt2); 
	int nBatch = 512;
	int nRowSize = sizeof(int) + sizeof(wchar_t) * 256 + sizeof(wchar_t) * 256 + sizeof(int) + 4 * sizeof(SQLINTEGER);
	nRowSize = nRowSize * nBatch;
	std::stringstream stream;
	stream << "INSERT INTO [dbo].Table_1 (id,name,city,age) select ?,?,?,?";
	for(int i = 1;i < nBatch;i++)
		stream << " union all select(?,?,?,?)";
	std::string pszSQL = stream.str();
	SQLCHAR *      Statement = (SQLCHAR*)pszSQL.c_str();
	int _nBatch = 1;
	char* pBuffer = (char*)malloc(nRowSize);
	SQLUSMALLINT* ParamStatusArray = new SQLUSMALLINT[nBatch];
	SQLULEN ParamsProcessed;

	long begin = GetTickCount();
	sr = SQLSetConnectAttr(hDbConn, SQL_ATTR_AUTOCOMMIT, (SQLPOINTER)SQL_AUTOCOMMIT_OFF, SQL_IS_INTEGER);

	sr = SQLSetStmtAttr(hstmt, SQL_ATTR_PARAM_BIND_TYPE, (SQLPOINTER)nRowSize, SQL_IS_INTEGER);
	
	sr = SQLSetStmtAttr(hstmt, SQL_ATTR_PARAMSET_SIZE, (SQLPOINTER)_nBatch, SQL_IS_INTEGER);
	sr = SQLSetStmtAttr(hstmt, SQL_ATTR_PARAM_STATUS_PTR, ParamStatusArray, SQL_IS_INTEGER);
	sr = SQLSetStmtAttr(hstmt, SQL_ATTR_PARAMS_PROCESSED_PTR, &ParamsProcessed, SQL_IS_INTEGER);

	sr = SQLPrepare(hstmt,Statement,SQL_NTS);
	{
		int nPos = 0;
		for(int i = 0;i < nBatch;i++)
		{
			SQLBindParameter(hstmt, 1 + i * 4, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 10, 0,pBuffer + nPos, 0, (SQLINTEGER *)(pBuffer + nPos + sizeof(int)) );
			nPos += (sizeof(int) + sizeof(SQLINTEGER));
			SQLBindParameter(hstmt, 2  + i * 4, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, 255, 0,pBuffer + nPos, 0, (SQLINTEGER *)(pBuffer + nPos + sizeof(wchar_t) * 256 ));
			nPos += (sizeof(wchar_t) * 256 + sizeof(SQLINTEGER));
			SQLBindParameter(hstmt, 3  + i * 4, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR,255, 0,pBuffer + nPos, 0, (SQLINTEGER *)(pBuffer + nPos + sizeof(wchar_t) * 256 ));
			nPos += (sizeof(wchar_t) * 256 + sizeof(SQLINTEGER));
			SQLBindParameter(hstmt, 4  + i * 4, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 10, 0,pBuffer + nPos, 0, (SQLINTEGER *)(pBuffer + nPos + sizeof(int)) );
			nPos += (sizeof(int) + sizeof(SQLINTEGER));
		}
	}
	

	const wchar_t* pszName = L"helloworld";
	int nCount = 274;
	int id;
	int index = 0;
	for (int k = 0;k < nCount;k++)
	{
		int nPos = 0;
		SQLINTEGER    ind = 0;
		for (int i = 0; i < nBatch; i++) 
		{
			//id
			id = k * nBatch + i;
			memcpy(pBuffer + nPos,&id,sizeof(id));
			nPos += sizeof(id);
			memcpy(pBuffer + nPos,&ind,sizeof(ind));
			nPos += sizeof(ind);

			//name
			memcpy(pBuffer + nPos,pszName,sizeof(wchar_t) * wcslen(pszName));
			pBuffer[nPos + sizeof(wchar_t) * wcslen(pszName)] = 0;
			pBuffer[nPos + sizeof(wchar_t) * wcslen(pszName) + 1] = 0;
			nPos += sizeof(wchar_t) * 256;
			ind = sizeof(wchar_t) * wcslen(pszName);
			memcpy(pBuffer + nPos,&ind,sizeof(ind));
			nPos += sizeof(ind);
			
			//city
			memcpy(pBuffer + nPos,pszName,sizeof(wchar_t) * wcslen(pszName));
			pBuffer[nPos + sizeof(wchar_t) * wcslen(pszName)] = 0;
			pBuffer[nPos + sizeof(wchar_t) * wcslen(pszName) + 1] = 0;
			nPos += sizeof(wchar_t) * 256;
			ind = sizeof(wchar_t) * wcslen(pszName);
			memcpy(pBuffer + nPos,&ind,sizeof(ind));
			nPos += sizeof(ind);

			//age
			memcpy(pBuffer + nPos,&id,sizeof(id));
			nPos += sizeof(id);
			memcpy(pBuffer + nPos,&ind,sizeof(ind));
			nPos += sizeof(ind);

			//assert((nPos % nRowSize) == 0);
			index++;
		}
		sr = SQLExecute(hstmt);
		SQLCHAR pStatus[100],pMsg[100];
		SQLSMALLINT SQLmsglen;
		SQLCHAR error[200]={0};
		SQLINTEGER SQLerr;
		sr = SQLGetDiagRec(SQL_HANDLE_STMT,hstmt,1,(SQLCHAR*)pStatus,&SQLerr,(SQLCHAR*)pMsg,100,&SQLmsglen);
		sr = 0;
	}	
	SQLEndTran(SQL_HANDLE_DBC, hDbConn, SQL_COMMIT);
	sr = SQLSetConnectAttr(hDbConn, SQL_ATTR_AUTOCOMMIT, (SQLPOINTER)SQL_AUTOCOMMIT_ON, SQL_IS_INTEGER);
	long end = GetTickCount();
	std::cout << "total" << index <<std::endl;
	std::cout << (end - begin) << "ms" <<std::endl;
	std::cout << "ave" <<(end - begin) * 1.0/(nCount*nBatch) <<std::endl;;
	std::cout << "ave" <<(nCount*nBatch)  * 1000.0 / (end - begin) <<std::endl;;
}

void TestBulkInsertProcedure(SQLHANDLE hDbConn)
{
	SQLHSTMT hstmt; //语句句柄
	SQLRETURN sr = SQLAllocHandle(SQL_HANDLE_STMT, hDbConn, &hstmt); 

	SQLCHAR *      Statement = (SQLCHAR*)("{call a(?,?,?)}");
	struct Data
	{
		int id;
		float age;
		double weight;
		SQLINTEGER    PriceInd;
		SQLINTEGER    PartIDInd;
		SQLINTEGER    DescLenOrInd;
	};
	Data rows[ARRAY_SIZE];
	memset(rows,0,sizeof(rows));
	SQLUSMALLINT   ParamStatusArray[ARRAY_SIZE];
	SQLULEN ParamsProcessed;

	sr = SQLSetConnectAttr(hDbConn, SQL_ATTR_AUTOCOMMIT, (SQLPOINTER)SQL_AUTOCOMMIT_OFF, SQL_IS_INTEGER);
	sr = SQLSetStmtAttr(hstmt, SQL_ATTR_PARAM_BIND_TYPE, (SQLPOINTER)sizeof(Data), SQL_IS_INTEGER);
	sr = SQLSetStmtAttr(hstmt, SQL_ATTR_PARAMSET_SIZE, (SQLPOINTER)ARRAY_SIZE, SQL_IS_INTEGER);
	sr = SQLSetStmtAttr(hstmt, SQL_ATTR_PARAM_STATUS_PTR, ParamStatusArray, SQL_IS_INTEGER);
	sr = SQLSetStmtAttr(hstmt, SQL_ATTR_PARAMS_PROCESSED_PTR, &ParamsProcessed, SQL_IS_INTEGER);

	long begin = GetTickCount();
	sr = SQLPrepare(hstmt,Statement,SQL_NTS);


	sr = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 5, 0,
		&(rows[0].id), 0, &(rows[0].PriceInd));
	SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_FLOAT, SQL_REAL, 24, 0,
		&(rows[0].age), 0,  &(rows[0].PartIDInd));
	SQLBindParameter(hstmt, 3, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_FLOAT, 53, 0,
		&(rows[0].weight), 0,  &(rows[0].DescLenOrInd));


	for (int k = 0;k < 100000;k++)
	{
		for (int i = 0; i < ARRAY_SIZE; i++) 
		{
			rows[i].id = k * ARRAY_SIZE + i;
			rows[i].age = k * ARRAY_SIZE + i * ARRAY_SIZE;
			rows[i].weight = k * ARRAY_SIZE - i * ARRAY_SIZE;
		}
		sr = SQLExecute(hstmt);
	}	
	SQLEndTran(SQL_HANDLE_DBC, hstmt, SQL_COMMIT);
	sr = SQLSetConnectAttr(hDbConn, SQL_ATTR_AUTOCOMMIT, (SQLPOINTER)SQL_AUTOCOMMIT_ON, SQL_IS_INTEGER);
	long end = GetTickCount();
	std::cout << (end - begin) << "ms" <<std::endl;
}
void TestBulkInsertProcedure2(SQLHANDLE hDbConn)
{
	SQLHSTMT hstmt; //语句句柄
	SQLRETURN sr = SQLAllocHandle(SQL_HANDLE_STMT, hDbConn, &hstmt); 

	SQLCHAR *      Statement = (SQLCHAR*)("{call b(?,?,?)}");
	struct Data
	{
		int id;
		float age;
		double weight;
		SQLINTEGER    PriceInd;
		SQLINTEGER    PartIDInd;
		SQLINTEGER    DescLenOrInd;
	};
	Data rows[ARRAY_SIZE];
	memset(rows,0,sizeof(rows));
	SQLUSMALLINT   ParamStatusArray[ARRAY_SIZE];
	SQLULEN ParamsProcessed;

	sr = SQLSetConnectAttr(hDbConn, SQL_ATTR_AUTOCOMMIT, (SQLPOINTER)SQL_AUTOCOMMIT_OFF, SQL_IS_INTEGER);
	sr = SQLSetStmtAttr(hstmt, SQL_ATTR_PARAM_BIND_TYPE, (SQLPOINTER)sizeof(Data), SQL_IS_INTEGER);
	sr = SQLSetStmtAttr(hstmt, SQL_ATTR_PARAMSET_SIZE, (SQLPOINTER)ARRAY_SIZE, SQL_IS_INTEGER);
	sr = SQLSetStmtAttr(hstmt, SQL_ATTR_PARAM_STATUS_PTR, ParamStatusArray, SQL_IS_INTEGER);
	sr = SQLSetStmtAttr(hstmt, SQL_ATTR_PARAMS_PROCESSED_PTR, &ParamsProcessed, SQL_IS_INTEGER);

	long begin = GetTickCount();
	sr = SQLPrepare(hstmt,Statement,SQL_NTS);


	sr = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 5, 0,
		&(rows[0].id), 0, &(rows[0].PriceInd));
	SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_FLOAT, SQL_REAL, 24, 0,
		&(rows[0].age), 0,  &(rows[0].PartIDInd));
	SQLBindParameter(hstmt, 3, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_FLOAT, 53, 0,
		&(rows[0].weight), 0,  &(rows[0].DescLenOrInd));


	for (int k = 0;k < 1000;k++)
	{
		for (int i = 0; i < ARRAY_SIZE; i++) 
		{
			rows[i].id = k * ARRAY_SIZE + i;
			rows[i].age = k * ARRAY_SIZE + i * ARRAY_SIZE;
			rows[i].weight = k * ARRAY_SIZE - i * ARRAY_SIZE;
		}
		sr = SQLExecute(hstmt);
	}	
	SQLEndTran(SQL_HANDLE_DBC, hstmt, SQL_COMMIT);
	sr = SQLSetConnectAttr(hDbConn, SQL_ATTR_AUTOCOMMIT, (SQLPOINTER)SQL_AUTOCOMMIT_ON, SQL_IS_INTEGER);
	long end = GetTickCount();
	std::cout << (end - begin) << "ms" <<std::endl;
}
int _tmain(int argc, _TCHAR* argv[])
{
	SQLRETURN sr;

	char szSql[]="SELECT EmpName,Sex FROM [dbo].[Employees]";

	

	//Allocate Environment 
	//Step 2 初始化环境 
	SQLHANDLE hOdbcEnv;
	sr=SQLAllocHandle(SQL_HANDLE_ENV,SQL_NULL_HANDLE,&hOdbcEnv);
	if (sr!=SQL_SUCCESS)
		printf("Error in Allocating Environment!\n");
	sr = SQLSetEnvAttr(hOdbcEnv,SQL_ATTR_ODBC_VERSION,(SQLPOINTER)SQL_OV_ODBC3,SQL_IS_INTEGER);

	 // Step 3 :建立连接 
	std::string connstr = "DRIVER=SQL Server Native Client 11.0;Server=HUIHUI\\MSSQLSERVER2012;Database=test;trusted_connection=yes;";
	SQLHANDLE hDbConn;
	SQLCHAR szOutConn[1024];
	SQLSMALLINT OutConnStrLen;
	sr = SQLAllocHandle(SQL_HANDLE_DBC, hOdbcEnv, &hDbConn); 
	sr=SQLSetConnectAttr(hDbConn,SQL_ATTR_LOGIN_TIMEOUT,(void *) 5,0);
	sr=SQLSetConnectAttr(hDbConn, SQL_COPT_SS_MARS_ENABLED, (SQLPOINTER)SQL_MARS_ENABLED_YES, SQL_IS_UINTEGER);
	sr=SQLSetConnectAttr(hDbConn, SQL_COPT_SS_BCP, (void *)SQL_BCP_ON, SQL_IS_INTEGER);

	sr = SQLDriverConnect(hDbConn,NULL,(SQLCHAR*)connstr.c_str(),SQL_NTS, szOutConn, 1024, &OutConnStrLen, SQL_DRIVER_NOPROMPT);
	if (!SQL_SUCCEEDED(sr)) //连接失败时返回错误值 
		return -1;
	TestBulkInsert3(hDbConn);
	getchar();
	return 0;
	TestColumnInfos(hDbConn);

	// Step 4 :初始化语句句柄 
	SQLHSTMT sqlstmt; //语句句柄
	sr = SQLAllocHandle(SQL_HANDLE_STMT, hDbConn, &sqlstmt); 

	//执行SQL语句，将当前行的列捆绑到一个固定的存储区中，
	// 如果SQLFetch(sqlstmt)返回SQL_NO_DATA_FOUND，说明没有数据了
	//  行捆绑
	SQLCHAR sName[1024], sSno[1024]; 
	SQLINTEGER  cbSno = SQL_NTS, cbName = SQL_NTS;
	sr = SQLExecDirect(sqlstmt,(UCHAR *) szSql,SQL_NTS); 
	sr = SQLSetStmtAttr(sqlstmt,SQL_ATTR_ROW_BIND_TYPE,(SQLPOINTER)SQL_BIND_BY_COLUMN,SQL_IS_INTEGER );

	sr = SQLBindCol(sqlstmt, 1, SQL_C_CHAR,sName, 1024, &cbName); 
	sr = SQLBindCol(sqlstmt, 2, SQL_C_CHAR,sSno,1024, &cbSno); 

	CHAR str[100] ;
	sr=SQLFetch(sqlstmt);
	while ( sr!=SQL_NO_DATA_FOUND) {
		sprintf(str,"Name:%s  \tSNO:%s\n",sName,sSno);
		std::cout << str << std::endl;
		sr=SQLFetch(sqlstmt);
	}
	SQLFreeStmt(sqlstmt,SQL_CLOSE);

	TestColumnWiseBindParams(hDbConn);
	return 0;
}

