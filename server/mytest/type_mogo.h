#ifndef _type_mogo_h
#define _type_mogo_h

#include"my_stl.h"
typedef char int8_t; //��mingw��������Ҫע�͵�  ò�Ʊ�mingw�ù�
typedef unsigned char uint8_t;
typedef short int int16_t;
typedef unsigned short int uint16_t;
typedef int int32_t;
typedef unsigned int uint32_t;
typedef long long int64_t;
typedef unsigned long long uint64_t;
typedef float float32_t;
typedef double float64_t;

typedef int32_t int32;
typedef uint32_t uint32;
typedef uint16_t pluto_msgid_t;


enum VTYPE{

	V_TYPE_ERR = -1,

	V_LUATABLE = 1,
	V_STR      = 2,
	V_INT8     =3,
	V_UINT8 = 4,
	V_INT16 = 5,
	V_UINT16 = 6,
	V_INT32 = 7,
	V_UINT32 = 8,
	V_INT64 = 9,
	V_UINT64 = 10,
	V_FLOAT32 = 11,
	V_FLOAT64 = 12,

	V_ENTITYMB= 13,
	V_ENTITY  = 14,
	V_CLSMETHOD = 15,
	V_BLOB = 16,

	//V_LIST = 4,
	//V_MAP = 5,

	V_REDIS_HASH = 22,      //redis hash��������
	V_LUA_OBJECT = 23,      //����lua����,����entity_index��newindex,�����ط���֧��
	V_ENTITY_POINTER = 24,      //������client rpc��
	V_MAX_VTYPE = 25,

};

struct VOBJECT;
union VVALUE
{
	int i;
	float f;
	string* s;
	list<VOBJECT*>* l;
	map<string, VOBJECT*>* m;
	//ENTITY_MEMBER_METHOD em;
	void* p;

	uint8_t u8;
	uint16_t u16;
	uint32_t u32;
	uint64_t u64;
	int8_t i8;
	int16_t i16;
	int32_t i32;
	int64_t i64;
	float32_t f32;
	float64_t f64;
	//my delete CEntityMailbox emb;
	pluto_msgid_t msgid;
};
#undef _PLUTO_POOL
struct VOBJECT
{
	VTYPE vt;
	VVALUE vv;

#ifdef _PLUTO_POOL
	void * operator new(size_t size);
	void operator delete(void* p, size_t size);
#endif

	void Clear();
	~VOBJECT();

#ifdef _PLUTO_POOL
private:
	static MemoryPool *memPool;
	static void expandMemoryPool();
	static MyLock m_lock;
#endif
};




#endif