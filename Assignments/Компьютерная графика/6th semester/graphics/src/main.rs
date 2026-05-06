mod app;
mod scenes;
mod types;
mod utils;

use glium::{
    backend::glutin::SimpleWindowBuilder,
    winit::event_loop::{ControlFlow, EventLoop},
};

use crate::app::App;

fn main() {
    let event_loop = EventLoop::new().unwrap();
    let (window, display) = SimpleWindowBuilder::new().build(&event_loop);

    event_loop.set_control_flow(ControlFlow::Poll);

    let mut app = App::new(window, display);

    event_loop.run_app(&mut app).unwrap();
}
