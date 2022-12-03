use std::fs::File;
use std::io::{BufRead, BufReader};

fn main() {
    star1();
    star2();
}

fn star1() {
    let mut sum = 0;
    let itemtypes: String = String::from("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
    let filename = "input.txt";
    let file = File::open(filename).unwrap();
    let reader = BufReader::new(file);
    
    for (_index, rucksack) in reader.lines().enumerate() {
        let rucksack = rucksack.unwrap();
        let rucksack_size = rucksack.len();
        let compart1: String = rucksack.chars().skip(rucksack_size/2).take(rucksack_size/2).collect();
        let compart2: String = rucksack.chars().skip(0).take(rucksack_size/2).collect();

        let mut item_idx = 1;
        for item in itemtypes.chars()
        {
            if compart1.contains(item) && compart2.contains(item) 
            {
                sum = sum + item_idx;
            }
            item_idx = item_idx + 1;
        }
    }

    println!("final sum: {}", sum);

}

fn star2() {
    let mut sum = 0;
    let itemtypes: String = String::from("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
    let filename = "input.txt";
    let file = File::open(filename).unwrap();
    let reader = BufReader::new(file);
    let lines: Vec<_> = reader.lines().collect();


    for rucksacks in lines.chunks(3){
        if rucksacks.len() != 3 { break; }
        let rucksack1 = rucksacks[0].as_ref().unwrap();
        let rucksack2 = rucksacks[1].as_ref().unwrap();
        let rucksack3 = rucksacks[2].as_ref().unwrap();
        
        let mut item_idx = 1;
        for item in itemtypes.chars()
        {
            if rucksack1.contains(item) && rucksack2.contains(item) && rucksack3.contains(item)
            {
                sum = sum + item_idx;
            }
            item_idx = item_idx + 1;
        }

    }

    println!("final sum: {}", sum);
}
