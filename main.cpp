#include<iostream>
#include<algorithm>
#include<vector>
#include<stack>
#include<queue>
#include<string>
#include<stdio.h>
#include<memory.h>
#include<string.h>
#include<time.h>
#include<armadillo>
#include<math.h>
#include<meta.h>
#include<hanning.h>
#include<enframe.h>
#define pi 3.1415926
using namespace std;
using namespace arma;

/*
mat tranverse(mat x, int win, int inc);
void audioread(string dest, mat x, int* Fs);//input dest,output x & Fs
mat fft(mat);
void spectrogram(mat x,int w,int o,int n,int fs,string lab);


int mean(mat x) {
	int s = 0;
	for (int i = 0; i < x.n_cols; i++) {
		for (int j = 0; j < x.n_rows; j++) {
			s += x(i, j);
		}
	}
	return s / x.n_cols / x.n_rows;
}




void zero_cross(mat xx, mat fs) {
	//xx=xx-mean(xx)
	int mean_xx = mean(xx);
	for (int i = 0; i < xx.n_cols; i++) {
		for (int j = 0; j < xx.n_rows; j++) {
			xx(i, j) -= mean_xx;
		}
	}

	int wlen = 200;
	int inc = 80;

	int win;
	//win = hanning(wlen);

	//int N = length(xx);

	mat X;
	mat afterTran = tranverse(xx,win,inc);
	X = enframe(afterTran);
	int fn = xx.n_cols;
	for (int i = 0; i < fn; i++) {
		zcr1(0, i) = 0;
	}

	for (int i = 1; i <= fn; i++) {
		for (int j = 1; j < wlen; j++) {
			if(X(i,j)*X(i,j+1)<0)
				zcr1(0,i) = zcr1(0,i) + 1;
		}
	}

	//somtting wrong with this
	//mat time = N / fs;
	//mat frameTime = (((1:fn) - 1)*inc + wlen / 2) / fs;

}


void pr241(string dest) {
	string fle = dest;
	mat x;
	int Fs;
	audioread(dest, x, &Fs);
	int wlen = 300, inc = 80;
	WIN win = hanning(wlen);
	int N = x.n_elem;
	int time = (N - 1) / Fs;
	mat y = enframe(x, win, inc);//'
	int fn = y.n_cols;


};
								  
void energy(string dest) {
	mat x;
	int Fs;
	audioread(dest, x, &Fs);
	int wlen = 200, inc = 80;
	WIN win = hanning(wlen);
	int N = x.n_elem;
	mat X = enframe(x, win, inc);//'
	int fn = X.n_cols;
	mat time;// = (0:N-1)/Fs
	for (int i = 1; i <= N - 1; i++) {
		int u = X(i);
		int u2 = u % u;
		//En(i)=sum(u2);
	}
	//....
}

void create_spectrogram(string dest) {
	mat y;
	int fs;
	audioread(dest, y, &fs);
	int nfft = 1024;
	int w = 512;
	int overlap_new = 256;
	spectrogram(y, w, overlap_new, nfft, fs, "yaxis");
}

/*
�����ʱ֡��������energy.mת.c
*/
/*void energy(mat x, double Fs)
{
	int wlen = 200;
	int inc = 80;			//����֡����֡��
	mat win = hanning(wlen);	//����������
	int N = x.n_cols;		//�źų���
	mat X = enframe(x, win, inc).t();	//��֡
	int fn = X.n_cols;		//���֡��
	mat time(1,N);
	for (int i = 1; i <= N; i++)
	{
		time(i - 1) = (i - 1) / Fs;
	}
	//��Ҫ����X��������������ÿ��ȡ��һ��
	int len;
	int nx = x.n_elem;	//ȡ���ݳ���
	int nwin = win.n_elem;	//ȡ����
	if (1 == nwin)	//�жϴ����Ƿ�Ϊ1����Ϊ1������ʾû���贰����
	{
		len = win(0);	//�ǣ�֡��=win
	}
	else
	{
		len = nwin;		//��֡��=����
	}
	int nf = floor((nx - len + inc) / inc);	//����֡��
	int j = 1;

	mat En(1, fn);			//��һ֡�ۼ����
	for (int t = 1; t <= fn; t++)
	{
		mat u(len, 1);			//ȡ��һ֡
		for (int k = 0; k < nf; k++)
		{
			for (int i = 1; j < j + len, i < len + 1; j++, i++) {

				u(i - 1) = X(j - 1);
			}
		}
		mat u2 = u % u;		//�������
		En(t - 1) = accu(u2);
		
	}

	mat frameTime = frame2time(fn, wlen, inc, Fs);   // ���ÿ֡��Ӧ��ʱ��
}
/*
��֡�����ÿ֡ʱ�䣬��frame2time.mת.c
*/
/*mat frame2time(int frameNum,int frameLen,int inc,double fs)
{
	mat frametime(1,frameNum);
	for (int i = 1; i <= frameNum; i++)
	{
	
		frametime(i-1)=((i - 1)*inc + frameLen/2)/fs;	//��֡��ÿ֡��Ӧ��ʱ��
	}
	return frametime;

}
*/


int main() {
	hanning(200);


	int T;
	cin >> T;
	return 0;
}