use glam::{Mat4, Quat, Vec3, Vec4};

use crate::types::{Normal, Pos};

pub fn model_transform(scale: Vec3, position: Vec3, rotation: Quat) -> Mat4 {
    Mat4::from_scale_rotation_translation(scale, rotation, position)
}

pub fn view_transform(eye_pos: Vec3, target: Vec3, up: Vec3) -> Mat4 {
    let f = (target - eye_pos).normalize();
    let r = f.cross(up).normalize();
    let u = r.cross(f);

    Mat4::from_cols(
        Vec4::new(r.x, u.x, -f.x, 0.0),
        Vec4::new(r.y, u.y, -f.y, 0.0),
        Vec4::new(r.z, u.z, -f.z, 0.0),
        Vec4::new(-r.dot(eye_pos), -u.dot(eye_pos), f.dot(eye_pos), 1.0),
    )
}

pub fn projection_transform(
    fov_y_radians: f32,
    aspect_ratio: f32,
    z_near: f32,
    z_far: f32,
) -> Mat4 {
    let t = (fov_y_radians / 2.0).tan();

    Mat4::from_cols(
        Vec4::new(1.0 / (aspect_ratio * t), 0.0, 0.0, 0.0),
        Vec4::new(0.0, 1.0 / t, 0.0, 0.0),
        Vec4::new(0.0, 0.0, (z_far + z_near) / (z_near - z_far), -1.0),
        Vec4::new(0.0, 0.0, (2.0 * z_far * z_near) / (z_near - z_far), 0.0),
    )
}

pub fn fragment_list(vertices: &[Pos]) -> Vec<[Pos; 3]> {
    vertices.chunks(3).map(|t| [t[0], t[1], t[2]]).collect()
}

pub fn fragment_normal(a: Pos, b: Pos, c: Pos) -> Normal {
    let a = Vec3::from_slice(&a.position[..3]);
    let b = Vec3::from_slice(&b.position[..3]);
    let c = Vec3::from_slice(&c.position[..3]);

    let u = b - a;
    let v = c - a;

    let n = u.cross(v).normalize();

    Normal::new(n.x, n.y, n.z)
}

pub fn triangle_normals(positions: &[Pos], indices: &[u16]) -> Vec<Normal> {
    indices
        .chunks(3)
        .map(|t| {
            fragment_normal(
                positions[t[0] as usize],
                positions[t[1] as usize],
                positions[t[2] as usize],
            )
        })
        .collect()
}
