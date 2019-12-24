#pragma once
#include <string>

namespace core
{
double to_rad(int deg);
double kts_to_ftm(int kts);
double nms_to_fts(int nm);
void log(std::string& text);
} // namespace core::utils