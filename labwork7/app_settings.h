#pragma once

struct AppSettings {
    int gridSize = 512;
    double stepX = 0.01;
    double stepFreq = 1.0 / (512 * 0.01);
    double diameter = 2.0;
    bool circular = true;

    void recalcFreq() { stepFreq = 1.0 / (gridSize * stepX); }
    void recalcX() { stepX = 1.0 / (gridSize * stepFreq); }
    void reset() { *this = AppSettings{}; }
};
