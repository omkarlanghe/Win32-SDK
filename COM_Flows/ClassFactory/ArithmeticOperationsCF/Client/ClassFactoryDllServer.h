#pragma once
class IArithmetic : public IUnknown
{
public:
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0;
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0;
	virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*) = 0;
	virtual HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*) = 0;
};
//CLSID of Arithmetic Component {0E51942E-63AF-4F59-AC59-60FF2248EA8B}
const CLSID CLSID_ArithmeticOperation = { 0xe51942e, 0x63af, 0x4f59, 0xac, 0x59, 0x60, 0xff, 0x22, 0x48, 0xea, 0x8b };

//IID of IArithmetic Interface {DCA36A67-B6C4-43CD-BDDC-58622BA719FB}
const IID IID_IArithmetic = { 0xdca36a67, 0xb6c4, 0x43cd, 0xbd, 0xdc, 0x58, 0x62, 0x2b, 0xa7, 0x19, 0xfb };
