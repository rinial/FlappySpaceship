#include "CPContactEvaluator.h"

#include "CPBody.h"
#include "CPCircle.h"
#include "CPRectangle.h"

#include "cocos2d.h" // We use Vec2 for physics
#include <array>

USING_NS_CC;

// Contact tests
bool CPContactEvaluator::intersects(CPBody * a, CPBody * b)
{
	assert(a && b);

	// If bit masks are not compatible
	if ((a->hitMask & b->selfMask) == 0 || (a->selfMask & b->hitMask) == 0)
		return false;

	const auto aC = dynamic_cast<CPCircle*>(a);
	if (aC) // a is circle
	{
		const auto bC = dynamic_cast<CPCircle*>(b);
		if (bC) // b is circle
			return intersects(aC, bC); // CIRCLE, CIRCLE

		const auto bR = dynamic_cast<CPRectangle*>(b);
		if (bR) // b is rectangle
			return intersects(aC, bR); // CIRCLE, RECTANGLE

		// b is unknown
		return false;
	}

	const auto aR = dynamic_cast<CPRectangle*>(a);
	if (aR)	// a is rectangle
	{
		const auto bC = dynamic_cast<CPCircle*>(b);
		if (bC) // b is circle
			return intersects(aR, bC); // RECTANGLE, CIRCLE

		const auto bR = dynamic_cast<CPRectangle*>(b);
		if (bR) // b is rectangle
			return intersects(aR, bR); // RECTANGLE, RECTANGLE

		// b is unknown
		return false;
	}

	// a is unknown
	return false;
}

// CIRCLE, CIRCLE
bool CPContactEvaluator::intersects(CPCircle* a, CPCircle* b)
{
	// distance(A, B) <= sum(radius A, radius B)
	return a->getPosition().getDistance(b->getPosition()) <= a->getRadius() + b->getRadius();
}

// RECTANGLE, RECTANGLE
bool CPContactEvaluator::intersects(CPRectangle* a, CPRectangle* b)
{
	// First check for the AABB case (Axis Aligned Bounding Box)
	if (a->getRotation() == 0 && b->getRotation() == 0)
	{
		// We could also check for every other angle that gives % 90 == 0, but usually if objects are supposed to be axis aligned, they are not rotated at all (rotation = 0)

		if (std::abs(a->getPosition().x - b->getPosition().x) > (a->getSize().width + b->getSize().width) / 2)
			return false; // Too far on X axis
		if (std::abs(a->getPosition().y - b->getPosition().y) > (a->getSize().height + b->getSize().height) / 2)
			return false; // Too far on Y axis
		return true; // Intersecting on both axis
	}

	// One or both of the rectangles are rotated, we need a different method
	// Now get perpendicular vectors of rectangles
	const auto aVecX = Vec2(a->getSize().width / 2, 0).rotateByAngle(Vec2::ZERO, -CC_DEGREES_TO_RADIANS(a->getRotation()));
	const auto aVecY = Vec2(0, a->getSize().height / 2).rotateByAngle(Vec2::ZERO, -CC_DEGREES_TO_RADIANS(a->getRotation()));
	const auto bVecX = Vec2(b->getSize().width / 2, 0).rotateByAngle(Vec2::ZERO, -CC_DEGREES_TO_RADIANS(b->getRotation()));
	const auto bVecY = Vec2(0, b->getSize().height / 2).rotateByAngle(Vec2::ZERO, -CC_DEGREES_TO_RADIANS(b->getRotation()));

	// Then for each edge of the first rectangle we test all vertices of the second rectangle to see if they are on the 'other side' of the edge
	// This implementation is based on SAT (Separation Axis Theorem)
	std::array<Vec2, 4> aNormals{ aVecX, -aVecX, aVecY, -aVecY };
	for (const auto& aNormal : aNormals)
	{
		// One point of the second vector
		const auto secondVBase = a->getPosition() + aNormal;

		// These are dot products of normal and vectors from one point on a's edge to b's vertices
		if (aNormal.dot(b->getPosition() + bVecX + bVecY - secondVBase) <= 0) continue;
		if (aNormal.dot(b->getPosition() + bVecX - bVecY - secondVBase) <= 0) continue;
		if (aNormal.dot(b->getPosition() - bVecX + bVecY - secondVBase) <= 0) continue;
		if (aNormal.dot(b->getPosition() - bVecX - bVecY - secondVBase) <= 0) continue;
		// All vertices are on the other side (dot product > 0)
		// Definitely not intersecting
		return false;
	}
	// We do the same thing the other way around (now we check bNormals)
	std::array<Vec2, 4> bNormals{ bVecX, -bVecX, bVecY, -bVecY };
	for (const auto& bNormal : bNormals)
	{
		// One point of the second vector
		const auto secondVBase = b->getPosition() + bNormal;

		// These are dot products of normal and vectors from one point on b's edge to a's vertices
		if (bNormal.dot(a->getPosition() + bVecX + bVecY - secondVBase) <= 0) continue;
		if (bNormal.dot(a->getPosition() + bVecX - bVecY - secondVBase) <= 0) continue;
		if (bNormal.dot(a->getPosition() - bVecX + bVecY - secondVBase) <= 0) continue;
		if (bNormal.dot(a->getPosition() - bVecX - bVecY - secondVBase) <= 0) continue;
		// All vertices are on the other side (dot product > 0)
		// Definitely not intersecting
		return false;
	}

	// For every edge of a there was at least one 'intersection' on the normal of this edge
	// Same for every edge of b
	// By SAT this means that a and b intersect
	return true;
}

// CIRCLE, RECTANGLE
bool CPContactEvaluator::intersects(CPCircle* circle, CPRectangle* rectangle)
{
	// First check for the AABB case (Axis Aligned Bounding Box), imagining a box around circle
	if (rectangle->getRotation() == 0)
	{
		// We could also check for every other angle that gives % 90 == 0, but usually if objects are supposed to be axis aligned, they are not rotated at all (rotation = 0)

		if (std::abs(circle->getPosition().x - rectangle->getPosition().x) > circle->getRadius() + rectangle->getSize().width / 2)
			return false; // Too far on X axis
		if (std::abs(circle->getPosition().y - rectangle->getPosition().y) > circle->getRadius() + rectangle->getSize().height / 2)
			return false; // Too far on Y axis

		// return true; // They are intersecting on both axis, but they may not actually be in contact
	}

	// Then get perpendicular vectors of rectangle
	const auto vecX = Vec2(rectangle->getSize().width / 2, 0).rotateByAngle(Vec2::ZERO, -CC_DEGREES_TO_RADIANS(rectangle->getRotation()));
	const auto vecY = Vec2(0, rectangle->getSize().height / 2).rotateByAngle(Vec2::ZERO, -CC_DEGREES_TO_RADIANS(rectangle->getRotation()));

	// Now check every vertice of the rectangle on whether it is inside of the circle
	// We also save special vectors for the vertice that is closest to circle's center to use later
	float closestD = -1;
	std::array<Vec2, 3> specialVectors;
	for (auto i1 : { -1, 1 }) for (auto i2 : { -1, 1 })
	{
		const auto vToCenter = circle->getPosition() - (rectangle->getPosition() + i1 * vecX + i2 * vecY);
		const auto distance = vToCenter.length();
		if (distance <= circle->getRadius())
			return true; // Found vertice inside of a circle
		if (closestD == -1 || closestD > distance)
		{
			closestD = distance;
			specialVectors[0] = vToCenter;
			specialVectors[1] = i1 * vecX; // one normal
			specialVectors[2] = i2 * vecY; // other normal
		}
	}

	// Then for each edge of the rectangle we test if the circle is on the 'other side' of the edge
	std::array<Vec2, 4> normals{ vecX, -vecX, vecY, -vecY };
	for (const auto& normal : normals)
	{
		// If both are > 0, it means that we found a proof of NOT collision
		if (normal.dot(circle->getPosition() + normal.getNormalized() * circle->getRadius() - (rectangle->getPosition() + normal)) <= 0) continue;
		if (normal.dot(circle->getPosition() - normal.getNormalized() * circle->getRadius() - (rectangle->getPosition() + normal)) <= 0) continue;
		// Definitely not intersecting
		return false;
	}

	// For every edge of a there was at least one 'intersection' on the normal of this edge
	// Also all vertices of the rectangle are outside of circle
	// However, there is one more case to test, the one where we can finally use specialVectors
	if (specialVectors[0].dot(specialVectors[1]) > 0 && specialVectors[0].dot(specialVectors[2]) > 0)
		return false; // case close to the angle without intersection
	return true; // intersection on the side of the rectangle
}

// RECTANGLE, CIRCLE
bool CPContactEvaluator::intersects(CPRectangle* rectangle, CPCircle* circle)
{
	return intersects(circle, rectangle); // it's symmetric
}
