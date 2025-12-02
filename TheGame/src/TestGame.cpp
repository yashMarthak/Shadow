#include <Shadow.h>

class TheGame : public Shadow::Application
{
public:
	TheGame()
	{
	}

	~TheGame()
	{
	}
};

Shadow::Application* Shadow::CreateApplication()
{
	return new TheGame();
}