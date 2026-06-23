#![feature(generic_const_exprs)]
#![allow(incomplete_features)]
#![allow(clippy::needless_range_loop)]

use std::array::from_fn;

use task_solver::{matrix::Matrix, *};

fn main() {
    let system = Matrix::from_rows([
        [1.0, 1.0, 1.0, 1.0, 2.0, 2.0],
        [2.0, 3.0, 4.0, 2.0, 6.0, 4.0],
        [0.0, 0.0, 1.0, 1.0, 2.0, 6.0],
        [2.0, 2.0, 4.0, 5.0, 8.0, 8.0],
        [1.0, 2.0, 5.0, 4.0, 9.0, 10.0],
    ]);

    let area = solve(system);

    println!("Итоговое полученное значение интеграла: {area}");
}

// Вычисляет площадь интерполяционного полинома, узлы которого рассчитываются из данной системы линейных уравнений.
fn solve(system: Matrix<f64, 5, 6>) -> f64 {
    println!("Система:\n{system}\n");

    let system_solution = gaussian_elimination(system);
    println!("Полученное решение системы:\n{system_solution:.20}\n");

    let interpolation_nodes: [(f64, f64); 5] =
        from_fn(|i| (system[(i, 5)], system_solution[(i, 0)]));
    println!("Полученные интерполяционные узлы:\n{interpolation_nodes:?}\n");

    let poly = |x| lagrange_poly(&interpolation_nodes, x);
    for x in [2.0, 4.0, 6.0, 8.0, 10.0] {
        println!("Полином в точке {x}: {:.20}", poly(x));
    }

    integral_simpson(2.0, 10.0, poly, 1e-5)
}
