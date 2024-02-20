package cache

import (
	"fmt"
	"testing"
)

func TestCacher(t *testing.T) {
	// Create a new cache with a size of 3
	c := NewCacher[int, string](3)

	// Put some key-value pairs into the cache
	c.Put(1, "one")
	c.Put(2, "two")
	c.Put(3, "three")

	// Get values from the cache
	val, err := c.Get(1)
	if err != nil {
		t.Errorf("Error getting value from cache: %v", err)
	}
	fmt.Println(val) // Output: one

	val, err = c.Get(2)
	if err != nil {
		t.Errorf("Error getting value from cache: %v", err)
	}
	fmt.Println(val) // Output: two

	val, err = c.Get(3)
	if err != nil {
		t.Errorf("Error getting value from cache: %v", err)
	}
	fmt.Println(val) // Output: three

	// Put a new key-value pair into the cache, which should evict the least recently used key-value pair
	c.Put(4, "four")

	// Try to get the evicted key-value pair, which should return an error
	_, err = c.Get(1)
	if err == nil {
		t.Errorf("Expected error getting evicted value from cache")
	}
}
