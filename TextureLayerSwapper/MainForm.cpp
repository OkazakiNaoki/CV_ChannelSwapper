#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#include "MainForm.h"
using namespace System;
using namespace System::Windows::Forms;
[STAThreadAttribute]

int main() {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	TextureLayerSwapper::MainForm mf;
	Application::Run(% mf);
	return 0;
}