#pragma once
#include "GameTransform.h"

#pragma region renderer-transform
/*
	<< renderer-transform >>
	renderer는 renderer면서 transform이다.
	자신만의 위치와 크기를 가지고 있다.
*/
#pragma endregion

class GameCamera;
class GameRenderer : public GameTransform
{
public:
	void Init(int _Order = 0);
	virtual void Render(CPtr<GameCamera> _CAM);

public:
	GameRenderer();
	~GameRenderer();
};