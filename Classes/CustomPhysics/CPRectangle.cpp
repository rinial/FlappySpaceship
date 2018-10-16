#include "CPRectangle.h"
#include "CPWorld.h"

USING_NS_CC;

// Updates size and informs world about it
void CPRectangle::setSize(Size& size)
{
	assert(size.width > 0 && size.height > 0);
	size_ = size;
	world_->onManipulatedBody(this);
}
