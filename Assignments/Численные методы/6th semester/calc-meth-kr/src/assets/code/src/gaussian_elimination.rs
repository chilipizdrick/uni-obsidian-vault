use crate::{
    matrix::{Matrix, Vector},
    num_traits::Zero,
};

pub fn gaussian_elimination<const N: usize>(mut mat: Matrix<f64, N, { N + 1 }>) -> Vector<f64, N> {
    // Прямой ход
    for i in 0..N - 1 {
        let mut max_abs = 0.0;
        let mut k = 0;
        for j in i..N {
            let abs = mat[(j, i)].abs();
            if abs > max_abs {
                max_abs = abs;
                k = j;
            }
        }
        mat.swap_rows(i, k);
        for j in i + 1..N {
            let coef = -(mat[(j, i)] / mat[(i, i)]);
            for k in i..N + 1 {
                mat[(j, k)] += mat[(i, k)] * coef;
            }
        }
    }

    // Обратный ход
    let mut res = Vector::ZERO;
    for i in (0..N).rev() {
        let sum_of_prev = (i + 1..N).fold(0.0, |acc, j| acc + mat[(i, j)] * res[j]);
        res[i] = (mat[(i, N)] - sum_of_prev) / mat[(i, i)];
    }

    res
}

// Тесты
#[cfg(test)]
mod tests {

    use super::*;

    // Вспомогательная функция для проверки решения подстановкой
    fn assert_solution_correct<const N: usize>(mat: [[f64; N + 1]; N], eps: f64) {
        let mat = Matrix::from_rows(mat);
        let b_expected = mat.column(N);
        let solution = gaussian_elimination(mat);
        let b_substituted = mat.leading_matrix() * solution;
        let error = b_expected - b_substituted;
        println!("Error: {error}");

        assert!(error.elements().all(|&x| x.abs() < eps));
    }

    // Вспомогательная функция для проверки точности найденного решения по сравнению с известным
    fn assert_approx_eq<const N: usize>(mat: [[f64; N + 1]; N], sol: [f64; N], eps: f64) {
        let mat = Matrix::from_rows(mat);
        let solution = gaussian_elimination(mat);
        let error = solution - Vector::from_row(sol);
        println!("Error: {error}");

        assert!(error.elements().all(|&x| x.abs() < eps));
    }

    // Тест на матрице СЛАУ, схожей с матирицей подзадачи №1
    #[test]
    fn test_similar_to_task() {
        assert_solution_correct(
            [
                [1., 0., 2., 1., 1., 2.],
                [2., 2., 5., 3., 4., 4.],
                [1., 1., 4., 2., 5., 8.],
                [0., 2., 3., 5., 6., 10.],
                [3., 4., 6., 5., 9., 12.],
            ],
            1e-12,
        );
    }

    // Тест на положительных и отрицательных дробних числах мо модулю приближенных к данным в подзадаче №1
    #[test]
    fn test_mixed() {
        assert_solution_correct(
            [
                [-4.56, 12.30, -0.89, 7.45, -15.20, 5.4],
                [8.90, -3.45, 18.22, -9.01, 2.34, -11.2],
                [-11.11, 5.67, -4.32, 14.50, -0.55, 8.88],
                [6.78, -19.30, 2.15, -8.76, 11.45, -3.21],
                [-2.34, 9.87, -16.50, 3.21, -7.89, 14.56],
            ],
            1e-12,
        );
    }

    // Тест на относительно малых положительных дробных числах
    #[test]
    fn test_small() {
        assert_solution_correct(
            [
                [0.875, 0.122, 0.954, 0.332, 0.541, 1.205],
                [0.443, 0.765, 0.012, 0.889, 0.234, 2.341],
                [0.198, 0.556, 0.877, 0.401, 0.912, 1.876],
                [0.654, 0.231, 0.543, 0.776, 0.110, 0.998],
                [0.321, 0.908, 0.445, 0.156, 0.678, 2.112],
            ],
            1e-12,
        );
    }

    // Проверка работы алгоритма для матрицы с первым нулевым элементом
    #[test]
    fn test_zero_pivot_matrix() {
        assert_approx_eq(
            [
                [0., 1., 2., 1., 3., 7.],
                [2., 2., 1., 3., 1., 9.],
                [1., 3., 2., 1., 2., 9.],
                [3., 1., 3., 2., 4., 13.],
                [2., 4., 1., 4., 5., 16.],
            ],
            [1.0, 1.0, 1.0, 1.0, 1.0],
            1e-12,
        );
    }

    // Проверка работы алгоритма для плохо обусловленной матрицы
    #[test]
    fn test_ill_conditioned_matrix() {
        assert_approx_eq(
            [
                [1., 1. / 2., 1. / 3., 1. / 4., 1. / 5., 137. / 60.],
                [1. / 2., 1. / 3., 1. / 4., 1. / 5., 1. / 6., 29. / 20.],
                [1. / 3., 1. / 4., 1. / 5., 1. / 6., 1. / 7., 153. / 140.],
                [1. / 4., 1. / 5., 1. / 6., 1. / 7., 1. / 8., 743. / 840.],
                [1. / 5., 1. / 6., 1. / 7., 1. / 8., 1. / 9., 1879. / 2520.],
            ],
            [1.0, 1.0, 1.0, 1.0, 1.0],
            1e-12,
        );
    }
}
