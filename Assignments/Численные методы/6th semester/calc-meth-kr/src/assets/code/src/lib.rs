#![feature(generic_const_exprs)]
#![allow(incomplete_features)]
#![allow(clippy::needless_range_loop)]

pub mod gaussian_elimination;
pub mod lagrange_poly;
pub mod matrix;
pub mod num_traits;
pub mod simpson_integral;

pub use gaussian_elimination::*;
pub use lagrange_poly::*;
pub use simpson_integral::*;
