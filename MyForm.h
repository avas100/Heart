#pragma once
#include "Spline.h"
#include <list>
#include <vector>
#include <stdio.h>
#include<iostream>
#include<stdlib.h>
#include <vector>
#include <math.h>


using namespace System::Drawing;
using namespace System::Collections;

namespace WindForm {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;



	/// <summary>
	/// Сводка для HeartApp
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	private:
		Bitmap^ buffer; // Буфер для рисования
		ArrayList^ pointsList = gcnew ArrayList();
		System::Boolean F = false;
		int count = 0;
	private: System::Windows::Forms::Button^ button_save;
	private: System::Windows::Forms::Button^ button_plot;
	private: System::Windows::Forms::Button^ button_curve;
	private: System::Windows::Forms::Button^ button_help;




	private: System::Windows::Forms::HelpProvider^ helpProvider1;
	private: System::Windows::Forms::Label^ label_result;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::SaveFileDialog^ saveFileDialog1;

	private: System::Windows::Forms::TextBox^ textBox1;

		void InitializeBuffer() {
			buffer = gcnew Bitmap(pictureBox1->Width, pictureBox1->Height);
		}

	public:
		MyForm(void)
		{

			InitializeComponent();
			InitializeBuffer();
			//
			//TODO: добавьте код конструктора
			//
		}



	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete buffer; // Освобождение ресурсов Bitmap
				delete pointsList; // Освобождение объекта ArrayList
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button_add;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
	private: System::Windows::Forms::Button^ button_clear;


	protected:

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button_add = (gcnew System::Windows::Forms::Button());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->button_clear = (gcnew System::Windows::Forms::Button());
			this->button_save = (gcnew System::Windows::Forms::Button());
			this->button_plot = (gcnew System::Windows::Forms::Button());
			this->button_curve = (gcnew System::Windows::Forms::Button());
			this->button_help = (gcnew System::Windows::Forms::Button());
			this->helpProvider1 = (gcnew System::Windows::Forms::HelpProvider());
			this->label_result = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// button_add
			// 
			this->button_add->BackColor = System::Drawing::SystemColors::AppWorkspace;
			this->button_add->Font = (gcnew System::Drawing::Font(L"Microsoft Uighur", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button_add->Location = System::Drawing::Point(608, 23);
			this->button_add->Margin = System::Windows::Forms::Padding(4);
			this->button_add->Name = L"button_add";
			this->button_add->Size = System::Drawing::Size(108, 60);
			this->button_add->TabIndex = 0;
			this->button_add->Text = L"Добавить";
			this->button_add->UseVisualStyleBackColor = false;
			this->button_add->Click += gcnew System::EventHandler(this, &MyForm::button_add_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->pictureBox1->ImageLocation = L"";
			this->pictureBox1->Location = System::Drawing::Point(12, 12);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(562, 529);
			this->pictureBox1->TabIndex = 2;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::pictureBox1_Paint);
			this->pictureBox1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox1_MouseDown);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// button_clear
			// 
			this->button_clear->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->button_clear->Location = System::Drawing::Point(609, 156);
			this->button_clear->Name = L"button_clear";
			this->button_clear->Size = System::Drawing::Size(108, 60);
			this->button_clear->TabIndex = 3;
			this->button_clear->Text = L"Очистить";
			this->button_clear->UseVisualStyleBackColor = false;
			this->button_clear->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// button_save
			// 
			this->button_save->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->button_save->Location = System::Drawing::Point(608, 222);
			this->button_save->Name = L"button_save";
			this->button_save->Size = System::Drawing::Size(108, 60);
			this->button_save->TabIndex = 4;
			this->button_save->Text = L"Сохранить";
			this->button_save->UseVisualStyleBackColor = false;
			this->button_save->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// button_plot
			// 
			this->button_plot->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->button_plot->Location = System::Drawing::Point(609, 90);
			this->button_plot->Name = L"button_plot";
			this->button_plot->Size = System::Drawing::Size(108, 60);
			this->button_plot->TabIndex = 5;
			this->button_plot->Text = L"Построить\r\nкривую";
			this->button_plot->UseVisualStyleBackColor = false;
			this->button_plot->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// button_curve
			// 
			this->button_curve->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->button_curve->Location = System::Drawing::Point(608, 317);
			this->button_curve->Name = L"button_curve";
			this->button_curve->Size = System::Drawing::Size(108, 61);
			this->button_curve->TabIndex = 6;
			this->button_curve->Text = L"Кривизна";
			this->button_curve->UseVisualStyleBackColor = false;
			this->button_curve->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
			// 
			// button_help
			// 
			this->button_help->Location = System::Drawing::Point(868, 513);
			this->button_help->Name = L"button_help";
			this->button_help->Size = System::Drawing::Size(108, 28);
			this->button_help->TabIndex = 8;
			this->button_help->Text = L"Справка";
			this->button_help->UseVisualStyleBackColor = true;
			// 
			// label_result
			// 
			this->label_result->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->label_result->Location = System::Drawing::Point(723, 318);
			this->label_result->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label_result->Name = L"label_result";
			this->label_result->Size = System::Drawing::Size(242, 192);
			this->label_result->TabIndex = 1;
			// 
			// label2
			// 
			this->label2->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->label2->Location = System::Drawing::Point(724, 54);
			this->label2->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(242, 238);
			this->label2->TabIndex = 9;
			// 
			// textBox1
			// 
			this->textBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->textBox1->BackColor = System::Drawing::SystemColors::ControlLight;
			this->textBox1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox1->Location = System::Drawing::Point(728, 23);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(100, 18);
			this->textBox1->TabIndex = 10;
			this->textBox1->Text = L"Действия";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 23);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ControlLight;
			this->ClientSize = System::Drawing::Size(988, 586);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->button_help);
			this->Controls->Add(this->button_curve);
			this->Controls->Add(this->button_plot);
			this->Controls->Add(this->button_save);
			this->Controls->Add(this->button_clear);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->label_result);
			this->Controls->Add(this->button_add);
			this->Font = (gcnew System::Drawing::Font(L"Microsoft Uighur", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Margin = System::Windows::Forms::Padding(3, 5, 3, 5);
			this->Name = L"MyForm";
			this->Text = L"HeartApp";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button_add_Click(System::Object^ sender, System::EventArgs^ e) {
		if (this->openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			pictureBox1->ImageLocation = openFileDialog1->FileName;
			this->label2->Text += "Снимок успешно открыт\n";
		}
		else {
			this->label2->Text += "Ошибка при открытии\n";
		}
	}

	private: System::Void pictureBox1_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		if (e->Button == System::Windows::Forms::MouseButtons::Left) {
			PointF point = pictureBox1->PointToClient(Control::MousePosition);
			pointsList->Add(point);
			this->label2->Text += "Точка добавлена\n ";
			count++;
			pictureBox1->Invalidate();
		}
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		pointsList->Clear();
		Graphics^ g = Graphics::FromImage(buffer);
		g->Clear(Color::Transparent); 
		F = false;
		count = 0;
		label2->Text = "";
		this->label_result->Text = "";
		pictureBox1->Invalidate();
	}
	private: System::Void pictureBox1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
		array<PointF>^ pointsArray = dynamic_cast<array<PointF>^>(pointsList->ToArray(PointF::typeid));
		Pen^ pen = gcnew Pen(Color::Red, 1.0f);
		SolidBrush^ brush = gcnew SolidBrush(Color::Blue);
		for (int i = 0; i < count; i++) {
			e->Graphics->FillEllipse(brush, pointsArray[i].X - 3.0f, pointsArray[i].Y - 3.0f, 6.0f, 6.0f);
		}
		if (pointsList->Count > 1) {
			std::vector<double> t_vec = Init_T(pointsList);
			int N = pointsList->Count;
			array<PointF>^ b = Init_B(pointsList);
			std::vector<std::vector<double>> M = Init_Matrix(pointsList);
			array<PointF>^ s = gcnew array<PointF>(N);
			array<PointF>^ r = R(pointsList);
			int r_count = 0;
			for (int i = 0; i < N - 1; i++) {
				float t_i = t_vec[i];
				float t_ii = t_vec[i + 1];
				for (float t = t_i; t <= t_ii - H;) {
					r_count++;
					t += H;
				}
			}
			
			if (F == true && count >= 2) {
				for (int i = 0; i < r_count - 1; i++) {
					e->Graphics->DrawLine(pen, PointF(r[i].X, r[i].Y), PointF(r[i + 1].X, r[i + 1].Y));
				}
				F = false;
				this->label2->Text += "Кривая построена\n";
			}
			
			delete brush;
			delete pen;
		}
		e->Graphics->DrawImage(buffer, Point::Empty);
	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		saveFileDialog1->Filter = "PNG files (*.png)|*.png|All files (*.*)|*.*";
		if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			System::String^ filename = saveFileDialog1->FileName;
			pictureBox1->Image->Save(filename);
			this->label2->Text += "Снимок сохранен \n";
		}
		else this->label2->Text += "Ошибка при сохранении \n";
	}
	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
		F = true;
		pictureBox1->Invalidate();
	}
private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {
	int N = pointsList->Count;
	array<PointF>^ s = gcnew array<PointF>(N);
	s = Result(pointsList);
	array<PointF>^ d = gcnew array<PointF>(N);
	d = d_i(pointsList);
	this->label_result->Text = " ";
	for (int i = 1; i < N - 1; i++) {
		double k = fabs(d[i].X * s[i].Y - s[i].X * d[i].Y);
		double r = pow(pow(d[i].X, 2) + pow(d[i].Y, 2) ,1./2);
		k /= pow(r, 3);
		this->label_result->Text += "Кривизна в точке p"+ i + " = " + k + " ; \n";
	}
}

private: System::Void button5_Click(System::Object^ sender, System::EventArgs^ e) {
}

};
}
