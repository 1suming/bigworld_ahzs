#ifndef PLUTO_H
#define PLUTO_H

#include <list>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <string>
#include "bitcryto.h"
#include"type_mogo.h"
#include"my_stl.h"
using namespace std;



#define atoll _atoi64;
#define MSGLEN_HEAD           4                          //��Ϣ��ͷ����
#define MSGLEN_RESERVED       2                          //����2λ,�������汾������
#define MSGLEN_MSGID          2                          //��Ϣid����
#define MSGLEN_TEXT_POS       (MSGLEN_HEAD + MSGLEN_RESERVED + MSGLEN_MSGID)   //���Ŀ�ʼ��λ��
#define MSGLEN_MAX            65000                       //��Ϣ����󳤶�

#define PLUTO_CLIENT_MSGLEN_MAX  65000  //�ͻ��˰�����󳤶�
#define PLUTO_MSGLEN_HEAD        MSGLEN_HEAD  //��������ģ������
#define PLUTO_FILED_BEGIN_POS (MSGLEN_HEAD + MSGLEN_RESERVED + MSGLEN_MSGID)   //�ֶο�ʼ��λ��,��ǰ��λ�ö���Э���Լ���Ҫ��
#define MAX_CLIENT_SERVER_MSGID 50

typedef uint32_t TENTITYID;
typedef uint32_t TDBID;
typedef uint16_t TENTITYTYPE;
typedef uint32_t TSPACEID;
typedef unsigned short T_INTEREST_SIZE;
typedef int32_t int32;
typedef uint32_t uint32;
typedef uint16_t pluto_msgid_t;

struct VOBJECT;

enum
{
	SERVER_NONE = 0,
	SERVER_LOGINAPP = 1,
	SERVER_BASEAPPMGR = 2,
	SERVER_DBMGR = 3,
	SERVER_TIMERD = 4,
	SERVER_CLIENT = 5,

	//SERVER_PROXY         = 1,
	//SERVER_CELLAPPMGR    = 4,

	SERVER_BASEAPP = 6,
	SERVER_CELLAPP = 7,

	SERVER_MULTI_MIN_ID = 11,      //��������������̵ķ�������Сid�����￪ʼ

	SERVER_MAILBOX_RESERVE_SIZE = 30,   //Ԥ��30������������
};

enum
{
	MSGTYPE_LOGINAPP = SERVER_LOGINAPP << 12,
	MSGTYPE_BASEAPPMGR = SERVER_BASEAPPMGR << 12,
	//MSGTYPE_CELLAPPMGR   = SERVER_CELLAPPMGR << 12,  
	MSGTYPE_BASEAPP = SERVER_BASEAPP << 12,
	MSGTYPE_CELLAPP = SERVER_CELLAPP << 12,
	MSGTYPE_DBMGR = SERVER_DBMGR << 12,
};

 

union FLOAT32_CONVERT
{
	float32_t f;
	unsigned char s[sizeof(float32_t)];
};

union FLOAT64_CONVERT
{
	float64_t f;
	unsigned char s[sizeof(float64_t)];
};

union UINT64_CONVERT
{
	uint64_t i;
	unsigned char s[sizeof(uint64_t)];
};

 
extern bool IsValidMsgid(uint16_t msgid);
extern void bool_to_sz(bool n, char *s);
extern void uint8_to_sz(uint8_t n, char* s);
extern void uint16_to_sz(uint16_t n, char* s);
extern void uint32_to_sz(uint32_t n, char* s);
//extern void uint64_to_sz(uint64_t n, char* s);
extern bool sz_to_bool(unsigned char *s);
extern uint8_t sz_to_uint8(unsigned char* s);
extern uint16_t sz_to_uint16(unsigned char* s);
extern uint32_t sz_to_uint32(unsigned char* s);
//extern uint64_t sz_to_uint64(unsigned char* s);
//��ֵ��0x12��charת��Ϊ�ַ���"12"
extern void char_to_sz(unsigned char c, char* s);
//������"12"���ַ���ת��ΪֵΪ0x12��char
extern unsigned char sz_to_char(char* s);
extern void PrintHex16(const char* s, size_t n);
extern void PrintHex(const char* s, size_t n);

struct charArrayDummy
{
	charArrayDummy();
	~charArrayDummy();

	uint16_t m_l;
	char* m_s;
};

template<typename T>
T sz_to_msgid(unsigned char* s);

template<>
inline uint16_t sz_to_msgid<uint16_t>(unsigned char* s)
{
	return sz_to_uint16(s);
}

//��pluto�н���������entity prop���ݼ���
struct SEntityPropFromPluto
{
	TENTITYTYPE etype;
	map<string, VOBJECT*> data;

	~SEntityPropFromPluto();
};

enum { DEFAULT_PLUTO_BUFF_SIZE = 1024, };       //ȱʡ��buff_size

class CPluto
{
public:
	CPluto(uint32_t buff_size = DEFAULT_PLUTO_BUFF_SIZE);  //for encode
	CPluto(const char* s, uint32_t n);  //for decode
	~CPluto();

public:
	//����
	CPluto& Encode(pluto_msgid_t msgid);
	CPluto& operator<< (bool n);
	CPluto& operator<< (uint8_t n);
	CPluto& operator<< (uint16_t n);
	CPluto& operator<< (uint32_t n);
	CPluto& operator<< (uint64_t n);
	CPluto& operator<< (int8_t n);
	CPluto& operator<< (int16_t n);
	CPluto& operator<< (int32_t n);
	CPluto& operator<< (int64_t n);
	CPluto& operator<< (float32_t f);
	CPluto& operator<< (float64_t f);
	CPluto& operator<< (const char* s);
	CPluto& operator<< (const string& s);
	CPluto& operator<< (const charArrayDummy& r);
	typedef CPluto& (*pluto_op) (CPluto&);
	CPluto& operator<< (pluto_op op);
	friend CPluto& EndPluto(CPluto& p);
	//CPluto& operator<< (const CEntityMailbox& m);
	//CPluto& operator<< (const CEntityParent& e);
	CPluto& FillPluto(const VOBJECT& v);
	CPluto& FillPlutoFromStr(VTYPE vt, const char* s, unsigned long ll);
	//   CPluto& FillPlutoFromLua(VTYPE vt, lua_State* L, int idx);

private:
	//encodeʱ�Զ�����buff��С
	void Resize(uint32_t n);

public:
	//�������������operator<<,������ʵ����ʽ���ʽ
	template<typename T>
	CPluto& FillField(const T& value);
	//������buff�ĳ���,ֻ����buff����
	CPluto& FillBuff(const char* s, uint32_t n);
	//������EndPluto
	CPluto& endPluto();

public:
	//�滻��ĳ��λ�ÿ�ʼ��һ���ֶε�ֵ
	template<typename T>
	void ReplaceField(uint32_t nIdx, const T& value);

public:
	//���
	//��ͷ���¼�İ�����
	uint32_t GetMsgLen();
	//ȥ����ͷ��ʣ�³���
	uint16_t GetMsgLeftLen();
	//��Ϣid
	pluto_msgid_t GetMsgId();
	CPluto& Decode();
	CPluto& operator>> (bool& n);
	CPluto& operator>> (uint8_t& n);
	CPluto& operator>> (uint16_t& n);
	CPluto& operator>> (uint32_t& n);
	CPluto& operator>> (uint64_t& n);
	CPluto& operator>> (int8_t& n);
	CPluto& operator>> (int16_t& n);
	CPluto& operator>> (int32_t& n);
	CPluto& operator>> (int64_t& n);
	CPluto& operator>> (float32_t& f);
	CPluto& operator>> (float64_t& f);
	CPluto& operator>> (charArrayDummy& d);
	CPluto& operator>> (string& s);
	//CPluto& operator>> (CEntityMailbox& m);
	void FillVObject(VTYPE vt, VOBJECT& v);
	//bool UnpickleEntity(VOBJECT& v);


public:
	inline const char* GetBuff() const
	{
		return m_szBuff;
	}

	inline char* GetRecvBuff()
	{
		return m_szBuff;
	}

	inline void SetLen(uint32_t n)
	{
		m_unLen = n;
	}
	inline void SetMaxLen(uint32_t n)
	{
		m_unMaxLen = n;
	}

	inline void EndRecv(uint32_t n)
	{
		m_unLen = n;
		m_unMaxLen = n;
	}

	inline uint32_t GetBuffSize() const
	{
		return m_unBuffSize;
	}

	inline uint32_t GetLen() const
	{
		return m_unLen;
	}

	inline uint32_t GetMaxLen() const
	{
		return m_unMaxLen;
	}

	// inline CMailBox* GetMailbox()
	// {
	//     return m_mb;
	// }

	// inline void SetMailbox(CMailBox* mb)
	// {
	//     m_mb = mb;
	// }

	inline bool IsEnd() const
	{
		return m_unLen >= m_unMaxLen;
	}

	inline uint32_t GetDecodeErrIdx() const
	{
		return m_nDecodeErrIdx;
	}

private:
	char* m_szBuff;
	uint32_t m_unBuffSize;
	uint32_t m_unLen;
	uint32_t m_unMaxLen;
	uint32_t m_nDecodeErrIdx;
	// CMailBox* m_mb;

};

template<typename T>
CPluto& CPluto::FillField(const T& value)
{
	(*this) << value;
	return *this;
}

template<typename T>
void CPluto::ReplaceField(uint32_t nIdx, const T& value)
{
	uint32_t old_len = m_unLen;
	m_unLen = nIdx;
	(*this) << value;
	m_unLen = old_len;
}

CPluto& EndPluto(CPluto& p);

extern void PrintHexPluto(CPluto& c);

#endif