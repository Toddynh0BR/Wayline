#pragma once
namespace wayline::hardware {
void begin();
void update();
bool displayReady();
bool touchReady();
bool gpsBusReady();
}
