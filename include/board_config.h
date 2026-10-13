#pragma once
// Waveshare ESP32-S3-Touch-AMOLED-1.75-G.
// Keep display/touch initialization aligned with the official board example.
namespace wayline::board {
constexpr int kDisplayWidth = 466;
constexpr int kDisplayHeight = 466;
constexpr int kI2cSda = 15;
constexpr int kI2cScl = 14;
constexpr int kGpsWriteAddress = 0x50;
constexpr int kGpsReadAddress = 0x54;
constexpr int kTouchAddress = 0x5A;
constexpr int kImuAddress = 0x6B;
constexpr int kRtcAddress = 0x51;
constexpr int kAxp2101Address = 0x34;
}
