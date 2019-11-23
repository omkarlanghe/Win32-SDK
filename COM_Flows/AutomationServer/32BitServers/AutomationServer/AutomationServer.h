class IMyMath : public IDispatch
{
public:
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0;
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0;
};

// {8FD1609B-35AF-4E51-9D6B-B8F17998AF3A}
const CLSID CLSID_MyMath = { 0x8fd1609b, 0x35af, 0x4e51, 0x9d, 0x6b, 0xb8, 0xf1, 0x79, 0x98, 0xaf, 0x3a };

// {27583FD0-2EED-4A94-BAF5-26E288B9D729}
const IID IID_IMyMath = { 0x27583fd0, 0x2eed, 0x4a94, 0xba, 0xf5, 0x26, 0xe2, 0x88, 0xb9, 0xd7, 0x29 };
