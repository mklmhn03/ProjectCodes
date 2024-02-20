package textproc

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"sort"
	"strings"
)

// Find the top K most common words in a text document.
// Input path: location of the document, K top words
// Output: Slice of top K words
// For this exercise, a word is defined as characters separated by a whitespace
// Note: You should use `checkError` to handle potential errors.

func topWords(path string, K int) []WordCount {
	// Open the file
	file, err := os.Open(path)
	checkError(err)
	defer file.Close()

	// Create a map to store word counts
	wordCounts := make(map[string]int)

	// Read the file line by line
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		// Split each line into words
		words := strings.Fields(scanner.Text())

		// Update word counts in the map
		for _, word := range words {
			wordCounts[word]++
		}
	}

	// Check for scanner errors
	err = scanner.Err()
	checkError(err)

	// Create a slice of WordCount from the map
	var result []WordCount
	for word, count := range wordCounts {
		result = append(result, WordCount{Word: word, Count: count})
	}

	// Sort the WordCount slice
	sortWordCounts(result)

	// Return the top K words
	if K > len(result) {
		return result
	}
	return result[:K]
}

// A struct that represents how many times a word is observed in a document
type WordCount struct {
	Word  string
	Count int
}

// Method to convert struct to string format
func (wc WordCount) String() string {
	return fmt.Sprintf("%v: %v", wc.Word, wc.Count)
}

// Helper function to sort a list of word counts in place.
// This sorts by the count in decreasing order, breaking ties using the word.
func sortWordCounts(wordCounts []WordCount) {
	sort.Slice(wordCounts, func(i, j int) bool {
		wc1 := wordCounts[i]
		wc2 := wordCounts[j]
		if wc1.Count == wc2.Count {
			return wc1.Word < wc2.Word
		}
		return wc1.Count > wc2.Count
	})
}

func checkError(err error) {
	if err != nil {
		log.Fatal(err)
	}
}
