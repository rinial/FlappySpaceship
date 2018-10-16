#include "CPWorld.h"

#include "CPBody.h"
#include "CPContactListener.h"
#include "CPContactEvaluator.h"

// Finds collisions, sends events (and can move physics simulation if we were actually simulating something)
void CPWorld::step(const float dT)
{
	std::unordered_set<CPBody*> testedBodies;
	CONTACTS_SET newContacts;

	// Check only those that have moved
	for (auto bodyA : forEvaluation_)
	{
		testedBodies.insert(bodyA);

		// We test it with every other body in the world, except for those that are already tested in their evaluation cycle
		// TODO add space partioning to lessen the number of checks
		for (auto bodyB : bodies)
		{
			if (testedBodies.find(bodyB) != testedBodies.end()) // if testedBodies.contains(bodyB)
				continue;

			if (!CPContactEvaluator::intersects(bodyA, bodyB))
				continue;

			// Contact occured, but it may be old. For now, just save it
			newContacts.insert(CPContact(bodyA, bodyB));
		}
	}
	forEvaluation_.clear();

	// We now have all the contacts and need to find, which ones are new
	// First we remove old contacts
	std::vector<CPContact> forRemovalFromCurrent;
	for (const auto contact : currentContacts)
	{
		if (newContacts.find(contact) != newContacts.end()) // if newContacts.contains(contact)
			newContacts.erase(contact); // it's an old contact, remove from new
		else
			forRemovalFromCurrent.push_back(contact); // it's not a contact anymore, mark from removal from current
	}
	// Remove old contacts that are no longer contacts
	for (const auto contact : forRemovalFromCurrent)
		currentContacts.erase(contact);
	// Add new contacts to current and notify listeners
	for (auto contact : newContacts)
	{
		currentContacts.insert(contact);
		for (auto listener : listeners_)
			listener->onBeginContact(contact);
	}
}

// Destructor clears all memory for all bodies
CPWorld::~CPWorld()
{
	// We dont need to clear listeners_ and forEvaluation_, only bodies_
	for (auto body : bodies)
		delete body; // This way whenever body is created with new, we know it will be cleared afterwards when world is destroyed
}
