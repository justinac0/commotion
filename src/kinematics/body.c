#include "body.h"

#include "../common/defs.h"

void draw_shape(Shape shape) {
    switch (shape.type) {
    case S_CIRCLE:
        DrawCircle(shape.position.x, shape.position.y, shape.size.x, shape.color);
        break;
    case S_RECTANGLE:
        Rectangle rect = (Rectangle){
            .x = shape.position.x,
            .y = shape.position.y,
            .width = shape.size.x,
            .height = shape.size.y
        };
        DrawRectanglePro(rect, (Vector2){shape.size.x/2, shape.size.y/2}, shape.rotation, shape.color);
        break;
    }
}

Shape shape_create(Vec2 position, Vec2 size, real rotation, Color color, ShapeType type) {
    return (Shape){
        .position = position,
        .size = size,
        .rotation = rotation,
        .color = color,
        .type = type
    };
}

void body_draw(Body *b, Body *target) {
    if (b == NULL) return;

    if (target == b) {
        Shape outline = b->shape;
        outline.size.x += 5;
        outline.size.y += 5;
        outline.color = WHITE;
        draw_shape(outline);
        // DrawCircle(b->state.position.x, b->state.position.y, b->radius + b->radius*0.25, YELLOW);
    }

    draw_shape(b->shape);
    // DrawCircle(b->state.position.x, b->state.position.y, b->radius, b->color);
}

void body_add_force(Body *b, Vec2 f) {
    if (b == NULL) return;

    // add a force scaled from pixel to world space
    b->state.force = vec2_addv(b->state.force, vec2_mulr(f, METER_SCALE_PX));
}

void body_clear_forces(Body *b) {
    if (b == NULL) return;
    
    b->state.force = (Vec2){0.0f, 0.0f};
}

void body_integrate(Body *b, float dt) {
    if (b == NULL) return;

    b->state.acceleration = vec2_divr(b->state.force, b->state.mass);

    b->state.velocity = vec2_addv(b->state.velocity, vec2_mulr(b->state.acceleration, dt));
    b->state.position = vec2_addv(b->state.position, vec2_mulr(b->state.velocity, dt));
    b->shape.position = b->state.position;

    body_clear_forces(b);
}
