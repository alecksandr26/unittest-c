/*!
  @file atom.h
  @brief An atom is a pointer to a unique, immutable sequence of zeros
  of more arbitrary bytes. Most atoms are pointers to a null
  terminated strings, but a pointer to any sequence of bytes can be an atom,
  there is only a single occurrence of any atom which its called an atom.
  
  @author Erick Carrillo.
  @copyright Copyright (C) 2022, Erick Alejandro Carrillo López, All rights reserved.
  @license This project is released under the MIT License
*/

#ifndef ATOM_INCLUDE
#define ATOM_INCLUDE

/* Atom_hash: To hash some string and return some random integer */
extern unsigned long Atom_hash(const char *str);

/* Atom_length: Returns the length of the atom argument. */
extern int Atom_length(const char *str);

/* Atom_new: Creates a new atom in the table of atoms and making a copy
   of the passed pointer, never returns a null pointer */
extern const char *Atom_new(const char *str, int len);

/* Atom_string: Its do the same thing as Atom_new the difference is that str can be null
 * terminated */
extern const char *Atom_string(const char *str);

/* Atom_int: Initialize a new atom from an integer. */
extern const char *Atom_int(long n);

/* Atom_free: To dealloc an atom. */
extern void Atom_free(const char *str);

#endif
