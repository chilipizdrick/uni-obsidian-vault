use glam::{Quat, Vec3};
use glium::{
    BackfaceCullingMode, Depth, DrawParameters, Frame, Program, Surface, VertexBuffer,
    index::{NoIndices, PrimitiveType},
    uniform,
};

use crate::{
    app::App,
    types::{Pos, TexCoord},
    utils::{model_transform, projection_transform, triangle_normals, view_transform},
};

const POSITIONS: [Pos; 7] = [
    Pos::new(1.0, 0.0, 0.0),
    Pos::new(0.5, 0.866, 0.0),
    Pos::new(-0.5, 0.866, 0.0),
    Pos::new(-1.0, 0.0, 0.0),
    Pos::new(-0.5, -0.866, 0.0),
    Pos::new(0.5, -0.866, 0.0),
    Pos::new(0.0, 0.0, 5.0),
];

const TEX_COORDS: [TexCoord; 7] = [
    TexCoord::new(0.0, 0.0),
    TexCoord::new(0.5, 0.0),
    TexCoord::new(0.0, 0.0),
    TexCoord::new(0.5, 0.0),
    TexCoord::new(0.0, 0.0),
    TexCoord::new(0.5, 0.0),
    TexCoord::new(0.0, 1.0),
];

const INDICES: [u16; 30] = [
    4, 2, 0, 2, 1, 0, 4, 3, 2, 0, 5, 4, 1, 6, 0, 2, 6, 1, 3, 6, 2, 4, 6, 3, 5, 6, 4, 0, 6, 5,
];

const CAMERA_POSITION: Vec3 = Vec3::new(0.0, 5.0, 5.0);
// const CAMERA_POSITION: Vec3 = Vec3::new(6.666, -6.666, 6.666);
const SPOTLIGHT_POSITION: Vec3 = Vec3::new(0.0, 15.0, 15.0);
const SPOTLIGHT_TARGET: Vec3 = Vec3::new(0.0, 0.0, 0.0);
const SPOTLIGHT_CUTOFF_COS: f32 = 0.9995;
const SPOTLIGHT_OUTER_CUTOFF_COS: f32 = 0.998;

pub fn draw_scene3(app: &App, frame: &mut Frame) {
    frame.clear_color_srgb_and_depth((0.3, 0.3, 0.3, 1.0), 1.0);

    let program = Program::from_source(
        &app.display,
        include_str!("./scene3_vert.glsl"),
        include_str!("./scene3_frag.glsl"),
        None,
    )
    .unwrap();

    let positions: Vec<_> = INDICES.iter().map(|i| POSITIONS[*i as usize]).collect();
    let positions_buf = VertexBuffer::new(&app.display, &positions).unwrap();

    let normals: Vec<_> = triangle_normals(&POSITIONS, &INDICES)
        .into_iter()
        .flat_map(|n| [n, n, n])
        .collect();
    let normals_buf = VertexBuffer::new(&app.display, &normals).unwrap();

    let tex_coords: Vec<_> = INDICES.iter().map(|i| TEX_COORDS[*i as usize]).collect();
    let tex_coords_buf = VertexBuffer::new(&app.display, &tex_coords).unwrap();

    let indices = NoIndices(PrimitiveType::TrianglesList);

    let draw_parameters = DrawParameters {
        depth: Depth {
            test: glium::DepthTest::IfLess,
            write: true,
            ..Default::default()
        },
        backface_culling: BackfaceCullingMode::CullClockwise,
        ..Default::default()
    };

    let model_transform = model_transform(Vec3::splat(1.0), Vec3::ZERO, Quat::IDENTITY);

    let view_transform = view_transform(CAMERA_POSITION, Vec3::ZERO, Vec3::Z);

    let light_direction = light_position_on_ellipse(app.time);

    let dimensions = app.window.inner_size();
    let aspect_ratio = dimensions.width as f32 / dimensions.height as f32;
    let projection_transform =
        projection_transform(std::f32::consts::PI / 3.0, aspect_ratio, 0.1, 100.0);

    let uniforms = uniform! {
        model: model_transform.to_cols_array_2d(),
        view: view_transform.to_cols_array_2d(),
        projection: projection_transform.to_cols_array_2d(),
        directional_light_direction: light_direction.to_array(),
        tex: &app.texture,
        camera_position: CAMERA_POSITION.to_array(),
        s_position: SPOTLIGHT_POSITION.to_array(),
        s_direction: (SPOTLIGHT_TARGET - SPOTLIGHT_POSITION).to_array(),
        s_cut_off: SPOTLIGHT_CUTOFF_COS,
        s_outer_cut_off: SPOTLIGHT_OUTER_CUTOFF_COS,
    };

    frame
        .draw(
            (&positions_buf, &normals_buf, &tex_coords_buf),
            indices,
            &program,
            &uniforms,
            &draw_parameters,
        )
        .unwrap();
}

fn light_position_on_ellipse(t: f32) -> Vec3 {
    let u = Vec3::new(12.0, 12.0, 0.0);
    let v = Vec3::new(0.0, 7.0, 7.0);
    let c = Vec3::new(6.666, -6.666, 6.666);
    c + t.cos() * u + t.sin() * v
}
