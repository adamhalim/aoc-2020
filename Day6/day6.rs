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

    let mut answers_2 = HashSet::<char>::new();
    let mut unique_answers_2 = 0;
    let mut first_line = true;

    
    for (_index, line) in reader.lines().enumerate() {
        let line = line.unwrap();

        // If the line is blank, we know we are at a new group.
        // We add the amount of chars in our hashset and reset it.
        if line == "" {
            unique_answers += answers.len();
            unique_answers_2 += answers_2.len();
            answers.clear();
            answers_2.clear();
            first_line = true;
        } else {
            // We create a char vector from our string and insert
            // all chars in our hashset
            let vec: Vec<char> = line.chars().collect();
            for n in 0..=vec.len()-1 {
                answers.insert(vec[n]);
            }

            // If we are at the first line for a new group, we add all chars to the hashset.
            // If we're not at the first line, we do an intersection with the line and our 
            // hashset, keeping only chars that are present in both.
            if first_line {
                for n in 0..=vec.len()-1 {
                    answers_2.insert(vec[n]);
                    first_line = false;
                }
            } else {
                let mut temp_set = HashSet::<char>::new();
                for n in 0..=vec.len()-1 {
                    temp_set.insert(vec[n]);
                }
                let mut temp_set_2 = HashSet::<char>::new();
                for x in answers_2.intersection(&temp_set) {
                    temp_set_2.insert(*x);
                }
                answers_2 = temp_set_2;
            }
        }
    }

    // For the last group, we don't reach a blank \n line. So we still have
    // data left in our hashset we need to add to our sum of unique answers.
    unique_answers += answers.len();
    unique_answers_2 += answers_2.len();

    println!("Sum on unique counts: {}", unique_answers);
    println!("Sum on unique counts 2: {}", unique_answers_2);

    Ok(())
}