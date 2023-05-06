/*!
  @file unittest_map.h
  @brief contains the declarations for a simple implementation of a map structure used in a
  unittesting library. It provides functions to hash a string or an array of bytes, map a set
  of bytes and make them unique, free mapped data and the bucket, and find mapped bytes.

  @author Erick Carrillo.
  @copyright Copyright (C) 2022, Erick Alejandro Carrillo López, All rights reserved.
  @license This project is released under the MIT License
*/

#ifndef UNITTEST_MAP_INCLUDE
#define UNITTEST_MAP_INCLUDE

#include <stddef.h>
#include <stdint.h>

/* unittest_hash: To hash some string or a simple array of bytes and return some random
 * integer */
extern unsigned long unittest_hash(const uint8_t *str);

/* unittest_map: Maps and makes a set of bytes unique and returns a new copy of the */
extern const uint8_t *unittest_map(const uint8_t *str, size_t len);

/* unittest_map_free: Frees mapped data and the bucket. */
extern void unittest_map_free(const uint8_t *data, size_t len);

/* unittest_map_find: Trys to find some mapped bytes if they weren't mapped return NULL
   otheriwese
   return its address */
extern const uint8_t *unittest_map_find(const uint8_t *data, size_t len);

#endif
