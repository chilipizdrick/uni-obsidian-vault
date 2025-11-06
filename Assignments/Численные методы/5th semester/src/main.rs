use std::{fmt::Debug, io, str::FromStr};

mod task_1;
mod task_2;
mod task_3;
mod task_4;
mod task_5;
mod task_6;

fn main() {
    let args = std::env::args().collect::<Vec<String>>();
    let task = args.get(1).unwrap().parse().unwrap();

    match task {
        1 => task_1::task_1(),
        2 => task_2::task_2(),
        3 => task_3::task_3(),
        4 => task_4::task_4(),
        5 => task_5::task_5(),
        6 => task_6::task_6(),
        _ => println!("Неверный номер задачи"),
    }
}

pub fn read_line() -> String {
    let mut line = String::new();
    io::stdin().read_line(&mut line).unwrap();
    line.trim().to_string()
}

pub fn read_value<T: FromStr>() -> T
where
    <T as FromStr>::Err: Debug,
{
    read_line().parse().unwrap()
}
