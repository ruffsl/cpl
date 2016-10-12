// stack.h
// This library implements a stack in C.  The stack is a stack of integers.

#include <stdlib.h>
#include <string.h>

#define MAP_SIZE 1024

struct HashNode {
  char *key;
  char type;
  char *pointerToString;
  float Float;
  int Int;
};

struct Hashmap {
  struct HashNode HashNodeArray[MAP_SIZE];
};

int add_key_value_pair_int( struct Hashmap *pointerToHashmap, char *key, int value );
int get_key_type( struct Hashmap *pointerToHashmap, char *key );
int get_int_at_key( struct Hashmap *pointerToHashmap, char *key, int *value );
int hash( const char *key, unsigned int *hashvalue );

int add_key_value_pair_int( struct Hashmap *pointerToHashmap, char *key, int value ) {
  // This function stores a key value pair
  // Returns 0 for success
  // Returns 1 if the map is full
  unsigned int hashValue;
  hash( key, &hashValue );
  hashValue = hashValue % MAP_SIZE;
  if ( pointerToHashmap->HashNodeArray[hashValue].type == 0 ) {
    pointerToHashmap->HashNodeArray[hashValue].type = 1;
    pointerToHashmap->HashNodeArray[hashValue].Int = value;
    pointerToHashmap->HashNodeArray[hashValue].key = key;
    return 0;
  } else {
    for ( int i = hashValue + 1; i < MAP_SIZE; i++ ) {
      if ( pointerToHashmap->HashNodeArray[i].type == 0 ) {
        pointerToHashmap->HashNodeArray[i].type = 1;
        pointerToHashmap->HashNodeArray[i].Int = value;
        pointerToHashmap->HashNodeArray[i].key = key;
        return 0;
      }
    }
    for ( int i = 0; i < hashValue; i++ ) {
      if ( pointerToHashmap->HashNodeArray[i].type == 0 ) {
        pointerToHashmap->HashNodeArray[i].type = 1;
        pointerToHashmap->HashNodeArray[i].Int = value;
        pointerToHashmap->HashNodeArray[i].key = key;
        return 0;
      }
    }
    return 1;
  }
}

int get_key_type( struct Hashmap *pointerToHashmap, char *key ) {
  unsigned int hashValue;
  hash( key, &hashValue );
  hashValue = hashValue % MAP_SIZE;
  if ( strcmp(pointerToHashmap->HashNodeArray[hashValue].key,key) ) {
    return pointerToHashmap->HashNodeArray[hashValue].type;
  } else {
    for ( int i = hashValue + 1; i < MAP_SIZE; i++ ) {
      if ( strcmp(pointerToHashmap->HashNodeArray[i].key,key) ) {
        return pointerToHashmap->HashNodeArray[i].type;
      }
    }
    for ( int i = 0; i < hashValue; i++ ) {
      if ( strcmp(pointerToHashmap->HashNodeArray[i].key,key) ) {
        return pointerToHashmap->HashNodeArray[i].type;
      }
    }
    return -1;
  }
}

int get_int_at_key( struct Hashmap *pointerToHashmap, char *key, int *value ) {
  unsigned int hashValue;
  hash( key, &hashValue );
  hashValue = hashValue % MAP_SIZE;
  printf("Hashed\n");
  if ( pointerToHashmap->HashNodeArray[hashValue].key == NULL ) {
    printf("Null key\n");
    printf("%s\n",pointerToHashmap->HashNodeArray[hashValue].key);
  }
  printf("Key not Null\n");
  printf("%s\n",pointerToHashmap->HashNodeArray[hashValue].key);
  printf("HERE again\n");
  if ( strcmp(pointerToHashmap->HashNodeArray[hashValue].key,key) ) {
    printf("hash found right away\n");
    *value = pointerToHashmap->HashNodeArray[hashValue].Int;
    return 0;
  } else {
    printf("not found in right place\n");
    for ( int i = hashValue + 1; i < MAP_SIZE; i++ ) {
      if ( strcmp(pointerToHashmap->HashNodeArray[i].key,key) ) {
        *value = pointerToHashmap->HashNodeArray[i].Int;
        return 0;
      }
    }
    for ( int i = 0; i < hashValue; i++ ) {
      if ( strcmp(pointerToHashmap->HashNodeArray[i].key,key) ) {
        *value = pointerToHashmap->HashNodeArray[i].Int;
        return 0;
      }
    }
    printf("Not found\n");
    return 1;
  }
}

int hash( const char *key, unsigned int *hashValue) {
  // This function hashes some key.
  // The hash is written to the integer: hashValue
  // Returns 0 for success
  *hashValue = 0x55555555;
  while ( strcmp(key,"\0") != 0 ) {
    *hashValue = ( ( *hashValue << 5 ) | ( ( *hashValue & 0xF8000000 ) >> 27 ) ^ *key++ );
  }
  return 0;
}
