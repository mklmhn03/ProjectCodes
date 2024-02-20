package main

import (
	"ex.com/myadder"

	"bufio"
	"fmt"
	"os"
	"sort"
	"strings"
)

func main() {
	fmt.Println("Addition of 5 and 6: ", myadder.Add(5, 6))

	filename := "input.txt"
	k := 10 // Replace with the desired value of K

	wordCount := make(map[string]int)

	file, err := os.Open(filename)
	if err != nil {
		fmt.Println("Error opening file:", err)
		return
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	scanner.Split(bufio.ScanWords)

	for scanner.Scan() {
		word := strings.ToLower(scanner.Text())
		wordCount[word]++
	}

	if err := scanner.Err(); err != nil {
		fmt.Println("Error reading file:", err)
		return
	}

	type wordCountPair struct {
		word  string
		count int
	}

	pairs := make([]wordCountPair, 0, len(wordCount))
	for word, count := range wordCount {
		pairs = append(pairs, wordCountPair{word, count})
	}

	sort.Slice(pairs, func(i, j int) bool {
		return pairs[i].count > pairs[j].count
	})

	fmt.Printf("Top %d occurrences of words:\n", k)
	for i := 0; i < k && i < len(pairs); i++ {
		fmt.Printf("%s: %d\n", pairs[i].word, pairs[i].count)
	}
}
