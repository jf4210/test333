// $_FILEHEADER_BEGIN ****************************
// �ļ�����: DebugTrace.cpp
// �ļ�˵��: ��־����,������ֵ�������
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
// ��������: CDebugTrace( )
// ��������: 
// �� �� ֵ: 
// ����˵��: ���캯��
// $_FUNCTION_END ********************************
CDebugTrace::CDebugTrace( )
{
    mlDataLen = 0;	
}


// $_FUNCTION_BEGIN ******************************
// ��������: ~CDebugTrace( )
// ��������: 
// �� �� ֵ: 
// ����˵��: ��������
// $_FUNCTION_END ********************************
CDebugTrace::~CDebugTrace( )
{
    
}


// $_FUNCTION_BEGIN ******************************
// ��������: CDebugTrace& operator << ( char acCharVal )
// ��������: char acCharVal��Ҫ��ӡ���ַ�
// �� �� ֵ: 
// ����˵��: ��ӡ�����ַ�
// $_FUNCTION_END ********************************
CDebugTrace& CDebugTrace::operator << ( char acCharVal )
{
    char * lpWritePtr = mszPrintBuff + mlDataLen;
    
    mlDataLen += sprintf( lpWritePtr,"%c",acCharVal );
    
    ASSERT( mlDataLen <= DEF_TRACE_BUFF_LEN );
    return *this;
}



// $_FUNCTION_BEGIN ******************************
// ��������: CDebugTrace& operator << ( bool abBoolVal )
// ��������: bool abBoolVal:Ҫ��ӡ��BOOL������
// �� �� ֵ: 
// ����˵��: ��ӡboolֵ
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
// ��������: CDebugTrace& operator << ( short asShortVal )
// ��������: short asShortVal��Ҫ��ӡ��short������
// �� �� ֵ: 
// ����˵��: ��ӡshortֵ
// $_FUNCTION_END ********************************
CDebugTrace& CDebugTrace::operator << ( short asShortVal )
{
    char * lpWritePtr = mszPrintBuff + mlDataLen;
    
    mlDataLen += sprintf( lpWritePtr,"%d",asShortVal );
    
    ASSERT( mlDataLen <= DEF_TRACE_BUFF_LEN );
    return *this;
}


// $_FUNCTION_BEGIN ******************************
// ��������: CDebugTrace& operator << ( unsigned short asShortVal )
// ��������: unsigned short asShortVal��Ҫ��ӡ�� unsigned short������
// �� �� ֵ: 
// ����˵��: ��ӡunsigned shortֵ
// $_FUNCTION_END ********************************
CDebugTrace& CDebugTrace::operator << ( unsigned short asShortVal )
{
    char * lpWritePtr = mszPrintBuff + mlDataLen;
    
    mlDataLen += sprintf( lpWritePtr,"%u",asShortVal );
    
    ASSERT( mlDataLen <= DEF_TRACE_BUFF_LEN );
    return *this;
}

// $_FUNCTION_BEGIN ******************************
// ��������: CDebugTrace& operator << ( int aiIntVal )
// ��������: int aiIntVal��Ҫ��ӡ�� int ������
// �� �� ֵ: 
// ����˵��: ��ӡintֵ
// $_FUNCTION_END ********************************
CDebugTrace& CDebugTrace::operator << ( int aiIntVal )
{
    char * lpWritePtr = mszPrintBuff + mlDataLen;
    
    mlDataLen += sprintf( lpWritePtr,"%d",aiIntVal );
    
    ASSERT( mlDataLen <= DEF_TRACE_BUFF_LEN );
    return *this;
}


// $_FUNCTION_BEGIN ******************************
// ��������: CDebugTrace& operator << ( unsigned int aiIntVal )
// ��������: unsigned int aiIntVal��Ҫ��ӡ�� unsigned int ������
// �� �� ֵ: 
// ����˵��: ��ӡ unsigned intֵ
// $_FUNCTION_END ********************************
CDebugTrace& CDebugTrace::operator << ( unsigned int aiIntVal )
{
    char * lpWritePtr = mszPrintBuff + mlDataLen;
    
    mlDataLen += sprintf( lpWritePtr,"%u",aiIntVal );
    
    ASSERT( mlDataLen <= DEF_TRACE_BUFF_LEN );
    return *this;
}

// $_FUNCTION_BEGIN ******************************
// ��������: CDebugTrace& operator << ( long aiIntVal )
// ��������: long aiIntVal��Ҫ��ӡ�� long ������
// �� �� ֵ: 
// ����˵��: ��ӡ longֵ
// $_FUNCTION_END ********************************
CDebugTrace& CDebugTrace::operator << ( long alLongVal )
{
    char * lpWritePtr = mszPrintBuff + mlDataLen;
    
    mlDataLen += sprintf( lpWritePtr,"%ld",alLongVal );
    
    ASSERT( mlDataLen <= DEF_TRACE_BUFF_LEN );
    return *this;
}

// $_FUNCTION_BEGIN ******************************
// ��������: CDebugTrace& operator << ( unsigned long aiIntVal )
// ��������: unsigned long aiIntVal��Ҫ��ӡ�� unsigned long ������
// �� �� ֵ: 
// ����˵��: ��ӡ unsigned long
// $_FUNCTION_END ********************************
CDebugTrace& CDebugTrace::operator << ( unsigned long alLongVal )
{
    char * lpWritePtr = mszPrintBuff + mlDataLen;
    
    mlDataLen += sprintf( lpWritePtr,"%lu",alLongVal );
    
    ASSERT( mlDataLen <= DEF_TRACE_BUFF_LEN );
    return *this;
}

// $_FUNCTION_BEGIN ******************************
// ��������: CDebugTrace& operator << ( float afFloatVal )
// ��������: float afFloatVal��Ҫ��ӡ�� float ������
// �� �� ֵ: 
// ����˵��: ��ӡfloatֵ
// $_FUNCTION_END ********************************
CDebugTrace& CDebugTrace::operator << ( float afFloatVal )
{
    char * lpWritePtr = mszPrintBuff + mlDataLen;
    
    mlDataLen += sprintf( lpWritePtr,"%f",afFloatVal );
    
    ASSERT( mlDataLen <= DEF_TRACE_BUFF_LEN );
    return *this;
}

// $_FUNCTION_BEGIN ******************************
// ��������: CDebugTrace& operator << ( double afdoubleVal )
// ��������: double afdoubleVal��Ҫ��ӡ�� double ������
// �� �� ֵ: 
// ����˵��: ��ӡdoubleֵ
// $_FUNCTION_END ********************************
CDebugTrace& CDebugTrace::operator << ( double afdoubleVal )
{
    char * lpWritePtr = mszPrintBuff + mlDataLen;
    
    mlDataLen += sprintf( lpWritePtr,"%f",afdoubleVal );
    
    ASSERT( mlDataLen <= DEF_TRACE_BUFF_LEN );
    return *this;
}


// $_FUNCTION_BEGIN ******************************
// ��������: CDebugTrace& operator << ( __int64 aiInt64Val )
// ��������: __int64 aiInt64Val��Ҫ��ӡ�� __int64  ������
// �� �� ֵ: 
// ����˵��: ��ӡ64λ����
// $_FUNCTION_END ********************************
CDebugTrace& CDebugTrace::operator << ( __int64 aiInt64Val )
{
    char *lpWritePtr = mszPrintBuff + mlDataLen;
    
    mlDataLen += sprintf( lpWritePtr,"%I64d",aiInt64Val );
    
    ASSERT( mlDataLen <= DEF_TRACE_BUFF_LEN );
    return *this;
}


// $_FUNCTION_BEGIN ******************************
// ��������: CDebugTrace& operator << ( const char *apStrVal )
// ��������: const char *apStrVal��Ҫ��ӡ��\0��β���ַ���
// �� �� ֵ: 
// ����˵��: ��ӡ��\0��β���ַ���ֵ
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
// ��������: void TraceFormat( const char * pFmt,... )
// ��������: const char * pFmt,...( �ɱ䳤�Ȳ���,��:"����:%s,����:%d","zht",26 )
// �� �� ֵ: void
// ����˵��: ����printf�����ĸ�ʽ��ӡһ����־
// $_FUNCTION_END ********************************
void CDebugTrace::TraceFormat( const char * pFmt,... )
{
    va_list argptr;
    char strPrintBuff[512];
    
    //�ѿɱ�������л���strPrintBuff��
    va_start( argptr,pFmt );
    vsprintf( strPrintBuff, pFmt, argptr );
    va_end( argptr );
    
    //��strPrintBuff׷�ӵ�mszPrintBuff��
    char * lpWritePtr = mszPrintBuff + mlDataLen;
    mlDataLen += sprintf( lpWritePtr,"%s",strPrintBuff );
    
    //����EndTrace������ӡ
    EndTrace( *this );
}

////////////////////////////////////////////////
//�����Ǿ�̬����

// $_FUNCTION_BEGIN ******************************
// ��������: void CDebugTrace::SetTraceLevel( int aiTraceLevel )
// ��������: int aiTraceLevel:��־����
// �� �� ֵ: void
// ����˵��: ����TRACE�ȼ�( 0�����,1���,��������,С�ڸõȼ�����־����ӡ )
// $_FUNCTION_END ********************************
void CDebugTrace::SetTraceLevel( int aiTraceLevel )
{
    CDebugTrace::mnLogLevel = aiTraceLevel;
}



// $_FUNCTION_BEGIN ******************************
// ��������: void CDebugTrace::SetLogFileName( char *aszLogFile )
// ��������: char *aszLogFile:��־�ļ���
// �� �� ֵ: void
// ����˵��: ���������־�ļ���
// $_FUNCTION_END ********************************
void CDebugTrace::SetLogFileName( char *aszLogFile )
{
    if ( aszLogFile != NULL )
    {
        strcpy( CDebugTrace::mszLogFileName,aszLogFile );
    }
}

// $_FUNCTION_BEGIN ******************************
// ��������: void CDebugTrace::SetTraceOptions( unsigned options /** New level for trace */ )
// ��������: unsigned options:��ӡѡ�� ��ѡ��������
// �� �� ֵ: void
// ����˵��: ����TRACEѡ��
// $_FUNCTION_END ********************************
void CDebugTrace::SetTraceOptions( unsigned options /** New level for trace */ )
{
    CDebugTrace::muTraceOptions = options;
}

//
// $_FUNCTION_BEGIN ******************************
// ��������: unsigned CDebugTrace::GetTraceOptions( void )
// ��������: 
// �� �� ֵ: unsigned ��ӡѡ��
// ����˵��: ȡ��TRACEѡ��
// $_FUNCTION_END ********************************
unsigned CDebugTrace::GetTraceOptions( void )
{
    return CDebugTrace::muTraceOptions;
}

// $_FUNCTION_BEGIN ******************************
// ��������: bool CDebugTrace::CanTrace( int aiLogLevel )
// ��������: int aiLogLevel:��־����
// �� �� ֵ: bool
// ����˵��: �жϸ��������Ƿ���Դ�ӡ
// $_FUNCTION_END ********************************
bool CDebugTrace::CanTrace( int aiLogLevel )
{
    return ( aiLogLevel <= CDebugTrace::mnLogLevel );
}

//*****************************************************************************
//	����ԭ�ͣ�	BeginTrace( int aiLogLevel,char *apSrcFile,int aiSrcLine )
//  ����˵��:   ��ʼ��ӡһ����־
//  ������      int aiLogLevel( ��־�ļ��� ),char *apSrcFile( Դ�ļ��� ),
//				int aiSrcLine( Դ���� )
//  ����ֵ��    �������������
//  �÷���		BeginTrace( 3,__FILE__,__LINE__ )
//*****************************************************************************
CDebugTrace& CDebugTrace::BeginTrace( int aiLogLevel,char *apSrcFile,int aiSrcLine )
{
    CDebugTrace *lpDebugTrace = NULL;
    //lpDebugTrace = new CDebugTrace( );
    lpDebugTrace = &goDebugTrace;
	lpDebugTrace->moCriticalSection.Wait();

    ASSERT( lpDebugTrace != NULL );
    lpDebugTrace->mlDataLen = 0;	 //�Ѵ�ӡ�����ݳ�����0
    
    //���Ҫ�����ʱ��,������־�������־������ʱ��( ��:��:���� )
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
    //���Ҫ�������־����,������־�������־����
    if ( CDebugTrace::muTraceOptions & LogLevel )
    {
        *lpDebugTrace << aiLogLevel << ' ';
    }
    
    //���Ҫ�����Դ�ļ������к�,������־�����Դ�ļ������к�
    if ( CDebugTrace::muTraceOptions & FileAndLine ) 
    {
        *lpDebugTrace << apSrcFile << "( " << aiSrcLine << " ) ";
    }
    
    //���ض�������
    return *lpDebugTrace;
}


//*****************************************************************************
//	����ԭ�ͣ�	EndTrace( CDebugTrace &aoDebugTrace )
//  ����˵��:   ������ӡһ����־
//  ������      CDebugTrace &aoDebugTrace( CDebugTrace �������� )
//  ����ֵ��    
//  �÷���		
//*****************************************************************************
void CDebugTrace::EndTrace( CDebugTrace &aoDebugTrace )		//������ӡ
{
#ifdef WIN32
    //��������Դ�����
    OutputDebugStringA( aoDebugTrace.mszPrintBuff ); 
#endif	
    //��Ҫ�����������̨,�����־��Ϣ�ڿ���̨Ҳ��ӡһ��
    if ( CDebugTrace::muTraceOptions & PrintToConsole ) 
        printf( "%s",aoDebugTrace.mszPrintBuff );
    
    //��Ҫ��д�ļ�����������־�ļ���,�����־��Ϣд���ļ���
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
// ��������: void CDebugTrace::AssertFail( char * strCond,char *strFile, unsigned uLine )
// ��������: char * strCond: �������ʽ
//           char *strFile:Դ�ļ���
//           unsigned uLine���к�
// �� �� ֵ: void
// ����˵��: ����ASSERT������Ϣ
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