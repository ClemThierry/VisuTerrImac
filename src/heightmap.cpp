#include "../include/heightmap.h"

HeightMap::HeightMap(glm::vec2 world_size, const unsigned char *data, int data_w, int data_h, int data_max, float hMin, float hMax) {
  world_to_map = glm::vec2((float)data_w, (float)data_h) / world_size;
  wi = data_w;
  hi = data_h;
  height_norm = (hMax-hMin) / data_max;
  hOffset = hMin;
  this->data = data;
}

float HeightMap::get_pixel(int x, int y) {
  return height_norm * data[x+y*wi] + hOffset;
}

float HeightMap::get_height(glm::vec2 pos) {
  pos = pos * world_to_map + glm::vec2(wi*0.5f, hi*0.5f);
  int x = pos.x;
  int y = pos.y;
  float fx = pos.x-x;
  float fy = pos.y-y;

  float p00 = get_pixel(x, y);
  float p10 = get_pixel(x+1, y);
  float h0 = p00 + fx * (p10 - p00);

  float p01 = get_pixel(x, y+1);
  float p11 = get_pixel(x+1, y+1);
  float h1 = p01 + fx * (p11 - p01);
  
  return h0 + fy * (h1 - h0);
}