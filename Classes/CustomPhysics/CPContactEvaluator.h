#ifndef __CP_CONTACT_EVALUATOR_H__
#define __CP_CONTACT_EVALUATOR_H__

// Forward declarations
class CPBody;
class CPCircle;
class CPRectangle;

// Class containing static functions for contact evaluation
class CPContactEvaluator
{
public:
	// Contact tests
	static bool intersects(CPBody* a, CPBody* b);
private:
	static bool intersects(CPCircle* a, CPCircle* b);
	static bool intersects(CPRectangle* a, CPRectangle* b);
	static bool intersects(CPCircle* circle, CPRectangle* rectangle);
	static bool intersects(CPRectangle* rectangle, CPCircle* circle);

	CPContactEvaluator() = default; // We don't want instances of this class
};

#endif // __CP_CONTACT_EVALUATOR_H__
