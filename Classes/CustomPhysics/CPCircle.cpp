#include "CPCircle.h"
#include "CPWorld.h"

// Updates radius and informs world about it
void CPCircle::setRadius(const float radius)
{
	assert(radius > 0);
	radius_ = radius;
	world_->onManipulatedBody(this);
}
