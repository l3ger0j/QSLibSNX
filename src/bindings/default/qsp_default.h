/* Copyright (C) 2005-2010 Valeriy Argunov (nporep AT mail DOT ru) */
/*
* This library is free software; you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation; either version 2.1 of the License, or
* (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with this library; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*/

#include "../qsp.h"

#ifndef QSP_DEFAULTDEFINES
	#define QSP_DEFAULTDEFINES

	static int qspEndiannessTestValue = 1;

	#ifdef _UNICODE
		#ifdef __APPLE__
			#include <stddef.h>
			#include <stdint.h>
		#else
			#include <uchar.h>
		#endif

		typedef char16_t QSP_CHAR;
		#define QSP_FMT2(x) u##x
		#define QSP_FMT(x) QSP_FMT2(x)

		#define QSP_STRCOLL qspStrsComp
		#define QSP_CHRLWR qspToWLower
		#define QSP_CHRUPR qspToWUpper
		#define QSP_ONIG_ENC ((*(char *)&(qspEndiannessTestValue) == 1) ? \
					(sizeof(QSP_CHAR) == 2 ? ONIG_ENCODING_UTF16_LE : ONIG_ENCODING_UTF32_LE) : \
					(sizeof(QSP_CHAR) == 2 ? ONIG_ENCODING_UTF16_BE : ONIG_ENCODING_UTF32_BE))
		#define QSP_FROM_OS_CHAR(a) qspReverseConvertUC(a, qspCP1251ToUnicodeTable)
		#define QSP_TO_OS_CHAR(a) qspDirectConvertUC(a, qspCP1251ToUnicodeTable)
		#define QSP_WCTOB
		#define QSP_BTOWC

		#ifdef _MSC_VER
			#define QSP_FOPEN _wfopen
		#else
			#define QSP_FOPEN qspFileOpen
		#endif
	#else
		#define QSP_FOPEN fopen
			#if defined(_WIN) || defined(_PSP)
			#define QSP_FROM_OS_CHAR
						#define QSP_TO_OS_CHAR
						#define QSP_WCTOB(a) qspReverseConvertUC(a, qspCP1251ToUnicodeTable)
						#define QSP_BTOWC(a) qspDirectConvertUC(a, qspCP1251ToUnicodeTable)
						#define QSP_CHRLWR(a) qspCP1251ToLowerTable[(unsigned char)(a)]
						#define QSP_CHRUPR(a) qspCP1251ToUpperTable[(unsigned char)(a)]
						#define QSP_STRCOLL(a, b) qspStrCmpSB(a, b, qspCP1251OrderTable)
						#define QSP_ONIG_ENC ONIG_ENCODING_CP1251
		#else
			#define QSP_FROM_OS_CHAR(a) qspReverseConvertSB(a, qspCP1251ToKOI8RTable)
			#define QSP_TO_OS_CHAR(a) qspDirectConvertSB(a, qspCP1251ToKOI8RTable)
			#define QSP_WCTOB(a) qspReverseConvertUC(a, qspKOI8RToUnicodeTable)
			#define QSP_BTOWC(a) qspDirectConvertUC(a, qspKOI8RToUnicodeTable)
			#define QSP_CHRLWR(a) qspKOI8RToLowerTable[(unsigned char)(a)]
			#define QSP_CHRUPR(a) qspKOI8RToUpperTable[(unsigned char)(a)]
			#define QSP_STRCOLL(a, b) qspStrCmpSB(a, b, qspKOI8ROrderTable)
			#define QSP_ONIG_ENC ONIG_ENCODING_KOI8_R
		#endif
	#endif

	#define QSP_FIXBYTESORDER(a) ((*(char *)&(qspEndiannessTestValue) == 1) ? \
			(a) : \
			((unsigned short)(((a) << 8) | ((a) >> 8))))

	#ifdef _MSC_VER
		#define QSP_TIME _time64
	#else
		#define QSP_TIME time
	#endif

	#ifdef __cplusplus
		typedef int (*QSP_CALLBACK)(...);
	#else
		typedef int (*QSP_CALLBACK)();
	#endif

	#ifdef __cplusplus
	extern "C"
	{
	#endif

	char16_t* c16sncpy( char16_t* dest, const char16_t* src, size_t count );

	QSLIBSNX_EXTERN QSP_BOOL QSPIsInCallBack();
	QSLIBSNX_EXTERN void QSPEnableDebugMode(QSP_BOOL isDebug);
	QSLIBSNX_EXTERN void QSPGetCurStateData(QSP_CHAR **loc, int *actIndex, int *line);
	QSLIBSNX_EXTERN const QSP_CHAR *QSPGetVersion();
	QSLIBSNX_EXTERN const QSP_CHAR *QSPGetCompiledDateTime();
	QSLIBSNX_EXTERN int QSPGetFullRefreshCount();
	QSLIBSNX_EXTERN const QSP_CHAR *QSPGetQstFullPath();
	QSLIBSNX_EXTERN const QSP_CHAR *QSPGetCurLoc();
	QSLIBSNX_EXTERN const QSP_CHAR *QSPGetMainDesc();
	QSLIBSNX_EXTERN QSP_BOOL QSPIsMainDescChanged();
	QSLIBSNX_EXTERN const QSP_CHAR *QSPGetVarsDesc();
	QSLIBSNX_EXTERN QSP_BOOL QSPIsVarsDescChanged();
	QSLIBSNX_EXTERN QSP_BOOL QSPGetExprValue(const QSP_CHAR *str, QSP_BOOL *isString, int *numVal, QSP_CHAR *strVal, int strValBufSize);
	QSLIBSNX_EXTERN void QSPSetInputStrText(const QSP_CHAR *str);
	QSLIBSNX_EXTERN int QSPGetActionsCount();
	QSLIBSNX_EXTERN void QSPGetActionData(int ind, QSP_CHAR **imgPath, QSP_CHAR **desc);
	QSLIBSNX_EXTERN QSP_BOOL QSPExecuteSelActionCode(QSP_BOOL isRefresh);
	QSLIBSNX_EXTERN QSP_BOOL QSPSetSelActionIndex(int ind, QSP_BOOL isRefresh);
	QSLIBSNX_EXTERN int QSPGetSelActionIndex();
	QSLIBSNX_EXTERN QSP_BOOL QSPIsActionsChanged();
	QSLIBSNX_EXTERN int QSPGetObjectsCount();
	QSLIBSNX_EXTERN void QSPGetObjectData(int ind, QSP_CHAR **imgPath, QSP_CHAR **desc);
	QSLIBSNX_EXTERN QSP_BOOL QSPSetSelObjectIndex(int ind, QSP_BOOL isRefresh);
	QSLIBSNX_EXTERN int QSPGetSelObjectIndex();
	QSLIBSNX_EXTERN QSP_BOOL QSPIsObjectsChanged();
	QSLIBSNX_EXTERN void QSPShowWindow(int type, QSP_BOOL isShow);
	QSLIBSNX_EXTERN QSP_BOOL QSPGetVarValuesCount(const QSP_CHAR *name, int *count);
	QSLIBSNX_EXTERN QSP_BOOL QSPGetVarValues(const QSP_CHAR *name, int ind, int *numVal, QSP_CHAR **strVal);
	QSLIBSNX_EXTERN int QSPGetMaxVarsCount();
	QSLIBSNX_EXTERN QSP_BOOL QSPGetVarNameByIndex(int ind, QSP_CHAR **name);
	QSLIBSNX_EXTERN QSP_BOOL QSPExecString(const QSP_CHAR *str, QSP_BOOL isRefresh);
	QSLIBSNX_EXTERN QSP_BOOL QSPExecCounter(QSP_BOOL isRefresh);
	QSLIBSNX_EXTERN QSP_BOOL QSPExecUserInput(QSP_BOOL isRefresh);
	QSLIBSNX_EXTERN QSP_BOOL QSPExecLocationCode(const QSP_CHAR *name, QSP_BOOL isRefresh);
	QSLIBSNX_EXTERN void QSPGetLastErrorData(int *errorNum, QSP_CHAR **errorLoc, int *errorActIndex, int *errorLine);
	QSLIBSNX_EXTERN const QSP_CHAR *QSPGetErrorDesc(int errorNum);
	QSLIBSNX_EXTERN QSP_BOOL QSPLoadGameWorld(const QSP_CHAR *file);
	QSLIBSNX_EXTERN QSP_BOOL QSPLoadGameWorldFromData(const void *data, int dataSize, const QSP_CHAR *file);
	QSLIBSNX_EXTERN QSP_BOOL QSPSaveGame(const QSP_CHAR *file, QSP_BOOL isRefresh);
    QSLIBSNX_EXTERN QSP_BOOL QSPSaveGameAsData(void **buf, int *realSize, QSP_BOOL isRefresh);
	QSLIBSNX_EXTERN QSP_BOOL QSPOpenSavedGame(const QSP_CHAR *file, QSP_BOOL isRefresh);
	QSLIBSNX_EXTERN QSP_BOOL QSPOpenSavedGameFromData(const void *data, int dataSize, QSP_BOOL isRefresh);
	QSLIBSNX_EXTERN QSP_BOOL QSPRestartGame(QSP_BOOL isRefresh);
    //QSLIBSNX_EXTERN void QSPSelectMenuItem(int ind);
	QSLIBSNX_EXTERN void QSPSetCallBack(int type, QSP_CALLBACK func);
	QSLIBSNX_EXTERN void QSPInit();
	QSLIBSNX_EXTERN void QSPDeInit();

	#ifdef __cplusplus
	}
	#endif

#endif
