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
// {9547B3F9-E868-4724-A05B-1403CF9D3C3F}
const CLSID CLSID_MultiplicationDivision = { 0x9547b3f9, 0xe868, 0x4724, 0xa0, 0x5b, 0x14, 0x3, 0xcf, 0x9d, 0x3c, 0x3f };
// {0955F70C-25B2-42DC-AFAD-522EFEC287C5}
const IID IID_IMultiplication = { 0x955f70c, 0x25b2, 0x42dc, 0xaf, 0xad, 0x52, 0x2e, 0xfe, 0xc2, 0x87, 0xc5 };
// {DB5BD993-05E0-4DE7-860A-888328964D82}
const IID IID_IDivision = { 0xdb5bd993, 0x5e0, 0x4de7, 0x86, 0xa, 0x88, 0x83, 0x28, 0x96, 0x4d, 0x82 };

