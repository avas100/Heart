#include "pch.h"
#include "MyForm.h"
//#include"Spline.h"
using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]

int main(array<String^>^ args) {
	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();
	WindForm::MyForm form;
	Application::Run(% form);
	return  0;
}