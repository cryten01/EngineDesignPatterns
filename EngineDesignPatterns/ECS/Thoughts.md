# Entity Component System

## Problem
1. Deep inheritance structures tend to get rigid and unflexible.
2. Traditional component systems produce a lot of memory inefficiency (mainly cache misses) which ultimately results in frame rate drops. Function and data is grouped. This means that every entity has its own set of functions which is often not needed.
3. Cache misses and branch mispredictions (= if/else, switch cases etc.)

## Goals
* Easy multithreading
* Scalable
* Memory efficient
* Understandable

## Solution

Problem Nr. 1 can be solved by using a component based approach.

Problem Nr. 2 can be solved by packing data that gets regularly iterated upon tightly into memory. So that an entire cache line’s worth of data can be loaded at once, and when the next item is iterated upon, its data is already in the cache. 

The whole point of an ECS system is to keep the data packed in memory, meaning that you should be able to iterate over all of the indices in the array without needing any sort of “if(valid)” checks.

### Elements

**Components** are merely represented as structs of data that don't contain any functional behavior. Since arrays are contiguous in memory they are usually the first choice for storing components.

```cpp
struct Transform
{
	Vec3 position;
	Vec3 rotation;
	Vec3 scale;
};
```

**EntitiyIDs** are lookup indices required for accessing different component storages (usually arrays). Those IDs don't contain any data or functions. Those Entities are stored across different arrays and only virtually linked together. 

The traditional OOP approach on the other hand defines Entities as containers of components. 

```cpp
// A simple type alias
using EntityID = std::uint32_t;
```


**Systems** are sets of functions that operate on component sets. Those systems can be seen as work unit which query the right components.

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

## Used concepts

**Functional programming**
*  Immutability goes well with the multithreading aspect and reduces unwanted side effects such as race conditions.

**Actor model**
*  For save multithreading.

**Data oriented design**


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