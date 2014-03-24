
#include "CollisionBox.h"


CollisionBox::CollisionBox(void)
{
	IsGrounded = false;
	IsGround = false;
	IsPlatform = false;
	IsDangerous = false;
	IsDeadly = false;
	IsSwing = false;
	IsClimbable = false;
	IsLedge = false;
	IsGoal = false;
	IsPlayer = false;
	IsEnemy = false;
	IsAggressive = false;
	IsCarried = false;
	IsSafe = false;
	
}

CollisionBox::CollisionBox(float minimumX, float minimumY, float maximumX, float maximumY)
{

	minimumX = Min.m_fX;
	minimumY = Min.m_fY;
	Min.m_fZ = 0.0f;

	maximumX = Max.m_fX;
	maximumY = Max.m_fY;
	Max.m_fZ = 0.0f;

	IsGrounded = false;
	IsGround = false;
	IsPlatform = false;
	IsDangerous = false;
	IsDeadly = false;
	IsSwing = false;
	IsClimbable = false;
	IsLedge = false;
	IsGoal = false;
	IsPlayer = false;
	IsEnemy = false;
	IsAggressive = false;
	IsCarried = false;
	IsSafe = false;
	
}

CollisionBox::~CollisionBox(void)
{
}

bool CollisionBox::CheckCollision(CollisionBox aOtherObject)
{
	if(Min.m_fX > aOtherObject.Max.m_fX || aOtherObject.Min.m_fX > Max.m_fX)
		return false; // There has been no collision
	if (Min.m_fY > aOtherObject.Max.m_fY || aOtherObject.Min.m_fY > Max.m_fY)
		return false; // There has been no collision
	CheckGrounded(aOtherObject);
	return true; // Collision happens if neither of the above have happened.
}

bool CollisionBox::CheckGrounded(CollisionBox aOtherObject)
{
	if (aOtherObject.IsGround == true)
	{
		IsGrounded = true;
		printf ("%s\n","Is Grounded");
	return true;
	}
	else
		printf ("%s\n","Is Not Grounded");
		return false;
}

void CollisionBox::SetFlag(FlagType eFlagType, bool a_OnOff)
{
	switch(eFlagType)
	{
	case GROUND:
		IsGround = a_OnOff;
		break;
	case GROUNDED:
		IsGrounded = a_OnOff;
		break;
	case PLATFORM:
		IsPlatform = a_OnOff;
		break;
	case DANGEROUS:
		IsDangerous = a_OnOff;
		break;
	case DEADLY:
		IsDeadly = a_OnOff;
		break;
	case SWING:
		IsSwing = a_OnOff;
		break;
	case CLIMB:
		IsClimbable = a_OnOff;
		break;
	case LEDGE:
		IsLedge = a_OnOff;
		break;
	case SAFE:
		IsSafe = a_OnOff;
		break;
	case GOAL:
		IsPlatform = a_OnOff;
		break;
	case PLAYER:
		IsPlayer = a_OnOff;
		break;
	case AGGRESSIVE:
		IsAggressive = a_OnOff;
		break;
	case ENEMY:
		IsEnemy = a_OnOff;
		break;
	case CARRY:
		IsCarried = a_OnOff;
		break;

	default:
		break;
	}
}