#pragma once
#ifndef _COLLISIONOBJECTS_H_
#define _COLLISIONOBJECTS_H_
#include "Utilities.h"

class CollisionBox
{
public:
	CollisionBox(void);
	CollisionBox(float minimumX, float minimumY, float maximumX, float maximumY);
	~CollisionBox(void);

	Vector3 Min;
	Vector3 Max;
	Flag IsGrounded; // is the sprite sitting on solid ground?
	Flag IsGround; // is the Sprite a surface that supports another sprite?
	Flag IsPlatform; // is the Sprite a platform?
	Flag IsDangerous; // Can collision with the sprite cause damage?
	Flag IsDeadly;// Will collision with this sprite kill?
	Flag IsSwing; // is this an object that can be used to swing on?
	Flag IsClimbable;// is this an object that can be climbed?
	Flag IsLedge;// is this hitbox a ledge that can be climbed up?
	Flag IsSafe; // is this hitbox a Safe Area?
	Flag IsGoal; // is this hotbox the end goal?
	Flag IsPlayer; // Is this sprite a player?
	Flag IsEnemy; // is this Sprite an enemy?
	Flag IsAggressive; // is this Sprite aggressive?
	Flag IsCarried; // is the sprite able to be carried?



	bool CheckCollision(CollisionBox aOtherObject);
	bool CheckGrounded(CollisionBox aOtherObject);
	void SetFlag(FlagType eFlagType, bool a_OnOff); //sets the flag on an object to use during collision checks
};

#endif //_COLLISIONOBJECTS_H_


