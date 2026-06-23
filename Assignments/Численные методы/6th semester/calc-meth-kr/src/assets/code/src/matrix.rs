use std::{
    array::from_fn,
    fmt::{Debug, Display},
    ops::{Add, AddAssign, Index, IndexMut, Mul, MulAssign, Sub, SubAssign},
};

use crate::num_traits::{One, Zero};

#[derive(Debug, Clone, Copy)]
pub struct Matrix<T, const N: usize, const M: usize> {
    pub values: [[T; M]; N],
}

impl<T: Display, const N: usize, const M: usize> Display for Matrix<T, N, M> {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        for i in 0..N {
            for j in 0..M {
                self.values[i][j].fmt(f)?;

                if j + 1 < M {
                    write!(f, "\t")?;
                }
            }
            if i + 1 < N {
                writeln!(f)?;
            }
        }
        Ok(())
    }
}

pub type Vector<T, const N: usize> = Matrix<T, N, 1>;

impl<T, const N: usize> Vector<T, N>
where
    T: Copy,
{
    pub fn from_row(row: [T; N]) -> Self {
        let values = from_fn(|i| [row[i]]);
        Self { values }
    }
}

impl<T, const N: usize> Index<usize> for Vector<T, N> {
    type Output = T;

    #[inline(always)]
    fn index(&self, index: usize) -> &Self::Output {
        &self.values[index][0]
    }
}

impl<T, const N: usize> IndexMut<usize> for Vector<T, N> {
    #[inline(always)]
    fn index_mut(&mut self, index: usize) -> &mut Self::Output {
        &mut self.values[index][0]
    }
}

pub type VectorRow<T, const N: usize> = Matrix<T, 1, N>;

impl<T: Copy + Default, const N: usize, const M: usize> Default for Matrix<T, N, M> {
    #[inline]
    fn default() -> Self {
        Self::from_rows([[T::default(); M]; N])
    }
}

impl<T, const N: usize, const M: usize> Index<(usize, usize)> for Matrix<T, N, M> {
    type Output = T;

    #[inline(always)]
    fn index(&self, (i, j): (usize, usize)) -> &Self::Output {
        &self.values[i][j]
    }
}

impl<T, const N: usize, const M: usize> IndexMut<(usize, usize)> for Matrix<T, N, M> {
    #[inline(always)]
    fn index_mut(&mut self, (i, j): (usize, usize)) -> &mut Self::Output {
        &mut self.values[i][j]
    }
}

impl<T: Copy + AddAssign, const N: usize, const M: usize> Add for Matrix<T, N, M> {
    type Output = Self;

    fn add(mut self, rhs: Self) -> Self::Output {
        for i in 0..N {
            for j in 0..M {
                self[(i, j)] += rhs[(i, j)];
            }
        }

        self
    }
}

impl<T: Copy + SubAssign, const N: usize, const M: usize> Sub for Matrix<T, N, M> {
    type Output = Self;

    fn sub(mut self, rhs: Self) -> Self::Output {
        for i in 0..N {
            for j in 0..M {
                self[(i, j)] -= rhs[(i, j)];
            }
        }

        self
    }
}

impl<T, const N: usize, const M: usize> Mul<T> for Matrix<T, N, M>
where
    T: Copy + MulAssign,
{
    type Output = Self;

    fn mul(mut self, rhs: T) -> Self::Output {
        for i in 0..N {
            for j in 0..M {
                self[(i, j)] *= rhs;
            }
        }

        self
    }
}

macro_rules! impl_matrix_mul {
    ($T:ty) => {
        impl<const N: usize, const M: usize> Mul<Matrix<$T, N, M>> for $T {
            type Output = Matrix<$T, N, M>;

            #[inline]
            fn mul(self, rhs: Matrix<$T, N, M>) -> Self::Output {
                rhs * self
            }
        }
    };
}

macro_rules! impl_matrix_mul_for {
    ( $($T:ty),+ ) => {
        $( impl_matrix_mul!($T); )+
    };
}

impl_matrix_mul_for!(
    usize, u8, u16, u32, u64, u128, isize, i8, i16, i32, i64, i128, f32, f64
);

impl<T, const N: usize, const M: usize, const K: usize> Mul<Matrix<T, M, K>> for Matrix<T, N, M>
where
    T: Copy + Zero + Mul<Output = T> + AddAssign,
{
    type Output = Matrix<T, N, K>;

    fn mul(self, rhs: Matrix<T, M, K>) -> Self::Output {
        let mut res = Matrix::ZERO;

        for i in 0..N {
            for j in 0..M {
                for k in 0..K {
                    res[(i, k)] += self[(i, j)] * rhs[(j, k)];
                }
            }
        }

        res
    }
}

impl<T, const N: usize, const M: usize> Zero for Matrix<T, N, M>
where
    T: Copy + Zero,
{
    const ZERO: Self = Self::from_rows([[T::ZERO; M]; N]);

    #[inline]
    fn is_zero(&self) -> bool {
        self.iter().all(|row| row.iter().all(|x| x.is_zero()))
    }
}

impl<T, const N: usize, const M: usize> Matrix<T, N, M> {
    #[inline]
    pub const fn ncols(&self) -> usize {
        M
    }

    #[inline]
    pub const fn nrows(&self) -> usize {
        N
    }

    #[inline]
    pub const fn from_rows(values: [[T; M]; N]) -> Self {
        Self { values }
    }

    pub fn identity() -> Self
    where
        T: Copy + Zero + One,
    {
        let mut res = Self::ZERO;

        for i in 0..N {
            res[(i, i)] = T::ONE;
        }

        res
    }

    #[inline]
    pub fn swap_rows(&mut self, i: usize, j: usize) {
        self.values.swap(i, j);
    }

    pub fn column(&self, i: usize) -> Vector<T, N>
    where
        T: Copy + Zero,
    {
        let mut res = Vector::ZERO;

        for j in 0..N {
            res[j] = self[(j, i)];
        }

        res
    }

    #[inline]
    pub const fn row(&self, i: usize) -> VectorRow<T, M>
    where
        T: Copy + Zero,
    {
        VectorRow::from_rows([self.values[i]])
    }

    pub fn norm_squared(&self) -> T
    where
        T: Copy + Zero + Mul<Output = T> + Add<Output = T>,
    {
        self.iter().flatten().fold(T::ZERO, |acc, &x| acc + x * x)
    }

    pub fn transpose(&self) -> Matrix<T, M, N>
    where
        T: Copy + Zero,
    {
        let mut res = Matrix::ZERO;

        for i in 0..M {
            for j in 0..N {
                res[(i, j)] = self[(j, i)];
            }
        }

        res
    }

    #[inline]
    pub fn iter(&'_ self) -> std::slice::Iter<'_, [T; M]> {
        self.values.iter()
    }

    #[inline]
    pub fn get(&self, i: usize, j: usize) -> Option<&T> {
        self.values.get(i).and_then(|row| row.get(j))
    }

    #[inline]
    pub fn elements(&self) -> impl Iterator<Item = &T> {
        self.iter().flatten()
    }
}

impl<T: Copy + Zero, const N: usize> Matrix<T, N, { N + 1 }> {
    pub fn leading_matrix(&self) -> Matrix<T, N, N> {
        let mut res = Matrix::ZERO;

        for i in 0..N {
            for j in 0..N {
                res[(i, j)] = self[(i, j)];
            }
        }

        res
    }
}
