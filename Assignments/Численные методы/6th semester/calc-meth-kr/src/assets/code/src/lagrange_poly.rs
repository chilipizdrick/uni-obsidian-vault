pub fn lagrange_poly(nodes: &[(f64, f64)], x: f64) -> f64 {
    let mut result = 0.0;
    let n = nodes.len();

    for i in 0..n {
        let mut l = 1.0;
        for j in 0..n {
            if j != i {
                l *= (x - nodes[j].0) / (nodes[i].0 - nodes[j].0);
            }
        }
        result += nodes[i].1 * l;
    }

    result
}

// Тесты
#[cfg(test)]
mod tests {
    use std::array::from_fn;

    use super::*;

    // Вспомогательная функция для проверки точности найденного значения по сравнению с известным
    fn assert_approx_eq(a: f64, b: f64, eps: f64) {
        let error = (a - b).abs() / (a.abs().max(b.abs()));
        println!("Error: {error}");
        assert!(error < eps);
    }

    // Тест на полиноме степени 2
    #[test]
    fn test_quadratic_interpolation() {
        let poly = |x: f64| -2.1415926 * x * x + 3.71828 * x + 0.61803;
        let xs = [-1.49, 0.43, 2.52];
        let ys = xs.map(poly);
        let nodes: [_; 3] = from_fn(|i| (xs[i], ys[i]));
        let interp_poly = |x| lagrange_poly(&nodes, x);

        for x in [0.0, -1.1, 10.7, -20.2, 122.5] {
            assert_approx_eq(interp_poly(x), poly(x), 1e-12);
        }
    }

    // Тест на полиноме степени 3
    #[test]
    fn test_cubic_interpolation() {
        let poly = |x: f64| 1.23 * x.powi(3) - 2.234 * x * x + 7.64 * x - 1.567;
        let xs = [-2.78, 1.45, 3.23, 10.3];
        let ys = xs.map(poly);
        let nodes: [_; 4] = from_fn(|i| (xs[i], ys[i]));
        let interp_poly = |x| lagrange_poly(&nodes, x);

        for x in [0.0, 0.023, -9.5, 41.4, -231.2] {
            assert_approx_eq(interp_poly(x), poly(x), 1e-12);
        }
    }

    // Тест на полиноме степени 5
    #[test]
    fn test_fifth_poly_interpolation() {
        let poly = |x: f64| {
            10.4 * x.powi(5) - 6.8 * x.powi(4) - 2.12 * x.powi(3) - 7.589 * x * x + 15.34 * x
                - 23.567
        };
        let xs = [-5.23, -3.43, -1.78, 0.34, 2.23, 4.509];
        let ys = xs.map(poly);
        let nodes: [_; 6] = from_fn(|i| (xs[i], ys[i]));
        let interp_poly = |x| lagrange_poly(&nodes, x);

        for x in [0.0, -0.58, 2.34, -14.4, 321.7] {
            assert_approx_eq(interp_poly(x), poly(x), 1e-12);
        }
    }
}
