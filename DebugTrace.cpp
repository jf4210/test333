// $_FILEHEADER_BEGIN ****************************
// 文件名称: DebugTrace.cpp
// 文件说明: 日志调试,输出各种调试数据
// $_FILEHEADER_END ******************************

//#include "stdafx.h"
#include "DebugTrace.h"

#ifdef WIN32
#include <windows.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/timeb.h>
#include <stdarg.h>
#include <string.h>


int CDebugTrace::mnLogLevel = 3;	
char CDebugTrace::mszLogFileName[512] = {0};
unsigned CDebugTrace::muTraceOptions = Timestamp;
static CDebugTrace goDebugTrace;

// $_FUNCTION_BEGIN ******************************
// 函数名称: CDebugTrace( )
// 函数参数: 
// 返 回 值: 
// 函数说明: 构造函数
// $_FUNCTION_END ********************************
CDebugTrace::CDebugTrace( )
{
    mlDataLen = 0;	
}


// $_FUNCTION_BEGIN ******************************
// 函数名称: ~CDebugTrace( )
// 函数参数: 
// 返 回 值: 
// 函数说明: 析构函数
// $_FUNCTION_END ********************************
CDebugTrace::~CDebugTrace( )
{
    
}


// $_FUNCTION_BEGIN ******************************
// 函数名称: CDebugTrace& operator << ( char acCharVal )
// 函数参数: char acCharVal：要打印的字符
// 返 回 值: 
// 函数说明: 打印单个字符
// $_FUNCTION_END ********************************
CDebugTrace& CDebugTrace::operator << ( char acCharVal )
{
    char * lpWritePtr = mszPrintBuff + mlDataLen;
    
    mlDataLen += sprintf( lpWritePtr,"%c",acCharVal );
    
    ASSERT( mlDataLen <= DEF_TRACE_BUFF_LEN );
    return *this;
}



// $_FUNCTION_BEGIN ******************************
// 函数名称: CDebugTrace& operator << ( bool abBoolVal )
// 函数参数: bool abBoolVal:要打印的BOOL型数据
// 返 回 值: 
// 函数说明: 打印bool值
// $_FUNCTION_END ********************************
CDebugTrace& CDebugTrace::operator << ( bool abBoolVal )
{
    char * lpWritePtr = mszPrintBuff + mlDataLen;
    if ( abBoolVal )
    {
        mlDataLen += sprintf( lpWritePtr,"%s","true" );
    }
    else
    {
        mlDataLen += sprintf( lpWritePtr,"%s","false" );
    }
    ASSERT( mlDataLen <= DEF_TRACE_BUFF_LEN );
    return *this;
}



// $_FUNCTION_BEGIN ******************************
// 函数名称: CDebugTrace& operator << ( short asShortVal )
// 函数参数: short asShortVal：要打印的short型数据
// 返 回 值: 
// 函数说明: 打印short值
// $_FUNCTION_END ********************************
CDebugTrace& CDebugTrace::operator << ( short asShortVal )
{
    char * lpWritePtr = mszPrintBuff + mlDataLen;
    
    mlDataLen += sprintf( lpWritePtr,"%d",asShortVal );
    
    ASSERT( mlDataLen <= DEF_TRACE_BUFF_LEN );
    return *this;
}


// $_FUNCTION_BEGIN ******************************
// 函数名称: CDebugTrace& operator << ( unsigned short asShortVal )
// 函数参数: unsigned short asShortVal：要打印的 unsigned short型数据
// 返 回 值: 
// 函数说明: 打印unsigned short值
// $_FUNCTION_END ********************************
CDebugTrace& CDebugTrace::operator << ( unsigned short asShortVal )
{
    char * lpWritePtr = mszPrintBuff + mlDataLen;
    
    mlDataLen += sprintf( lpWritePtr,"%u",asShortVal );
    
    ASSERT( mlDataLen <= DEF_TRACE_BUFF_LEN );
    return *this;
}

// $_FUNCTION_BEGIN ******************************
// 函数名称: CDebugTrace& operator << ( int aiIntVal )
// 函数参数: int aiIntVal：要打印的 int 型数据
// 返 回 值: 
// 函数说明: 打印int值
// $_FUNCTION_END ********************************
CDebugTrace& CDebugTrace::operator << ( int aiIntVal )
{
    char * lpWritePtr = mszPrintBuff + mlDataLen;
    
    mlDataLen += sprintf( lpWritePtr,"%d",aiIntVal );
    
    ASSERT( mlDataLen <= DEF_TRACE_BUFF_LEN );
    return *this;
}


// $_FUNCTION_BEGIN ******************************
// 函数名称: CDebugTrace& operator << ( unsigned int aiIntVal )
// 函数参数: unsigned int aiIntVal：要打印的 unsigned int 型数据
// 返 回 值: 
// 函数说明: 打印 unsigned int值
// $_FUNCTION_END ********************************
CDebugTrace& CDebugTrace::operator << ( unsigned int aiIntVal )
{
    char * lpWritePtr = mszPrintBuff + mlDataLen;
    
    mlDataLen += sprintf( lpWritePtr,"%u",aiIntVal );
    
    ASSERT( mlDataLen <= DEF_TRACE_BUFF_LEN );
    return *this;
}

// $_FUNCTION_BEGIN ******************************
// 函数名称: CDebugTrace& operator << ( long aiIntVal )
// 函数参数: long aiIntVal：要打印的 long 型数据
// 返 回 值: 
// 函数说明: 打印 long值
// $_FUNCTION_END ********************************
CDebugTrace& CDebugTrace::operator << ( long alLongVal )
{
    char * lpWritePtr = mszPrintBuff + mlDataLen;
    
    mlDataLen += sprintf( lpWritePtr,"%ld",alLongVal );
    
    ASSERT( mlDataLen <= DEF_TRACE_BUFF_LEN );
    return *this;
}

// $_FUNCTION_BEGIN ******************************
// 函数名称: CDebugTrace& operator << ( unsigned long aiIntVal )
// 函数参数: unsigned long aiIntVal：要打印的 unsigned long 型数据
// 返 回 值: 
// 函数说明: 打印 unsigned long
// $_FUNCTION_END ********************************
CDebugTrace& CDebugTrace::operator << ( unsigned long alLongVal )
{
    char * lpWritePtr = mszPrintBuff + mlDataLen;
    
    mlDataLen += sprintf( lpWritePtr,"%lu",alLongVal );
    
    ASSERT( mlDataLen <= DEF_TRACE_BUFF_LEN );
    return *this;
}

// $_FUNCTION_BEGIN ******************************
// 函数名称: CDebugTrace& operator << ( float afFloatVal )
// 函数参数: float afFloatVal：要打印的 float 型数据
// 返 回 值: 
// 函数说明: 打印float值
// $_FUNCTION_END ********************************
CDebugTrace& CDebugTrace::operator << ( float afFloatVal )
{
    char * lpWritePtr = mszPrintBuff + mlDataLen;
    
    mlDataLen += sprintf( lpWritePtr,"%f",afFloatVal );
    
    ASSERT( mlDataLen <= DEF_TRACE_BUFF_LEN );
    return *this;
}

// $_FUNCTION_BEGIN ******************************
// 函数名称: CDebugTrace& operator << ( double afdoubleVal )
// 函数参数: double afdoubleVal：要打印的 double 型数据
// 返 回 值: 
// 函数说明: 打印double值
// $_FUNCTION_END ********************************
CDebugTrace& CDebugTrace::operator << ( double afdoubleVal )
{
    char * lpWritePtr = mszPrintBuff + mlDataLen;
    
    mlDataLen += sprintf( lpWritePtr,"%f",afdoubleVal );
    
    ASSERT( mlDataLen <= DEF_TRACE_BUFF_LEN );
    return *this;
}


// $_FUNCTION_BEGIN ******************************
// 函数名称: CDebugTrace& operator << ( __int64 aiInt64Val )
// 函数参数: __int64 aiInt64Val：要打印的 __int64  型数据
// 返 回 值: 
// 函数说明: 打印64位整数
// $_FUNCTION_END ********************************
CDebugTrace& CDebugTrace::operator << ( __int64 aiInt64Val )
{
    char *lpWritePtr = mszPrintBuff + mlDataLen;
    
    mlDataLen += sprintf( lpWritePtr,"%I64d",aiInt64Val );
    
    ASSERT( mlDataLen <= DEF_TRACE_BUFF_LEN );
    return *this;
}


// $_FUNCTION_BEGIN ******************************
// 函数名称: CDebugTrace& operator << ( const char *apStrVal )
// 函数参数: const char *apStrVal：要打印的\0结尾的字符串
// 返 回 值: 
// 函数说明: 打印以\0结尾的字符串值
// $_FUNCTION_END ********************************
CDebugTrace& CDebugTrace::operator << ( const char *apStrVal )
{
    char * lpWritePtr = mszPrintBuff + mlDataLen;
    if ( apStrVal == 0 )
    {
        mlDataLen += sprintf( lpWritePtr,"%s","NULL" );
    }
    else
    {
        mlDataLen += sprintf( lpWritePtr,"%s",apStrVal );
    }
    
    ASSERT( mlDataLen <= DEF_TRACE_BUFF_LEN );
    return *this;
}


// $_FUNCTION_BEGIN ******************************
// 函数名称: void TraceFormat( const char * pFmt,... )
// 函数参数: const char * pFmt,...( 可变长度参数,如:"姓名:%s,年龄:%d","zht",26 )
// 返 回 值: void
// 函数说明: 类似printf函数的格式打印一串日志
// $_FUNCTION_END ********************************
void CDebugTrace::TraceFormat( const char * pFmt,... )
{
    va_list argptr;
    char strPrintBuff[512];
    
    //把可变参数序列化到strPrintBuff中
    va_start( argptr,pFmt );
    vsprintf( strPrintBuff, pFmt, argptr );
    va_end( argptr );
    
    //把strPrintBuff追加到mszPrintBuff中
    char * lpWritePtr = mszPrintBuff + mlDataLen;
    mlDataLen += sprintf( lpWritePtr,"%s",strPrintBuff );
    
    //调用EndTrace结束打印
    EndTrace( *this );
}

////////////////////////////////////////////////
//以下是静态函数

// $_FUNCTION_BEGIN ******************************
// 函数名称: void CDebugTrace::SetTraceLevel( int aiTraceLevel )
// 函数参数: int aiTraceLevel:日志级别
// 返 回 值: void
// 函数说明: 设置TRACE等级( 0级最高,1其次,依次类推,小于该等级的日志不打印 )
// $_FUNCTION_END ********************************
void CDebugTrace::SetTraceLevel( int aiTraceLevel )
{
    CDebugTrace::mnLogLevel = aiTraceLevel;
}



// $_FUNCTION_BEGIN ******************************
// 函数名称: void CDebugTrace::SetLogFileName( char *aszLogFile )
// 函数参数: char *aszLogFile:日志文件名
// 返 回 值: void
// 函数说明: 设置输出日志文件名
// $_FUNCTION_END ********************************
void CDebugTrace::SetLogFileName( char *aszLogFile )
{
    if ( aszLogFile != NULL )
    {
        strcpy( CDebugTrace::mszLogFileName,aszLogFile );
    }
}

// $_FUNCTION_BEGIN ******************************
// 函数名称: void CDebugTrace::SetTraceOptions( unsigned options /** New level for trace */ )
// 函数参数: unsigned options:打印选项 各选项可以相加
// 返 回 值: void
// 函数说明: 设置TRACE选项
// $_FUNCTION_END ********************************
void CDebugTrace::SetTraceOptions( unsigned options /** New level for trace */ )
{
    CDebugTrace::muTraceOptions = options;
}

//
// $_FUNCTION_BEGIN ******************************
// 函数名称: unsigned CDebugTrace::GetTraceOptions( void )
// 函数参数: 
// 返 回 值: unsigned 打印选项
// 函数说明: 取得TRACE选项
// $_FUNCTION_END ********************************
unsigned CDebugTrace::GetTraceOptions( void )
{
    return CDebugTrace::muTraceOptions;
}

// $_FUNCTION_BEGIN ******************************
// 函数名称: bool CDebugTrace::CanTrace( int aiLogLevel )
// 函数参数: int aiLogLevel:日志级别
// 返 回 值: bool
// 函数说明: 判断给定级别是否可以打印
// $_FUNCTION_END ********************************
bool CDebugTrace::CanTrace( int aiLogLevel )
{
    return ( aiLogLevel <= CDebugTrace::mnLogLevel );
}

//*****************************************************************************
//	函数原型：	BeginTrace( int aiLogLevel,char *apSrcFile,int aiSrcLine )
//  函数说明:   开始打印一个日志
//  参数：      int aiLogLevel( 日志的级别 ),char *apSrcFile( 源文件名 ),
//				int aiSrcLine( 源行数 )
//  返回值：    返回类对象自身
//  用法：		BeginTrace( 3,__FILE__,__LINE__ )
//*****************************************************************************
CDebugTrace& CDebugTrace::BeginTrace( int aiLogLevel,char *apSrcFile,int aiSrcLine )
{
    CDebugTrace *lpDebugTrace = NULL;
    //lpDebugTrace = new CDebugTrace( );
    lpDebugTrace = &goDebugTrace;
	lpDebugTrace->moCriticalSection.Wait();

    ASSERT( lpDebugTrace != NULL );
    lpDebugTrace->mlDataLen = 0;	 //已打印的数据长度清0
    
    //如果要求输出时间,则在日志中输出日志产生的时间( 分:秒:毫秒 )
    if ( CDebugTrace::muTraceOptions & Timestamp ) 
    {
        time_t	ltmNow;	
        struct timeb loTimeb;
        
        time( &ltmNow );	
        ftime( &loTimeb ); 
        struct tm * lstrutime = localtime( &ltmNow );
        
        char lszTraceBuff[20];
        sprintf( lszTraceBuff,"%02d:%02d:%02d:%03d ",\
            lstrutime->tm_hour,lstrutime->tm_min,lstrutime->tm_sec,loTimeb.millitm );
        
        *lpDebugTrace << lszTraceBuff;
    }
    //如果要求输出日志级别,则在日志中输出日志级别
    if ( CDebugTrace::muTraceOptions & LogLevel )
    {
        *lpDebugTrace << aiLogLevel << ' ';
    }
    
    //如果要求输出源文件名和行号,则在日志中输出源文件名和行号
    if ( CDebugTrace::muTraceOptions & FileAndLine ) 
    {
        *lpDebugTrace << apSrcFile << "( " << aiSrcLine << " ) ";
    }
    
    //返回对象引用
    return *lpDebugTrace;
}


//*****************************************************************************
//	函数原型：	EndTrace( CDebugTrace &aoDebugTrace )
//  函数说明:   结束打印一个日志
//  参数：      CDebugTrace &aoDebugTrace( CDebugTrace 对象引用 )
//  返回值：    
//  用法：		
//*****************************************************************************
void CDebugTrace::EndTrace( CDebugTrace &aoDebugTrace )		//结束打印
{
#ifdef WIN32
    //输出到调试窗口中
    OutputDebugStringA( aoDebugTrace.mszPrintBuff ); 
#endif	
    //若要求输出到控制台,则把日志信息在控制台也打印一下
    if ( CDebugTrace::muTraceOptions & PrintToConsole ) 
        printf( "%s",aoDebugTrace.mszPrintBuff );
    
    //若要求写文件且设置了日志文件名,则把日志信息写入文件中
    if ( ( CDebugTrace::muTraceOptions & AppendToFile ) \
        && ( strlen( CDebugTrace::mszLogFileName ) > 1 ) )
    {
        FILE * lfpTraceFile = NULL;
        lfpTraceFile = fopen( CDebugTrace::mszLogFileName,"a" ); 	
        if ( lfpTraceFile != NULL )
        {
            fprintf( lfpTraceFile,"%s",aoDebugTrace.mszPrintBuff );
            fclose( lfpTraceFile );
        }
    }
	aoDebugTrace.moCriticalSection.Signal();
    //delete &aoDebugTrace;	
}


// $_FUNCTION_BEGIN ******************************
// 函数名称: void CDebugTrace::AssertFail( char * strCond,char *strFile, unsigned uLine )
// 函数参数: char * strCond: 函数表达式
//           char *strFile:源文件名
//           unsigned uLine：行号
// 返 回 值: void
// 函数说明: 弹出ASSERT出错信息
// $_FUNCTION_END ********************************
void CDebugTrace::AssertFail( char * strCond,char *strFile, unsigned uLine )
{
#ifdef WIN32    
    char szMessage[512]; 
    char strExePath[512];
    GetModuleFileNameA( 0, strExePath, 200 );
      
    sprintf( szMessage, "\nDebug Assertion Failed!\nFile: %s \nLine:%d \nCond: ASSERT( %s ); \n",strFile,uLine,strCond );    
    OutputDebugStringA( szMessage );

    sprintf( szMessage, " Debug Assertion Failed!\n\n Program:    %s     \n Condition:  ASSERT( %s );       \n SourceFile: %s       \n LineNum:    %d \n\n Continue?",
        strExePath,strCond,strFile,uLine );		
    int nResult = MessageBoxA( NULL,szMessage,"Assert failure",MB_OKCANCEL+MB_ICONERROR );    
    if ( nResult == IDCANCEL )
    {
        FatalExit( -1 );
    }
    else
    {
        DebugBreak();
    }
#else    
    printf( "Debug Assertion Failed!\n\nCondition:  ASSERT( %s );       \nSourceFile: %s       \nLineNum:    %d \n\nContinue?",
        strCond,strFile,uLine );		
    
    char lcUserInput =  getchar( );	
    if ( lcUserInput != 'y' && lcUserInput != 'Y' )
    {
        exit( -1 );
    }
#endif 
}