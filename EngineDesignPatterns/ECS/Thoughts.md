# Entity Component System

## Problem
* Traditional component systems produce a lot of memory inefficiency which results in frame rate drops. 
* Function and data is grouped. This means that every entity has its own set of functions which is often not needed.

## Goals
* Easy multithreading
* Scalable
* Memory efficient

## Solution
### Elements
**Components** are represented as structs with raw data that don't contain any functional behavior.

```cpp
struct Transform
{
	Vec3 position;
	Vec3 rotation;
	Vec3 scale;
};
```

**Entities** are unique identifiers that are required for accessing different Component Arrays. This means that the entity itself does not contain any data or functional behavior.

```cpp
// A simple type alias
using EntityID = std::uint32_t;
```

**Systems** are collections of functional behavior that operate on component sets. Those systems can be seen as work unit.

```cpp
// A system for managing entities
class EntityManagerSystem : public System
{
public:
	EntityID IssueEntity(EntityManagerData& data);
	void ReturnEntity(EntityManagerData& data, EntityID entity);
	void SetSignature(EntityManagerData& data, EntityID entity);
	Signature GetSignature(EntityManagerData& data, EntityID entity);
};
```

### Used concepts

**Functional programming**
*  Immutability goes well with the multithreading aspect and reduces unwanted side effects such as race conditions.

**Actor model**
*  For save multithreading.

## Benefits
* Easy component interaction
* Easy saving and loading of data
* Easy multithreading

## Challenges
* Handling entity lifetime
* Event communication

## Tipps & Tricks

* Use Classes when:
   * Multiple instances are required
   * Lifetime needs to be controlled
   * Inheritance is needed

 * Use Namespaces when:
   * A single instance is sufficient
   * Global access is required
   * For pure system interfaces

 * Separate Data from Systems when:
   * Multiple entities are needed and therefore memory optimization is required

* Always use composition (Has-a relationship) over inheritance except:
   * Inheritance is absolutely necessary for a Is-a relationship