#ifndef __CP_WORLD_H__
#define __CP_WORLD_H__

#include "cocos2d.h"
#include "CPContactListener.h"
#include <unordered_set>

#define CONTACTS_SET std::unordered_set<CPContact, CPContact::CPContactHasher>

// Forward declarations
class CPBody;

// Physics world that stores all the bodies and evaluates their contacts in step function
// When world is destroyed, all memory for all of its bodies is cleared
class CPWorld
{
public:
	// All bodies handled by this world. Public so that user can iterate through them easily
	std::vector<CPBody*> bodies;
	// All contacts detected in this world. Public so that user can iterate through them easily
	CONTACTS_SET currentContacts;

	// Finds collisions, sends events (and can move physics simulation if we were actually simulating something)
	void step(float dT);

	// Add a new listener that will react to collisions
	void addContactListener(CPContactListener* listener) {
		assert(listener);
		listeners_.push_back(listener);
	}
	// Removes a contact listener
	void removeContactListener(CPContactListener* listener)	{
		assert(listener);
		listeners_.erase(std::find(listeners_.begin(), listeners_.end(), listener));
	}

	// Called from newly created bodies
	// Adds these bodies and sets them for evaluation
	void onCreatedBody(CPBody* body) {
		assert(body);
		bodies.push_back(body);
		forEvaluation_.insert(body);
	}
	// Called from bodies when they are moved or changed in other ways
	// Sets these bodies for evaluation
	void onManipulatedBody(CPBody* body) {
		assert(body);
		forEvaluation_.insert(body);
	}

	// Destructor clears all memory for all bodies
	~CPWorld();

private:
	std::vector<CPContactListener*> listeners_;
	std::unordered_set<CPBody*> forEvaluation_; // we need set so that one body isn't added for evaluation several times
};

#endif // __CP_WORLD_H__
