package textproc

import (
	"testing"
)

func TestTopwords(t *testing.T) {
	topK := topWords("/home/itcs4151/Cloud Computing/lab1/input.txt", 3)
	want := "butter: 4 better: 2 betty: 2 "
	got := ""
	for _, word := range topK {
		got += word.String() + " "
	}
	if got != want {
		t.Errorf("TopWords test failed, Want-{%s} Got-{%s}", want, got)
	}
}
