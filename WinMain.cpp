#include	"GameApp.h"
#include    "resource.h"

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Mof::LPFramework pFrame = new Mof::CDX11GameFramework();
	Mof::WINDOWSGAMEFRAMEWORKINITIALIZEINFO Info;
	Info.WindowCreateInfo.hIcon = ::LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	//フォントの追加
	AddFontResource("Text\\poprum.otf");
	//RemoveFontResource("poprum.otf");

	Info.pApplication = new CGameApp();
	//画面サイズ指定
	Info.WindowCreateInfo.Width = 1920;
	Info.WindowCreateInfo.Height = 1080;
	if (pFrame->Initialize(&Info))
	{
		pFrame->Run();
	}
	MOF_SAFE_DELETE(pFrame);
	return 0;
}