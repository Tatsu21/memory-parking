#include "pch.h"
#include <filesystem>
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <list>
#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
int main()
{


	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	memoryparking::MyForm form;
	Application::Run(% form);



    return 0;
}
