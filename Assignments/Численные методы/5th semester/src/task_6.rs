pub fn task_6() {
    let a = -2.0;
    let b = 2.0;
    let h = 1.0;
    let f = |x: f64| 1.0 / (x * x + 4.0);

    let s = integral_left_rectangle(a, b, f, h);
    println!("Формула левых прямоугольников:    {s}");
    let s = integral_right_rectangle(a, b, f, h);
    println!("Формула правых прямоугольников:   {s}");
    let s = integral_middle_rectangle(a, b, f, h);
    println!("Формула средних прямоугольников:  {s}",);
    let s = integral_trapezoid_rectangle(a, b, f, h);
    println!("Аппроксимация по методу трапеций: {s}",);
    let s = integral_simpson(a, b, f, h);
    println!("Метод Симпсона (метод парабол):   {s}",);
}

fn integral_right_rectangle(a: f64, b: f64, f: fn(f64) -> f64, h: f64) -> f64 {
    let mut res = 0.0;
    for i in 1..=iter_count(a, b, h) {
        res += f(a + (i as f64) * h) * h;
    }
    res
}

fn integral_left_rectangle(a: f64, b: f64, f: fn(f64) -> f64, h: f64) -> f64 {
    let mut res = 0.0;
    for i in 0..iter_count(a, b, h) {
        res += f(a + (i as f64) * h) * h;
    }
    res
}

fn integral_middle_rectangle(a: f64, b: f64, f: fn(f64) -> f64, h: f64) -> f64 {
    let mut res = 0.0;
    for i in 0..iter_count(a, b, h) {
        res += f(a + (i as f64 + 0.5) * h) * h;
    }
    res
}

fn integral_trapezoid_rectangle(a: f64, b: f64, f: fn(f64) -> f64, h: f64) -> f64 {
    (integral_right_rectangle(a, b, f, h) + integral_left_rectangle(a, b, f, h)) / 2.0
}

fn integral_simpson(a: f64, b: f64, f: fn(f64) -> f64, h: f64) -> f64 {
    let mut res = f(a) + f(b);
    for i in 1..iter_count(a, b, h) {
        let x = a + (i as f64) * h;
        res += if i % 2 == 0 { 2.0 * f(x) } else { 4.0 * f(x) };
    }
    res * h / 3.0
}

fn iter_count(a: f64, b: f64, h: f64) -> usize {
    ((b - a) / h).round() as usize
}
