#pragma once

typedef enum __FUNCTION_TYPE{
	FUN_UNDEF=-1,
	FUN_CONTROL=0,
	FUN_BIDIR,
	FUN_INTERNAL,
	FUN_INPUT,
	FUN_OUTPUT3,
} FUNCTION_TYPE;

typedef enum __LEVEL{
	LEVEL_0,
	LEVEL_1,
	LEVEL_X,
	LEVEL_Z,
} LEVEL;

typedef enum __JTAG_INSTRUCTION{
	JI_UNDEFINE=0,
	JI_BYPASS,
	JI_SAMPLE,
	JI_EXTEST,
	JI_IDCODE,
	JI_PRELOAD,
	JI_INTEST,
	JI_HIGHZ,
	MAX_JTAG_INSTRUCTION,
} JTAG_INSTRUCTION;

class CBSDException
{
private:
	CString msg;
public:
	CBSDException(CString str){
		msg = str;
	}
	~CBSDException(){};
	CString GetMsg() {return msg;}

};

class CBCell
{
public:
	CString sProtName;		// name
	int num;				// bc num
	int bc;					// cell
	int fun;				// function
	int ccell;				// ccell
	char safe;				// safe
	char disval;			// disval
	char rslt;				// rslt
	CBCell();
	~CBCell();
};

class CJtagInstruct{
public:
	CString sName;
	CString sCode;
	int nInstruct;
	CJtagInstruct();
	~CJtagInstruct();
};

// boundary scan 扫描的数据
class CScanData{
public:
	int len;
	CString sData;
	int * changetime;
	CScanData();
	CScanData(const CScanData & c);
	~CScanData();
	void Create(int len);
	void RemoveAll();
};

class CBSDInfo
{
public:
	CBCell * pBCell;
	CJtagInstruct jtag_ins[MAX_JTAG_INSTRUCTION];
	CString m_strDeviceName;
	int m_nBSRLength;
	
	int m_nInstructionLength;
	CBSDInfo();
	~CBSDInfo();
	void CreateBCell(int num);
	BOOL ParseRegister(CStringArray& slist);
	BOOL ParseRegisterFunction(int index,CString str);
	void RemoveAll();
	BOOL ParseRegisterSafe(int index,CString str);
	BOOL ParseRegisterRSLT(int index,CString str);
};

// CCPUData
class CBsd
{
public:
	typedef enum{
		s_idle=0,
		s_entity,
		s_bregister,
		s_binstruction,
	} SCAN_STATE;
public:
	CBsd();
	virtual ~CBsd();
	BOOL GetToken( CString&str,CString &token,char&next_separtor);
	void ParseLine(CString& str);
	BOOL LoadFromFile(CString strFileName);
	BOOL Analyse(CString &token,char &s);


// 粗略分析
	void ParseLineSimple( CString str );
	void ConvertToTokens(CString str,CStringArray& slist);
	void _ParseBoundaryLength(CString str);
	void _ParseDeviceName(CString str);
	void _ParseBoundaryRegister(CString str);
	void _ParseInstructionLength(CString str);
	void _ParseInstruction(CString str);
public:
	SCAN_STATE m_scanstate;
	CBSDInfo m_devinfo;
};

class CCPUData
{
public:
	CCPUData();
	virtual ~CCPUData();
	BOOL LoadBSDFile(CString strFileName);

protected:
	CBsd m_bsd;
};


