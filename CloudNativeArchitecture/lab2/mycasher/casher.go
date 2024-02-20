package cache

import "fmt"

type Cacher[K comparable, V any] interface {
	Get(key K) (value V, err error)
	Put(key K, value V) (err error)
}

// Concrete LRU cache
type lruCache[K comparable, V any] struct {
	size      int
	remaining int
	cache     map[K]V
	queue     []K
}

// Constructor
func NewCacher[K comparable, V any](size int) Cacher[K, V] {
	return &lruCache[K, V]{size: size, remaining: size, cache: make(map[K]V), queue: make([]K, 0)}
}
func (c *lruCache[K, V]) Get(key K) (V, error) {
	// Check if the key exists in the cache
	if val, ok := c.cache[key]; ok {
		// Move the key to the tail of the queue (recently used)
		c.moveToTail(key)
		return val, nil
	}

	// Key not found in the cache, return the zero value of type V and an error
	var zeroValue V
	return zeroValue, fmt.Errorf("key not found")
}

func (c *lruCache[K, V]) Put(key K, value V) (err error) {
	// Check if the key already exists in the cache
	if _, ok := c.cache[key]; ok {
		// Key already exists, move it to the tail of the queue (recently used)
		c.moveToTail(key)
		c.cache[key] = value
		return nil
	}

	// Check if the cache is full
	if c.remaining == 0 {
		// Cache is full, evict the least recently used element from the head of the queue
		// and remove it from the cache
		oldestKey := c.queue[0]
		c.deleteFromQueue(oldestKey)
		delete(c.cache, oldestKey)
		c.remaining++
	}

	// Add the new key-value pair to the cache and append the key to the tail of the queue
	c.cache[key] = value
	c.queue = append(c.queue, key)
	c.remaining--

	return nil
}

// Helper method to move a key to the tail of the queue (recently used)
func (c *lruCache[K, V]) moveToTail(key K) {
	// Find the index of the key in the queue
	for i, k := range c.queue {
		if k == key {
			// Remove the key from its current position and append it to the end
			c.queue = append(c.queue[:i], c.queue[i+1:]...)
			c.queue = append(c.queue, key)
			return
		}
	}
}

// Helper method to delete all occurrences of a key from the queue
func (c *lruCache[K, V]) deleteFromQueue(key K) {
	newQueue := make([]K, 0, c.size)
	for _, k := range c.queue {
		if k != key {
			newQueue = append(newQueue, k)
		}
	}
	c.queue = newQueue
}
