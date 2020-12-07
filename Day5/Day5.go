package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
)

func main() {

	file, err := os.Open("input.txt")
	if err != nil {
		log.Fatal(err)
	}
	defer file.Close()
	scanner := bufio.NewScanner(file)

	var line string
	var rowID int16
	var highestID int16 = 0

	for scanner.Scan() {
		line, rowID = getRow(scanner.Text())
		var seatID int16 = getID(line, rowID)
		if seatID > highestID {
			highestID = seatID
		}
	}

	fmt.Printf("Highest seat ID: %d\n", highestID)

	// Opens the file again. Not sure how to avoid this
	// and still be able to read the file line by line again
	file, err = os.Open("input.txt")
	if err != nil {
		log.Fatal(err)
	}
	defer file.Close()
	scanner = bufio.NewScanner(file)

	// We create a bool array that says if a certain seat ID
	// is taken up or not
	var seatTaken = make([]bool, highestID+1)
	for scanner.Scan() {
		line, rowID = getRow(scanner.Text())
		seatTaken[getID(line, rowID)] = true
	}

	// Check if seat before and after are taken
	for i := 1; i < int(highestID); i++ {
		if seatTaken[i-1] && seatTaken[i+1] && !seatTaken[i] {
			fmt.Printf("My seatID is %d.\n", i)
		}
	}
}

func getID(line string, rowID int16) int16 {

	var minCol int16 = 0
	var maxCol int16 = 7

	for i := 7; i < 10; i++ {
		if line[i] == 'L' {
			maxCol = (minCol + maxCol) / 2
		} else {
			minCol = (minCol + maxCol + 1) / 2
		}
	}

	if line[9] == 'L' {
		return rowID*8 + minCol
	}
	return rowID*8 + maxCol
}

func getRow(line string) (string, int16) {
	var minRow int16 = 0
	var maxRow int16 = 127

	for i := 0; i < 7; i++ {
		if line[i] == 'F' {
			maxRow = (minRow + maxRow) / 2
		} else {
			minRow = (minRow + maxRow + 1) / 2
		}
	}
	return line, minRow
}
