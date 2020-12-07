use std::fs::File;
use std::io::{self, BufRead, BufReader};
use std::collections::HashSet;

fn main() -> io::Result<()> {

    // Open the file and use a bufferedReader
    // to read file line by line
    let file = File::open("input.txt").unwrap();
    let reader = BufReader::new(file);

    // We use a hashset to store all of our characters per group in
    let mut answers = HashSet::<char>::new();
    let mut unique_answers = 0;
    
    for (_index, line) in reader.lines().enumerate() {
        let line = line.unwrap();

        // If the line is blank, we know we are at a new group.
        // We add the amount of chars in our hashset and reset it.
        if line == "" {
            unique_answers += answers.len();
            answers.clear();
        } else {
            // We create a char vector from our string and insert
            // all chars in our hashset
            let vec: Vec<char> = line.chars().collect();
            for n in 0..=vec.len()-1 {
                answers.insert(vec[n]);
            }
        }
    }

    // For the last group, we don't reach a blank \n line. So we still have
    // data left in our hashset we need to add to our sum of unique answers.
    unique_answers += answers.len();

    println!("Sum on unique counts: {}", unique_answers);


    Ok(())
}