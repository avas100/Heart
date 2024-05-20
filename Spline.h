#pragma once
#include <list>
#include <vector>
#include <stdio.h>
#include<iostream>
#include<stdlib.h>
#include <vector>
#include <math.h>


using namespace System::Drawing;
using namespace System::Collections;

#define M_PI 3.14159265358979323846
const float H = 0.001f;

//немного измененный чебышев
//возможно из-за неправильной параметризации кривая для 6 и более точек строится неправильно 
// Голованов " геом. моделировнаие" с. 37
std::vector<double> Init_T(ArrayList^ p) {
	int N = p->Count;
	std::vector<double> t;
	for (int i = N - 1; i >= 0; --i) {
		t.push_back(static_cast<float>(cos(M_PI * ((2.0f * i + 1.0f)) / (2.0f * (N - 1.0f) + 2.0f))));
	}
	return t;
}
// (2.3.8) с. 36
array<PointF>^ Init_B(ArrayList^ Points) {
	int N = Points->Count;
	std::vector<double> t = Init_T(Points);
	array<PointF>^ b_vec = gcnew array<PointF>(N);
	b_vec[0] = PointF(0, 0);
	array<PointF>^ pointsArray = dynamic_cast<array<PointF>^>(Points->ToArray(PointF::typeid));
	for (int i = 1; i < N - 1; i++) {
		PointF b;
		b.X = static_cast<float>(6.0 * ((pointsArray[i + 1].X - pointsArray[i].X) / (t[i + 1] - t[i]) - (pointsArray[i].X - pointsArray[i - 1].X) / (t[i] - t[i - 1])));
		b.Y = static_cast<float>(6.0 * ((pointsArray[i + 1].Y - pointsArray[i].Y) / (t[i + 1] - t[i]) - (pointsArray[i].Y - pointsArray[i - 1].Y) / (t[i] - t[i - 1])));
		b_vec[i] = b;
	}
	b_vec[N - 1] = PointF(0., 0.);
	return b_vec;
}
std::vector<std::vector<double>> Init_Matrix(ArrayList^ Points) {
	std::vector<double> t = Init_T(Points);
	int N = Points->Count;
	std::vector<std::vector<double>> A(N, std::vector<double>(N, 0.));
	A[0][0] = 1;

	int k = 1;
	for (int i = 1; i <= N - 2; i++) {
		A[k][k - 1] = t[i] - t[i - 1];
		A[k][k] = 2 * (t[i + 1] - t[i - 1]);
		A[k][k + 1] = t[i + 1] - t[i];
		k++;
		if (k + 2 > N) break;
	}
	A[N - 1][N - 1] = 1;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			std::cout << " " << A[i][j];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	return A;
}
// решение системы линейных уравнений из получ матрицы и свобод. векторов (по методу Зейделя)
array<PointF>^ Result(ArrayList^ Points) {
	int N = Points->Count;
	array<PointF>^ b = Init_B(Points);
	std::vector<std::vector<double>> A = Init_Matrix(Points);
	std::vector<double> t = Init_T(Points);

	array<PointF>^ s_prev = gcnew array<PointF>(N);
	array<PointF>^ s = gcnew array<PointF>(N);

	PointF eps_max;
	PointF eps(2.0f / 10000.0f, 2.0f / 10000.0f);
	do {
		for (int i = 0; i < N; i++) {
			s[i] = b[i];

			for (int j = 0; j < N; j++) {

				if (j > i && j != i) {
					s[i].X -= s_prev[j].X * A[i][j];
					s[i].Y -= s_prev[j].Y * A[i][j];
				}
				else if (j < i && j != i) {
					s[i].X -= s[j].X * A[i][j];
					s[i].Y -= s[j].Y * A[i][j];
				}
				s[i].X /= A[i][i];
				s[i].Y /= A[i][i];
			}
		}
		eps_max.X = fabs(s[0].X - s_prev[0].X);
		eps_max.Y = fabs(s[0].Y - s_prev[0].Y);
		for (int i = 0; i < N; i++) {
			if (fabs(s[i].X - s_prev[i].X) > eps_max.X && fabs(s[i].Y - s_prev[i].Y) > eps_max.Y) {
				eps_max.X = fabs(s[i].X - s_prev[i].X);
				eps_max.Y = fabs(s[i].Y - s_prev[i].Y);
			}
			s_prev[i] = s[i];
		}

	} while (eps_max.X > eps.X && eps_max.Y > eps.Y);
	return s;
}

// кубический полином (2.3.9)
float W(float t, float t_i, float t_ip) {
	return ((t - t_i) / (t_ip - t_i));
}
array<PointF>^ R(ArrayList^ Points) {
	std::vector<double> t = Init_T(Points);
	int N = Points->Count;
	array<PointF>^ s = Result(Points);
	array<PointF>^ pointsArray = dynamic_cast<array<PointF>^>(Points->ToArray(PointF::typeid));
	int r_count = 0;
	for (int i = 0; i < N - 1; i++) {
		double t_i = t[i];
		double t_ii = t[i + 1];
		for (double t = t_i; t <= t_ii - H;) {
			r_count++;
			t += H;
		}
	}
	ArrayList^ Res = gcnew ArrayList(r_count);
	for (int i = 0; i < N - 1; i++) {
		std::cout << "___________________" << std::endl;
		float t_i = t[i];
		float t_ii = t[i + 1];
		for (float t = t_i; t <= t_ii - H;) {
			PointF Fun_R(0, 0);
			float w = W(t, t_i, t_ii);

			float deltaX = (pointsArray[i].X * (1 - w));
			float deltaY = (pointsArray[i].Y * (1 - w));

			deltaX += (pointsArray[i + 1].X * (w));
			deltaY += (pointsArray[i + 1].Y * (w));

			deltaX += ((-2.) * w + 3 * pow(w, 2) - pow(w, 3)) * s[i].X;
			deltaY += ((-2.) * w + 3 * pow(w, 2) - pow(w, 3)) * s[i].Y;

			deltaX += ((-1.) * w + pow(w, 3)) * s[i + 1].X * (pow(t_ii - t_i, 2) / 6.0f);
			deltaY += ((-1.) * w + pow(w, 3)) * s[i + 1].Y * (pow(t_ii - t_i, 2) / 6.0f);

			Fun_R.X = deltaX;
			Fun_R.Y = deltaY;
			t += H;
			Res->Add(Fun_R);
		}
	}
	array<PointF>^ ResArray = static_cast<array<PointF>^>(Res->ToArray(PointF::typeid));
	return ResArray;
}

//  Первые производные 
// продиф 2-ые производ (2.3.7)(с. 35)
array<PointF>^ d_i(ArrayList^ Points) {
	int N = Points->Count;
	array<PointF>^ P = dynamic_cast<array<PointF>^>(Points->ToArray(PointF::typeid));
	std::vector<double> t = Init_T(Points);
	array<PointF>^ S = Result(Points);
	array<PointF>^ pointsArray = gcnew array<PointF>(N);
	for (int i = 0; i < N - 1; i++) {
		PointF D;
		D.X = (P[i + 1].X - P[i].X) / (t[i + 1] - t[i]);
		D.Y = (P[i + 1].Y - P[i].Y) / (t[i + 1] - t[i]);

		D.X -= 1. / 6 * (2 * S[i].X + S[i + 1].X) * (t[i + 1] - t[i]);
		D.Y -= 1. / 6 * (2 * S[i].Y + S[i + 1].Y) * (t[i + 1] - t[i]);

		pointsArray[i] = D;
	}
	return pointsArray;
}