import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class Day2 {

    public static void main(String[] args) throws IOException {

        BufferedReader reader = new BufferedReader(new FileReader("Day2/input.txt"));

        String line;
        // Read through the file, line by line and do all
        // necessary logic for the task
        int validPasswordsOne = 0;
        int validPasswordsTwo = 0;
        while((line = reader.readLine()) != null) {
            String password = line.split(":")[1];
            int charCounter = 0;
            boolean firstDone = false;
            boolean secondDone = false;
            boolean nextIsChar = false;
            int min = 0;
            int max = 0;
            String memory  = "";
            char charToCheck = ' ';

            // This will get the values for the minimums, maximums, and the character
            // we're looking for in the password. (I suck at regex)
            for(char c : line.toCharArray()) {
                if(c == '-') {
                    min = Integer.parseInt(memory);
                    memory = "";
                    firstDone = true;
                }else if(c == ' ' && !secondDone) {
                    max = Integer.parseInt(memory);
                    secondDone = true;
                    nextIsChar = true;
                } else if (!firstDone) {
                    memory += c;
                } else if(!secondDone) {
                    memory += c;
                } else if(nextIsChar) {
                    charToCheck = c;
                    nextIsChar = false;
                } else {
                    // From here on, we have all values we need to start counting/verifying
                    if(c == charToCheck) {
                        charCounter++;
                    }
                }
            }
            // When the line loop is over, we can check if the charCounter
            // is between the min- and max value
            if(charCounter >= min && charCounter <= max) {
                validPasswordsOne++;
            }
            boolean oneMatch = false;
            if(password.charAt(min) == charToCheck) {
                oneMatch = true;
            }
            if(password.charAt(max) == charToCheck) {
                oneMatch = !oneMatch;
            }
            if(oneMatch) {
                validPasswordsTwo++;
            }
        }
        System.out.println("Part 1 | Valid passwords: " + validPasswordsOne);
        System.out.println("Part 2 | Valid passwords: " + validPasswordsTwo);
    }
}
