pub fn integral_simpson(a: f64, b: f64, f: impl Fn(f64) -> f64, eps: f64) -> f64 {
    let mut h = (b - a) / 10.0;
    let mut s = integral_simpson_iteration(a, b, &f, h);
    println!("h: {h}, S: {s}");

    loop {
        h /= 2.0;
        let new_s = integral_simpson_iteration(a, b, &f, h);
        println!("h: {h}, S: {s}");
        if (new_s - s).abs() / 15.0 < eps {
            return new_s;
        }
        s = new_s;
    }
}

pub fn integral_simpson_iteration(a: f64, b: f64, f: impl Fn(f64) -> f64, h: f64) -> f64 {
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

// Тесты
#[cfg(test)]
mod tests {
    use std::f64::consts::PI;

    use super::*;

    // Вспомогательная функция для проверки точности найденного значения по сравнению с известным
    fn assert_approx_eq(a: f64, b: f64, eps: f64) {
        let error = (a - b).abs() / a.abs().max(b.abs());
        println!("Error: {error}");
        assert!(error < eps);
    }

    // Тест на функции sin^2(x)
    #[test]
    fn test_sin_squared() {
        // sin^2(x)
        let f = |x: f64| x.sin() * x.sin();
        let eps = 1e-12;
        let result = integral_simpson(0.0, PI, f, eps);
        assert_approx_eq(result, PI / 2.0, eps);
    }

    // Тест на функции x^2
    #[test]
    fn test_x_squared() {
        // x^2
        let f = |x: f64| x * x;
        let eps = 1e-12;
        let result = integral_simpson(-0.5, 1.5, f, eps);
        assert_approx_eq(result, 7.0 / 6.0, eps);
    }

    // Тест на функции f(x) = x^4 + 1.5 x^3 + 1/3 x^2 + 5/7 x + 13/5
    #[test]
    fn test_poly() {
        // x^4 + 1.5 x^3 + 1/3 x^2 + 5/7 x + 13/5
        let f = |x: f64| {
            x.powi(4) + 1.5 * x.powi(3) + (1.0 / 3.0) * x.powi(2) + (5.0 / 7.0) * x + 13.0 / 5.0
        };
        let eps = 1e-12;
        // 1/5 x^5 + 3/8 x^4 + 1/9 x^3 + 5/14 x^2 + 13/5 x
        let result = integral_simpson(-2.0, 3.0, f, eps);
        assert_approx_eq(result, 49_417.0 / 504.0, eps);
    }
}
