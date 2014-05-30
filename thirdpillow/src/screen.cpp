/*
 * screen.cpp
 *
 *  Created on: Apr 29, 2014
 *      Author: jwpilly
 */

#include "screen.h"

screen::screen(int render_width, int render_height) {
	this->render_width = render_width;
	this->render_height = render_height;
	this->buffer = new float[render_width * render_height * 3];
	this->z_buffer = new float[render_width* render_height];
}

void screen::cls() {
	memset(this->buffer, (float)0, (render_width*render_height*3) * sizeof(float));
	for (int i = 0; i < render_width * render_height; i++) {
		z_buffer[i] = (float)1;
	}
}

int screen::get_width() {
	return this->render_width;
}

int screen::get_height() {
	return this->render_height;
}

void screen::set_buffer(float* buffer) {
	this->buffer = buffer;
}

float* screen::get_buffer() {
	return this->buffer;
}

void screen::set_z_buffer(float* buffer) {
	this->z_buffer = buffer;
}

float* screen::get_z_buffer() {
	return this->z_buffer; 
}

float screen::get_at(int i) {
	return this->buffer[i];
}

void screen::set_at(int i, float f) {
	this->buffer[i] = f;
}

color* screen::get_pixel(int x, int y) {
	int index = putils::get_index_3d(x, y, 0, this->render_width, 3);
	color* c = new color(this->buffer[index], this->buffer[index + 1],
			this->buffer[index + 2], 1);
	return c;
}

void screen::set_pixel(int x, int y, color* c) {
	if (x >= 0 && x < this->render_width && y >= 0 && y < this->render_height) {
		int index = putils::get_index_3d(x, y, 0, this->render_width, 3);
		this->buffer[index] = c->get_r();
		this->buffer[index + 1] = c->get_g();
		this->buffer[index + 2] = c->get_b();
	}

}

float screen::get_z(int x, int y) {
	int index = putils::get_index_2d(x, y, this->render_width);
	return this->z_buffer[index];
}

void screen::set_z(int x, int y, float z) {
	int index = putils::get_index_2d(x, y, this->render_width);
	this->z_buffer[index] = z;
}

screen::~screen() {
	delete this->buffer;
	delete this->z_buffer;
}

