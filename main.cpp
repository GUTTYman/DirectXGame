#include"DirectXGame.h"
#include <stdlib.h>
#include <crtdbg.h>

#ifdef _DEBUG
int main()
{
#else
//Windows�A�v���ł̃G���g���[�|�C���g(main�֐�)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
#endif
	auto game=new DirectXGame();
	game->Run();
	delete game;

	//_CrtDumpMemoryLeaks();
	return 0;
}