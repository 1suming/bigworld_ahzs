#include"pluto.h"
#include"my_stl.h"

#include<iostream>
using namespace std;

void pluto_test()
{
	CPluto c1; 
	c1.Encode(120); //uint16_t
	c1 << (uint8_t)121;
	c1 << (uint16_t)120;
	c1 << (uint32_t)120;
	c1 << (uint64_t)120;

	c1 << EndPluto;

	PrintHexPluto(c1);

	CPluto c2(c1.GetBuff(), c1.GetLen());
	c2.Decode();
	uint8_t u8;
	uint16_t u16;
	uint32_t u32;
	uint64_t u64;
	c2 >> u8 >> u16 >> u32 >> u64;
	cout << (int)u8 << endl; //这里的输出为char，要转成int
	cout << (int)u8 << "->" << u16 << "->" << u32 << "->" << u64 << endl;



}
int main()
{
	pluto_test();
}