// CPUData.cpp : 实现文件
//

#include "stdafx.h"
#include "chipData.h"

// CCPUData
CCPUData::CCPUData()
{

}

CCPUData::~CCPUData()
{
}

BOOL CCPUData::LoadBSDFile( CString strFileName )
{
	return m_bsd.LoadFromFile(strFileName);
}




CBsd::CBsd()
{

}

CBsd::~CBsd()
{

}

BOOL CBsd::LoadFromFile( CString strFileName )
{
	CString str;
	CStdioFile f;
	if(f.Open(strFileName,CStdioFile::modeRead))
	{
		while(f.ReadString(str)){
			str.Trim();
			if(str==""||(str[0]==_T('-') && str[1]==_T('-'))) continue;
			ParseLineSimple(str);
		}
		f.Close();
	}

	for(int i=0;i<m_devinfo.m_nBSRLength;i++)
	{
		if(m_devinfo.pBCell[i].sProtName!="*")
		{
			TRACE("[%d] %s",i,m_devinfo.pBCell[i].sProtName);
		}
	}
	return FALSE;
}


void CBsd::ConvertToTokens(CString str,CStringArray& slist)
{
	char s;
	CString token;
	slist.RemoveAll();
	while(GetToken(str,token,s))
	{
		if(token!="") slist.Add(token);
		if(s!=' ')
		{
			CString t;
			t.Format("%c",s);
			slist.Add(t);
		}
		str.Trim(s);
		str.Trim();
	};
}

void CBsd::_ParseBoundaryLength(CString str)
{
	CStringArray slist;
	ConvertToTokens(str,slist);
	int n=slist.GetCount();
	for(int i=0;i<n;i++)
	{
		if(slist.GetAt(i)=="is")
		{
			m_devinfo.CreateBCell(_ttoi(slist.GetAt(i+1)));
			break;
		}
	}
}

void CBsd::_ParseInstructionLength(CString str)
{
	CStringArray slist;
	ConvertToTokens(str,slist);
	int n=slist.GetCount();
	for(int i=0;i<n;i++)
	{
		if(slist.GetAt(i)=="is")
		{
			// m_devinfo.CreateBCell(_ttoi(slist.GetAt(i+1)));
			m_devinfo.m_nInstructionLength = _ttoi(slist.GetAt(i+1));
			break;
		}
	}

}

void CBsd::_ParseDeviceName(CString str)
{
	CStringArray slist;
	ConvertToTokens(str,slist);
	int n=slist.GetCount();
	m_devinfo.m_strDeviceName =slist.GetAt(1);
	TRACE("DeviceName:%s",m_devinfo.m_strDeviceName);
}

void CBsd::_ParseInstruction(CString str)
{
	CStringArray slist;
	ConvertToTokens(str,slist);
	int n=slist.GetCount();
	/*for(int i=0;i<n;i++)
	{
		TRACE("[%d] %s",i,slist.GetAt(i));
	}*/
	CString ins = slist.GetAt(1);
	CString code = slist.GetAt(3);
	JTAG_INSTRUCTION index=JI_UNDEFINE;
	TRACE(ins + code);
	if(ins=="BYPASS")
		index = JI_BYPASS;
	else if(ins=="EXTEST")
		index = JI_EXTEST;
	else if(ins=="SAMPLE")
		index = JI_SAMPLE;
	else if(ins=="INTEST")
		index = JI_INTEST;
	else if(ins=="PRELOAD")
		index = JI_PRELOAD;
	else if(ins=="HIGHZ")
		index = JI_HIGHZ;
	else if(ins=="IDCODE")
		index = JI_IDCODE;
	else
	{
		// throw CBSDException("Unknown Instruction: " + ins);
		TRACE("Unknown Instruction: " + ins);
	}
	m_devinfo.jtag_ins[index].nInstruct=index;
	m_devinfo.jtag_ins[index].sCode = code;
	m_devinfo.jtag_ins[index].sName = ins;

	if(slist.GetAt(n-1)!="&")
	{
		m_scanstate = s_idle;
	}
}

void CBsd::_ParseBoundaryRegister(CString str)
{
	CStringArray slist;
	ConvertToTokens(str,slist);
	try{
		if(!m_devinfo.ParseRegister(slist))
		{	
			// 边界寄存器定义完毕，恢复到idle状态
			m_scanstate=s_idle;
		}
	}
	catch(CBSDException e)
	{
		TRACE(e.GetMsg());
	}
}

// 处理一行语句
void CBsd::ParseLineSimple( CString str )
{
	switch(m_scanstate)
	{
	case s_idle:
		if(str.Find("attribute")>=0)
		{
			TRACE("attribute: %s",str);
			if(str.Find("BOUNDARY_LENGTH")>=0) 
			{
				_ParseBoundaryLength(str);
			}
			else if(str.Find("BOUNDARY_REGISTER")>=0)
			{
				// 开始boundary_register的扫描
				// _ParseBoundaryRegister(str);
				m_scanstate=s_bregister;
			}
			else if(str.Find("INSTRUCTION_LENGTH")>=0)
			{
				_ParseInstructionLength(str);
			}
			else if(str.Find("INSTRUCTION_OPCODE")>=0)
			{
				m_scanstate = s_binstruction;
			}
		}
		else if(str.Find("entity")>=0)
		{
			TRACE("entity: %s",str);
			_ParseDeviceName(str);
		}
	break;
	case s_bregister:
		// TRACE("BoundaryRegister: %s",str);
		_ParseBoundaryRegister(str);
		break;
	case s_binstruction:
		_ParseInstruction(str);
		break;
	default:
		break;
	}
}

BOOL CBsd::Analyse(CString &token,char &s)
{
	switch(m_scanstate)
	{
	case s_idle:
		break;
	default:
		break;
	}
	return TRUE;
}

// 处理一行语句
void CBsd::ParseLine( CString& str )
{
/*	CStringArray slist;
	char s;
	CString token;
	while(GetToken(str,token,s))
	{
		if(token!="") slist.Add(token);
		if(s!=' ')
		{
			CString t;
			t.Format("%c",s);
			slist.Add(t);
		}
		str.Trim(s);
		str.Trim();
	};
	CString cstr;
	for(int i=0;i<slist.GetCount();i++)
	{
		cstr += slist.GetAt(i) +" ";
	}
	TRACE(cstr);*/

	char s;
	CString token;
	while(GetToken(str,token,s))
	{
		str.Trim(s);
		str.Trim();
	};
}

// 获取token
BOOL CBsd::GetToken( CString&str,CString &token,char&next_separtor)
{
	token="";
	char separtor[]=" ~`!@#$%^&*()-+=:;,<>?{}|[]\"'/";
	str.Trim();
	if(str=="") return FALSE;
	
	int len=str.GetLength();
	for(int i=0;i<len;i++)
	{
		for(int j=0;j<sizeof(separtor);j++)
		{
			if(str[i]==separtor[j])
			{
				// 找到分隔符
				next_separtor=separtor[j];
				str = &(str.GetBuffer()[i]);
				return TRUE;
			}
		}
		token += str[i];
	}
	str="";
	return TRUE;
}

CBCell::CBCell()
{
	sProtName="";				// name
	int num=-1;					// bc num
	int bc=-1;					// cell
	int fun=-1;					// function
	int ccell=-1;				// ccell
	char safe=0;				// safe
	char disval=0;				// disval
	char rslt=0;				// rslt
}

CBCell::~CBCell()
{

}


CBSDInfo::CBSDInfo()
{
	pBCell = NULL;
	m_nInstructionLength = 0;
	m_nBSRLength = 0;
}

CBSDInfo::~CBSDInfo()
{
	RemoveAll();
}

void CBSDInfo::RemoveAll()
{
	if(pBCell)
	{
		delete []pBCell;
		pBCell = NULL;
	}
}

void CBSDInfo::CreateBCell( int num )
{
	m_nBSRLength =num;
	RemoveAll();
	pBCell = new CBCell[num];
}

BOOL CBSDInfo::ParseRegisterFunction(int index,CString str)
{
	if(str=="control")
		pBCell[index].fun = FUN_CONTROL;
	else if(str=="bidir")
		pBCell[index].fun = FUN_BIDIR;
	else if(str=="internal")
		pBCell[index].fun = FUN_INTERNAL;
	else if(str=="input")
		pBCell[index].fun = FUN_INPUT;
	else if(str=="output3")
		pBCell[index].fun = FUN_OUTPUT3;
	else 
	{
		throw CBSDException("Unknown Function:"+str);
		return FALSE;
	}
	return TRUE;
}

BOOL CBSDInfo::ParseRegisterSafe(int index,CString str)
{
	if(str=="0")
		pBCell[index].safe = LEVEL_0;
	else if(str=="1")
		pBCell[index].safe = LEVEL_1;
	else if(str=="X")
		pBCell[index].safe = LEVEL_X;
	else if(str=="Z")
		pBCell[index].safe = LEVEL_Z;
	else
	{
		throw CBSDException("Unknown Safe Level:"+str);
		return FALSE;
	}
	return TRUE;
}

BOOL CBSDInfo::ParseRegisterRSLT(int index,CString str)
{
	if(str=="0")
		pBCell[index].rslt = LEVEL_0;
	else if(str=="1")
		pBCell[index].rslt = LEVEL_1;
	else if(str=="X")
		pBCell[index].rslt = LEVEL_X;
	else if(str=="Z")
		pBCell[index].rslt = LEVEL_Z;
	else
	{
		throw CBSDException("Unknown rslt Level:"+str);
		return FALSE;
	}
	return TRUE;
}


BOOL CBSDInfo::ParseRegister(CStringArray& slist)
{
	enum {
		START=0,
		NUM,
		LEFT_BRACKET,
		CELL,
		PORT,
		FUNCTION,
		SAFE,
		CCELL,
		DISVAL,
		RSLT,
		RIGHT_BRACKET,
		END,
	} s=START;
	int index=0;
	int n=slist.GetCount();
	if(n>0)
	{
		for(int i=0;i<n;i++)
		{
			// TRACE("%d - %s",i,slist.GetAt(i));
			CString c=slist.GetAt(i);
			switch(s)
			{
			case START:	// 开始的引号
				if(c="\"") s=NUM;
				break;
			case NUM:	// 寄存器索引下标
				index=_ttoi(c);
				if(index<m_nBSRLength)
					pBCell[index].num = index;
				else
					throw CBSDException("越界");
				s=LEFT_BRACKET;
				break;
			case LEFT_BRACKET:	// 左括号
				if(c="(") s=CELL;
				break;
			case CELL:
				if(c.Left(3)=="BC_")
				{	
					pBCell[index].bc = _ttoi(c.Mid(3));
					if(slist.GetAt(i+1)==",")
					{
						s = PORT;
						i++;
					}
				}
				else
					throw CBSDException("定义 Boundary Cell 语法错误,或无法识别" + c );
				break;
			case PORT:
				if(c==",")
					s= FUNCTION;
				else
				pBCell[index].sProtName+=c;
				break;
			case FUNCTION:
				ParseRegisterFunction(index,c);
				if(slist.GetAt(i+1)==",")
				{
					s = SAFE;
					i++;
				}
				break;
			case SAFE:
				ParseRegisterSafe(index,c);
				if(slist.GetAt(i+1)==",")
				{
					s = CCELL;
					i++;
				} 
				else if(slist.GetAt(i+1)==")")
				{
					s = END;
					i++;
				}
				break;
			case CCELL:
				pBCell[index].ccell = _ttoi(c);
				if(slist.GetAt(i+1)==",")
				{
					s = DISVAL;
					i++;
				}
				break;
			case DISVAL:
				pBCell[index].disval = _ttoi(c);
				if(slist.GetAt(i+1)==",")
				{
					s = RSLT;
					i++;
				}
				break;
			case RSLT:
				ParseRegisterRSLT(index,c);
				if(slist.GetAt(i+1)==")")
				{
					s = END;
					i++;
				}
				break;
			case END:
				break;
			default:
				break;
			}
		}
		if(slist.GetAt(n-1)=="&")
			return TRUE;
	}
	return FALSE;
}

CJtagInstruct::CJtagInstruct()
{
	nInstruct=JI_UNDEFINE;
}

CJtagInstruct::~CJtagInstruct()
{

}

// JTAG测试数据及结果
CScanData::CScanData()
{
	len = 0;
	changetime =NULL;
}

CScanData::CScanData( const CScanData & c )
{
	len = 0;
	changetime =NULL;
	Create(c.len);
	sData = c.sData;
	memcpy(changetime,c.changetime,len*sizeof(int));
}

CScanData::~CScanData()
{
	RemoveAll();
}

void CScanData::Create( int len )
{
	RemoveAll();
	sData="";
	this->len = len;
	changetime = new int[len+10];
	memset(changetime,0,(len+10)*sizeof(int));

}

void CScanData::RemoveAll()
{
	sData = "";
	if(changetime)
	{
		delete [] changetime;
		changetime = NULL;
	}
}
