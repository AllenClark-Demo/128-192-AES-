#include <iostream>
#include <stdio.h>
#include <fstream>
#include <windows.h>
#include <string>
using namespace std;


void Init();
void encyptedecypte();
void fileencyptedecypte();
//S盒
const int sBox[16][16] = {
	// 0     1     2     3     4     5     6     7     8     9     a     b     c     d     e     f
	{0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76}, // 0
	{0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0}, // 1
	{0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15}, // 2
	{0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75}, // 3
	{0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84}, // 4
	{0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf}, // 5
	{0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8}, // 6
	{0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2}, // 7
	{0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73}, // 8
	{0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb}, // 9
	{0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79}, // a
	{0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08}, // b
	{0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a}, // c
	{0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e}, // d
	{0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf}, // e
	{0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16} };// f
 
//逆S盒
const int invSBox[16][16] = {
	// 0     1     2     3     4     5     6     7     8     9     a     b     c     d     e     f
	{0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb}, // 0
	{0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb}, // 1
	{0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e}, // 2
	{0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25}, // 3
	{0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92}, // 4
	{0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84}, // 5
	{0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06}, // 6
	{0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b}, // 7
	{0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73}, // 8
	{0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e}, // 9
	{0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b}, // a
	{0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4}, // b
	{0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f}, // c
	{0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef}, // d
	{0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61}, // e
	{0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d} };// f
 
//用于扩展密钥
const int RCON[13][4] =
{
{ 0x00,0x00,0x00,0x00 },
{ 0x01,0x00,0x00,0x00 },
{ 0x02,0x00,0x00,0x00 },
{ 0x04,0x00,0x00,0x00 },
{ 0x08,0x00,0x00,0x00 },
{ 0x10,0x00,0x00,0x00 },
{ 0x20,0x00,0x00,0x00 },
{ 0x40,0x00,0x00,0x00 },
{ 0x80,0x00,0x00,0x00 },
{ 0x1b,0x00,0x00,0x00 },
{ 0x36,0x00,0x00,0x00 },
{ 0x6C,0x00,0x00,0x00 },
{ 0xD8,0x00,0x00,0x00 }
 };
 
//用于列混淆左乘
const int mixColumnMatrix[4][4] = 
{
	{0x02,0x03,0x01,0x01},
	{0x01,0x02,0x03,0x01},
	{0x01,0x01,0x02,0x03},
	{0x03,0x01,0x01,0x02}
};
 
//用于逆向列混淆左乘
const int invMixColumnMatrix[4][4] =
{
	{0x0E,0x0B,0x0D,0x09},
	{0x09,0x0E,0x0B,0x0D},
	{0x0D,0x09,0x0E,0x0B},
	{0x0B,0x0D,0x09,0x0E}
};
  
 
char** changeToMatrix(const string& text,int length)	//将字符串变成矩阵 
{
	char **in = new char* [4];
	for (int i = 0;i < 4;i++)
		in[i] = new char[length];
 
	for (int i = 0;i < 4;i++)
	{
		for (int j = 0;j < length;j++)
		{
			in[i][j] = text[i + j * 4];
		}
	}
 
	return in;
}
 
void rolWord(char word[4])	//循环左移
{
	char temp = word[0];
	for (int i = 0;i < 3;i++)
	{
		word[i] = word[i + 1];
	}
	word[3] = temp;
}
 
void subWord(char column[4])	//S盒替换
{
	for (int i = 0;i < 4;i++)
		column[i] = sBox[(column[i] & 0xf0) >> 4][column[i] & 0x0f];
}
 
void xorWord(char column[4],int index)	//异或轮常数
{
	for (int i = 0;i < 4;i++)
	{
		column[i] = column[i] ^ RCON[index][i];
	}
}
 
char** keyExpansion(char** key, int round)	//密钥扩展
{
	int length = round - 6;	
	char temp[4];
	char ** w = new char*[4 * (round + 1)];		//扩展成4*(round + 1)列，每列4字节
	for (int i = 0;i < 4 * (round + 1);i++)
		w[i] = new char[4];
 
	for (int i = 0;i < length;i++)	//密钥前几列保持原样
	{
		for (int j = 0;j < 4;j++)
		{
			w[i][j] = key[j][i];
		}
	}
 
	for (int i = length;i < 4 * (round + 1);i++)
	{
		for (int j = 0;j < 4;j++)	//取得前一列，根据前一列递推出后面的列
			temp[j] = w[i-1][j];
		if (i % length == 0)	//i是密钥列数的倍数时
		{
			rolWord(temp);	//循环左移
			subWord(temp);	//S盒替换
			xorWord(temp,i / length);	//异或轮常数
		}
		else if (length > 6 && i % length == 4)	//列数大于6且对列数取余为4
		{
			subWord(temp);	//S盒替换
		}
 
		for (int j = 0;j < 4;j++)
			w[i][j] = w[i - length][j] ^ temp[j];	//进行异或
 
	}
 
	return w;
}
 
void addRoundKey(char** in, char** roundKey ,int index)	//轮密钥加
{
	for (int i = 0;i < 4;i++)
	{
		for (int j = 0;j < 4;j++)
		{
			in[j][i] ^= roundKey[index * 4 + i][j];
		}
	}
}
 
void byteSub(char **in)	//字节代替
{
	for (int i = 0;i < 4;i++)
	{
		for (int j = 0;j < 4;j++)
		{
			in[i][j] = sBox[(in[i][j] & 0xf0) >> 4][in[i][j] & 0x0f];
		}
	}
}
 
void invByteSub(char **in)	//逆字节代替
{
	for (int i = 0;i < 4;i++)
	{
		for (int j = 0;j < 4;j++)
		{
			in[i][j] = invSBox[(in[i][j] & 0xf0) >> 4][in[i][j] & 0x0f];
		}
	}
}
 
void shiftRow(char ** in)	//行移位
{
	char temp[4][4];
	for (int i = 0;i < 4;i++)
	{
		for (int j = 0;j < 4;j++)
		{
			temp[i][j] = in[i][(j + i) % 4];
		}
	}
 
	for (int i = 0;i < 4;i++)
		for (int j = 0;j < 4;j++)
			in[i][j] = temp[i][j];
}
 
void invShiftRow(char** in)	//逆向行移位
{
	char temp[4][4];
	for (int i = 0;i < 4;i++)
	{
		for (int j = 0;j < 4;j++)
		{
			temp[i][j] = in[i][(4 + j - i) % 4];
		}
	}
 
	for (int i = 0;i < 4;i++)
		for (int j = 0;j < 4;j++)
			in[i][j] = temp[i][j];
}
 
void mixColumn(char** in)	//列混淆
{
	char result[4][4];
	char temp[4];
	for (int k = 0; k < 4;k++)	//对于每一列，共4列
	{
		for (int i = 0;i < 4;i++)	//确定每一列上的四个值
		{
			for (int j = 0;j < 4;j++)
			{
				if (mixColumnMatrix[i][j] == 0x01)
				{
					temp[j] = in[j][k];
				}
				else if (mixColumnMatrix[i][j] == 0x02)
				{
					if (in[j][k] >= 128)
					{
						temp[j] = (in[j][k] << 1) ^ 0x1b;
					}
					else
					{
						temp[j] = in[j][k] << 1;
					}
				}
				else
				{
					if (in[j][k] >= 128)
					{
						temp[j] = in[j][k] ^ ((in[j][k] << 1) ^ 0x1b);
					}
					else
					{
						temp[j] = in[j][k] ^ (in[j][k] << 1);
					}
				}
			}
			result[i][k] = temp[0] ^ temp[1] ^ temp[2] ^ temp[3];
		}
	}
 
	for (int i = 0;i < 4;i++)
		for (int j = 0;j < 4;j++)
			in[i][j] = result[i][j];
	
}
 
void invMixColumn(char** in)	//逆向列混淆
{
	char result[4][4];
	char temp[4];
	for (int k = 0; k < 4;k++)	//对于每一列，共4列
	{
		for (int i = 0;i < 4;i++)	//确定每一列上的四个值
		{
			for (int j = 0;j < 4;j++)
			{
				if (invMixColumnMatrix[i][j] == 0x09)
				{
					if (in[j][k] >= 128)	//*2
					{
						temp[j] = (in[j][k] << 1) ^ 0x1b;
					}
					else
					{
						temp[j] = in[j][k] << 1;
					}
 
					if(temp[j] >= 128)		//*2
					{
						temp[j] = (temp[j] << 1) ^ 0x1b;
					}
					else
					{
						temp[j] = temp[j] << 1;
					}
 
					if (temp[j] >= 128)		//*2
					{
						temp[j] = (temp[j] << 1) ^ 0x1b;
					}
					else
					{
						temp[j] = temp[j] << 1;
					}
 
					//+1
					temp[j] ^= in[j][k];
				}
				else if (invMixColumnMatrix[i][j] == 0x0B)
				{
					if (in[j][k] >= 128)	//*2
					{
						temp[j] = (in[j][k] << 1) ^ 0x1b;
					}
					else
					{
						temp[j] = in[j][k] << 1;
					}
 
					if (temp[j] >= 128)		//*2
					{
						temp[j] = (temp[j] << 1) ^ 0x1b;
					}
					else
					{
						temp[j] = temp[j] << 1;
					}
 
					if (temp[j] >= 128)		//*2
					{
						temp[j] = (temp[j] << 1) ^ 0x1b;
					}
					else
					{
						temp[j] = temp[j] << 1;
					}
 
					// +2
					if (in[j][k] >= 128)	//*2
					{
						temp[j] ^= (in[j][k] << 1) ^ 0x1b;
					}
					else
					{
						temp[j] ^= in[j][k] << 1;
					}
 
					//+1
					temp[j] ^= in[j][k];
					
				}
				else if(invMixColumnMatrix[i][j] == 0x0D)
				{
					if (in[j][k] >= 128)	//*2
					{
						temp[j] = (in[j][k] << 1) ^ 0x1b;
					}
					else
					{
						temp[j] = in[j][k] << 1;
					}
 
					if (temp[j] >= 128)		//*2
					{
						temp[j] = (temp[j] << 1) ^ 0x1b;
					}
					else
					{
						temp[j] = temp[j] << 1;
					}
 
					if (temp[j] >= 128)		//*2
					{
						temp[j] = (temp[j] << 1) ^ 0x1b;
					}
					else
					{
						temp[j] = temp[j] << 1;
					}
 
					// +4
					char temp2;
					if (in[j][k] >= 128)	//*2
					{
						temp2 = (in[j][k] << 1) ^ 0x1b;
					}
					else
					{
						temp2 = in[j][k] << 1;
					}
 
					if (temp2 >= 128)		//*2
					{
						temp2 = (temp2 << 1) ^ 0x1b;
					}
					else
					{
						temp2 = temp2 << 1;
					}
 
					temp[j] ^= temp2;
 
					//+1
					temp[j] ^= in[j][k];
				}
				else
				{
					if (in[j][k] >= 128)	//*2
					{
						temp[j] = (in[j][k] << 1) ^ 0x1b;
					}
					else
					{
						temp[j] = in[j][k] << 1;
					}
 
					if (temp[j] >= 128)		//*2
					{
						temp[j] = (temp[j] << 1) ^ 0x1b;
					}
					else
					{
						temp[j] = temp[j] << 1;
					}
 
					if (temp[j] >= 128)		//*2
					{
						temp[j] = (temp[j] << 1) ^ 0x1b;
					}
					else
					{
						temp[j] = temp[j] << 1;
					}
 
					// +4
					char temp2;
					if (in[j][k] >= 128)	//*2
					{
						temp2 = (in[j][k] << 1) ^ 0x1b;
					}
					else
					{
						temp2 = in[j][k] << 1;
					}
 
					if (temp2 >= 128)		//*2
					{
						temp2 = (temp2 << 1) ^ 0x1b;
					}
					else
					{
						temp2 = temp2 << 1;
					}
 
					temp[j] ^= temp2;
 
					// +2
					if (in[j][k] >= 128)	//*2
					{
						temp[j] ^= (in[j][k] << 1) ^ 0x1b;
					}
					else
					{
						temp[j] ^= in[j][k] << 1;
					}
				}
			}
			result[i][k] = temp[0] ^ temp[1] ^ temp[2] ^ temp[3];
		}
	}
 
	for (int i = 0;i < 4;i++)
		for (int j = 0;j < 4;j++)
			in[i][j] = result[i][j];
 
}
 
string aesEncypteBlock(char** in, char** key,int length)	//对16字节明文进行AES加密
{
	string result;
	int round = length + 6;	//轮数
	char** roundKey = keyExpansion(key,round);	//密钥扩展
 
	addRoundKey(in, roundKey,0);//第0轮只做addRoundKey
 
	for(int i = 1;i < round;i++)
	{
		byteSub(in);	//S盒替换
		shiftRow(in);	//行移位
		mixColumn(in);	//列混淆
		addRoundKey(in, roundKey, i); //轮密钥加
	}
 
 
	//最后一轮不做mixcolumn
	byteSub(in);
	shiftRow(in);
	addRoundKey(in, roundKey,round);
	
	for (int i = 0;i < 4;i++)
		for (int j = 0;j < 4;j++)
			result.push_back(in[j][i]);
 
	return result;
}
 
string aesEncypte(string& clearText, const string& key)  //aes加密
{
	string cipherText;
	char **in,**keyMatrix;
	int length;
	//判断key长度
	switch (key.length())
	{
	case 16:
		length = 4;
		break;
	case 24:
		length = 6;
		break;
	case 32:
		length = 8;
		break;
	default:
		cout << "密钥长度不合法" << endl;
		exit(0);
		break;
	}
	keyMatrix = changeToMatrix(key, length);
 
	for (int i = 0;i < clearText.size();i += 16)
	{
		if (i + 15 >= clearText.size())	//不满16字节需要填充
		{
			for (int k = i + 15 - clearText.size();k >= 0;k--)
			{
				clearText.push_back('\0');
			}
		}
		in = changeToMatrix(clearText.substr(i, 16),4);
		cipherText += aesEncypteBlock(in, keyMatrix,length);	//每次处理16字节
	}
 
	return cipherText;
}
 
string aesDecypteBlock(char** in, char** key, int length)	//对16字节密文进行AES解密
{
	string result;
	int round = length + 6;	//轮数
	char** roundKey = keyExpansion(key, round);	//密钥扩展
 
	addRoundKey(in, roundKey, round);//第10轮
	invShiftRow(in);	//逆行移位
	invByteSub(in);	//逆S盒替换
	
	for (int i = round - 1;i > 0;i--)
	{
		addRoundKey(in, roundKey, i); //轮密钥加
		invMixColumn(in);	//逆列混淆
		invShiftRow(in);	//逆行移位
		invByteSub(in);	//逆S盒替换
	}
 
	addRoundKey(in, roundKey, 0);
 
	for (int i = 0;i < 4;i++)
		for (int j = 0;j < 4;j++)
			result.push_back(in[j][i]);
 
	return result;
}
string aesDecypte(string& cipherText, const string& key)  //aes解密
{
	string clearText;
	char **in, **keyMatrix;
	int length;
	//判断key长度
	switch (key.length())
	{
	case 16:
		length = 4;
		break;
	case 24:
		length = 6;
		break;
	case 32:
		length = 8;
		break;
	default:
		cout << "密钥长度不合法" << endl;
		exit(0);
		break;
	}
	keyMatrix = changeToMatrix(key, length);
 
	for (int i = 0;i < cipherText.size();i += 16)
	{
		if (i + 15 >= cipherText.size())	//不满16字节需要填充
		{
			for (int k = i + 15 - cipherText.size();k >= 0;k--)
			{
				cipherText.push_back('\0');
			}
		}
		in = changeToMatrix(cipherText.substr(i, 16), 4);
		clearText += aesDecypteBlock(in, keyMatrix, length);	//每次处理16字节
	}
 
	return clearText;
}


void encyptedecypte()
{
	system("cls");
	printf("\n\n\n");
	printf("--------------------------------------------------------------------------------\n");
	int number;
	string key, clearText, cipherText;
	int a[10002];
	int i = 0;
	double run_time;
	_LARGE_INTEGER time_start;	//开始时间
	_LARGE_INTEGER time_over;	//结束时间
	double dqFreq;		//计时器频率
	LARGE_INTEGER f;	//计时器频率
	QueryPerformanceFrequency(&f);
	dqFreq=(double)f.QuadPart;
	QueryPerformanceCounter(&time_start);
	printf("\t\t\t");
	cout <<"请输入明文(128bit):" << endl;
	printf("\t\t\t");
	cin >> clearText;
	printf("\t\t\t");
	cout << "请选择密钥长度:" << endl;
	printf("\t\t\t");
	cout << "1、128位" << endl;
	printf("\t\t\t");
	cout << "2、192位" << endl;
	//cout << "3、256位" << endl;
	printf("\t\t\t");
	cout << "请输入1、2来选择密钥长度:";
	printf("\t\t\t");
	cin >> number;
	printf("\t\t\t");
	cout << "请输入密钥:" << endl;
	printf("\t\t\t");
	cin >> key;
	cipherText = aesEncypte(clearText, key);
	printf("\t\t\t");
	cout << "密文:" << endl;
	printf("\t\t\t");
	cout << cipherText << endl;
	QueryPerformanceCounter(&time_over);	//计时结束
 	run_time=1000000*(time_over.QuadPart-time_start.QuadPart)/dqFreq;
	//乘以1000000把单位由秒化为微秒，精度为1000 000/（cpu主频）微秒
 
	clearText = aesDecypte(cipherText, key);
	printf("\n\n\n");
	printf("\t\t\t");
	cout << "解密后的明文:" << endl;
	printf("\t\t\t");
	cout << clearText << endl;
	
	
	printf("--------------------------------------------------------------------------------\n");
	printf("\n加密用时：%fus\n",run_time);

	char ret;
	printf("\n\n\n\n\t请按任意键并回车回到主菜单 \n");
	scanf("%d",&ret);
	if(ret!=0)
	    {
			Init();
		}
	else
		{
			Init();
		} 
	
	
}


void encryptByFile()
{	
	system("cls");
	printf("\n\n\n");
	printf("--------------------------------------------------------------------------------\n");
    int number;
	ifstream in;
	string key, clearText, cipherText;
	
	int a[10002];
	int i = 0;
	double run_time;
	_LARGE_INTEGER time_start;	//开始时间
	_LARGE_INTEGER time_over;	//结束时间
	double dqFreq;		//计时器频率
	LARGE_INTEGER f;	//计时器频率
	QueryPerformanceFrequency(&f);
	dqFreq=(double)f.QuadPart;
	QueryPerformanceCounter(&time_start);
	
	printf("\t\t\t");
	cout << "请输入明文:" << endl;
	printf("\t\t\t");
	cin >> clearText;
	printf("\t\t\t");
	cout << "请选择密钥长度:" << endl;
	printf("\t\t\t");
	cout << "1、128位" << endl;
	printf("\t\t\t");
	cout << "2、192位" << endl;
	//cout << "3、256位" << endl;
	printf("\t\t\t");
	cout << "请输入1、2来选择密钥长度:";
	cin >> number;
	switch (number)
	{
	case 1:
		in.open("Key128.txt", ios::in);
		break;
	case 2:
		in.open("Key192.txt", ios::in);
		break;
	default:
		cout << "输入不合法" << endl;
		exit(0);
		break;
	}
	
	in >> key;
	cipherText = aesEncypte(clearText, key);
	printf("\t\t\t");
	cout << "密文:" << endl;
	printf("\t\t\t");
	cout << cipherText << endl; 
	
	QueryPerformanceCounter(&time_over);	//计时结束
 	run_time=1000000*(time_over.QuadPart-time_start.QuadPart)/dqFreq;
	//乘以1000000把单位由秒化为微秒，精度为1000 000/（cpu主频）微秒
	
	//数据输出至out.txt文件中
	ofstream outfile("cipher.txt", ios::trunc);
	outfile<<cipherText<<endl;
	outfile.close();
	printf("--------------------------------------------------------------------------------\n");
	printf("\n加密用时：%fus\n",run_time);
	char ret;
	printf("\n\n\n\n\t请按任意键并回车回到二级菜单 \n");
	scanf("%d",&ret);
	if(ret!=0)
	    {
			fileencyptedecypte(); 
		}
	else
		{
			fileencyptedecypte();
		} 

}


void decryptByFile()
{
	system("cls");
	printf("\n\n\n");
	printf("--------------------------------------------------------------------------------\n");

	int number;
	ifstream in;
	string key, clearText, cipherText;
	printf("\t\t\t");
	cout << "正在打开密文所在文件（cipher.txt）:" << endl;
//	cin >> clearText;
	ifstream infile;

	infile.open("cipher.txt",ios::in);
	printf("\t\t\t");
	while(!infile.eof())
	{	
		infile>>cipherText;
	}

	cout<<cipherText<<endl;//已保存在变量str中
	printf("\t\t\t");
	cout << "请选择密钥长度:" << endl;
	printf("\t\t\t");
	cout << "1、128位" << endl;
	printf("\t\t\t");
	cout << "2、192位" << endl;
	//cout << "3、256位" << endl;
	printf("\t\t\t");
	cout << "请输入1、2来选择密钥长度:";
	cin >> number;
	switch (number)
	{
	case 1:
		in.open("Key128.txt", ios::in);
		break;
	case 2:
		in.open("Key192.txt", ios::in);
		break;
	default:
		cout << "输入不合法" << endl;
		exit(0);
		break;
	}
	
	in >> key;
	clearText = aesDecypte(cipherText, key);
	printf("\t\t\t");
	cout << "明文:" << endl;
	printf("\t\t\t");
	cout << clearText << endl;
	printf("--------------------------------------------------------------------------------\n");
	char ret;
	printf("\n\n\n\n\t请按任意键并回车回到二级菜单 \n");
	scanf("%d",&ret);
	if(ret!=0)
	    {
			fileencyptedecypte(); 
		}
	else
		{
			fileencyptedecypte(); 
		} 
}


void Init()
{
	SetConsoleTitle("AES加解密");
	system("color F0");

    system ("cls");
	printf("\t\t\t欢迎使用192位AES加密解密算法\tv2.1.2\n");   

	printf("\t\tWelcome to 192 bit AES encryption and decryption algorithm\n");

	printf("--------------------------------------------------------------------------------\n");
	printf("                                                                                       ");
	printf("\n\n \t\t\t\t1.通过文件进行加解密                                                                \n");
	printf("");
	printf("\n\n \t\t\t\t0.通过键盘输入加解密                                                                \n");
	printf("");
	printf("");
	printf("\n\n \t\t\t\t请按键选择，回车确定\n");

	printf("--------------------------------------------------------------------------------\n");
	
	int choice;
	scanf("%d",&choice);
	if(choice==0)
	{
		encyptedecypte();
	}
	else if(choice==1)
	{
		fileencyptedecypte();
	}
	else
	{
		Init();
	}

}



void fileencyptedecypte()
{
	system ("cls");
	printf("\n\n\n");
	printf("--------------------------------------------------------------------------------\n");
	printf("                                                                                       ");
	printf("\n\n \t\t\t\t1.通过文件进行加密                                                                \n");
	printf("");
	printf("\n\n \t\t\t\t0.通过文件进行解密                                                                \n");
	printf("");
	printf("");
	printf("\n\n \t\t\t\t请按键选择，回车确定\n");

	printf("--------------------------------------------------------------------------------\n");
	int choice;
	cin>>choice;
	if (choice==1)
	{
		encryptByFile();
	 } 
	else if(choice==0)
	{
		decryptByFile();
	}
	else
	{
		Init();
	}
 } 



int main()
{	
	
	Init();
	system("Pause");
	return 0;
 
}

	
	
	

	

 
 


