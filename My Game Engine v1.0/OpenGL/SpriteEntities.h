#ifndef _GAMEENTITY_H_
#define _GAMEENTITY_H_

#include "Sprite.h"
#include <string>
#include <tinyxml2.h>




struct AniSprite
{
	union{
		struct{
			std::string sName;
			Vector2 v2Size;
			Vector4 v4Location;
		};
		struct
		{
			std::string Name;
			float width, height;
			float x0,x1,y0,y1;
		};
	};
};


struct Atlas
{
	Vector2 v2Size;
	std::string sSheet;
	std::string sAnimations;
};

typedef std::vector<std::string> frame;

class SpriteEntities :
	public Sprite
{
public:
	SpriteEntities(void);
	~SpriteEntities(void);
	SpriteEntities( const char* a_pSpriteSheet, GLFWwindow * window);
	virtual void Draw();
	void Update();
	void SetAnimation(std::string animation,PlayType type);
	void SetAnimation(std::string animation,PlayType type, int frame);
	void PlayAnimation();
	void SetSprite();
	void LoadSprites(const char* a_pSpriteSheet);
	void LoadAnimations(const char* a_pAnimationSheet);
	void Input();
	std::map<std::string,AniSprite> mSprites;
	std::map<std::string,frame> mAnimations;
	Atlas atlas;

	std::string currentAnimation, currentSprite;
	int currentFrame, loopFrame;
	double m_dFrames;
	PlayType currentPlayType;


double elapsedTime;

};


#endif //_GAMEENTITY_H_
