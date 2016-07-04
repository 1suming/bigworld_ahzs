// 模块描述：简单的移位加密算法
//----------------------------------------------------------------*/
#include <string>

#include "bitcryto.h"

using std::string;


CBitCryto::CBitCryto(const char* szKey) : m_strKey(szKey), m_nIdx(0)
{
}

CBitCryto::~CBitCryto()
{
}

unsigned char CBitCryto::Encode(unsigned char c)
{
	if (m_nIdx >= m_strKey.size())
	{
		m_nIdx = 0;
	}
	unsigned short k = (unsigned short)m_strKey[m_nIdx];
	++m_nIdx;

	unsigned char c2 = (unsigned char)((k + (unsigned short)c) & 0xff);

	return c2;
}

unsigned char CBitCryto::Decode(unsigned char c)
{
	if (m_nIdx >= m_strKey.size())
	{
		m_nIdx = 0;
	}
	short k = (short)m_strKey[m_nIdx];
	++m_nIdx;

	short c2 = (short)c - k;
	if (c2 < 0)
	{
		c2 += 256;
	}

	return (unsigned char)c2;
}