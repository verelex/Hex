#define ALL_OK 0
#define INVALID_INPUT_BUFFER 1;
#define INVALID_OUTPUT_BUFFER 2;

BYTE test1[256]; // 256 bytes

char* test2 = "1E8ED883EC061E9AFFFF00000BC07403BA00008B\
DA8EC28C46FC8C5EF833C033F633FFB9FFFF0BDB\
740E26803E0000007406F2AE46AE75FA8BC74024\
FE468BFED1E6D1E6B90900E85D0152508BC6E856\
01A36400891666008956FA061F8BCF8BD833F65F\
0749E3168E5EFA893F8C470283C3048E5EFCACAA\
0AC075FAE2EA8E5EFA890F894F021F83ED028BE5\
1F5D4DCB00721F33C083ED028BE51F5D4DCB73F3\
50E824005832E483ED028BE51F5D4DCB7307E813\
00B8FFFF9983ED028BE51F5D4DCB32E4E80100CB\
A246000AE4751B3C22730C3C207204B005EB063C\
137602B013BB7400D798A33A00C38AC4EBF7008B\
4E0E8B46068B56081EC57E0A571E07FC"; // 40*12+32=512 symbols => 1 byte presents in string as 2 symbols

void CHex1Dlg::Test()
{
	int len = strlen(test2); // 512
	// преобразуем из строки в массив чисел
	str2byteArray(test2, test1, len);

	char out[520]; // буфер для строки в 2 раза больше т.к. один байт кодируется 2-мя символами
	memset(out,0,520);
	// преобразуем из масива чисел в строку
	byteArray2str(test1, out, 256);

	int sz = lstrlenA(out);
	int count = MultiByteToWideChar(CP_ACP,0,out,sz,0,0); // 512
	if ( count > 0 )
	{
		PWSTR wstr = new TCHAR[count+4];
		if(wstr)
		{
			memset(wstr,0,sizeof(wstr)*(count+4));
			count = MultiByteToWideChar(CP_ACP, 0, out, sz, wstr, count);
			::SetWindowText(GetDlgItem(IDC_EDIT1)->m_hWnd,wstr);
			//MessageBox(wstr);
		}
	}
}

//-------------------------------------------------------------------------------------

int CHex1Dlg::byteArray2str(BYTE* in, char* out, int ByteArrayLength)
{
	char temp[4];
	if(!in) return INVALID_INPUT_BUFFER;
	if(!out) return INVALID_OUTPUT_BUFFER;

	for(int i=0,j=0; i<ByteArrayLength; i++,j+=2)
	{
		memset(temp,0,4);
		sprintf_s(temp,4,"%.2X",in[i]);
		int len = ByteArrayLength*2-lstrlenA(out);
		memcpy(out+j,temp,2);
	}
	return ALL_OK;
}

//-------------------------------------------------------------------------------------

int CHex1Dlg::str2byteArray(char* in, BYTE* out, int StringLength)
{
	char temp[4];
	char* iiter = in;
	if(!in) return INVALID_INPUT_BUFFER;
	if(!out) return INVALID_OUTPUT_BUFFER;

	int len = StringLength/2; // 2 symbols = 1 byte
	for(int i=0; i<len; i++)
	{
		int b = 0;
		memset(temp,0,4);
		strncpy_s(temp,3,iiter,2);
		sscanf_s(temp,"%X",&b);
		out[i] = b;
		iiter += 2;
	}
	return ALL_OK;
}
