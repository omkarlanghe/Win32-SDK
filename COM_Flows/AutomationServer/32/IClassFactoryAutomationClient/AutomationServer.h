#pragma once

class IMyMath : public IDispatch
{
public:
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int *) = 0;
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0;
};
// {CDE76EAA-902E-45CF-8CC4-2FE38428A3DC}
const CLSID CLSID_MyMath = { 0xcde76eaa, 0x902e, 0x45cf, 0x8c, 0xc4, 0x2f, 0xe3, 0x84, 0x28, 0xa3, 0xdc };
// {BA9CB321-6BF9-450E-8265-B89E227DB454}
const IID IID_IMyMath = { 0xba9cb321, 0x6bf9, 0x450e, 0x82, 0x65, 0xb8, 0x9e, 0x22, 0x7d, 0xb4, 0x54 };

