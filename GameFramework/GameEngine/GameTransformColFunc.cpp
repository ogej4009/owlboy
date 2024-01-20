#include "GameTransform.h"
#include "GameActor.h"
#include "GameScene.h"
#include <GameDebug.h>


bool GameTransform::SPHERE2DCOLOBB2D(CPtr<GameTransform> _Left, CPtr<GameTransform> _Right)
{
	return _Left->SPHERE2D().Intersects(_Right->OBB2D());
}

bool GameTransform::SPHERE2DCOLAABB2D(CPtr<GameTransform> _Left, CPtr<GameTransform> _Right)
{
	return _Left->SPHERE2D().Intersects(_Right->AABB2D());
}

bool GameTransform::SPHERE2DCOLSPHERE2D(CPtr<GameTransform> _Left, CPtr<GameTransform> _Right)
{
	return _Left->SPHERE2D().Intersects(_Right->SPHERE2D());
}

bool GameTransform::AABB2DCOLOBB2D(CPtr<GameTransform> _Left, CPtr<GameTransform> _Right)
{
	return _Left->AABB2D().Intersects(_Right->OBB2D());
}

bool GameTransform::AABB2DCOLAABB2D(CPtr<GameTransform> _Left, CPtr<GameTransform> _Right)
{
	return _Left->AABB2D().Intersects(_Right->AABB2D());
}

bool GameTransform::AABB2DCOLSPHERE2D(CPtr<GameTransform> _Left, CPtr<GameTransform> _Right)
{
	return _Left->AABB2D().Intersects(_Right->SPHERE2D());
}

bool GameTransform::OBB2DCOLOBB2D(CPtr<GameTransform> _Left, CPtr<GameTransform> _Right)
{
	return _Left->OBB2D().Intersects(_Right->OBB2D());
}

bool GameTransform::OBB2DCOLAABB2D(CPtr<GameTransform> _Left, CPtr<GameTransform> _Right)
{
	return _Left->OBB2D().Intersects(_Right->AABB2D());
}

bool GameTransform::OBB2DCOLSPHERE2D(CPtr<GameTransform> _Left, CPtr<GameTransform> _Right)
{
	return _Left->OBB2D().Intersects(_Right->SPHERE2D());
}