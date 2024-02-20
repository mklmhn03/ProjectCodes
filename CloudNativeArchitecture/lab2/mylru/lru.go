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
	return &lruCache[K, V]{size: size, remaining: size, cache: make(map[K]V),
		queue: make([]K, 0)}
}
func (c *lruCache[K, V]) Get(key K) (value V, err error) {
	if val, ok := c.cache[key]; ok {
		// Move key to the tail of the queue (mark as recently used)
		c.deleteFromQueue(key)
		c.queue = append(c.queue, key)
		return val, nil
	}
	return value, fmt.Errorf("key not found")
}

func (c *lruCache[K, V]) Put(key K, value V) (err error) {
	if _, exists := c.cache[key]; exists {
		// Key already exists, update the value and move to the tail of the queue
		c.cache[key] = value
		c.deleteFromQueue(key)
		c.queue = append(c.queue, key)
		return nil
	}

	if c.remaining == 0 {
		// Cache is full, evict the least recently used item
		oldestKey := c.queue[0]
		delete(c.cache, oldestKey)
		c.deleteFromQueue(oldestKey)
		c.remaining++
	}

	// Add new key-value pair
	c.cache[key] = value
	c.queue = append(c.queue, key)
	c.remaining--
	return nil
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
