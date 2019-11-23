#pragma once
class IMyMath : public IDispatch
{
public:
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int *) = 0;
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0;
};
// {E57C7333-9DC1-444D-BA05-86C7601B6C26}
const CLSID CLSID_MyMath = { 0xe57c7333, 0x9dc1, 0x444d, 0xba, 0x5, 0x86, 0xc7, 0x60, 0x1b, 0x6c, 0x26 };
// {228109E8-A471-4439-BDF6-82D9C21D815D}
const IID IID_IMyMath = { 0x228109e8, 0xa471, 0x4439, 0xbd, 0xf6, 0x82, 0xd9, 0xc2, 0x1d, 0x81, 0x5d };
