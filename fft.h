#ifndef _BA_FFT_H_
#define _BA_FFT_H_
#include "Complex.h"
#include <cmath>
// ���FFT������
#define MAX_FFT_SIZE 4096

#define PI 3.14159265358979323846

// ָ������
const int POW[] = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536 };

// ��ת����
static Complex W[MAX_FFT_SIZE / 2];

// �������㣨��2Ϊ�ף�
int LOG(int n)
{
	switch (n)
	{
	case 1:return 0; break;
	case 2:return 1; break;
	case 4:return 2; break;
	case 8:return 3; break;
	case 16:return 4; break;
	case 32:return 5; break;
	case 64:return 6; break;
	case 128:return 7; break;
	case 256:return 8; break;
	case 512:return 9; break;
	case 1024:return 10; break;
	case 2048:return 11; break;
	case 4096:return 12; break;
	case 8192:return 13; break;
	case 16384:return 14; break;
	case 32768:return 15; break;
	case 65536:return 16; break;
	default:return -1;
	}
}

// ��ת���ӵ�����
void GenerateRotationFactor(int size)
{
	double ReP = 0.0;
	double ImP = 0.0;
	// W[i] = exp(-2*pi*j*(i/N))
	// ֻ��Ҫ�õ�0~��Size-1������ת����
	for (int i = 0; i < size / 2; i++)
	{
		// ŷ����ʽչ��
		ReP = cos(2.0 * PI * ((double)i / (double)size));
		ImP = -sin(2.0 * PI * ((double)i / (double)size));
		Complex temp(ReP, ImP);
		W[i] = temp;
	}
}

// �������鸴��
void ArrayCopy(Complex dest[], Complex src[], int size)
{
	for (int i = 0; i < size; i++)
	{
		dest[i] = src[i];
	}
}

// ��λ����
void BitReverse(int inIndex[], int indexSize)
{
	int temp = 0;
	int bitSize = LOG(indexSize);
	for (int i = 0; i < indexSize; i++)
	{
		temp = inIndex[i];
		inIndex[i] = 0;
		for (int c = 0; c < bitSize; c++)
		{
			//temp >>= c;
			if ((temp >> c) & 1)
			{
				inIndex[i] += POW[bitSize - 1 - c];
			}
		}
	}
}

// ���ٸ���Ҷ�任
void FFT(Complex IN[], Complex OUT[], int Size)
{
	Complex buf[2][MAX_FFT_SIZE];
	// �������飬��������洢������������Ľ��
	// Complex bufA[MAX_FFT_SIZE];
	// Complex bufB[MAX_FFT_SIZE];

	//==== ѭ�����Ʊ��� =========================================

	// 1.���г���
	// int Size; ���βΣ�

	// 2.���г��ȵĶ���
	int M = LOG(Size);

	// 3.���㼶
	int Level = 0;

	// 4.�����е����
	int Group = 0;

	// 5.�������ڵ�Ԫ���±�
	// int i = 0; (ѭ���ڲ���Ч)
	//==== ѭ�����Ʊ������� =====================================

	// ��λ���ú�����������±�
	int indexIn[MAX_FFT_SIZE];

	//==== ���������е��±��ȡ��λ���ò��� =====================
	// �Ȱ�˳���ʼ���±�����
	for (int i = 0; i < MAX_FFT_SIZE; i++)
	{
		indexIn[i] = i;
	}
	// ִ����λ����
	BitReverse(indexIn, Size);
	// ��ʱ��indexIn[]���������λ���ú���±�
	//==== ��λ���ò������ =====================================

	//==== ������ת���ӱ��� =====================================
	GenerateRotationFactor(Size);
	//==== ��ת���Ӽ������ =====================================

	// FFT�����㷨��ʼ

	// �㷨˵��
	// һ���������г���Ϊ��Size���������Ϊ��M����
	// ��������M�����㼶��Level����
	// ����ÿ�������� POW[M-Level-1] �顾Group�������в���������㣬�����г���ΪPOW[Level+1]��
	// �ġ�ÿ��������ֻ��ǰ�벿����Ϊ��������ġ���Ԫ����������ǰ�벿�ֵĳ���Ϊ POW[Level]��
	// �塢ÿ���������� POW[Level] ����������ᣬ��������ǰ�벿�֣���Ԫ��������
	// ����ÿ�������������Ҫʹ��λ��������ǰ�벿�ֵ�һ��Ԫ�أ���Ԫ���Ͷ�Ӧ�ĺ�벿��Ԫ�أ���Ԫ������Ԫ�±�=��Ԫ�±�+POW[Level]��
	// �ߡ�ÿ�����㶼����bufA[]�����롢bufB[]�������
	// �ˡ�ÿ���һ�����㣬����Ҫ��bufB[]������bufA[]�Թ��¼�����ʹ�á�

	// ��ʼ��ѭ��
	// ���ȶ�ÿһ���������ѭ��������Ҫѭ��M����
	for (Level = 0; Level < M; Level++)
	{
		// �Ըü������е�ÿ�������н��е�������ı���������Ҫ����POW[M-Level-1]�������С�
		for (Group = 0; Group < POW[M - Level - 1]; Group++)
		{
			// �������е�ǰ�벿�ֽ���Ԫ�ر���
			// ÿ�α������һ�������ĵ��������
			for (int i = 0; i < POW[Level]; i++)
			{
				// �±���ʱ����
				// �ñ�����¼��������ľ���λ��
				//   ��Ϊi������������ǰ�벿���ڵ�Ԫ���±꣬��Χ��0~POW[Level]
				//   ����ÿ�������еĳ�����POW[Level+1]������
				//     �����±� = ��������±�i + ��ƫ����Group*POW[Level+1]��
				int indexBuf = i + Group * POW[Level + 1];

				// ��ת�����ϱ�ļ���
				// ��ת�����ϱ�������� = ��ǰ���㼶������������
				int ScalingFactor = POW[M - Level - 1];


				// ��������ᡣFFT�㷨�����еĺ��ġ�

				// ��Ϊ���㼶����
				// ���㼶����ʹ�õ�����λ���ú����������
				// ����������ԭ�±꣨��λ����ǰ���±꣩����bufB[]
				//   ��Ϊ����������˳����ƶ��ǻ�����Ȼ�����±���е�
				if (Level == 0)
				{
					buf[0][indexBuf] = IN[indexIn[indexBuf]] + W[i*ScalingFactor] * IN[indexIn[indexBuf + POW[Level]]];
					buf[0][indexBuf + POW[Level]] = IN[indexIn[indexBuf]] - W[i*ScalingFactor] * IN[indexIn[indexBuf + POW[Level]]];
				}
				// ��Ϊ���༶����
				else
				{
					buf[Level % 2][indexBuf] = buf[(Level + 1) % 2][indexBuf] + W[i*ScalingFactor] * buf[(Level + 1) % 2][indexBuf + POW[Level]];
					buf[Level % 2][indexBuf + POW[Level]] = buf[(Level + 1) % 2][indexBuf] - W[i*ScalingFactor] * buf[(Level + 1) % 2][indexBuf + POW[Level]];
				}
			} // �������еĵ������������������POW[Level]����������ᡣ

		} // �����б�����������ѭ��POW[M-Level-1]�Ρ�

		  // ��bufB[]�е�������������bufA[]
		  //ArrayCopy(bufA, bufB, Size);


	} // ���㼶ѭ����������ѭ��M�Ρ�

	  // �����һ����������bufB������OUT
	ArrayCopy(OUT, buf[(Level + 1) % 2], Size);

} // FFT������


mat FFT(mat m) {
	int num = m.n_elem;

	Complex* OUT = new Complex[m.n_elem];

	FFT(mat2com(m), OUT, num);

	return com2mat(OUT, num);

}
#endif
