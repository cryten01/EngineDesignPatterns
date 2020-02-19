#pragma once


/**
 * Use Classes when:
 *
 * Multiple instances are required.
 * Lifetime needs to be controlled.
 * Inheritance is needed.
 */

/**
 * Use Namespaces when:
 * A single instance is necessary.
 * Global access is required.
 * For pure system interfaces.
 */

/**
 * Combine Data with Systems when:
 *
 * Multiple entities are not needed.
 */


// Systems should be data independent if multiple instances are required.
// Data should be stored in own optimized storages if necessary.

// Always use composition for a Has-a relationship






/**
 *	Entity Component System (Separation Function/Data, Composition over inheritance, Save Multi Threading)
 *	Functional Programming (Immutability, Reduce Side effects, Save Multi Threading)
 *	Actor Model (Event Based, Save Multi Threading)
 */

 // Data types
 // Groups of different data types (0-n)

 // Function types
 // Groups of function types (0-n)

 // Separate isolated units

 // Node = Container of functionality that processes data, composed of other nodes
 // Message = Container of data that can be send across links
 // Connections = represented by the amount of node references each node has

 // Static methods are loaded during runtime (no loading control)

    // Efficient Storages
    // Single Systems
    // Node Communication