class IMultiplication :public IUnknown
{
public:
	virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*) = 0;
};
class IDivision :public IUnknown
{
public:
	virtual HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*) = 0;
};
// {47EED88D-F0C1-4DC5-9B85-F69EF2C12433}
const CLSID CLSID_MultiplicationDivision = { 0x47eed88d, 0xf0c1, 0x4dc5, 0x9b, 0x85, 0xf6, 0x9e, 0xf2, 0xc1, 0x24, 0x33 };
// {A895F4BC-CAE7-49AF-9818-C98E9BD9ACCE}
const IID IID_IMultiplication = { 0xa895f4bc, 0xcae7, 0x49af, 0x98, 0x18, 0xc9, 0x8e, 0x9b, 0xd9, 0xac, 0xce };
// {B730C728-0B9A-41E1-AA9C-E591EF8B2749}
const IID IID_IDivision = { 0xb730c728, 0xb9a, 0x41e1, 0xaa, 0x9c, 0xe5, 0x91, 0xef, 0x8b, 0x27, 0x49 };

