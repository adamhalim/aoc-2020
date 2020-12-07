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
		seatID := getID(line, rowID)
		if seatID > highestID {
			highestID = seatID
		}
	}
	fmt.Printf("%d\n", highestID)
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
