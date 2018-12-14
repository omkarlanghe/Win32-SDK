#pragma once
class IMyMath : public IDispatch
{
public:
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int *) = 0;
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0;
};
// {2970B7D4-781A-486A-A641-45E397C8F94E}
const CLSID CLSID_MyMath = { 0x2970b7d4, 0x781a, 0x486a, 0xa6, 0x41, 0x45, 0xe3, 0x97, 0xc8, 0xf9, 0x4e };
// {7B1350EC-DDC6-4BFA-A9D9-634857E2F54A}
const IID IID_IMyMath = { 0x7b1350ec, 0xddc6, 0x4bfa, 0xa9, 0xd9, 0x63, 0x48, 0x57, 0xe2, 0xf5, 0x4a };
