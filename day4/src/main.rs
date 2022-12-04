 use std::fs;

fn main() {
    let input = fs::read_to_string("input.txt");
    let lines = input.as_ref().unwrap().trim_end().lines();
    let mut sum = 0;
    for line in lines {
        /*
        if line == "" {
            break;
        }
        */
        let assignments = line.split(",").into_iter();
        let idxes: Vec<Vec<u32>> = assignments
            .map(
                |assignment| 
                assignment
                    .split("-")
                    .map(
                        |idx| 
                        idx
                            .parse::<u32>()
                            .unwrap())
                    .collect())
            .collect();
        /*
        if idxes[0][0] >= idxes [1][0] && idxes[0][1] <= idxes[1][1] {
           sum = sum + 1; 
        } 
        else if idxes[0][0] <= idxes [1][0] && idxes[0][1] >= idxes[1][1] {
           sum = sum + 1; 
        }
        */

        if idxes[0][0] <= idxes [1][1] && idxes[0][1] >= idxes[1][0] {
           sum = sum + 1; 
        } 
        
    }
    println!("sum: {}", sum);
}
