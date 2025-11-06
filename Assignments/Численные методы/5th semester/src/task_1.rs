use crate::read_value;

fn ln(mut x: f64, eps: f64) -> f64 {
    let mut ln_10_mult = 0;
    if x.abs() >= 2.0 {
        while x.abs() >= 2.0 {
            ln_10_mult += 1;
            x /= 10.0;
        }
    }

    x -= 1.0;
    let mut x_pow = 1.0;
    let mut res = 0.0;
    for i in 1.. {
        x_pow *= x;
        let delta = x_pow / (i as f64);

        if i % 2 == 0 {
            res -= delta;
        } else {
            res += delta;
        }

        if delta.abs() * 10.0 < eps {
            break;
        }
    }

    res + (ln_10_mult as f64) * std::f64::consts::LN_10
}

pub fn task_1() {
    println!("Введите x:");
    let x: f64 = read_value();
    println!("Введите точность вычисления:");
    let eps: f64 = read_value();
    println!("x: {}, точность: {}, ln(x): {}", x, eps, ln(x, eps));
}
