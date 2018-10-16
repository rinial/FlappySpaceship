#ifndef __CP_RECTANGLE_H__
#define __CP_RECTANGLE_H__

#include "CPBody.h"

// Forward declarations
class CPWorld;

// Rect body
class CPRectangle : public CPBody
{
public:
	CPRectangle(CPWorld* world, const cocos2d::Size size, const cocos2d::Vec2 pos = cocos2d::Vec2::ZERO, const float rot = 0) : CPBody(world, pos, rot) {
		assert(size.width > 0 && size.height > 0); 
		size_ = size;
	}

	// Updates size and informs world about it
	void setSize(cocos2d::Size& size);
	// Returns size
	cocos2d::Size getSize() const { return size_; }

private:
	cocos2d::Size size_;
};

#endif // __CP_RECTANGLE_H__
