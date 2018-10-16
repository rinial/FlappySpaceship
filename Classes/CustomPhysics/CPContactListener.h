#ifndef __CP_CONTANT_LISTENER_H__
#define __CP_CONTANT_LISTENER_H__

// Forward declarations
class CPBody;

// Represents special object that holds information about collision
class CPContact
{
public:
	// For hashing
	struct CPContactHasher
	{
		std::size_t operator()(const CPContact& contact) const
		{
			return std::hash<CPBody*>()(contact.a_)	^ std::hash<CPBody*>()(contact.b_);
		}
	};
	bool operator== (const CPContact& other) const
	{
		return (a_ == other.a_ && b_ == other.b_) || (a_ == other.b_ && b_ == other.a_);
	}

	CPContact(CPBody* a, CPBody* b) {
		assert(a && b);
		a_ = a;
		b_ = b;
	}

	// Gives access to collided objects
	CPBody* getBodyA() const { return a_; }
	CPBody* getBodyB() const { return b_; }

private:
	CPBody* a_ = nullptr;
	CPBody* b_ = nullptr;
};

// Abstract class that allows implementing onBeginContact function to handle collisions
class CPContactListener
{
public:
	// Called from CPWorld whenever some collision occurs
	virtual void onBeginContact(CPContact& contact) = 0;
};

#endif // __CP_CONTANT_LISTENER_H__
